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

#ifndef FSM_SUBGRAPH_TEST_H
#define FSM_SUBGRAPH_TEST_H

#include "fsm.h"

enum FSM_SUBGRAPH_TEST_StateEnum {
    FSM_SUBGRAPH_TEST_start = 0,
    FSM_SUBGRAPH_TEST_a0 = 1,
    FSM_SUBGRAPH_TEST_b0 = 2,
    FSM_SUBGRAPH_TEST_a1 = 3,
    FSM_SUBGRAPH_TEST_b3 = 4,
    FSM_SUBGRAPH_TEST_b2 = 5,
    FSM_SUBGRAPH_TEST_a3 = 6,
    FSM_SUBGRAPH_TEST_end = 7,

    _FSM_SUBGRAPH_TEST_STATE_COUNT = 8,

    /** @brief Invalid state, leads to irrecoverable error i.e. hard fault */
    _FSM_SUBGRAPH_TEST_DIE = 9
};

typedef enum FSM_SUBGRAPH_TEST_StateEnum FSM_SUBGRAPH_TEST_StateTypeDef;

/**
 * @brief
 * @param handle FSM handle
 * @param event_count number of events
 * @param run_callback callback of a run event
 * @param transition_callback callback of a transition event
 * @return status
 */
STMLIBS_StatusTypeDef FSM_SUBGRAPH_TEST_init(
    FSM_HandleTypeDef *handle,
    uint8_t event_count,
    FSM_callback_function run_callback,
    FSM_callback_function transition_callback
);

// State functions

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_start_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_start_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_start_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_start_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a0_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a0_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a0_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a0_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b0_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b0_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b0_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b0_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a1_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a1_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a1_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a1_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b3_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b3_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b3_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b3_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b2_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b2_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_b2_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_b2_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a3_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a3_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_a3_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_a3_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_end_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_end_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_SUBGRAPH_TEST_StateTypeDef FSM_SUBGRAPH_TEST_end_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_SUBGRAPH_TEST_end_exit();


#endif // FSM_SUBGRAPH_TEST_H