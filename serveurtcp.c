/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveurtcp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcim <jalcim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 00:32:17 by jalcim            #+#    #+#             */
/*   Updated: 2014/02/13 10:15:13 by jalcim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
typedef struct sockaddr_in t_sockaddr_in;
typedef struct in_addr t_in_addr;
typedef struct pollfd t_pollfd;
typedef struct sockaddr t_sockaddr;

#define PORT 1891
#define IP "127.0.0.1"

void error();

int main()
{
	int sock;
	t_sockaddr_in serveur, client;
	char *buffer;
	t_pollfd event[1];
	int err;
	int size;
	int compt;

	if (!(buffer = (char *)malloc(1001 * sizeof(char))))
		error();
	size = sizeof(t_sockaddr);

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket\n");
		error();
	}
	serveur.sin_family = PF_INET;
	serveur.sin_port = htons(PORT);
	serveur.sin_addr.s_addr = inet_addr(IP);
	if (bind(sock, (t_sockaddr *)&serveur, size) == -1)
	{
		printf("bind\n");
		error();
	}
	event->fd = sock;
	event->events = POLLIN;
	if ((err = poll(event, sizeof(t_pollfd), -1)) == -1)
	{
		printf("poll\n");
		error();
	}
	if (listen(event[0].fd, 0) == -1)
	{
		printf("listen\n");
		error();
	}
	if ((sock = accept(event[0].fd, (t_sockaddr *)&client, &size)) == -1)
	{
		printf("accept\n");
		error();
	}
	printf("connected\n");
	compt = -1;
	if(!((err = read(sock, &buffer[++compt], 1000)) > 0))
		error();
	strncat(buffer, "\0", 1);
	printf("buffer = %s\n", buffer);

	sleep(2);
	close(sock);
	close(event[0].fd);
	return (0);
}

void error()
{
	perror("error -> ");
	exit(0);
}
