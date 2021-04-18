#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "../inc/client.h"
#include "../inc/gpio.h"


int trigger = 0;
int once = 1 ;

void handle_initial(int signum){
	trigger=1;
}

int connect_server(unsigned short servidorPorta, char *IP_Servidor){
    int clienteSockets;
    struct sockaddr_in servidorAddr;
    // Criar Socket
	if((clienteSockets = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");
    // Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);
    if(connect(clienteSockets, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");
    
    return clienteSockets;
}

void send_message(char *mensagem, int clienteSocket){
    char buffer[16];
    int tamanhoMensagem = strlen(mensagem);
    int totalBytesRecebidos;


    if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	totalBytesRecebidos = 0;
	
	if((totalBytesRecebidos = recv(clienteSocket, buffer, 16-1, 0)) <= 0){
		printf("Não recebeu o total de bytes enviados\n");
	}
	buffer[totalBytesRecebidos] = '\0';
	printf("%s\n", buffer);
	close(clienteSocket);
    //close(clienteSocket);

}

void *wsensor_change(){
	char finals[9];

	int cliente;
	int i=0;
	signal(SIGUSR1, handle_initial);

	while(1){
		if(trigger){
			while(1){
				sensor_state_atualize(finals);
				for(i=0;i<8;i++){
					if(finals[i]!='D'){
					
						cliente = connect_server(10022, "192.168.0.53");
						
						send_message(finals, cliente);

						usleep(10000);

						break;
					}
				
				}
					printf("UGH1");
			}
			trigger=1;
		}
	}

}