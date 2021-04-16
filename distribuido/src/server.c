#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/server.h"
#include "../inc/gpio.h"

char initial[9];
char final[9];
char input_initial[6];

float temp;

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

void treat_messages(int servidorSocket){
	int clienteLength;
	int socketCliente;
	struct sockaddr_in clienteAddr;
    while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, (struct sockaddr *) &clienteAddr, &clienteLength)) < 0)
			printf("Falha no Accept\n");
		
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		
		TrataClienteTCP(socketCliente);
        close(socketCliente);
	}
}

void TrataClienteTCP(int socketCliente) {
	char buffer[16];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
		printf("Erro no recv()\n");

	if(buffer[0]=='I'){//Estado inicial
		initial_state(input_initial,initial);
		for(int i=0;i<8;i++){
			buffer[i]=initial[i];
		}
		for(int i=8;i<14;i++){
			buffer[i]=input_initial[i-8];
		}
		buffer[14]='\0';
		tamanhoRecebido = strlen(buffer);
	}

	if(buffer[0]=='O'){//Liga, desliga gadgets
		on_off_gadgets(buffer[1],buffer[2]);
	}

	if(buffer[0]=='T'){
		gcvt(temp, 5, buffer);

	}

	while (tamanhoRecebido > 0) {
		if(send(socketCliente, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
			printf("Erro no recv()\n");
	}
}