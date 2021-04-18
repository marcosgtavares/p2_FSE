#ifndef SERVER_H_
#define SERVER_H_

int open_socket(unsigned short servidorPorta);
void *treat_messages(void *alarm_p);
void TrataClienteTCP(int socketCliente, char *sen_states);

#endif