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

#include "test1.h"

#ifndef __weak
#define __weak __attribute__((weak))
#endif // __weak

// Private wrapper function signatures

uint32_t _FSM_TEST1_start_event_handle(uint8_t event);
uint32_t _FSM_TEST1_start_do_work();

uint32_t _FSM_TEST1_idle_event_handle(uint8_t event);
uint32_t _FSM_TEST1_idle_do_work();

uint32_t _FSM_TEST1_resetting_error_event_handle(uint8_t event);
uint32_t _FSM_TEST1_resetting_error_do_work();

uint32_t _FSM_TEST1_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_TEST1_closing_air_neg_do_work();

uint32_t _FSM_TEST1_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_TEST1_resetting_airs_precharge_do_work();

uint32_t _FSM_TEST1_balancing_event_handle(uint8_t event);
uint32_t _FSM_TEST1_balancing_do_work();

uint32_t _FSM_TEST1_closing_precharge_event_handle(uint8_t event);
uint32_t _FSM_TEST1_closing_precharge_do_work();

uint32_t _FSM_TEST1_precharge_event_handle(uint8_t event);
uint32_t _FSM_TEST1_precharge_do_work();

uint32_t _FSM_TEST1_closing_air_pos_event_handle(uint8_t event);
uint32_t _FSM_TEST1_closing_air_pos_do_work();

uint32_t _FSM_TEST1_opening_precharge_event_handle(uint8_t event);
uint32_t _FSM_TEST1_opening_precharge_do_work();

uint32_t _FSM_TEST1_charging_event_handle(uint8_t event);
uint32_t _FSM_TEST1_charging_do_work();

uint32_t _FSM_TEST1_driving_event_handle(uint8_t event);
uint32_t _FSM_TEST1_driving_do_work();

uint32_t _FSM_TEST1_ams_error_event_handle(uint8_t event);
uint32_t _FSM_TEST1_ams_error_do_work();

uint32_t _FSM_TEST1_ams_imd_error_event_handle(uint8_t event);
uint32_t _FSM_TEST1_ams_imd_error_do_work();

uint32_t _FSM_TEST1_imd_error_event_handle(uint8_t event);
uint32_t _FSM_TEST1_imd_error_do_work();


FSM_StateTypeDef state_table[_FSM_TEST1_STATE_COUNT] = {
    [FSM_TEST1_start] = {
        .event_handler = _FSM_TEST1_start_event_handle,
        .entry = FSM_TEST1_start_entry,
        .do_work = _FSM_TEST1_start_do_work,
        .exit = FSM_TEST1_start_exit,
    },
    [FSM_TEST1_idle] = {
        .event_handler = _FSM_TEST1_idle_event_handle,
        .entry = FSM_TEST1_idle_entry,
        .do_work = _FSM_TEST1_idle_do_work,
        .exit = FSM_TEST1_idle_exit,
    },
    [FSM_TEST1_resetting_error] = {
        .event_handler = _FSM_TEST1_resetting_error_event_handle,
        .entry = FSM_TEST1_resetting_error_entry,
        .do_work = _FSM_TEST1_resetting_error_do_work,
        .exit = FSM_TEST1_resetting_error_exit,
    },
    [FSM_TEST1_closing_air_neg] = {
        .event_handler = _FSM_TEST1_closing_air_neg_event_handle,
        .entry = FSM_TEST1_closing_air_neg_entry,
        .do_work = _FSM_TEST1_closing_air_neg_do_work,
        .exit = FSM_TEST1_closing_air_neg_exit,
    },
    [FSM_TEST1_resetting_airs_precharge] = {
        .event_handler = _FSM_TEST1_resetting_airs_precharge_event_handle,
        .entry = FSM_TEST1_resetting_airs_precharge_entry,
        .do_work = _FSM_TEST1_resetting_airs_precharge_do_work,
        .exit = FSM_TEST1_resetting_airs_precharge_exit,
    },
    [FSM_TEST1_balancing] = {
        .event_handler = _FSM_TEST1_balancing_event_handle,
        .entry = FSM_TEST1_balancing_entry,
        .do_work = _FSM_TEST1_balancing_do_work,
        .exit = FSM_TEST1_balancing_exit,
    },
    [FSM_TEST1_closing_precharge] = {
        .event_handler = _FSM_TEST1_closing_precharge_event_handle,
        .entry = FSM_TEST1_closing_precharge_entry,
        .do_work = _FSM_TEST1_closing_precharge_do_work,
        .exit = FSM_TEST1_closing_precharge_exit,
    },
    [FSM_TEST1_precharge] = {
        .event_handler = _FSM_TEST1_precharge_event_handle,
        .entry = FSM_TEST1_precharge_entry,
        .do_work = _FSM_TEST1_precharge_do_work,
        .exit = FSM_TEST1_precharge_exit,
    },
    [FSM_TEST1_closing_air_pos] = {
        .event_handler = _FSM_TEST1_closing_air_pos_event_handle,
        .entry = FSM_TEST1_closing_air_pos_entry,
        .do_work = _FSM_TEST1_closing_air_pos_do_work,
        .exit = FSM_TEST1_closing_air_pos_exit,
    },
    [FSM_TEST1_opening_precharge] = {
        .event_handler = _FSM_TEST1_opening_precharge_event_handle,
        .entry = FSM_TEST1_opening_precharge_entry,
        .do_work = _FSM_TEST1_opening_precharge_do_work,
        .exit = FSM_TEST1_opening_precharge_exit,
    },
    [FSM_TEST1_charging] = {
        .event_handler = _FSM_TEST1_charging_event_handle,
        .entry = FSM_TEST1_charging_entry,
        .do_work = _FSM_TEST1_charging_do_work,
        .exit = FSM_TEST1_charging_exit,
    },
    [FSM_TEST1_driving] = {
        .event_handler = _FSM_TEST1_driving_event_handle,
        .entry = FSM_TEST1_driving_entry,
        .do_work = _FSM_TEST1_driving_do_work,
        .exit = FSM_TEST1_driving_exit,
    },
    [FSM_TEST1_ams_error] = {
        .event_handler = _FSM_TEST1_ams_error_event_handle,
        .entry = FSM_TEST1_ams_error_entry,
        .do_work = _FSM_TEST1_ams_error_do_work,
        .exit = FSM_TEST1_ams_error_exit,
    },
    [FSM_TEST1_ams_imd_error] = {
        .event_handler = _FSM_TEST1_ams_imd_error_event_handle,
        .entry = FSM_TEST1_ams_imd_error_entry,
        .do_work = _FSM_TEST1_ams_imd_error_do_work,
        .exit = FSM_TEST1_ams_imd_error_exit,
    },
    [FSM_TEST1_imd_error] = {
        .event_handler = _FSM_TEST1_imd_error_event_handle,
        .entry = FSM_TEST1_imd_error_entry,
        .do_work = _FSM_TEST1_imd_error_do_work,
        .exit = FSM_TEST1_imd_error_exit,
    },
};

