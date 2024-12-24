#include "BMS.h"
#include <stdio.h>
#include "StateMachine.h"

extern uint64_t v_max_id_rx, v_min_id_rx, v_max_rx, v_min_rx, v_mean_rx;

// NTC readings
extern volatile uint8_t ntc_temp;   // probably for overtemperature errors
extern volatile uint16_t ntc_value; // raw reading of the ntc
// global variables for the BMS
extern uint32_t fsm_reset_error_entry_time;
// TLB signals
extern uint8_t air_neg_cmd_is_active, air_neg_is_closed, air_neg_stg_mech_state_signal_is_active, air_pos_cmd_is_active,
    air_pos_is_closed, air_pos_stg_mech_state_signal_is_active,
    ams_err_is_active, dcbus_is_over60_v, dcbus_prech_rly_cmd_is_active, dcbus_prech_rly_is_closed,
    imd_err_is_active, imp_dcbus_is_active, imp_any_is_active, imp_hv_relays_signals_is_active,
    tsal_green_is_active, close_precharge_is_done, current_state;

static BMS bmsObj;

SM_DEFINE(BMS1, &bmsObj)

int main(void){
    
    printf("Initializing allocator...\n");

    ALLOC_Init();
    printf("Allocator initialized\n");
    BMSData* BMS_data;
    BMS_data = (BMSData*)SM_XAlloc(sizeof(BMSData));

    if (BMS_data == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Failed to allocate memory for BMS_data\n");
        return 1;
    }else{
        printf("Memory allocated for BMS_data\n");
    }

    //Call BMS_Close_Air_Neg_Req event function
    printf("Sending close air neg command\n");
    SM_Event(BMS1, BMS_CLOSE_AIR_NEG_REQ_Event, BMS_data);

    printf("Waiting for precharge to close\n");
    while(BMS_data->current_state != BMS_DRIVING_PRECHARGE);

    if (BMS_data->current_state == BMS_DRIVING_PRECHARGE){
        printf("Sending open air pos command\n");
        SM_Event(BMS1, BMS_CLOSE_AIR_POS_REQ_Event, BMS_data);
    }
    while(BMS_data->current_state != BMS_DRIVING_DRIVING);

        if (BMS_data->current_state == BMS_DRIVING_DRIVING){
            printf("Sending STOP command\n");
            SM_Event(BMS1, BMS_STOP_REQ_Event, BMS_data);
        }
    
    // Send an error to see
    SM_Event(BMS1, BMS_IMD_Error_Event, BMS_data);
    for(int i = 0; i < 10000000; i++);
    SM_Event(BMS1, BMS_TEMPERATURE_Error_Event, BMS_data);

    if ((BMS_data->current_state == BMS_IMD_ERROR)||(BMS_data->current_state == BMS_AMS_IMD_ERROR)||(BMS_data->current_state == BMS_AMS_ERROR)){
        printf("Sending reset error command\n");
        SM_Event(BMS1, BMS_RESET_ERROR_REQ_Event, BMS_data);
    }

    ALLOC_Term();
    
    return 0;
}
