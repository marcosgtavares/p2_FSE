#ifndef GPIO_H_
#define GPIO_H_

void handle_initial(int signum);
void sensor_state_atualize(char *current);
void on_off_gadgets(char gadget, char on_off);
void initial_state(char *currentI, char *currentO);
void *wsensor_change();



#endif