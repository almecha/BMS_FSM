/*
 * "THE BEER-WARE LICENSE" (Revision 69):
 * Squadra Corse firmware team wrote this file. As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy us a beer in return.
 *
 * Authors
 * - Filippo Rossi <filippo.rossi.sc@gmail.com>
 * - Federico Carbone <federico.carbone.sc@gmail.com>
 */

#include "bms_hv_fsm.h"

#ifndef __weak
#define __weak __attribute__((weak))
#endif // __weak
/*      SIGNALS and COMMANDS I HAVE ON THE SCHEMATICS
*   AIR_POS_MECH_STATE_OPEN_3V3
*   AIR_POS_INT_STATE_CLOSED_3V3 - not sure
*   AIR_NEG_MECH_STATE_OPEN_3V3
*   AIR_NEG_INT_STATE_CLOSED_3V3 - not exactly sure
*   nSTG_AIR_NEG_3V3 - no idea what is it
*   nSTG_AIR_POS_3V3 - no idea what is it
*   DCBUS_PRCH_RLY_INT_STATE_CLOSED_3V3 - probably that the precharge relay is closed by logic
*   DCBUS_PRECH_MECH_STATE_OPEN_3V3 - precharge relay is mechanically open
*   nSTG_PRECH_3V3 - no idea
*   uC_GPIO_OUT_DCBUS_PRCH_RLY_COMMAND - to control the precharge relay
*   uC_GPIO_OUT_AIR_NEG_COMMAND - to control the negative AIR
*   uC_GPIO_OUT_AIR_POS_COMMAND - to control the positiveAIR
*
*/

/* SIGNALS WE NEED
*   done_balanceCells
*   closeAIRNegative
*   closePrecharge
*   closeAIRPositive
*   done_openPrecharge
*   done_closePrecharge
*/
/* QUESTIONS
*   1) How event handlers are done, where?
*   2) How do we create transitions
*   3) How do I create events and transitions if i do not have all of the drivers?
*   4) Try to use TIM, HAL and other stuff in this project
*/


extern volatile uint8_t ntc_temp;   // probably for overtemperature errors
extern volatile uint16_t ntc_value; // raw reading of the ntc

// TLB signals (copied from scarellino)
double air_neg_cmd_is_active, air_neg_is_closed, air_neg_stg_mech_state_signal_is_active, air_pos_cmd_is_active,
    air_pos_is_closed, air_pos_stg_mech_state_signal_is_active,
    ams_err_is_active = 1, dcbus_is_over60_v, dcbus_prech_rly_cmd_is_active, dcbus_prech_rly_is_closed,
    imd_err_is_active = 1, imp_dcbus_is_active, imp_any_is_active = 1, imp_hv_relays_signals_is_active,
    tsal_green_is_active;   // TO RECHECK LATER

// Private wrapper function signatures

uint32_t _FSM_BMS_HV_FSM_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_idle_do_work();

uint32_t _FSM_BMS_HV_FSM_active_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_active_idle_do_work();

uint32_t _FSM_BMS_HV_FSM_resetting_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_resetting_error_do_work();

uint32_t _FSM_BMS_HV_FSM_balancing_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_balancing_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_idle_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_neg_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_closing_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_closing_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_closing_air_pos_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_pos_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_opening_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_opening_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_charging_charging_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_charging_charging_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_idle_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_neg_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_closing_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_closing_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_closing_air_pos_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_pos_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_opening_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_opening_precharge_do_work();

uint32_t _FSM_BMS_HV_FSM_driving_driving_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_driving_driving_do_work();

uint32_t _FSM_BMS_HV_FSM_ams_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_ams_error_do_work();

uint32_t _FSM_BMS_HV_FSM_ams_imd_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_ams_imd_error_do_work();

uint32_t _FSM_BMS_HV_FSM_imd_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_HV_FSM_imd_error_do_work();


