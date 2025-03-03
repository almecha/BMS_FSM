#include "BMS.h"


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

static void balanceCells(struct BMS *fsm) {
	fsm->actions->balanceCells();
}

static void processEvent(enum State state, enum Event event, struct BMS *fsm, char *event_name) {

switch (state) {	// Switching between the states

case balancing:

switch (event) {	// Switching between the events of the particular state
case DONE_BALANCE_CELLS:
setState(fsm, charging_idle);
break;

case DISCONNECT:
setState(fsm, power_on);
break;

case IMD_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
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
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

default:	// In case no event happens return back to the current state
(fsm->actions->unexpected_transition)("charging_idle", event_name);
break;
}
break;

case fault:
switch (event) {
case DONE_OPEN_AIRS:
setState(fsm, power_on);
break;

case IMD_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("fault", event_name);
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
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
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

case IMD_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

case AMS_ERROR:
setState(fsm, fault);
openAIRs(fsm);
break;

default:
(fsm->actions->unexpected_transition)("power_on", event_name);
break;
}
break;

}
}

void BMS_BALANCING_REQ(struct BMS* fsm) {
	processEvent(fsm->state, BALANCING_REQ, fsm, "BALANCING_REQ");
}
void BMS_TURN_OFF(struct BMS* fsm) {
	processEvent(fsm->state, TURN_OFF, fsm, "TURN_OFF");
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
void BMS_CHARGING(struct BMS* fsm) {
	processEvent(fsm->state, CHARGING, fsm, "CHARGING");
}
void BMS_DONE_BALANCE_CELLS(struct BMS* fsm) {
	processEvent(fsm->state, DONE_BALANCE_CELLS, fsm, "DONE_BALANCE_CELLS");
}
void BMS_AMS_ERROR(struct BMS* fsm) {
	processEvent(fsm->state, AMS_ERROR, fsm, "AMS_ERROR");
}
