#ifndef ALARM_CONTROLER_H_
#define ALARM_CONTROLER_H_

void handle_change_s(char *sensor_state);
void liga_desliga_alarme();
void *play_audio();
void set_interface(void *inter);

#endif