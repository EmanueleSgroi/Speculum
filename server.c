/*
 * Simple EchoServer with multi-clients management without the use of threads
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include "lib/speculum.h"

int main(int argn,char **argv)
{
	int client;
	SOCKET server;
	
	server = initialize ();

	while (1)
	{
		if (client = acceptClient (server))
		{
			printf ("Client %ld si e' connesso.\n", client);
		}
		
		for(client = 0; client <= *(clients.num_clients); client++)
		{
			recvClient (clients.ptr[client]);
			
			if (!*clients.len_buf)
			{
				closesocket (clients.ptr[client]);
				printf ("Client %ld si e' disconnesso.\n", clients.ptr[client]);
			}
			if (*clients.len_buf > 0)
			{
				printf ("%s\n", clients.buffer);
				send (clients.ptr[client], clients.buffer, *clients.len_buf, 0);
				memset (clients.buffer, 0, *clients.len_buf);
			}
		}
	}
	return 0;
}