FSM_StateTypeDef state_table[_FSM_BMS_HV_FSM_STATE_COUNT] = {
    [FSM_BMS_HV_FSM_idle] = {
        .event_handler = _FSM_BMS_HV_FSM_idle_event_handle,
        .entry = FSM_BMS_HV_FSM_idle_entry,
        .do_work = _FSM_BMS_HV_FSM_idle_do_work,
        .exit = FSM_BMS_HV_FSM_idle_exit,
    },
    [FSM_BMS_HV_FSM_active_idle] = {
        .event_handler = _FSM_BMS_HV_FSM_active_idle_event_handle,
        .entry = FSM_BMS_HV_FSM_active_idle_entry,
        .do_work = _FSM_BMS_HV_FSM_active_idle_do_work,
        .exit = FSM_BMS_HV_FSM_active_idle_exit,
    },
    [FSM_BMS_HV_FSM_resetting_error] = {
        .event_handler = _FSM_BMS_HV_FSM_resetting_error_event_handle,
        .entry = FSM_BMS_HV_FSM_resetting_error_entry,
        .do_work = _FSM_BMS_HV_FSM_resetting_error_do_work,
        .exit = FSM_BMS_HV_FSM_resetting_error_exit,
    },
    [FSM_BMS_HV_FSM_balancing] = {
        .event_handler = _FSM_BMS_HV_FSM_balancing_event_handle,
        .entry = FSM_BMS_HV_FSM_balancing_entry,
        .do_work = _FSM_BMS_HV_FSM_balancing_do_work,
        .exit = FSM_BMS_HV_FSM_balancing_exit,
    },
    [FSM_BMS_HV_FSM_charging_idle] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_idle_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_idle_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_idle_do_work,
        .exit = FSM_BMS_HV_FSM_charging_idle_exit,
    },
    [FSM_BMS_HV_FSM_charging_closing_air_neg] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_closing_air_neg_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_closing_air_neg_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_closing_air_neg_do_work,
        .exit = FSM_BMS_HV_FSM_charging_closing_air_neg_exit,
    },
    [FSM_BMS_HV_FSM_charging_closing_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_closing_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_closing_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_closing_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_charging_closing_precharge_exit,
    },
    [FSM_BMS_HV_FSM_charging_resetting_airs_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_resetting_airs_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_charging_resetting_airs_precharge_exit,
    },
    [FSM_BMS_HV_FSM_charging_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_charging_precharge_exit,
    },
    [FSM_BMS_HV_FSM_charging_closing_air_pos] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_closing_air_pos_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_closing_air_pos_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_closing_air_pos_do_work,
        .exit = FSM_BMS_HV_FSM_charging_closing_air_pos_exit,
    },
    [FSM_BMS_HV_FSM_charging_opening_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_opening_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_opening_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_opening_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_charging_opening_precharge_exit,
    },
    [FSM_BMS_HV_FSM_charging_charging] = {
        .event_handler = _FSM_BMS_HV_FSM_charging_charging_event_handle,
        .entry = FSM_BMS_HV_FSM_charging_charging_entry,
        .do_work = _FSM_BMS_HV_FSM_charging_charging_do_work,
        .exit = FSM_BMS_HV_FSM_charging_charging_exit,
    },
    [FSM_BMS_HV_FSM_driving_idle] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_idle_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_idle_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_idle_do_work,
        .exit = FSM_BMS_HV_FSM_driving_idle_exit,
    },
    [FSM_BMS_HV_FSM_driving_closing_air_neg] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_closing_air_neg_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_closing_air_neg_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_closing_air_neg_do_work,
        .exit = FSM_BMS_HV_FSM_driving_closing_air_neg_exit,
    },
    [FSM_BMS_HV_FSM_driving_closing_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_closing_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_closing_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_closing_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_driving_closing_precharge_exit,
    },
    [FSM_BMS_HV_FSM_driving_resetting_airs_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_resetting_airs_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_driving_resetting_airs_precharge_exit,
    },
    [FSM_BMS_HV_FSM_driving_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_driving_precharge_exit,
    },
    [FSM_BMS_HV_FSM_driving_closing_air_pos] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_closing_air_pos_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_closing_air_pos_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_closing_air_pos_do_work,
        .exit = FSM_BMS_HV_FSM_driving_closing_air_pos_exit,
    },
    [FSM_BMS_HV_FSM_driving_opening_precharge] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_opening_precharge_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_opening_precharge_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_opening_precharge_do_work,
        .exit = FSM_BMS_HV_FSM_driving_opening_precharge_exit,
    },
    [FSM_BMS_HV_FSM_driving_driving] = {
        .event_handler = _FSM_BMS_HV_FSM_driving_driving_event_handle,
        .entry = FSM_BMS_HV_FSM_driving_driving_entry,
        .do_work = _FSM_BMS_HV_FSM_driving_driving_do_work,
        .exit = FSM_BMS_HV_FSM_driving_driving_exit,
    },
    [FSM_BMS_HV_FSM_ams_error] = {
        .event_handler = _FSM_BMS_HV_FSM_ams_error_event_handle,
        .entry = FSM_BMS_HV_FSM_ams_error_entry,
        .do_work = _FSM_BMS_HV_FSM_ams_error_do_work,
        .exit = FSM_BMS_HV_FSM_ams_error_exit,
    },
    [FSM_BMS_HV_FSM_ams_imd_error] = {
        .event_handler = _FSM_BMS_HV_FSM_ams_imd_error_event_handle,
        .entry = FSM_BMS_HV_FSM_ams_imd_error_entry,
        .do_work = _FSM_BMS_HV_FSM_ams_imd_error_do_work,
        .exit = FSM_BMS_HV_FSM_ams_imd_error_exit,
    },
    [FSM_BMS_HV_FSM_imd_error] = {
        .event_handler = _FSM_BMS_HV_FSM_imd_error_event_handle,
        .entry = FSM_BMS_HV_FSM_imd_error_entry,
        .do_work = _FSM_BMS_HV_FSM_imd_error_do_work,
        .exit = FSM_BMS_HV_FSM_imd_error_exit,
    },
};

