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

#ifndef FSM_TEST_H
#define FSM_TEST_H

#include "fsm.h"

enum FSM_TEST_StateEnum {
    FSM_TEST_idle = 0,
    FSM_TEST_closing_air_neg = 1,
    FSM_TEST_closing_precharge = 2,
    FSM_TEST_resetting_airs_precharge = 3,
    FSM_TEST_precharge = 4,
    FSM_TEST_closing_air_pos = 5,
    FSM_TEST_opening_precharge = 6,
    FSM_TEST_driving = 7,

    _FSM_TEST_STATE_COUNT = 8,

    /** @brief Invalid state, leads to irrecoverable error i.e. hard fault */
    _FSM_TEST_DIE = 9
};

typedef enum FSM_TEST_StateEnum FSM_TEST_StateTypeDef;

/**
 * @brief
 * @param handle FSM handle
 * @param event_count number of events
 * @param run_callback callback of a run event
 * @param transition_callback callback of a transition event
 * @return status
 */
STMLIBS_StatusTypeDef FSM_TEST_init(
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
FSM_TEST_StateTypeDef FSM_TEST_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_air_neg_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_air_neg_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_air_neg_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_air_neg_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_resetting_airs_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_resetting_airs_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_resetting_airs_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_resetting_airs_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_air_pos_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_air_pos_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_closing_air_pos_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_closing_air_pos_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_opening_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_opening_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_opening_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_opening_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_driving_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_driving_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST_StateTypeDef FSM_TEST_driving_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST_driving_exit();


#endif // FSM_TEST_H