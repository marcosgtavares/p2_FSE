#include <stdio.h>
#include <string.h>
#include "../inc/csv_gen.h"

FILE *fp;
void create_csv(char *d_h, char *com_trig){
    if(com_trig[0]=='S'){
        char temp[23];
        int i=0;
        while(d_h[i+9]!='\0'){
            temp[i]=d_h[i+4];
            i++;
        }
        temp[i]='2';
        temp[i+1]='1';
        temp[i+2]='.';
        temp[i+3]='c';
        temp[i+4]='s';
        temp[i+5]='v';
        temp[i+6]='\0';
        i=0;
        while(temp[i]!='\0'){
            if(temp[i]==' '){
                temp[i]='_';
            }
            i++;
        }
        char f_path[30];
        snprintf(f_path, 30, "../log/%s", temp);
        fp=fopen(f_path,"w");
        fprintf(fp, "Data e hora,Comando,Acionamento Sensor,Acionamento Alarme\n");
    }
    else{
        d_h[24]='\0';
        if(com_trig[0]=='L' || com_trig[0]=='D'){
            fprintf(fp, "%s,,%s,\n", d_h, com_trig);
        }
        else if(com_trig[0]=='O'){
            fprintf(fp, "%s,%s,,\n", d_h, com_trig);
        }
        else{
            fprintf(fp, "%s,,,%s\n", d_h, com_trig);
        }
        
    }
}
void close_csv(){
    fprintf(fp, "%c", '\0');
    fclose(fp);
}