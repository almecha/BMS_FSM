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

#include "BMS_FSM_test.h"

#ifndef __weak
#define __weak __attribute__((weak))
#endif // __weak

// Private wrapper function signatures

uint32_t _FSM_BMS_FSM_TEST_start_event_handle(uint8_t event);
uint32_t _FSM_BMS_FSM_TEST_start_do_work();

uint32_t _FSM_BMS_FSM_TEST_idle_event_handle(uint8_t event);
uint32_t _FSM_BMS_FSM_TEST_idle_do_work();

uint32_t _FSM_BMS_FSM_TEST_resetting_error_event_handle(uint8_t event);
uint32_t _FSM_BMS_FSM_TEST_resetting_error_do_work();

uint32_t _FSM_BMS_FSM_TEST_closing_air_neg_event_handle(uint8_t event);
uint32_t _FSM_BMS_FSM_TEST_closing_air_neg_do_work();

uint32_t _FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle(uint8_t event);
uint32_t _FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work();


FSM_StateTypeDef state_table[_FSM_BMS_FSM_TEST_STATE_COUNT] = {
    [FSM_BMS_FSM_TEST_start] = {
        .event_handler = _FSM_BMS_FSM_TEST_start_event_handle,
        .entry = FSM_BMS_FSM_TEST_start_entry,
        .do_work = _FSM_BMS_FSM_TEST_start_do_work,
        .exit = FSM_BMS_FSM_TEST_start_exit,
    },
    [FSM_BMS_FSM_TEST_idle] = {
        .event_handler = _FSM_BMS_FSM_TEST_idle_event_handle,
        .entry = FSM_BMS_FSM_TEST_idle_entry,
        .do_work = _FSM_BMS_FSM_TEST_idle_do_work,
        .exit = FSM_BMS_FSM_TEST_idle_exit,
    },
    [FSM_BMS_FSM_TEST_resetting_error] = {
        .event_handler = _FSM_BMS_FSM_TEST_resetting_error_event_handle,
        .entry = FSM_BMS_FSM_TEST_resetting_error_entry,
        .do_work = _FSM_BMS_FSM_TEST_resetting_error_do_work,
        .exit = FSM_BMS_FSM_TEST_resetting_error_exit,
    },
    [FSM_BMS_FSM_TEST_closing_air_neg] = {
        .event_handler = _FSM_BMS_FSM_TEST_closing_air_neg_event_handle,
        .entry = FSM_BMS_FSM_TEST_closing_air_neg_entry,
        .do_work = _FSM_BMS_FSM_TEST_closing_air_neg_do_work,
        .exit = FSM_BMS_FSM_TEST_closing_air_neg_exit,
    },
    [FSM_BMS_FSM_TEST_resetting_airs_precharge] = {
        .event_handler = _FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle,
        .entry = FSM_BMS_FSM_TEST_resetting_airs_precharge_entry,
        .do_work = _FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work,
        .exit = FSM_BMS_FSM_TEST_resetting_airs_precharge_exit,
    },
};

FSM_ConfigTypeDef config = {
    .state_length = _FSM_BMS_FSM_TEST_STATE_COUNT,
    .state_table = state_table,
};

STMLIBS_StatusTypeDef FSM_BMS_FSM_TEST_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
) {
    return FSM_init(handle, &config, event_count, run_callback, transition_callback);
}

// State control functions

/** @brief wrapper of FSM_BMS_FSM_TEST_event_handle, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_start_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_start_event_handle(event);

    switch (next) {
    case FSM_BMS_FSM_TEST_start: // Reentrance is always supported on event handlers
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_do_work, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_start_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_start_do_work();

    switch (next) {
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_event_handle, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_idle_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_idle_event_handle(event);

    switch (next) {
    case FSM_BMS_FSM_TEST_idle: // Reentrance is always supported on event handlers
    case FSM_BMS_FSM_TEST_closing_air_neg:
    case FSM_BMS_FSM_TEST_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_do_work, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_idle_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_idle_do_work();

    switch (next) {
    case FSM_BMS_FSM_TEST_closing_air_neg:
    case FSM_BMS_FSM_TEST_closing_air_neg:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_event_handle, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_resetting_error_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_resetting_error_event_handle(event);

    switch (next) {
    case FSM_BMS_FSM_TEST_resetting_error: // Reentrance is always supported on event handlers
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_do_work, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_resetting_error_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_resetting_error_do_work();

    switch (next) {
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_event_handle, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_closing_air_neg_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_closing_air_neg_event_handle(event);

    switch (next) {
    case FSM_BMS_FSM_TEST_closing_air_neg: // Reentrance is always supported on event handlers
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_do_work, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_closing_air_neg_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_closing_air_neg_do_work();

    switch (next) {
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_event_handle, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle(event);

    switch (next) {
    case FSM_BMS_FSM_TEST_resetting_airs_precharge: // Reentrance is always supported on event handlers
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}

/** @brief wrapper of FSM_BMS_FSM_TEST_do_work, with exit state checking */
uint32_t _FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work() {
    uint32_t next = (uint32_t)FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work();

    switch (next) {
    case FSM_BMS_FSM_TEST_idle:
        return next;
    default:
        return _FSM_BMS_FSM_TEST_DIE;
    }
}


// State functions

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_start_event_handle(uint8_t event) {
    return FSM_BMS_FSM_TEST_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_start_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_start_do_work() {
    return FSM_BMS_FSM_TEST_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_start_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_idle_event_handle(uint8_t event) {
    return FSM_BMS_FSM_TEST_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_idle_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_idle_do_work() {
    return FSM_BMS_FSM_TEST_idle;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_idle_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_error_event_handle(uint8_t event) {
    return FSM_BMS_FSM_TEST_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_resetting_error_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_error_do_work() {
    return FSM_BMS_FSM_TEST_resetting_error;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_resetting_error_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_closing_air_neg_event_handle(uint8_t event) {
    return FSM_BMS_FSM_TEST_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_closing_air_neg_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_closing_air_neg_do_work() {
    return FSM_BMS_FSM_TEST_closing_air_neg;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_closing_air_neg_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle(uint8_t event) {
    return FSM_BMS_FSM_TEST_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_resetting_airs_precharge_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work() {
    return FSM_BMS_FSM_TEST_resetting_airs_precharge;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_BMS_FSM_TEST_resetting_airs_precharge_exit() {
    return;
}

