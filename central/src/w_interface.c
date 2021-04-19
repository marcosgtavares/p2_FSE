#include <stdio.h>
#include <ncurses.h>
#include "../inc/alarm_controler.h"
#include "../inc/w_interface.h"
#include "../inc/client.h"


struct input_params{
    char command[30];
    char ret[16];
    WINDOW *input;
    WINDOW *interface;
};

void *screen_input(void *commands){
    int cliente;
    WINDOW *input = ((struct input_params *)commands)->input;
    WINDOW *interface = ((struct input_params *)commands)->interface;

    while(1){

        mvwprintw(input, 1, 12, "Input:");
        wmove(input, 1, 19);
       
        mvwscanw(input,1, 19,"%s", ((struct input_params *)commands)->command);
        if(((struct input_params *)commands)->command[1]!='G'){
            cliente = connect_server(10122, "192.168.0.4");
            send_message(((struct input_params *)commands)->command, cliente, ((struct input_params *)commands)->ret);
        }
        
        if(((struct input_params *)commands)->command[1]!='G'){
            if(((struct input_params *)commands)->command[2]=='1'){
                mvwprintw(interface, 7, 21, "ALARME:%c",'L');
            }
            else{
                mvwprintw(interface, 7, 21, "ALARME:%c",'D');
            }
            wrefresh(interface);
            liga_desliga_alarme();
        }

        switch(((struct input_params *)commands)->ret[1]){
            case 'A':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 2, "L1:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 2, "L1:%c",'D');
                }
                break;
            case 'B':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 8, "L2:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 8, "L2:%c",'D');
                }
                break;
            case 'C':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 14, "L3:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 14, "L3:%c",'D');
                }
                break;    
            case 'D':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 20, "L4:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 20, "L4:%c",'D');
                }
                break;
            case 'E':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 26, "A1:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 26, "A1:%c",'D');
                }
                break;
            case 'F':
                if(((struct input_params *)commands)->ret[2]=='1'){
                    mvwprintw(interface, 3, 32, "A2:%c",'L');
                }
                else{
                    mvwprintw(interface, 3, 32, "A2:%c",'D');
                }
                break;
            case 'G':
                break;
            
            default:
                    mvwprintw(interface, 9, 2, "NOPE");
                    break;       
        }

        wrefresh(interface);
    }
    
}