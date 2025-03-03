#include <stdlib.h>
#include "BMS_FSM.h"

struct BMS *make_BMS(struct BMS_Actions* actions) {
	struct BMS *fsm = malloc(sizeof(struct BMS));
	fsm->actions = actions;
	fsm->state = power_off;
	return fsm;
}

static void setState(struct BMS *fsm, enum State state) {
	fsm->state = state;
}

static void openAIRs(struct BMS *fsm) {
	fsm->actions->openAIRs();
}

static void closeAIRNegative(struct BMS *fsm) {
	fsm->actions->closeAIRNegative();
}

static void closePrecharge(struct BMS *fsm) {
	fsm->actions->closePrecharge();
}

static void balanceCells(struct BMS *fsm) {
	fsm->actions->balanceCells();
}

static void openAIRPositive(struct BMS *fsm) {
	fsm->actions->openAIRPositive();
}

static void openAIRNegative(struct BMS *fsm) {
	fsm->actions->openAIRNegative();
}

static void openShutdown(struct BMS *fsm) {
	fsm->actions->openShutdown();
}

static void closeAIRPositive(struct BMS *fsm) {
	fsm->actions->closeAIRPositive();
}

static void openPrecharge(struct BMS *fsm) {
	fsm->actions->openPrecharge();
}

static void processEvent(enum State state, enum Event event, struct BMS *fsm, char *event_name) {
switch (state) {
case balancing:
switch (event) {
case DONE_BALANCE_CELLS:
setState(fsm, charging_idle);
break;

case DISCONNECT:
setState(fsm, power_on);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("balancing", event_name);
break;
}
break;

case charging_idle:
switch (event) {
case BALANCING_REQ:
setState(fsm, balancing);
balanceCells(fsm);
break;

case DISCONNECT:
setState(fsm, power_on);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("charging_idle", event_name);
break;
}
break;

case closing_air_neg:
switch (event) {
case DONE_CLOSE_AIR_NEG:
setState(fsm, closing_precharge);
closePrecharge(fsm);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("closing_air_neg", event_name);
break;
}
break;

case closing_air_pos:
switch (event) {
case DONE_CLOSE_AIR_POS:
setState(fsm, opening_precharge);
openPrecharge(fsm);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("closing_air_pos", event_name);
break;
}
break;

case closing_precharge:
switch (event) {
case DONE_PRECHARGE:
setState(fsm, precharged);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("closing_precharge", event_name);
break;
}
break;

case driving:
switch (event) {
case STOP:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("driving", event_name);
break;
}
break;

case fault:
switch (event) {
case DONE_OPEN_AIRS:
setState(fsm, ready_idle);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("fault", event_name);
break;
}
break;

case opening_precharge:
switch (event) {
case DONE_OPEN_PRECHARGE:
setState(fsm, driving);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("opening_precharge", event_name);
break;
}
break;

case power_off:
switch (event) {
case TURN_ON:
setState(fsm, power_on);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("power_off", event_name);
break;
}
break;

case power_on:
switch (event) {
case TURN_OFF:
setState(fsm, power_off);
break;

case CHARGING:
setState(fsm, charging_idle);
break;

case MOUNT_CAR:
setState(fsm, ready_idle);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("power_on", event_name);
break;
}
break;

case precharged:
switch (event) {
case CLOSE_AIR_POS:
setState(fsm, closing_air_pos);
closeAIRPositive(fsm);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("precharged", event_name);
break;
}
break;

case ready_idle:
switch (event) {
case CLOSE_AIRS_REQ:
setState(fsm, closing_air_neg);
closeAIRNegative(fsm);
break;

case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("ready_idle", event_name);
break;
}
break;

case resetting_airs_precharge:
switch (event) {
case UNMOUNT_CAR:
setState(fsm, power_on);
break;

case ERROR_CLOSE_AIR_NEG:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_PRECHARGE:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case ERROR_CLOSE_AIR_POS:
setState(fsm, resetting_airs_precharge);
openAIRPositive(fsm);
openPrecharge(fsm);
openAIRNegative(fsm);
break;

case IMD_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openShutdown(fsm);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("resetting_airs_precharge", event_name);
break;
}
break;

}
}

