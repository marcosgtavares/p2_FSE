#ifndef CLIENT_H_
#define CLIENT_H_

int connect_server(unsigned short servidorPorta, char *IP_Servidor);
void send_message(char *mensagem, int clienteSocket, char *t_h);

#endif