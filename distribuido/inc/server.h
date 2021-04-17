#ifndef SERVER_H_
#define SERVER_H_

int open_socket(unsigned short servidorPorta);
void treat_messages(void *servidorSocketv);
void TrataClienteTCP(int socketCliente);

#endif