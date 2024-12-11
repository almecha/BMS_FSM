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

#include "subgraph_test.h"

#ifndef __weak
#define __weak __attribute__((weak))
#endif // __weak

// Private wrapper function signatures

uint32_t _FSM_SUBGRAPH_TEST_start_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_start_do_work();

uint32_t _FSM_SUBGRAPH_TEST_a0_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_a0_do_work();

uint32_t _FSM_SUBGRAPH_TEST_b0_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_b0_do_work();

uint32_t _FSM_SUBGRAPH_TEST_a1_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_a1_do_work();

uint32_t _FSM_SUBGRAPH_TEST_b3_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_b3_do_work();

uint32_t _FSM_SUBGRAPH_TEST_b2_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_b2_do_work();

uint32_t _FSM_SUBGRAPH_TEST_a3_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_a3_do_work();

uint32_t _FSM_SUBGRAPH_TEST_end_event_handle(uint8_t event);
uint32_t _FSM_SUBGRAPH_TEST_end_do_work();


FSM_StateTypeDef state_table[_FSM_SUBGRAPH_TEST_STATE_COUNT] = {
    [FSM_SUBGRAPH_TEST_start] = {
        .event_handler = _FSM_SUBGRAPH_TEST_start_event_handle,
        .entry = FSM_SUBGRAPH_TEST_start_entry,
        .do_work = _FSM_SUBGRAPH_TEST_start_do_work,
        .exit = FSM_SUBGRAPH_TEST_start_exit,
    },
    [FSM_SUBGRAPH_TEST_a0] = {
        .event_handler = _FSM_SUBGRAPH_TEST_a0_event_handle,
        .entry = FSM_SUBGRAPH_TEST_a0_entry,
        .do_work = _FSM_SUBGRAPH_TEST_a0_do_work,
        .exit = FSM_SUBGRAPH_TEST_a0_exit,
    },
    [FSM_SUBGRAPH_TEST_b0] = {
        .event_handler = _FSM_SUBGRAPH_TEST_b0_event_handle,
        .entry = FSM_SUBGRAPH_TEST_b0_entry,
        .do_work = _FSM_SUBGRAPH_TEST_b0_do_work,
        .exit = FSM_SUBGRAPH_TEST_b0_exit,
    },
    [FSM_SUBGRAPH_TEST_a1] = {
        .event_handler = _FSM_SUBGRAPH_TEST_a1_event_handle,
        .entry = FSM_SUBGRAPH_TEST_a1_entry,
        .do_work = _FSM_SUBGRAPH_TEST_a1_do_work,
        .exit = FSM_SUBGRAPH_TEST_a1_exit,
    },
    [FSM_SUBGRAPH_TEST_b3] = {
        .event_handler = _FSM_SUBGRAPH_TEST_b3_event_handle,
        .entry = FSM_SUBGRAPH_TEST_b3_entry,
        .do_work = _FSM_SUBGRAPH_TEST_b3_do_work,
        .exit = FSM_SUBGRAPH_TEST_b3_exit,
    },
    [FSM_SUBGRAPH_TEST_b2] = {
        .event_handler = _FSM_SUBGRAPH_TEST_b2_event_handle,
        .entry = FSM_SUBGRAPH_TEST_b2_entry,
        .do_work = _FSM_SUBGRAPH_TEST_b2_do_work,
        .exit = FSM_SUBGRAPH_TEST_b2_exit,
    },
    [FSM_SUBGRAPH_TEST_a3] = {
        .event_handler = _FSM_SUBGRAPH_TEST_a3_event_handle,
        .entry = FSM_SUBGRAPH_TEST_a3_entry,
        .do_work = _FSM_SUBGRAPH_TEST_a3_do_work,
        .exit = FSM_SUBGRAPH_TEST_a3_exit,
    },
    [FSM_SUBGRAPH_TEST_end] = {
        .event_handler = _FSM_SUBGRAPH_TEST_end_event_handle,
        .entry = FSM_SUBGRAPH_TEST_end_entry,
        .do_work = _FSM_SUBGRAPH_TEST_end_do_work,
        .exit = FSM_SUBGRAPH_TEST_end_exit,
    },
};