FSM_ConfigTypeDef config = {
    .state_length = _FSM_TEST1_STATE_COUNT,
    .state_table = state_table,
};

STMLIBS_StatusTypeDef FSM_TEST1_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
) {
    return FSM_init(handle, &config, event_count, run_callback, transition_callback);
}

// State control functions

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_start_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_start_event_handle(event);

    switch (next) {
    case FSM_TEST1_start: // Reentrance is always supported on event handlers
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_start_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_start_do_work();

    switch (next) {
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_idle_event_handle(event);

    switch (next) {
    case FSM_TEST1_idle: // Reentrance is always supported on event handlers
    case FSM_TEST1_closing_air_neg:
    case FSM_TEST1_closing_air_neg:
    case FSM_TEST1_balancing:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_idle_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_idle_do_work();

    switch (next) {
    case FSM_TEST1_closing_air_neg:
    case FSM_TEST1_closing_air_neg:
    case FSM_TEST1_balancing:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_resetting_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_resetting_error_event_handle(event);

    switch (next) {
    case FSM_TEST1_resetting_error: // Reentrance is always supported on event handlers
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_resetting_error_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_resetting_error_do_work();

    switch (next) {
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_TEST1_closing_air_neg: // Reentrance is always supported on event handlers
    case FSM_TEST1_closing_precharge:
    case FSM_TEST1_closing_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_closing_air_neg_do_work();

    switch (next) {
    case FSM_TEST1_closing_precharge:
    case FSM_TEST1_closing_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_TEST1_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_balancing_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_balancing_event_handle(event);

    switch (next) {
    case FSM_TEST1_balancing: // Reentrance is always supported on event handlers
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_balancing_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_balancing_do_work();

    switch (next) {
    case FSM_TEST1_idle:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_closing_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_closing_precharge_event_handle(event);

    switch (next) {
    case FSM_TEST1_closing_precharge: // Reentrance is always supported on event handlers
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_precharge:
    case FSM_TEST1_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_closing_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_closing_precharge_do_work();

    switch (next) {
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_precharge:
    case FSM_TEST1_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_precharge_event_handle(event);

    switch (next) {
    case FSM_TEST1_precharge: // Reentrance is always supported on event handlers
    case FSM_TEST1_closing_air_pos:
    case FSM_TEST1_closing_air_pos:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_precharge_do_work();

    switch (next) {
    case FSM_TEST1_closing_air_pos:
    case FSM_TEST1_closing_air_pos:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_closing_air_pos_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_closing_air_pos_event_handle(event);

    switch (next) {
    case FSM_TEST1_closing_air_pos: // Reentrance is always supported on event handlers
    case FSM_TEST1_opening_precharge:
    case FSM_TEST1_opening_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_closing_air_pos_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_closing_air_pos_do_work();

    switch (next) {
    case FSM_TEST1_opening_precharge:
    case FSM_TEST1_opening_precharge:
    case FSM_TEST1_resetting_airs_precharge:
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_opening_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_opening_precharge_event_handle(event);

    switch (next) {
    case FSM_TEST1_opening_precharge: // Reentrance is always supported on event handlers
    case FSM_TEST1_charging:
    case FSM_TEST1_driving:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_opening_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_opening_precharge_do_work();

    switch (next) {
    case FSM_TEST1_charging:
    case FSM_TEST1_driving:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_charging_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_charging_event_handle(event);

    switch (next) {
    case FSM_TEST1_charging: // Reentrance is always supported on event handlers
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_charging_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_charging_do_work();

    switch (next) {
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_driving_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_driving_event_handle(event);

    switch (next) {
    case FSM_TEST1_driving: // Reentrance is always supported on event handlers
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_driving_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_driving_do_work();

    switch (next) {
    case FSM_TEST1_resetting_airs_precharge:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_ams_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_ams_error_event_handle(event);

    switch (next) {
    case FSM_TEST1_ams_error: // Reentrance is always supported on event handlers
    case FSM_TEST1_ams_imd_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_ams_error_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_ams_error_do_work();

    switch (next) {
    case FSM_TEST1_ams_imd_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_ams_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_ams_imd_error_event_handle(event);

    switch (next) {
    case FSM_TEST1_ams_imd_error: // Reentrance is always supported on event handlers
    case FSM_TEST1_resetting_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_ams_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_ams_imd_error_do_work();

    switch (next) {
    case FSM_TEST1_resetting_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_event_handle, with exit state checking */
uint32_t _FSM_TEST1_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_TEST1_imd_error_event_handle(event);

    switch (next) {
    case FSM_TEST1_imd_error: // Reentrance is always supported on event handlers
    case FSM_TEST1_ams_imd_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}

/** @brief wrapper of FSM_TEST1_do_work, with exit state checking */
uint32_t _FSM_TEST1_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_TEST1_imd_error_do_work();

    switch (next) {
    case FSM_TEST1_ams_imd_error:
        return next;
    default:
        return _FSM_TEST1_DIE;
    }
}


// State functions

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_start_event_handle(uint8_t event) {
    return FSM_TEST1_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_start_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_start_do_work() {
    return FSM_TEST1_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_start_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_idle_event_handle(uint8_t event) {
    return FSM_TEST1_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_idle_do_work() {
    return FSM_TEST1_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_resetting_error_event_handle(uint8_t event) {
    return FSM_TEST1_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_resetting_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_resetting_error_do_work() {
    return FSM_TEST1_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_resetting_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_neg_event_handle(uint8_t event) {
    return FSM_TEST1_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_air_neg_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_neg_do_work() {
    return FSM_TEST1_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_air_neg_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_resetting_airs_precharge_event_handle(uint8_t event) {
    return FSM_TEST1_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_resetting_airs_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_resetting_airs_precharge_do_work() {
    return FSM_TEST1_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_resetting_airs_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_balancing_event_handle(uint8_t event) {
    return FSM_TEST1_balancing;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_balancing_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_balancing_do_work() {
    return FSM_TEST1_balancing;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_balancing_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_precharge_event_handle(uint8_t event) {
    return FSM_TEST1_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_precharge_do_work() {
    return FSM_TEST1_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_precharge_event_handle(uint8_t event) {
    return FSM_TEST1_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_precharge_do_work() {
    return FSM_TEST1_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_pos_event_handle(uint8_t event) {
    return FSM_TEST1_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_air_pos_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_pos_do_work() {
    return FSM_TEST1_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_closing_air_pos_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_opening_precharge_event_handle(uint8_t event) {
    return FSM_TEST1_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_opening_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_opening_precharge_do_work() {
    return FSM_TEST1_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_opening_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_charging_event_handle(uint8_t event) {
    return FSM_TEST1_charging;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_charging_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_charging_do_work() {
    return FSM_TEST1_charging;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_charging_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_driving_event_handle(uint8_t event) {
    return FSM_TEST1_driving;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_driving_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_driving_do_work() {
    return FSM_TEST1_driving;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_driving_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_ams_error_event_handle(uint8_t event) {
    return FSM_TEST1_ams_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_ams_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_ams_error_do_work() {
    return FSM_TEST1_ams_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_ams_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_ams_imd_error_event_handle(uint8_t event) {
    return FSM_TEST1_ams_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_ams_imd_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_ams_imd_error_do_work() {
    return FSM_TEST1_ams_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_ams_imd_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_imd_error_event_handle(uint8_t event) {
    return FSM_TEST1_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_imd_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_TEST1_StateTypeDef FSM_TEST1_imd_error_do_work() {
    return FSM_TEST1_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_TEST1_imd_error_exit() {
    return;
}

