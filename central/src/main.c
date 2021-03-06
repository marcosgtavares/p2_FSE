#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h> 
#include <signal.h>
#include <ncurses.h>
#include <time.h>

#include "../inc/server.h"
#include "../inc/client.h"
#include "../inc/alarm_controler.h"
#include "../inc/w_interface.h"
#include "../inc/csv_gen.h"


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


    int sockets = open_socket(servC);//Abertura do socket do servidor para observar as mudanças nos etados dos sensores(Enviados pelo servidor distribuido)
    struct sckt_sstate *alarm_params = (struct sckt_sstate *)malloc(sizeof(struct sckt_sstate));
    alarm_params->sockets=sockets;

    ret=(char *)malloc(sizeof(char)*16);//Necessario para armazenar os valores iniciais
    
    commands=(struct input_params *)malloc(sizeof(struct input_params));//Parametro para amrazenar os dados necessarios para a thread que captura o input

    th=(struct input_params *)malloc(sizeof(struct input_params));//Parametro para armazenar e temperatura e humidade.
    //th=(char *)malloc(sizeof(char)*16);

    initscr();// Incia a janela do ncurses
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    WINDOW *interface = newwin(10,50,max_y/2-5,max_x/2-25);
    WINDOW *input = newwin(4,50,max_y/2+5,max_x/2-25);

    set_interface((void *)interface);

    pthread_t alarm_watcher, temp_humidity, input_bar;
    pthread_create(&alarm_watcher, NULL, treat_messages, (void *)alarm_params);//Thread que observa mudanças nos estados dos sensores
    pthread_create(&temp_humidity, NULL, te_hum, (void *)th);//Thread que requisita a temperatura de 1 em 1 segundo

    int cliente;
    cliente = connect_server(servD, "192.168.0.4");
    usleep(10000);
    send_message("I", cliente, ret);//Requisição inicial dos estados dos sensores e gadgets
    
    
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );//Captura de tempo para criação do nome do arquivo csv
    create_csv(asctime (timeinfo),"S");//Criação do arquivo csv
    

    commands->input = input;
    commands->interface = interface;

    refresh();
    box(interface, 0, 0); box(input, 0, 0);

    mvwprintw(interface, 1, 2, "SP1:%c",ret[0]);mvwprintw(interface, 1, 8, "SP2:%c",ret[1]);//Estado inicial requisitado a parte
    mvwprintw(interface, 1, 14, "SA1:%c",ret[2]);mvwprintw(interface, 1, 32, "SA4:%c",ret[5]);
    mvwprintw(interface, 1, 20, "SA2:%c",ret[3]);mvwprintw(interface, 1, 38, "SA5:%c",ret[6]);
    mvwprintw(interface, 1, 26, "SA3:%c",ret[4]);mvwprintw(interface, 1, 44, "SA6:%c",ret[7]);
    
    mvwprintw(interface, 3, 2, "L1:%c",ret[8]);mvwprintw(interface, 3, 14, "L3:%c",ret[10]);
    mvwprintw(interface, 3, 8, "L2:%c",ret[9]);mvwprintw(interface, 3, 20, "L4:%c",ret[11]);
    mvwprintw(interface, 3, 26, "A1:%c",ret[12]);mvwprintw(interface, 3, 32, "A2:%c",ret[13]);
    
    mvwprintw(interface, 7, 21, "ALARME:D");

    cliente = connect_server(servD, "192.168.0.4");
    usleep(10000);
    send_message("T", cliente, ret);//Primeira requisição de temperatura(Ativa a leitura periodica do sensor no servidor distribuido)
    usleep(10000);

    char tempe[8];
    char humid[8];
    for(int i=0;i<7;i++){//Separa as informações do ponteiro
        tempe[i]=ret[i];
        humid[i]=ret[i+6];
    }
    tempe[7]='\0';
    humid[7]='\0';

    mvwprintw(interface, 5, 2, "Temperatura:%.6s",tempe);mvwprintw(interface, 5, 30, "Humidade:%.6s",humid);//Estado inicial requisitado a parte
    mvwprintw(input, 1, 12, "Input:");// Inicializa o texto inicial da janela
    wmove(input, 1, 19);
	wrefresh(interface);
    wrefresh(input);

    pthread_create(&input_bar, NULL, screen_input, (void *)commands);//Thread onde acontece a captura do input(Consome muita memoria)

    while(1){//Printa de 1 em um segundo os valores da temperatura e humidade gerados na thread que requisita e armazena esses dados a partir do ponteiro

        for(int i=0;i<6;i++){
            tempe[i]=((struct input_params *)th)->ret[i];
            humid[i]=((struct input_params *)th)->ret[i+6];
        }

        tempe[7]='\0';
        humid[7]='\0';
        mvwprintw(interface, 5, 2, "Temperatura:%.6s  ",tempe);
		mvwprintw(interface, 5, 30, "Humidade:%.6s  ",humid);
		wrefresh(interface);
        sleep(1);
    }

    return 0;
}