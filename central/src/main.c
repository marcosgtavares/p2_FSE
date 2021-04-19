#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <signal.h>
#include <ncurses.h>

#include "../inc/server.h"
#include "../inc/client.h"
#include "../inc/alarm_controler.h"
#include "../inc/w_interface.h"


int sockets;
char *ret;
struct input_params *th;
struct input_params *commands;

struct sckt_sstate{
    int sockets;
    char sstates[9];
};

struct input_params{
    char command[30];
    char ret[16];
    WINDOW *input;
    WINDOW *interface;
};

void end_exec(int sigint){
    close(sockets);
    free(th);
    free(ret);
    free(commands);
    endwin();
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGINT, end_exec);
    signal(SIGTSTP, end_exec);

    unsigned short servD = 10122;
    unsigned short servC = 10022;

    pthread_t alarm_watcher, temp_humidity, input_bar;
    int sockets = open_socket(servC);

    struct sckt_sstate *alarm_params = (struct sckt_sstate *)malloc(sizeof(struct sckt_sstate));

    alarm_params->sockets=sockets;

    ret=(char *)malloc(sizeof(char)*16);
    
    commands=(struct input_params *)malloc(sizeof(struct input_params));

    th=(struct input_params *)malloc(sizeof(struct input_params));
    //th=(char *)malloc(sizeof(char)*16);

    initscr();// Incia a janela do ncurses

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
 
    WINDOW *interface = newwin(10,50,max_y/2-5,max_x/2-25);
    WINDOW *input = newwin(4,50,max_y/2+5,max_x/2-25);

    set_interface((void *)interface);

    pthread_create(&alarm_watcher, NULL, treat_messages, (void *)alarm_params); 

    pthread_create(&temp_humidity, NULL, te_hum, (void *)th);

    int cliente;

    cliente = connect_server(servD, "192.168.0.4");
    usleep(10000);
    send_message("I", cliente, ret);
    
    

    

    commands->input = input;
    commands->interface = interface;

    refresh();
    box(interface, 0, 0); box(input, 0, 0);

    mvwprintw(interface, 1, 2, "SP1:%c",ret[0]);mvwprintw(interface, 1, 8, "SP2:%c",ret[1]);
    
    mvwprintw(interface, 1, 14, "SA1:%c",ret[2]);mvwprintw(interface, 1, 32, "SA4:%c",ret[5]);
    mvwprintw(interface, 1, 20, "SA2:%c",ret[3]);mvwprintw(interface, 1, 38, "SA5:%c",ret[6]);
    mvwprintw(interface, 1, 26, "SA3:%c",ret[4]);mvwprintw(interface, 1, 44, "SA6:%c",ret[7]);
    
    mvwprintw(interface, 3, 2, "L1:%c",ret[8]);mvwprintw(interface, 3, 14, "L3:%c",ret[10]);
    mvwprintw(interface, 3, 8, "L2:%c",ret[9]);mvwprintw(interface, 3, 20, "L4:%c",ret[11]);
    
    mvwprintw(interface, 3, 26, "A1:%c",ret[12]);mvwprintw(interface, 3, 32, "A2:%c",ret[13]);
    
    mvwprintw(interface, 7, 21, "ALARME:D");

    cliente = connect_server(servD, "192.168.0.4");

    usleep(10000);

    send_message("T", cliente, ret);

    char tempe[7];
    char humid[7];

    for(int i=0;i<6;i++){
        tempe[i]=ret[i];
        humid[i]=ret[i+6]
    }

    tempe[6]='\0';
    humid[13]='\0';

    mvwprintw(interface, 5, 2, "Temperatura:%s.5",tempe);mvwprintw(interface, 5, 24, "Humidade:%s.5",humid);
    

    mvwprintw(input, 1, 12, "Input:");// Inicializa o texto inicial da janela
    wmove(input, 1, 19);
	wrefresh(interface);
    wrefresh(input);

    pthread_create(&input_bar, NULL, screen_input, (void *)commands);

    while(1){

        for(int i=0;i<6;i++){
            tempe[i]=((struct input_params *)th)->ret[i];
            humid[i]=((struct input_params *)th)->ret[i+6];
        }

        tempe[6]='\0';
        humid[13]='\0';
        mvwprintw(interface, 5, 2, "Temperatura:%s.5  ",tempe;
		mvwprintw(interface, 5, 30, "Humidade:%s.5  ",humid);
        wmove(input, 1, 19);
		wrefresh(interface);
        wrefresh(input);
        sleep(1);
    }

    return 0;
}