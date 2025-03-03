#ifndef BMS_H
#define BMS_H
#include "BMS_Actions.h"
#include <stdlib.h>


enum Event {BALANCING_REQ,TURN_OFF,DONE_OPEN_AIRS,DISCONNECT,IMD_ERROR,TURN_ON,CHARGING,DONE_BALANCE_CELLS,AMS_ERROR};
enum State {balancing,charging_idle,fault,power_off,power_on};

struct BMS {
	enum State state;
	struct BMS_Actions *actions;
};
struct BMS *make_BMS(struct BMS_Actions*);
void BMS_BALANCING_REQ(struct BMS*);
void BMS_TURN_OFF(struct BMS*);
void BMS_DONE_OPEN_AIRS(struct BMS*);
void BMS_DISCONNECT(struct BMS*);
void BMS_IMD_ERROR(struct BMS*);
void BMS_TURN_ON(struct BMS*);
void BMS_CHARGING(struct BMS*);
void BMS_DONE_BALANCE_CELLS(struct BMS*);
void BMS_AMS_ERROR(struct BMS*);
#endif
