#include "BMS.h"
#include "StateMachine.h"
#include <stdio.h>
#include <stdint.h>

// Function prototype for HAL_GetTick
uint32_t HAL_GetTick();

uint64_t v_max_id_rx, v_min_id_rx, v_max_rx, v_min_rx, v_mean_rx;

// NTC readings
volatile uint8_t ntc_temp;   // probably for overtemperature errors
volatile uint16_t ntc_value; // raw reading of the ntc
// global variables for the BMS
uint32_t fsm_reset_error_entry_time = 0;
// TLB signals
uint8_t air_neg_cmd_is_active, air_neg_is_closed, air_neg_stg_mech_state_signal_is_active, air_pos_cmd_is_active,
    air_pos_is_closed, air_pos_stg_mech_state_signal_is_active,
    ams_err_is_active = 1, dcbus_is_over60_v, dcbus_prech_rly_cmd_is_active, dcbus_prech_rly_is_closed,
    imd_err_is_active = 1, imp_dcbus_is_active, imp_any_is_active = 1, imp_hv_relays_signals_is_active,
    tsal_green_is_active, close_precharge_is_done;   // TO RECHECK LATER

void VariableSaving(BMSData* variables){
    variables->v_max_id_rx = v_max_id_rx;
    variables->v_min_id_rx = v_min_id_rx;
    variables->v_max_rx = v_max_rx;
    variables->v_min_rx = v_min_rx;
    variables->v_mean_rx = v_mean_rx;
    variables->ntc_temp = ntc_temp;
    variables->ntc_value = ntc_value;
    variables->air_neg_cmd_is_active = air_neg_cmd_is_active;
    variables->air_neg_is_closed = air_neg_is_closed;
    variables->air_neg_stg_mech_state_signal_is_active = air_neg_stg_mech_state_signal_is_active;
    variables->air_pos_cmd_is_active = air_pos_cmd_is_active;
    variables->air_pos_is_closed = air_pos_is_closed;
    variables->air_pos_stg_mech_state_signal_is_active = air_pos_stg_mech_state_signal_is_active;
    variables->ams_err_is_active = ams_err_is_active;
    variables->dcbus_is_over60_v = dcbus_is_over60_v;
    variables->dcbus_prech_rly_cmd_is_active = dcbus_prech_rly_cmd_is_active;
    variables->dcbus_prech_rly_is_closed = dcbus_prech_rly_is_closed;
    variables->imd_err_is_active = imd_err_is_active;
    variables->imp_any_is_active = imp_any_is_active;
    variables->imp_dcbus_is_active = imp_dcbus_is_active;
    variables->imp_hv_relays_signals_is_active = imp_hv_relays_signals_is_active;
    variables -> tsal_green_is_active = tsal_green_is_active;
    variables -> close_precharge_is_done = close_precharge_is_done;
    variables -> fsm_reset_error_entry_time = fsm_reset_error_entry_time;
}

enum States
{   
    BMS_DRIVING_IDLE,
    BMS_DRIVING_CLOSING_AIR_NEG,
    BMS_DRIVING_CLOSING_PRECHARGE,
    BMS_DRIVING_PRECHARGE,
    BMS_DRIVING_CLOSING_AIR_POS,
    BMS_DRIVING_OPENING_PRECHARGE,
    BMS_DRIVING_DRIVING,
    BMS_DRIVING_RESETTING_AIRS_PRECHARGE,
    BMS_AMS_ERROR,
    BMS_IMD_ERROR,
    BMS_AMS_IMD_ERROR,
    BMS_RESETTING_ERROR,
    ST_MAX_STATES
};

// State machine state functions
STATE_DECLARE(DRIVING_IDLE, BMSData)
STATE_DECLARE(DRIVING_CLOSING_AIR_NEG, BMSData)
STATE_DECLARE(DRIVING_CLOSING_PRECHARGE, BMSData)
STATE_DECLARE(DRIVING_PRECHARGE, BMSData)
STATE_DECLARE(DRIVING_CLOSING_AIR_POS, BMSData)
STATE_DECLARE(DRIVING_OPENING_PRECHARGE, BMSData)
STATE_DECLARE(DRIVING_DRIVING, BMSData)
STATE_DECLARE(DRIVING_RESETTING_AIRS_PRECHARGE, BMSData)
STATE_DECLARE(AMS_ERROR, BMSData)
STATE_DECLARE(IMD_ERROR, BMSData)
STATE_DECLARE(AMS_IMD_ERROR, BMSData)
STATE_DECLARE(RESETTING_ERROR, BMSData)

