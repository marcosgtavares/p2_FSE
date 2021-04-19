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
char initials[9];

void handle_initial(int signum){//Funçao que lida com o sigusr1 e liga o loop da thread que observa as mudanças de estado dos sensores
	trigger=1;
	sensor_state_atualize(initials);//Define o primeiro estado
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

void *wsensor_change(){//Funçao que observa as mudanças de estados dos sensores
	char finals[9];
	int cliente;
	signal(SIGUSR1, handle_initial);
	sleep(1);

	while(1){
		//if(trigger){
			sensor_state_atualize(finals);
			printf("Sensor state sent\n");
			if(strcmp(initials,finals)!=0){//Caso o estado seja diferente do anterior, mande a mensagem com o estado atual
				for(int i=0;i<8;i++){
					initials[i]=finals[i];
				}
				cliente = connect_server(10022, "192.168.0.53");
				send_message(finals, cliente);
				
				
			}
			usleep(500000);//Observe a cada 500ms
		//}
	}

}