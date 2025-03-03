#ifndef BMS_H
#define BMS_H
#include "BMS_Actions.h"

struct BMS_Actions;

enum Event {DONE_PRECHARGE,STOP,DONE_CLOSE_AIR_NEG,MOUNT_CAR,DONE_CLOSE_AIR_POS,DONE_OPEN_PRECHARGE,UNMOUNT_CAR,ERROR_CLOSE_AIR_POS,CHARGING,DONE_BALANCE_CELLS,ERROR_CLOSE_AIR_NEG,BALANCING_REQ,TURN_OFF,ERROR_PRECHARGE,CLOSE_AIRS_REQ,CLOSE_AIR_POS,DONE_OPEN_AIRS,DISCONNECT,IMD_ERROR,TURN_ON,AMS_ERROR};
enum State {balancing,charging_idle,closing_air_neg,closing_air_pos,closing_precharge,driving,fault,opening_precharge,power_off,power_on,precharged,ready_idle,resetting_airs_precharge};

struct BMS {
	enum State state;
	struct BMS_Actions *actions;
};
struct BMS *make_BMS(struct BMS_Actions*);
void BMS_DONE_PRECHARGE(struct BMS*);
void BMS_STOP(struct BMS*);
void BMS_DONE_CLOSE_AIR_NEG(struct BMS*);
void BMS_MOUNT_CAR(struct BMS*);
void BMS_DONE_CLOSE_AIR_POS(struct BMS*);
void BMS_DONE_OPEN_PRECHARGE(struct BMS*);
void BMS_UNMOUNT_CAR(struct BMS*);
void BMS_ERROR_CLOSE_AIR_POS(struct BMS*);
void BMS_CHARGING(struct BMS*);
void BMS_DONE_BALANCE_CELLS(struct BMS*);
void BMS_ERROR_CLOSE_AIR_NEG(struct BMS*);
void BMS_BALANCING_REQ(struct BMS*);
void BMS_TURN_OFF(struct BMS*);
void BMS_ERROR_PRECHARGE(struct BMS*);
void BMS_CLOSE_AIRS_REQ(struct BMS*);
void BMS_CLOSE_AIR_POS(struct BMS*);
void BMS_DONE_OPEN_AIRS(struct BMS*);
void BMS_DISCONNECT(struct BMS*);
void BMS_IMD_ERROR(struct BMS*);
void BMS_TURN_ON(struct BMS*);
void BMS_AMS_ERROR(struct BMS*);
#endif
