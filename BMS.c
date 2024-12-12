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

#include "BMS.h"

#ifndef __weak
#define __weak __attribute__((weak))
#endif // __weak

// Private wrapper function signatures

uint32_t _FSM_BMS_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_idle_do_work();

uint32_t _FSM_BMS_active_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_active_idle_do_work();

uint32_t _FSM_BMS_resetting_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_resetting_error_do_work();

uint32_t _FSM_BMS_balancing_event_handle(uint8_t event);
uint32_t _FSM_BMS_balancing_do_work();

uint32_t _FSM_BMS_charging_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_idle_do_work();

uint32_t _FSM_BMS_charging_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_closing_air_neg_do_work();

uint32_t _FSM_BMS_charging_closing_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_closing_precharge_do_work();

uint32_t _FSM_BMS_charging_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_resetting_airs_precharge_do_work();

uint32_t _FSM_BMS_charging_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_precharge_do_work();

uint32_t _FSM_BMS_charging_closing_air_pos_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_closing_air_pos_do_work();

uint32_t _FSM_BMS_charging_opening_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_opening_precharge_do_work();

uint32_t _FSM_BMS_charging_charging_event_handle(uint8_t event);
uint32_t _FSM_BMS_charging_charging_do_work();

uint32_t _FSM_BMS_driving_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_idle_do_work();

uint32_t _FSM_BMS_driving_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_closing_air_neg_do_work();

uint32_t _FSM_BMS_driving_closing_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_closing_precharge_do_work();

uint32_t _FSM_BMS_driving_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_resetting_airs_precharge_do_work();

uint32_t _FSM_BMS_driving_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_precharge_do_work();

uint32_t _FSM_BMS_driving_closing_air_pos_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_closing_air_pos_do_work();

uint32_t _FSM_BMS_driving_opening_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_opening_precharge_do_work();

uint32_t _FSM_BMS_driving_driving_event_handle(uint8_t event);
uint32_t _FSM_BMS_driving_driving_do_work();

uint32_t _FSM_BMS_ams_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_ams_error_do_work();

uint32_t _FSM_BMS_ams_imd_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_ams_imd_error_do_work();

uint32_t _FSM_BMS_imd_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_imd_error_do_work();


