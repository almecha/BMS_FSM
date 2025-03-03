#include "BMS_FSM.h"
#include <stdint.h>
#define LOW 0
#define HIGH 1

typedef struct{
    struct BMS *bms;
    variableTypeDef *variables;
} BMS_FSM_Handle;

typedef struct{

    uint8_t air_neg_int_state_closed;
    uint8_t air_neg_mech_state_open;
    uint8_t air_pos_int_state_closed;
    uint8_t air_pos_mech_state_open;
    uint8_t precharge_int_state_closed;
    uint8_t precharge_mech_state_open;
    uint8_t ams_error;
    uint8_t imd_error;
    uint8_t doneBalancing;
    uint8_t BALANCING_REQ;

}variableTypeDef;

// Main BMS FSM functions
void variables_saving(variableTypeDef* variables);
void BMS_FSM_Handle_Init(BMS_FSM_Handle *handle, struct BMS *bms, variableTypeDef *variables);
void BMS_FSM_Loop_Routine(BMS_FSM_Handle *handle);

// Specific state routines
void balancing_routine(BMS_FSM_Handle *handle);