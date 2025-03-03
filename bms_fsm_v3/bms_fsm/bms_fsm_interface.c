#include "bms_fsm_interface.h"

uint8_t air_neg_int_state_closed = LOW;
uint8_t air_neg_mech_state_open = LOW;
uint8_t air_pos_int_state_closed = LOW;
uint8_t air_pos_mech_state_open = LOW;
uint8_t precharge_int_state_closed = LOW;
uint8_t precharge_mech_state_open = LOW;
uint8_t ams_error = LOW;
uint8_t imd_error = LOW;
uint8_t doneBalancing = LOW;
uint8_t BALANCING_REQ = LOW;


// Variables struct to hold and update everything in one place
variableTypeDef variables;

// Handle to properly operate the FSM in the main loop, and call events reading the pins
void BMS_FSM_Handle_Init(BMS_FSM_Handle *handle, struct BMS *bms, variableTypeDef *variables){
    handle->bms = bms;
    handle->variables = variables;
}

// This loop is called in the main function of the BMS_HV_Core
void BMS_FSM_Loop_Routine(BMS_FSM_Handle *handle){
    // Each call update the variables
    variables_saving(&variables);
    // Error check
    if (handle->variables->ams_error) BMS_AMS_ERROR(handle->bms);  // Call the AMS_ERROR event
    if (handle->variables->ams_error) BMS_IMD_ERROR(handle->bms);
    // Calling the state routines specific to the state (MAIN SWITCH)
    switch (handle->bms->state) {
        // Balancing state
        case balancing:
            balancing_routine(handle);
            if (handle -> variables->doneBalancing)  BMS_DONE_BALANCE_CELLS(handle->bms);    // Sending an event to change the state
            break;
            case charging_idle:
            if (handle ->variables->BALANCING_REQ)  BMS_BALANCING_REQ(handle->bms);
            break;

    }
}

// Variable saving routine
void variables_saving(variableTypeDef* variables){
    variables -> air_neg_int_state_closed = air_neg_int_state_closed;
    variables -> air_neg_mech_state_open = air_neg_mech_state_open;
    variables -> air_pos_int_state_closed = air_pos_int_state_closed;
    variables -> air_pos_mech_state_open = air_pos_mech_state_open;
    variables -> ams_error = ams_error;
    variables -> imd_error = imd_error;
    variables -> precharge_int_state_closed = precharge_int_state_closed;
    variables -> precharge_mech_state_open = precharge_mech_state_open;
    variables ->doneBalancing = doneBalancing;
    variables ->BALANCING_REQ = BALANCING_REQ;
}

// Specific state functions
void balancing_routine(BMS_FSM_Handle *handle){
}