#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/client.h"
#include "../inc/control_acess.h"


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

void send_message(char *mensagem, int clienteSocket, char *t_h){
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
		if(buffer[0]=='O'){
			handle_on_off(buffer);
		}
		else if(buffer[0]=='L' || buffer[0]=='D'){
			init_state(buffer);
		}
		else{
			for(int i=0;i<tamanhoMensagem;i++){
				t_h[i]=buffer[i];
			}
			
		}
	}
	close(clienteSocket);
    //close(clienteSocket);

}