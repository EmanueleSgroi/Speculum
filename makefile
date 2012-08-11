# Makefile Speculum
# Emanuele Sgroi - emanuele.sgroi@gmail.com 

speculum: server.c lib/speculum.c
	gcc server.c lib/speculum.c -lws2_32 -o Server