// State map to define state function order
BEGIN_STATE_MAP(BMS)

    STATE_MAP_ENTRY(BMS_DRIVING_IDLE)
    STATE_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_NEG)
    STATE_MAP_ENTRY(BMS_DRIVING_CLOSING_PRECHARGE)
    STATE_MAP_ENTRY(BMS_DRIVING_PRECHARGE)
    STATE_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_POS)
    STATE_MAP_ENTRY(BMS_DRIVING_OPENING_PRECHARGE)
    STATE_MAP_ENTRY(BMS_DRIVING_DRIVING)
    STATE_MAP_ENTRY(BMS_DRIVING_RESETTING_AIRS_PRECHARGE)
    STATE_MAP_ENTRY(BMS_AMS_ERROR)
    STATE_MAP_ENTRY(BMS_IMD_ERROR)
    STATE_MAP_ENTRY(BMS_AMS_IMD_ERROR)
    STATE_MAP_ENTRY(BMS_RESETTING_ERROR)

END_STATE_MAP(BMS)

/**************EVENTS DEFINITION **************/
/*  BMS IMD error event
    *  This event is triggered when the IMD error is detected */
/*  BMS AMS error event
    *  This event is triggered when the AMS error is detected */
/*  BMS CLOSING_AIR_NEG command event
    *  This event is triggered when the CLOSING_AIR_NEG command is detected */
/*  BMS CLOSING_AIR_POS command event
    *  This event is triggered when the CLOSING_AIR_POS command is detected */

EVENT_DEFINE(BMS_IMD_Error_Event, BMSData){
    // Given the SetSpeed event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP                    // - Current State -

        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_IMD_ERROR)         // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)}

EVENT_DEFINE(BMS_TEMPERATURE_Error_Event, BMSData){
    // Given the SetSpeed event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP // - Current State -

        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)     // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)}

EVENT_DEFINE(BMS_ELECTRICAL_Error_Event, BMSData){
    // Given the SetSpeed event, transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP // - Current State -

        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_IMD_ERROR)     // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(BMS_AMS_ERROR)         // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)}

EVENT_DEFINE(BMS_CLOSE_AIR_NEG_REQ_Event, BMSData){
    // Given the BMS_CLOSE_AIR_NEG_REQ_Event , transition to a new state based upon
    // the current state of the state machine
    // Reentrance is permitted
    BEGIN_TRANSITION_MAP                                   // - Current State -

        TRANSITION_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_NEG)  // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_NEG)  // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)}

EVENT_DEFINE(BMS_CLOSE_AIR_POS_REQ_Event, BMSData){
    // Given the BMS_CLOSE_AIR_POS_REQ_Event , transition to a new state based upon
    // the current state of the state machine
    // Reentrance is permitted
    BEGIN_TRANSITION_MAP                                  // - Current State -

        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_POS) // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_DRIVING_CLOSING_AIR_POS) // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)               // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)}

EVENT_DEFINE(BMS_STOP_REQ_Event, BMSData)
{
    // Given the BMS_STOP_REQ_Event , transition to a new state based upon 
    // the current state of the state machine
    // Reentrance is permitted
    BEGIN_TRANSITION_MAP                                            // - Current State -

        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_IDLE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_CLOSING_AIR_NEG
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_CLOSING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_CLOSING_AIR_POS
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_DRIVING_OPENING_PRECHARGE
        TRANSITION_MAP_ENTRY(BMS_DRIVING_RESETTING_AIRS_PRECHARGE)  // BMS_DRIVING_DRIVING
        TRANSITION_MAP_ENTRY(BMS_DRIVING_RESETTING_AIRS_PRECHARGE)  // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_AMS_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_AMS_IMD_ERROR
        TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                         // BMS_RESETTING_ERROR

    END_TRANSITION_MAP(BMS, pEventData)
}

EVENT_DEFINE(BMS_RESET_ERROR_REQ_Event, BMSData)
{
    // Given the BMS_CHARGE_REQ_Event , transition to a new state based upon 
    // the current state of the state machine
    // Reentrance is permitted
    BEGIN_TRANSITION_MAP // - Current State -

            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_IDLE
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_CLOSING_AIR_NEG
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_CLOSING_PRECHARGE
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_PRECHARGE
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_CLOSING_AIR_POS
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_OPENING_PRECHARGE
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_DRIVING
            TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)                        // BMS_DRIVING_RESETTING_AIRS_PRECHARGE
            TRANSITION_MAP_ENTRY(BMS_RESETTING_ERROR)                  // BMS_AMS_ERROR
            TRANSITION_MAP_ENTRY(BMS_RESETTING_ERROR)                  // BMS_IMD_ERROR
            TRANSITION_MAP_ENTRY(BMS_RESETTING_ERROR)                  // BMS_AMS_IMD_ERROR
            TRANSITION_MAP_ENTRY(BMS_RESETTING_ERROR)                  // BMS_RESETTING_ERROR

        END_TRANSITION_MAP(BMS, pEventData)
}

/**************STATES DEFINITION **************/