FSM_StateTypeDef state_table[_FSM_BMS_STATE_COUNT] = {
    [FSM_BMS_idle] = {
        .event_handler = _FSM_BMS_idle_event_handle,
        .entry = FSM_BMS_idle_entry,
        .do_work = _FSM_BMS_idle_do_work,
        .exit = FSM_BMS_idle_exit,
    },
    [FSM_BMS_active_idle] = {
        .event_handler = _FSM_BMS_active_idle_event_handle,
        .entry = FSM_BMS_active_idle_entry,
        .do_work = _FSM_BMS_active_idle_do_work,
        .exit = FSM_BMS_active_idle_exit,
    },
    [FSM_BMS_resetting_error] = {
        .event_handler = _FSM_BMS_resetting_error_event_handle,
        .entry = FSM_BMS_resetting_error_entry,
        .do_work = _FSM_BMS_resetting_error_do_work,
        .exit = FSM_BMS_resetting_error_exit,
    },
    [FSM_BMS_balancing] = {
        .event_handler = _FSM_BMS_balancing_event_handle,
        .entry = FSM_BMS_balancing_entry,
        .do_work = _FSM_BMS_balancing_do_work,
        .exit = FSM_BMS_balancing_exit,
    },
    [FSM_BMS_charging_idle] = {
        .event_handler = _FSM_BMS_charging_idle_event_handle,
        .entry = FSM_BMS_charging_idle_entry,
        .do_work = _FSM_BMS_charging_idle_do_work,
        .exit = FSM_BMS_charging_idle_exit,
    },
    [FSM_BMS_charging_closing_air_neg] = {
        .event_handler = _FSM_BMS_charging_closing_air_neg_event_handle,
        .entry = FSM_BMS_charging_closing_air_neg_entry,
        .do_work = _FSM_BMS_charging_closing_air_neg_do_work,
        .exit = FSM_BMS_charging_closing_air_neg_exit,
    },
    [FSM_BMS_charging_closing_precharge] = {
        .event_handler = _FSM_BMS_charging_closing_precharge_event_handle,
        .entry = FSM_BMS_charging_closing_precharge_entry,
        .do_work = _FSM_BMS_charging_closing_precharge_do_work,
        .exit = FSM_BMS_charging_closing_precharge_exit,
    },
    [FSM_BMS_charging_resetting_airs_precharge] = {
        .event_handler = _FSM_BMS_charging_resetting_airs_precharge_event_handle,
        .entry = FSM_BMS_charging_resetting_airs_precharge_entry,
        .do_work = _FSM_BMS_charging_resetting_airs_precharge_do_work,
        .exit = FSM_BMS_charging_resetting_airs_precharge_exit,
    },
    [FSM_BMS_charging_precharge] = {
        .event_handler = _FSM_BMS_charging_precharge_event_handle,
        .entry = FSM_BMS_charging_precharge_entry,
        .do_work = _FSM_BMS_charging_precharge_do_work,
        .exit = FSM_BMS_charging_precharge_exit,
    },
    [FSM_BMS_charging_closing_air_pos] = {
        .event_handler = _FSM_BMS_charging_closing_air_pos_event_handle,
        .entry = FSM_BMS_charging_closing_air_pos_entry,
        .do_work = _FSM_BMS_charging_closing_air_pos_do_work,
        .exit = FSM_BMS_charging_closing_air_pos_exit,
    },
    [FSM_BMS_charging_opening_precharge] = {
        .event_handler = _FSM_BMS_charging_opening_precharge_event_handle,
        .entry = FSM_BMS_charging_opening_precharge_entry,
        .do_work = _FSM_BMS_charging_opening_precharge_do_work,
        .exit = FSM_BMS_charging_opening_precharge_exit,
    },
    [FSM_BMS_charging_charging] = {
        .event_handler = _FSM_BMS_charging_charging_event_handle,
        .entry = FSM_BMS_charging_charging_entry,
        .do_work = _FSM_BMS_charging_charging_do_work,
        .exit = FSM_BMS_charging_charging_exit,
    },
    [FSM_BMS_driving_idle] = {
        .event_handler = _FSM_BMS_driving_idle_event_handle,
        .entry = FSM_BMS_driving_idle_entry,
        .do_work = _FSM_BMS_driving_idle_do_work,
        .exit = FSM_BMS_driving_idle_exit,
    },
    [FSM_BMS_driving_closing_air_neg] = {
        .event_handler = _FSM_BMS_driving_closing_air_neg_event_handle,
        .entry = FSM_BMS_driving_closing_air_neg_entry,
        .do_work = _FSM_BMS_driving_closing_air_neg_do_work,
        .exit = FSM_BMS_driving_closing_air_neg_exit,
    },
    [FSM_BMS_driving_closing_precharge] = {
        .event_handler = _FSM_BMS_driving_closing_precharge_event_handle,
        .entry = FSM_BMS_driving_closing_precharge_entry,
        .do_work = _FSM_BMS_driving_closing_precharge_do_work,
        .exit = FSM_BMS_driving_closing_precharge_exit,
    },
    [FSM_BMS_driving_resetting_airs_precharge] = {
        .event_handler = _FSM_BMS_driving_resetting_airs_precharge_event_handle,
        .entry = FSM_BMS_driving_resetting_airs_precharge_entry,
        .do_work = _FSM_BMS_driving_resetting_airs_precharge_do_work,
        .exit = FSM_BMS_driving_resetting_airs_precharge_exit,
    },
    [FSM_BMS_driving_precharge] = {
        .event_handler = _FSM_BMS_driving_precharge_event_handle,
        .entry = FSM_BMS_driving_precharge_entry,
        .do_work = _FSM_BMS_driving_precharge_do_work,
        .exit = FSM_BMS_driving_precharge_exit,
    },
    [FSM_BMS_driving_closing_air_pos] = {
        .event_handler = _FSM_BMS_driving_closing_air_pos_event_handle,
        .entry = FSM_BMS_driving_closing_air_pos_entry,
        .do_work = _FSM_BMS_driving_closing_air_pos_do_work,
        .exit = FSM_BMS_driving_closing_air_pos_exit,
    },
    [FSM_BMS_driving_opening_precharge] = {
        .event_handler = _FSM_BMS_driving_opening_precharge_event_handle,
        .entry = FSM_BMS_driving_opening_precharge_entry,
        .do_work = _FSM_BMS_driving_opening_precharge_do_work,
        .exit = FSM_BMS_driving_opening_precharge_exit,
    },
    [FSM_BMS_driving_driving] = {
        .event_handler = _FSM_BMS_driving_driving_event_handle,
        .entry = FSM_BMS_driving_driving_entry,
        .do_work = _FSM_BMS_driving_driving_do_work,
        .exit = FSM_BMS_driving_driving_exit,
    },
    [FSM_BMS_ams_error] = {
        .event_handler = _FSM_BMS_ams_error_event_handle,
        .entry = FSM_BMS_ams_error_entry,
        .do_work = _FSM_BMS_ams_error_do_work,
        .exit = FSM_BMS_ams_error_exit,
    },
    [FSM_BMS_ams_imd_error] = {
        .event_handler = _FSM_BMS_ams_imd_error_event_handle,
        .entry = FSM_BMS_ams_imd_error_entry,
        .do_work = _FSM_BMS_ams_imd_error_do_work,
        .exit = FSM_BMS_ams_imd_error_exit,
    },
    [FSM_BMS_imd_error] = {
        .event_handler = _FSM_BMS_imd_error_event_handle,
        .entry = FSM_BMS_imd_error_entry,
        .do_work = _FSM_BMS_imd_error_do_work,
        .exit = FSM_BMS_imd_error_exit,
    },
};

