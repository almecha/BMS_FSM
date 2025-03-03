#ifndef BMS_ACTIONS_H
#define BMS_ACTIONS_H

struct BMS_Actions {
	void (*openAIRs)();
	void (*balanceCells)();
    void (*closeAIRNegative)();
    void (*closePrecharge)();
    void (*openAIRPositive)();
    void (*openAIRNegative)();
    void (*closeAIRPositive)();
    void (*openPrecharge)();
    void (*openShutdown)();
	void (*unexpected_transition)(char* state, char* event);
};

#endif