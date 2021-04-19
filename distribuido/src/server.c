#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "../inc/server.h"
#include "../inc/client.h"

#include "../inc/gpio.h"
#include "../inc/bme280_i2c.h"


float temp, hum;

int one_activation=1;

int only_once_bme=1;

struct param_adress{
	float temp;
	float hum;
};

struct param_adress *th;


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

void *treat_messages(void *servidorSocketv){
	int clienteLength;
	int socketCliente;
	struct sockaddr_in clienteAddr;


	int servidorSocket = *((int *)servidorSocketv);

	precocious_req(&temp, &hum);//Primeira chamada da funçao que lê o sensor bme280 para ter os dados disponiveis de imediato

	pthread_t temp_iterator;

	th = (struct param_adress *)malloc(sizeof(struct param_adress));

	pthread_create(&temp_iterator, NULL, req_temp_hum, (void *)th); //Thread da função que lê o sensor bme280

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
	char initial[9];
	char input_initial[9];
	pthread_t s_change;

	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
		printf("Erro no recv()\n");

	if(buffer[0]=='I' && one_activation){//Caso receba 'I' como mensagem, irá enviar o estado atual dos sensores e gadgets(lampada, ar)
		one_activation=0;
		initial_state(input_initial,initial);
		//kill(getpid(), SIGUSR2);//Sinal para sincronia da funçao cliente que comunica mudanças nos sensores para o servidor central NAO FUNCIONA MAIS
		
		pthread_create(&s_change, NULL, wsensor_change, NULL);//Cria a thread que trata as mudanças nos sensores

		for(int i=0;i<8;i++){
			buffer[i]=input_initial[i];
		}
		for(int i=8;i<14;i++){
			buffer[i]=initial[i-8];
		}
		buffer[14]='\0';
		tamanhoRecebido = strlen(buffer);
		printf("|%s|",buffer);
	}

	if(buffer[0]=='O'){//Liga, desliga gadgets
		on_off_gadgets(buffer[1],buffer[2]);
	}

	if(buffer[0]=='T'){//Envia a temperatura e a humidade
		if(only_once_bme){//Primeira chamada usa os valores gerados por precocious_req
			alarm(1);
			only_once_bme=0;
			gcvt(temp, 5, buffer);
			gcvt(hum, 5, buffer+6);
		}
		else{//Usa os valores gerados pela thread que le o sensor bme280
			gcvt(th->temp, 5, buffer);
			gcvt(th->hum, 5, buffer+6);
		}
		

		tamanhoRecebido = strlen(buffer);
	}

	
	if(send(socketCliente, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
		printf("Erro no envio - send()\n");
		
}