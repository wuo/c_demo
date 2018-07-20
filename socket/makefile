all: server_unix server_inet client_unix client_inet
server_unix: server.c
	gcc -o server_unix -DDOMAIN_UNIX server.c
server_inet: server.c
	gcc -o server_inet -DDOMAIN_INET server.c
client_unix: client.c
	gcc -o client_unix -DDOMAIN_UNIX client.c
client_inet: client.c
	gcc -o client_inet -DDOMAIN_INET client.c