FSM_ConfigTypeDef config = {
    .state_length = _FSM_SUBGRAPH_TEST_STATE_COUNT,
    .state_table = state_table,
};

STMLIBS_StatusTypeDef FSM_SUBGRAPH_TEST_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
) {
    return FSM_init(handle, &config, event_count, run_callback, transition_callback);
}

// State control functions

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_start_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_start_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_start: // Reentrance is always supported on event handlers
    case FSM_SUBGRAPH_TEST_a0:
    case FSM_SUBGRAPH_TEST_b0:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_start_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_start_do_work();

    switch (next) {
    case FSM_SUBGRAPH_TEST_a0:
    case FSM_SUBGRAPH_TEST_b0:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a0_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a0_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_a0: // Reentrance is always supported on event handlers
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a0_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a0_do_work();

    switch (next) {
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b0_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b0_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_b0: // Reentrance is always supported on event handlers
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b0_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b0_do_work();

    switch (next) {
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a1_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a1_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_a1: // Reentrance is always supported on event handlers
    case FSM_SUBGRAPH_TEST_b3:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a1_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a1_do_work();

    switch (next) {
    case FSM_SUBGRAPH_TEST_b3:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b3_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b3_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_b3: // Reentrance is always supported on event handlers
    case FSM_SUBGRAPH_TEST_end:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b3_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b3_do_work();

    switch (next) {
    case FSM_SUBGRAPH_TEST_end:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b2_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b2_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_b2: // Reentrance is always supported on event handlers
    case FSM_SUBGRAPH_TEST_a3:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_b2_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_b2_do_work();

    switch (next) {
    case FSM_SUBGRAPH_TEST_a3:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a3_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a3_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_a3: // Reentrance is always supported on event handlers
    case FSM_SUBGRAPH_TEST_a0:
    case FSM_SUBGRAPH_TEST_end:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_a3_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_a3_do_work();

    switch (next) {
    case FSM_SUBGRAPH_TEST_a0:
    case FSM_SUBGRAPH_TEST_end:
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_event_handle, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_end_event_handle(uint8_t event) {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_end_event_handle(event);

    switch (next) {
    case FSM_SUBGRAPH_TEST_end: // Reentrance is always supported on event handlers
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}

/** @brief wrapper of FSM_SUBGRAPH_TEST_do_work, with exit state checking */
uint32_t _FSM_SUBGRAPH_TEST_end_do_work() {
    uint32_t next = (uint32_t)FSM_SUBGRAPH_TEST_end_do_work();

    switch (next) {
        return next;
    default:
        return _FSM_SUBGRAPH_TEST_DIE;
    }
}


// State functions

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_start_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_start_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_start_do_work() {
    return FSM_SUBGRAPH_TEST_start;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_start_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a0_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_a0;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a0_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a0_do_work() {
    return FSM_SUBGRAPH_TEST_a0;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a0_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b0_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_b0;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b0_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b0_do_work() {
    return FSM_SUBGRAPH_TEST_b0;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b0_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a1_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_a1;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a1_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a1_do_work() {
    return FSM_SUBGRAPH_TEST_a1;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a1_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b3_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_b3;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b3_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b3_do_work() {
    return FSM_SUBGRAPH_TEST_b3;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b3_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b2_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_b2;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b2_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b2_do_work() {
    return FSM_SUBGRAPH_TEST_b2;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_b2_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a3_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_a3;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a3_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a3_do_work() {
    return FSM_SUBGRAPH_TEST_a3;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_a3_exit() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_end_event_handle(uint8_t event) {
    return FSM_SUBGRAPH_TEST_end;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_end_entry() {
    return;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_end_do_work() {
    return FSM_SUBGRAPH_TEST_end;
}

/** @attention this function is a stub and as such is declared as weak. */
__weak void FSM_SUBGRAPH_TEST_end_exit() {
    return;
}

