#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT 4444
#define LISTENERS 10

int main (void)
{
	printf ("I'm here!\n");
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
		
	while(1) {
		char input_buff[1024];
		ssize_t rec_size = recvfrom(udp_socket, (void*)input_buff, 1024, 0, (struct sockaddr*)&socket_addr, sizeof(struct sockaddr));
		if (rec_size == -1){
			printf("fails 2\n");
			//goto exit;
		}
		printf("data: %s\n", input_buff);

	}
exit:
	if (udp_socket) {
		close(udp_socket);
	}
	printf("finishes!\n");
	return 0;
}