FSM_ConfigTypeDef config = {
    .state_length = _FSM_BMS_HV_FSM_STATE_COUNT,
    .state_table = state_table,
};

STMLIBS_StatusTypeDef FSM_BMS_HV_FSM_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
) {
    return FSM_init(handle, &config, event_count, run_callback, transition_callback);
}

// State control functions

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_idle_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_active_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_active_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_balancing:
    case FSM_BMS_HV_FSM_charging_idle:
    case FSM_BMS_HV_FSM_driving_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_active_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_active_idle_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_balancing:
    case FSM_BMS_HV_FSM_charging_idle:
    case FSM_BMS_HV_FSM_driving_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_resetting_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_resetting_error_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_resetting_error: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_idle:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_resetting_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_resetting_error_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_idle:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_balancing_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_balancing_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_balancing: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_balancing_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_balancing_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_charging_closing_air_neg:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_idle_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_charging_closing_air_neg:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_closing_air_neg: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_closing_precharge:
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_air_neg_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_closing_precharge:
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_closing_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_charging_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_charging_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_closing_air_pos:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_closing_air_pos:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_pos_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_air_pos_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_closing_air_pos: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_opening_precharge:
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_closing_air_pos_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_closing_air_pos_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_opening_precharge:
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_opening_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_opening_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_opening_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_charging:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_opening_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_opening_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_charging:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_charging_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_charging_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_charging_charging: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_charging_charging_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_charging_charging_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_charging_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_driving_closing_air_neg:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_idle_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_driving_closing_air_neg:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_closing_air_neg: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_closing_precharge:
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_air_neg_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_closing_precharge:
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_closing_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_driving_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_driving_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_active_idle:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_closing_air_pos:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_closing_air_pos:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_pos_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_air_pos_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_closing_air_pos: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_driving_opening_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_closing_air_pos_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_closing_air_pos_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_driving_opening_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_opening_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_opening_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_opening_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_driving:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_opening_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_opening_precharge_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_driving:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_driving_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_driving_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_driving_driving: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_driving_driving_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_driving_driving_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_driving_resetting_airs_precharge:
    case FSM_BMS_HV_FSM_ams_error:
    case FSM_BMS_HV_FSM_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_ams_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_ams_error_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_ams_error: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_ams_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_ams_error_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_ams_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_ams_imd_error_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_ams_imd_error: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_resetting_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_ams_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_ams_imd_error_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_resetting_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_event_handle, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_imd_error_event_handle(event);

    switch (next) {
    case FSM_BMS_HV_FSM_imd_error: // Reentrance is always supported on event handlers
    case FSM_BMS_HV_FSM_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}

/** @brief wrapper of FSM_BMS_HV_FSM_do_work, with exit state checking */
uint32_t _FSM_BMS_HV_FSM_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_HV_FSM_imd_error_do_work();

    switch (next) {
    case FSM_BMS_HV_FSM_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_HV_FSM_DIE;
    }
}


