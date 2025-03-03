#include <stdio.h>
#include "BMS.h"

// Define the actions
void openAIRs() {
    printf("Opening AIRs\n");
}

void balanceCells() {
    printf("Balancing cells\n");
}

void unexpected_transition(char* state, char* event) {
    printf("Unexpected transition from state %s on event %s\n", state, event);
}

int main() {
    // Initialize the actions
    struct BMS_Actions actions = {openAIRs, balanceCells, unexpected_transition};

    // Create the BMS instance
    struct BMS *bms = make_BMS(&actions);

    // Test the state machine by triggering various events
    printf("Initial state: power_off\n");

    BMS_TURN_ON(bms);
    printf("State after TURN_ON: %d\n", bms->state); // Expected: power_on

    BMS_CHARGING(bms);
    printf("State after CHARGING: %d\n", bms->state); // Expected: charging_idle

    BMS_BALANCING_REQ(bms);
    printf("State after BALANCING_REQ: %d\n", bms->state); // Expected: balancing

    BMS_DONE_BALANCE_CELLS(bms);
    printf("State after DONE_BALANCE_CELLS: %d\n", bms->state); // Expected: charging_idle

    BMS_DISCONNECT(bms);
    printf("State after DISCONNECT: %d\n", bms->state); // Expected: power_on

    BMS_IMD_ERROR(bms);
    printf("State after IMD_ERROR: %d\n", bms->state); // Expected: fault

    BMS_DONE_OPEN_AIRS(bms);
    printf("State after DONE_OPEN_AIRS: %d\n", bms->state); // Expected: power_on

    // Free the BMS instance
    free(bms);

    return 0;
}