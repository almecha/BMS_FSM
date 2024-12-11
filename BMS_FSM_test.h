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

#ifndef FSM_BMS_FSM_TEST_H
#define FSM_BMS_FSM_TEST_H

#include "fsm.h"

enum FSM_BMS_FSM_TEST_StateEnum {
    FSM_BMS_FSM_TEST_start = 0,
    FSM_BMS_FSM_TEST_idle = 1,
    FSM_BMS_FSM_TEST_resetting_error = 2,
    FSM_BMS_FSM_TEST_closing_air_neg = 3,
    FSM_BMS_FSM_TEST_resetting_airs_precharge = 4,

    _FSM_BMS_FSM_TEST_STATE_COUNT = 5,

    /** @brief Invalid state, leads to irrecoverable error i.e. hard fault */
    _FSM_BMS_FSM_TEST_DIE = 6
};

typedef enum FSM_BMS_FSM_TEST_StateEnum FSM_BMS_FSM_TEST_StateTypeDef;

/**
 * @brief
 * @param handle FSM handle
 * @param event_count number of events
 * @param run_callback callback of a run event
 * @param transition_callback callback of a transition event
 * @return status
 */
STMLIBS_StatusTypeDef FSM_BMS_FSM_TEST_init(
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
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_start_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_start_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_start_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_start_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_resetting_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_resetting_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_closing_air_neg_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_closing_air_neg_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_closing_air_neg_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_closing_air_neg_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_airs_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_resetting_airs_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_FSM_TEST_StateTypeDef FSM_BMS_FSM_TEST_resetting_airs_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_FSM_TEST_resetting_airs_precharge_exit();


#endif // FSM_BMS_FSM_TEST_H