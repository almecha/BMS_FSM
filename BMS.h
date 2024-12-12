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

#ifndef FSM_BMS_H
#define FSM_BMS_H

#include "fsm.h"

enum FSM_BMS_StateEnum {
    FSM_BMS_idle = 0,
    FSM_BMS_active_idle = 1,
    FSM_BMS_resetting_error = 2,
    FSM_BMS_balancing = 3,
    FSM_BMS_charging_idle = 4,
    FSM_BMS_charging_closing_air_neg = 5,
    FSM_BMS_charging_closing_precharge = 6,
    FSM_BMS_charging_resetting_airs_precharge = 7,
    FSM_BMS_charging_precharge = 8,
    FSM_BMS_charging_closing_air_pos = 9,
    FSM_BMS_charging_opening_precharge = 10,
    FSM_BMS_charging_charging = 11,
    FSM_BMS_driving_idle = 12,
    FSM_BMS_driving_closing_air_neg = 13,
    FSM_BMS_driving_closing_precharge = 14,
    FSM_BMS_driving_resetting_airs_precharge = 15,
    FSM_BMS_driving_precharge = 16,
    FSM_BMS_driving_closing_air_pos = 17,
    FSM_BMS_driving_opening_precharge = 18,
    FSM_BMS_driving_driving = 19,
    FSM_BMS_ams_error = 20,
    FSM_BMS_ams_imd_error = 21,
    FSM_BMS_imd_error = 22,

    _FSM_BMS_STATE_COUNT = 23,

    /** @brief Invalid state, leads to irrecoverable error i.e. hard fault */
    _FSM_BMS_DIE = 24
};

typedef enum FSM_BMS_StateEnum FSM_BMS_StateTypeDef;

/**
 * @brief
 * @param handle FSM handle
 * @param event_count number of events
 * @param run_callback callback of a run event
 * @param transition_callback callback of a transition event
 * @return status
 */
STMLIBS_StatusTypeDef FSM_BMS_init(
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
FSM_BMS_StateTypeDef FSM_BMS_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_active_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_active_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_active_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_active_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_resetting_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_resetting_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_resetting_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_resetting_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_balancing_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_balancing_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_balancing_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_balancing_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_neg_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_air_neg_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_neg_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_air_neg_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_resetting_airs_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_resetting_airs_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_resetting_airs_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_resetting_airs_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_pos_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_air_pos_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_closing_air_pos_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_closing_air_pos_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_opening_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_opening_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_opening_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_opening_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_charging_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_charging_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_charging_charging_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_charging_charging_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_idle_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_idle_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_idle_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_idle_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_neg_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_air_neg_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_neg_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_air_neg_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_resetting_airs_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_resetting_airs_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_resetting_airs_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_resetting_airs_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_pos_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_air_pos_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_closing_air_pos_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_closing_air_pos_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_opening_precharge_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_opening_precharge_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_opening_precharge_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_opening_precharge_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_driving_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_driving_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_driving_driving_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_driving_driving_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_ams_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_ams_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_ams_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_ams_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_ams_imd_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_ams_imd_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_ams_imd_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_ams_imd_error_exit();

/**
 * @brief
 * @param handle FSM handle
 * @param event event
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_imd_error_event_handle(uint8_t event);

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_imd_error_entry();

/**
 * @brief
 * @param handle FSM handle
 * @return next state
 */
FSM_BMS_StateTypeDef FSM_BMS_imd_error_do_work();

/**
 * @brief
 * @param handle FSM handle
 */
void FSM_BMS_imd_error_exit();


#endif // FSM_BMS_H