void BMS_DONE_PRECHARGE(struct BMS* fsm) {
	processEvent(fsm->state, DONE_PRECHARGE, fsm, "DONE_PRECHARGE");
}
void BMS_STOP(struct BMS* fsm) {
	processEvent(fsm->state, STOP, fsm, "STOP");
}
void BMS_DONE_CLOSE_AIR_NEG(struct BMS* fsm) {
	processEvent(fsm->state, DONE_CLOSE_AIR_NEG, fsm, "DONE_CLOSE_AIR_NEG");
}
void BMS_MOUNT_CAR(struct BMS* fsm) {
	processEvent(fsm->state, MOUNT_CAR, fsm, "MOUNT_CAR");
}
void BMS_DONE_CLOSE_AIR_POS(struct BMS* fsm) {
	processEvent(fsm->state, DONE_CLOSE_AIR_POS, fsm, "DONE_CLOSE_AIR_POS");
}
void BMS_DONE_OPEN_PRECHARGE(struct BMS* fsm) {
	processEvent(fsm->state, DONE_OPEN_PRECHARGE, fsm, "DONE_OPEN_PRECHARGE");
}
void BMS_UNMOUNT_CAR(struct BMS* fsm) {
	processEvent(fsm->state, UNMOUNT_CAR, fsm, "UNMOUNT_CAR");
}
void BMS_ERROR_CLOSE_AIR_POS(struct BMS* fsm) {
	processEvent(fsm->state, ERROR_CLOSE_AIR_POS, fsm, "ERROR_CLOSE_AIR_POS");
}
void BMS_CHARGING(struct BMS* fsm) {
	processEvent(fsm->state, CHARGING, fsm, "CHARGING");
}
void BMS_DONE_BALANCE_CELLS(struct BMS* fsm) {
	processEvent(fsm->state, DONE_BALANCE_CELLS, fsm, "DONE_BALANCE_CELLS");
}
void BMS_ERROR_CLOSE_AIR_NEG(struct BMS* fsm) {
	processEvent(fsm->state, ERROR_CLOSE_AIR_NEG, fsm, "ERROR_CLOSE_AIR_NEG");
}
void BMS_BALANCING_REQ(struct BMS* fsm) {
	processEvent(fsm->state, BALANCING_REQ, fsm, "BALANCING_REQ");
}
void BMS_TURN_OFF(struct BMS* fsm) {
	processEvent(fsm->state, TURN_OFF, fsm, "TURN_OFF");
}
void BMS_ERROR_PRECHARGE(struct BMS* fsm) {
	processEvent(fsm->state, ERROR_PRECHARGE, fsm, "ERROR_PRECHARGE");
}
void BMS_CLOSE_AIRS_REQ(struct BMS* fsm) {
	processEvent(fsm->state, CLOSE_AIRS_REQ, fsm, "CLOSE_AIRS_REQ");
}
void BMS_CLOSE_AIR_POS(struct BMS* fsm) {
	processEvent(fsm->state, CLOSE_AIR_POS, fsm, "CLOSE_AIR_POS");
}
void BMS_DONE_OPEN_AIRS(struct BMS* fsm) {
	processEvent(fsm->state, DONE_OPEN_AIRS, fsm, "DONE_OPEN_AIRS");
}
void BMS_DISCONNECT(struct BMS* fsm) {
	processEvent(fsm->state, DISCONNECT, fsm, "DISCONNECT");
}
void BMS_IMD_ERROR(struct BMS* fsm) {
	processEvent(fsm->state, IMD_ERROR, fsm, "IMD_ERROR");
}
void BMS_TURN_ON(struct BMS* fsm) {
	processEvent(fsm->state, TURN_ON, fsm, "TURN_ON");
}
void BMS_AMS_ERROR(struct BMS* fsm) {
	processEvent(fsm->state, AMS_ERROR, fsm, "AMS_ERROR");
}