FSM_ConfigTypeDef config = {
    .state_length = _FSM_BMS_STATE_COUNT,
    .state_table = state_table,
};

STMLIBS_StatusTypeDef FSM_BMS_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
) {
    return FSM_init(handle, &config, event_count, run_callback, transition_callback);
}

// State control functions

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_idle_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_active_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_active_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_active_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_balancing:
    case FSM_BMS_charging_idle:
    case FSM_BMS_driving_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_active_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_active_idle_do_work();

    switch (next) {
    case FSM_BMS_balancing:
    case FSM_BMS_charging_idle:
    case FSM_BMS_driving_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_resetting_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_resetting_error_event_handle(event);

    switch (next) {
    case FSM_BMS_resetting_error: // Reentrance is always supported on event handlers
    case FSM_BMS_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_resetting_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_resetting_error_do_work();

    switch (next) {
    case FSM_BMS_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_balancing_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_balancing_event_handle(event);

    switch (next) {
    case FSM_BMS_balancing: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_balancing_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_balancing_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
    case FSM_BMS_charging_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_idle_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
    case FSM_BMS_charging_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_closing_air_neg: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_closing_precharge:
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_air_neg_do_work();

    switch (next) {
    case FSM_BMS_charging_closing_precharge:
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_closing_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_closing_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_resetting_airs_precharge:
    case FSM_BMS_charging_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_closing_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_precharge_do_work();

    switch (next) {
    case FSM_BMS_charging_resetting_airs_precharge:
    case FSM_BMS_charging_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_closing_air_pos:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_precharge_do_work();

    switch (next) {
    case FSM_BMS_charging_closing_air_pos:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_closing_air_pos_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_air_pos_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_closing_air_pos: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_opening_precharge:
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_closing_air_pos_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_closing_air_pos_do_work();

    switch (next) {
    case FSM_BMS_charging_opening_precharge:
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_opening_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_opening_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_opening_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_charging:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_opening_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_opening_precharge_do_work();

    switch (next) {
    case FSM_BMS_charging_charging:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_charging_charging_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_charging_charging_event_handle(event);

    switch (next) {
    case FSM_BMS_charging_charging: // Reentrance is always supported on event handlers
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_charging_charging_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_charging_charging_do_work();

    switch (next) {
    case FSM_BMS_charging_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
    case FSM_BMS_driving_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_idle_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
    case FSM_BMS_driving_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_closing_air_neg: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_closing_precharge:
    case FSM_BMS_driving_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_air_neg_do_work();

    switch (next) {
    case FSM_BMS_driving_closing_precharge:
    case FSM_BMS_driving_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_closing_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_closing_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_resetting_airs_precharge:
    case FSM_BMS_driving_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_closing_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_precharge_do_work();

    switch (next) {
    case FSM_BMS_driving_resetting_airs_precharge:
    case FSM_BMS_driving_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_BMS_active_idle:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_closing_air_pos:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_precharge_do_work();

    switch (next) {
    case FSM_BMS_driving_closing_air_pos:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_closing_air_pos_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_air_pos_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_closing_air_pos: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_resetting_airs_precharge:
    case FSM_BMS_driving_opening_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_closing_air_pos_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_closing_air_pos_do_work();

    switch (next) {
    case FSM_BMS_driving_resetting_airs_precharge:
    case FSM_BMS_driving_opening_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_opening_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_opening_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_opening_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_driving:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_opening_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_opening_precharge_do_work();

    switch (next) {
    case FSM_BMS_driving_driving:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_driving_driving_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_driving_driving_event_handle(event);

    switch (next) {
    case FSM_BMS_driving_driving: // Reentrance is always supported on event handlers
    case FSM_BMS_driving_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_driving_driving_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_driving_driving_do_work();

    switch (next) {
    case FSM_BMS_driving_resetting_airs_precharge:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_ams_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_ams_error_event_handle(event);

    switch (next) {
    case FSM_BMS_ams_error: // Reentrance is always supported on event handlers
    case FSM_BMS_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_ams_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_ams_error_do_work();

    switch (next) {
    case FSM_BMS_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_ams_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_ams_imd_error_event_handle(event);

    switch (next) {
    case FSM_BMS_ams_imd_error: // Reentrance is always supported on event handlers
    case FSM_BMS_resetting_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_ams_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_ams_imd_error_do_work();

    switch (next) {
    case FSM_BMS_resetting_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_event_handle, with exit state checking */
uint32_t _FSM_BMS_imd_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_imd_error_event_handle(event);

    switch (next) {
    case FSM_BMS_imd_error: // Reentrance is always supported on event handlers
    case FSM_BMS_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}

/** @brief wrapper of FSM_BMS_do_work, with exit state checking */
uint32_t _FSM_BMS_imd_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_imd_error_do_work();

    switch (next) {
    case FSM_BMS_ams_imd_error:
        return next;
    default:
        return _FSM_BMS_DIE;
    }
}


// State functions

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_idle_event_handle(uint8_t event) {
    return FSM_BMS_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_idle_do_work() {
    return FSM_BMS_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_active_idle_event_handle(uint8_t event) {
    return FSM_BMS_active_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_active_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_active_idle_do_work() {
    return FSM_BMS_active_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_active_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_resetting_error_event_handle(uint8_t event) {
    return FSM_BMS_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_resetting_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_resetting_error_do_work() {
    return FSM_BMS_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_resetting_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_balancing_event_handle(uint8_t event) {
    return FSM_BMS_balancing;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_balancing_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_balancing_do_work() {
    return FSM_BMS_balancing;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_balancing_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_idle_event_handle(uint8_t event) {
    return FSM_BMS_charging_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_idle_do_work() {
    return FSM_BMS_charging_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_neg_event_handle(uint8_t event) {
    return FSM_BMS_charging_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_air_neg_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_neg_do_work() {
    return FSM_BMS_charging_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_air_neg_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_precharge_event_handle(uint8_t event) {
    return FSM_BMS_charging_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_precharge_do_work() {
    return FSM_BMS_charging_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_resetting_airs_precharge_event_handle(uint8_t event) {
    return FSM_BMS_charging_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_resetting_airs_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_resetting_airs_precharge_do_work() {
    return FSM_BMS_charging_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_resetting_airs_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_precharge_event_handle(uint8_t event) {
    return FSM_BMS_charging_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_precharge_do_work() {
    return FSM_BMS_charging_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_pos_event_handle(uint8_t event) {
    return FSM_BMS_charging_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_air_pos_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_pos_do_work() {
    return FSM_BMS_charging_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_closing_air_pos_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_opening_precharge_event_handle(uint8_t event) {
    return FSM_BMS_charging_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_opening_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_opening_precharge_do_work() {
    return FSM_BMS_charging_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_opening_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_charging_event_handle(uint8_t event) {
    return FSM_BMS_charging_charging;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_charging_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_charging_charging_do_work() {
    return FSM_BMS_charging_charging;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_charging_charging_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_idle_event_handle(uint8_t event) {
    return FSM_BMS_driving_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_idle_do_work() {
    return FSM_BMS_driving_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_neg_event_handle(uint8_t event) {
    return FSM_BMS_driving_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_air_neg_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_neg_do_work() {
    return FSM_BMS_driving_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_air_neg_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_precharge_event_handle(uint8_t event) {
    return FSM_BMS_driving_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_precharge_do_work() {
    return FSM_BMS_driving_closing_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_resetting_airs_precharge_event_handle(uint8_t event) {
    return FSM_BMS_driving_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_resetting_airs_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_resetting_airs_precharge_do_work() {
    return FSM_BMS_driving_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_resetting_airs_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_precharge_event_handle(uint8_t event) {
    return FSM_BMS_driving_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_precharge_do_work() {
    return FSM_BMS_driving_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_pos_event_handle(uint8_t event) {
    return FSM_BMS_driving_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_air_pos_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_pos_do_work() {
    return FSM_BMS_driving_closing_air_pos;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_closing_air_pos_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_opening_precharge_event_handle(uint8_t event) {
    return FSM_BMS_driving_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_opening_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_opening_precharge_do_work() {
    return FSM_BMS_driving_opening_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_opening_precharge_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_driving_event_handle(uint8_t event) {
    return FSM_BMS_driving_driving;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_driving_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_driving_driving_do_work() {
    return FSM_BMS_driving_driving;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_driving_driving_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_ams_error_event_handle(uint8_t event) {
    return FSM_BMS_ams_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_ams_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_ams_error_do_work() {
    return FSM_BMS_ams_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_ams_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_ams_imd_error_event_handle(uint8_t event) {
    return FSM_BMS_ams_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_ams_imd_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_ams_imd_error_do_work() {
    return FSM_BMS_ams_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_ams_imd_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_imd_error_event_handle(uint8_t event) {
    return FSM_BMS_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_imd_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_StateTypeDef FSM_BMS_imd_error_do_work() {
    return FSM_BMS_imd_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_imd_error_exit() {
    return;
}

