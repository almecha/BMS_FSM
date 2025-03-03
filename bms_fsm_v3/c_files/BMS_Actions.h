#ifndef BMS_ACTIONS_H
#define BMS_ACTIONS_H

struct BMS_Actions {
	void (*openAIRs)();
	void (*balanceCells)();
	void (*unexpected_transition)(char* state, char* event);
};

#endif