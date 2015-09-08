#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>

#define PORT 4444
#define SERVER_IP "192.168.4.67"

int main(void)
{
	int data_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (data_socket == -1) {
		return 0;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(PORT);
	
	struct in_addr server_ip;
	inet_aton(SERVER_IP, &server_ip);
	server_addr.sin_addr.s_addr = htonl(server_ip.s_addr);
	
	char *buff = "Hello from Client!\n";
	int bytes_sent = sendto(data_socket, buff, strlen(buff) + 1, 0, (struct sockaddr*)&data_socket, sizeof(struct sockaddr_in)); 
	
	if (bytes_sent < 0){
		printf("bytes_sent < 0\n");
	}
	
	close(data_socket);
	return 0;
}

