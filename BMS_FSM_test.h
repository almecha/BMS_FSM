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

#ifndef FSM_TEST1_H
#define FSM_TEST1_H

#include "fsm.h"

enum FSM_TEST1_StateEnum {
    FSM_TEST1_start = 0,
    FSM_TEST1_idle = 1,
    FSM_TEST1_resetting_error = 2,
    FSM_TEST1_closing_air_neg = 3,
    FSM_TEST1_resetting_airs_precharge = 4,
    FSM_TEST1_balancing = 5,
    FSM_TEST1_closing_precharge = 6,
    FSM_TEST1_precharge = 7,
    FSM_TEST1_closing_air_pos = 8,
    FSM_TEST1_opening_precharge = 9,
    FSM_TEST1_charging = 10,
    FSM_TEST1_driving = 11,
    FSM_TEST1_ams_error = 12,
    FSM_TEST1_ams_imd_error = 13,
    FSM_TEST1_imd_error = 14,

    _FSM_TEST1_STATE_COUNT = 15,

    /** @brief Invalid state, leads to irrecoverable error i.e. hard fault */
    _FSM_TEST1_DIE = 16
};

typedef enum FSM_TEST1_StateEnum FSM_TEST1_StateTypeDef;

/**
 * @brief
 * @param handle FSM handle
 * @param event_count number of events
 * @param run_callback callback of a run event
 * @param transition_callback callback of a transition event
 * @return status
 */
STMLIBS_StatusTypeDef FSM_TEST1_init(
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
FSM_TEST1_StateTypeDef FSM_TEST1_start_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_start_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_start_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_start_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_resetting_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_resetting_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_resetting_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_resetting_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_neg_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_air_neg_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_neg_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_air_neg_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_resetting_airs_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_resetting_airs_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_resetting_airs_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_resetting_airs_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_balancing_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_balancing_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_balancing_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_balancing_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_pos_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_air_pos_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_closing_air_pos_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_closing_air_pos_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_opening_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_opening_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_opening_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_opening_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_charging_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_charging_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_charging_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_charging_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_driving_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_driving_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_driving_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_driving_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_ams_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_ams_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_ams_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_ams_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_ams_imd_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_ams_imd_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_ams_imd_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_ams_imd_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_imd_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_imd_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_TEST1_StateTypeDef FSM_TEST1_imd_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_TEST1_imd_error_exit();


#endif // FSM_TEST1_H