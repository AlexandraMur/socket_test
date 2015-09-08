#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdio.h>

#define PORT 4444
#define LISTENERS 10

int main (void)
{
	int udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (udp_socket == -1) {
		printf ("smt goes wrong\n");
		return 0;
	} 
	
	struct sockaddr_in socket_addr;
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(PORT);
	socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bzero(&socket_addr.sin_zero, sizeof(socket_addr.sin_zero));
	int bound = bind(udp_socket, (struct sockaddr*)&socket_addr, sizeof(struct sockaddr));
	
	if (bound < 0) {
		printf("fails 1\n");
		goto exit;
	}
	
	fd_set rfds;
    	struct timeval tv;
    	int retval;

	FD_ZERO(&rfds);
    	FD_SET(udp_socket, &rfds);
	
	tv.tv_sec = 60;
   	tv.tv_usec = 0;

	retval = select(udp_socket + 1, &rfds, (fd_set*) 0, (fd_set*) 0, &tv);
	
	if (retval == -1) {
		printf("return value == -1");
	}
exit:
	if (udp_socket) {
		close(udp_socket);
	}
	printf("finishes!\n");
	return 0;
}

