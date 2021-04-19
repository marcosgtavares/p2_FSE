#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/client.h"

int once_dt=1;

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

void send_message(char *mensagem, int clienteSocket, char *ret){
    char buffer[16];
    int tamanhoMensagem = strlen(mensagem);
    int totalBytesRecebidos;


    if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	if(mensagem=="T" && once_dt==1){
		once_dt=0;
		usleep(10000);
	}
	totalBytesRecebidos = 0;
	if((totalBytesRecebidos = recv(clienteSocket, buffer, 16-1, 0)) <= 0){
		printf("Não recebeu o total de bytes enviados\n");
	}	
	buffer[totalBytesRecebidos] = '\0';

	for(int i=0;i<totalBytesRecebidos;i++){
		ret[i]=buffer[i];
	}
	ret[totalBytesRecebidos] = '\0';

	close(clienteSocket);
    //close(clienteSocket);

}

void *te_hum(void *temp_hum){
	int cliente;
	while(1){
		sleep(1);
		cliente = connect_server(10122, "192.168.0.4");
		send_message("T", cliente, (char *)temp_hum);
	}
}