STATE_DEFINE(DRIVING_IDLE, BMSData)
{
    ASSERT_TRUE(pEventData);
    VariableSaving(pEventData);

    printf("%s DRIVING_Idle\n", self->name);

}
STATE_DEFINE(DRIVING_CLOSING_AIR_NEG, BMSData)
{   
    ASSERT_TRUE(pEventData);
    air_neg_cmd_is_active = 1;
    air_neg_is_closed = 1;
    VariableSaving(pEventData);

    printf("%s DRIVING_CLOSING_AIR\n", self->name);
    if ( pEventData->air_neg_cmd_is_active && pEventData->air_neg_is_closed){
        SM_InternalEvent(BMS_DRIVING_CLOSING_PRECHARGE, NULL);
    } else if (!(pEventData->air_neg_cmd_is_active && pEventData->air_neg_is_closed)){
        SM_InternalEvent(BMS_DRIVING_RESETTING_AIRS_PRECHARGE, NULL);
    }
    
}
STATE_DEFINE(DRIVING_CLOSING_PRECHARGE, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    
    if (pEventData->close_precharge_is_done){
        SM_InternalEvent(BMS_DRIVING_PRECHARGE,NULL);
    } else {
        SM_InternalEvent(BMS_DRIVING_RESETTING_AIRS_PRECHARGE, NULL);
    }

    printf("%s DRIVING_CLOSING_PRECHARGE\n", self->name);
    
}

STATE_DEFINE(DRIVING_PRECHARGE, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    
    printf("%s DRIVING_PRECHARGE\n", self->name);
    
}

STATE_DEFINE(DRIVING_CLOSING_AIR_POS, BMSData)
{   
    ASSERT_TRUE(pEventData);
    air_pos_cmd_is_active = 1;
    VariableSaving(pEventData);

    printf("%s DRIVING_CLOSING_AIR_POS\n", self->name);
    if ( pEventData->air_pos_cmd_is_active && pEventData->air_pos_is_closed){
        SM_InternalEvent(BMS_DRIVING_OPENING_PRECHARGE, NULL);
    } else if (!(pEventData->air_pos_cmd_is_active && pEventData->air_pos_is_closed)){
        SM_InternalEvent(BMS_DRIVING_RESETTING_AIRS_PRECHARGE, NULL);
    }
}

STATE_DEFINE(DRIVING_OPENING_PRECHARGE, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    
    if (pEventData->close_precharge_is_done){
        SM_InternalEvent(BMS_DRIVING_DRIVING,NULL);
    }

    printf("%s DRIVING_OPENING_PRECHARGE\n", self->name);
    
}

STATE_DEFINE(DRIVING_DRIVING, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    

    printf("%s DRIVING_DRIVING OOOOOO\n", self->name);
    
}

STATE_DEFINE(DRIVING_RESETTING_AIRS_PRECHARGE, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    
    printf("OPENING PRECHARGE\n");
    printf("OPENING AIR POSITIVE\n");
    printf("OPENING AIR NEGATIVE\n");


    printf("%s DRIVING_RESET DONE\n", self->name);
    
    SM_InternalEvent(BMS_DRIVING_IDLE,NULL);
}

STATE_DEFINE(AMS_ERROR, BMSData)
{
    ASSERT_TRUE(pEventData);
    ams_err_is_active = 1;
    VariableSaving(pEventData);
    
    printf("%s SET AMS ERROR HIGH\n", self->name);
    
}
STATE_DEFINE(IMD_ERROR, BMSData)
{
    ASSERT_TRUE(pEventData);
    imd_err_is_active = 1;
    VariableSaving(pEventData);
    
    printf("%s SET IMD ERROR HIGH\n", self->name);
    
}
STATE_DEFINE(AMS_IMD_ERROR, BMSData)
{
    ASSERT_TRUE(pEventData);

    VariableSaving(pEventData);
    
    printf("%s SET AMS_IMD ERROR HIGH\n", self->name);
    
}
STATE_DEFINE(RESETTING_ERROR, BMSData)
{
    ASSERT_TRUE(pEventData);
    ams_err_is_active = 0;
    imd_err_is_active = 0;
    VariableSaving(pEventData);
    
    if (HAL_GetTick() - pEventData->fsm_reset_error_entry_time > 10000){
        SM_InternalEvent(BMS_DRIVING_IDLE,NULL);
    }

    printf("%s RESETTING ERROR\n", self->name);
    
}
ENTRY_DEFINE(RESETTING_ERROR, BMSData)
{
    ASSERT_TRUE(pEventData);
    printf("%s Entry to resetting error\n", self->name);
    fsm_reset_error_entry_time = HAL_GetTick();

}

// Provide definition for HAL_GetTick
uint32_t HAL_GetTick() {
    // Implementation of HAL_GetTick
    return 0; // Placeholder implementation
}




