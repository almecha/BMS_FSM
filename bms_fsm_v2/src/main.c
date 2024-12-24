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
    tsal_green_is_active, close_precharge_is_done;

static BMS bmsObj;

SM_DEFINE(BMS, &bmsObj)

int main(void){
    ALLOC_Init();

    BMSData* BMS_data;
    BMS_data = SM_XAlloc(sizeof(BMSData));
    VariableSaving(BMS_data);

    //Call BMS_Close_Air_Neg_Req event function
    SM_Event(BMS, BMS_CLOSE_AIR_NEG_REQ_Event, BMS_data);

    ALLOC_Term();
    
    return 0;
}
