#ifndef _BMS_H
#define _BMS_H

#include "StateMachine.h"
#include <stdint.h>


// BMS object structure
typedef struct
{

    uint32_t state_of_charge;
    uint32_t state_of_health;

} BMS;

// Event data structure
typedef struct
{
    uint64_t v_max_id_rx, v_min_id_rx, v_max_rx, v_min_rx, v_mean_rx;
    uint8_t ntc_temp;
    uint16_t ntc_value;
    uint8_t air_neg_cmd_is_active, air_neg_is_closed, air_neg_stg_mech_state_signal_is_active, air_pos_cmd_is_active,
    air_pos_is_closed, air_pos_stg_mech_state_signal_is_active,
    ams_err_is_active, dcbus_is_over60_v, dcbus_prech_rly_cmd_is_active, dcbus_prech_rly_is_closed,
    imd_err_is_active, imp_dcbus_is_active, imp_any_is_active, imp_hv_relays_signals_is_active,
    tsal_green_is_active, close_precharge_is_done;
    uint32_t fsm_reset_error_entry_time;

} BMSData;

EVENT_DECLARE(BMS_IMD_Error_Event, BMSData);
EVENT_DECLARE(BMS_CELL_TEMPERATURE_Error_Event, BMSData);
EVENT_DECLARE(BMS_CELL_ELECTRICAL_Error_Event, BMSData);
EVENT_DECLARE(BMS_CLOSE_AIR_NEG_REQ_Event, BMSData);
EVENT_DECLARE(BMS_CLOSE_AIR_POS_REQ_Event, BMSData);
EVENT_DECLARE(BMS_STOP_REQ_Event, BMSData);
EVENT_DECLARE(BMS_RESET_ERROR_REQ_Event, BMSData);




#endif // _BMS_H