#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/server.h"
#include "../inc/alarm_controler.h"

struct sckt_sstate{
    int sockets;
    char sstates[9];
};

int open_socket(unsigned short servidorPorta){
	int servidorSocket;
	struct sockaddr_in servidorAddr;
	// Abrir Socket
	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");	

    return servidorSocket;

}

void *treat_messages(void *alarm_p){
	int clienteLength;
	int socketCliente;
	int servidorSocket = ((struct sckt_sstate *)alarm_p)->sockets;

	struct sockaddr_in clienteAddr;
    while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, (struct sockaddr *) &clienteAddr, &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		TrataClienteTCP(socketCliente, ((struct sckt_sstate *)alarm_p)->sstates);
        close(socketCliente);
	}
}

void TrataClienteTCP(int socketCliente, char *sen_states) {
	char buffer[16];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0){
		printf("Erro no recv()\n");
	}
	else{
		for(int i=0;i<8;i++){
			sen_states[i]=buffer[i];
		}
		sen_states[8]='\0';
		handle_change_s(sen_states);//Lida com a mudança de estados e decide se o alarme sera acionado ou nao
	}

	if(send(socketCliente, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
		printf("Erro no envio - send()\n");
		
}

