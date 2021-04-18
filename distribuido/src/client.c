#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "../inc/client.h"
#include "../inc/gpio.h"

char initial[9];

int trigger = 0;
int once = 1 ;

void handle_initial(int signum){
	sensor_state_atualize(initial);
	trigger=1;
}

int connect_server(unsigned short servidorPorta, char *IP_Servidor){
    int clienteSocket;
    struct sockaddr_in servidorAddr;
    // Criar Socket
	if((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");
    // Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);
    if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");
    
    return clienteSocket;
}

void send_message(char *mensagem, int clienteSocket){
    char buffer[16];
    int tamanhoMensagem = strlen(mensagem);
    int totalBytesRecebidos;
    int bytesRecebidos;

    if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	totalBytesRecebidos = 0;
	while(totalBytesRecebidos < tamanhoMensagem) {
		if((bytesRecebidos = recv(clienteSocket, buffer, 16-1, 0)) <= 0)
			printf("Não recebeu o total de bytes enviados\n");
		totalBytesRecebidos += bytesRecebidos;
		buffer[bytesRecebidos] = '\0';
		printf("%s\n", buffer);
	}
	close(clienteSocket);
    //close(clienteSocket);

}

void *wsensor_change(){
	char final[9];
	int cliente;

	signal(SIGUSR1, handle_initial);

	while(1){
		if(trigger){
			usleep(100000);
			sensor_state_atualize(final);
			if(!strcmp(initial,final)){
				for(int i=0; i<9; i++){
					initial[i] = final[i];
				}
				
				if(once){
					once = 0;
					int cliente = connect_server(10022, "192.168.0.53");
				}
    			send_message(final, cliente);
			}
		}
	}

}