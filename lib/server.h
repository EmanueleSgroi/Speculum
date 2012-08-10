/*
 * Simple EchoServer with multi-clients management without the use of threads
 */

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>

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

SOCKET initialize()
{
	int length = sizeof (struct sockaddr);
	int client;
		
	SOCKET server;
	struct sockaddr_in server_addr;
   
	WSADATA data;
	WSAStartup (MAKEWORD(2,2), &data);
	
	server = socket (PF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons (PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind (server, (struct sockaddr*)&server_addr, sizeof (struct sockaddr_in));
	listen (server, MAX_CONN);

	clients.first = (int*) malloc (1 * sizeof (int));
	clients.num_clients = (int*) malloc (1 * sizeof (int));
	clients.len_buf = (int*) malloc (1 * sizeof (int));
	clients.clients = (int*) malloc (10 * sizeof (int));

	*(clients.first) = 0;
	*(clients.num_clients) = 0;
	clients.ptr = &*(clients.clients);
	memset (clients.clients, 0, MAX_CONN);
	
	return server;
}

int acceptClient (SOCKET server)
{
	int retval;
	int length = sizeof (struct sockaddr);
	SOCKET client;
	fd_set read_set;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	
	FD_ZERO (&read_set);
	FD_SET (server, &read_set);
	retval = select (server, &read_set, NULL, NULL, &timeout);
	if (retval == 1)
	{
		client = accept (server, &(clients.client_addr), &length);
		if (*clients.first == 0)
		{
			*(clients.clients) = client;
			*(clients.first) = 1;
			return client;
		}
		else
		{
			*(clients.clients+(++*(clients.num_clients))) = client;
			return client;
		}
	}
	return 0;
}

int recvClient (SOCKET client)
{
	int retval;
	char buffer[200] = {0};
	fd_set read_set;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	FD_ZERO (&read_set);
	FD_SET (client, &read_set);
	
	*clients.len_buf = -1;
	retval = select (client, &read_set, NULL, NULL, &timeout);
	
	if (retval)
	{
		*clients.len_buf = recv (client, clients.buffer, 200, 0);
	}
	return *clients.len_buf;
}
