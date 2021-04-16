#ifndef SERVER_H_
#define SERVER_H_

void open_socket(int servidorSocket, unsigned short servidorPorta);
void treat_messages(int servidorSocket);
void TrataClienteTCP(int socketCliente);

#endif