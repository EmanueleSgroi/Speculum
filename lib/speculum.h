/*
 * Simple EchoServer with multi-clients management without the use of threads
 */

#define MAX_CONN 10
#define PORT 1337

typedef struct {
	int *num_clients;
	int *first;
	int *len_buf;
	char buffer[200];
	SOCKET *clients;
	SOCKET *ptr;
	struct sockaddr client_addr;
} Clients;

Clients clients;

SOCKET initialize();
int acceptClient (SOCKET server);
int recvClient (SOCKET client);
