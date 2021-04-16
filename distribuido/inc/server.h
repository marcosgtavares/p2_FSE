#ifndef SERVER_H_
#define SERVER_H_

int open_socket(unsigned short servidorPorta);
void treat_messages(int servidorSocket);
void TrataClienteTCP(int socketCliente);

#endif