#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

#define PORT 4444
#define SERVER_IP "192.168.4.67"

int main(void)
{
	int data_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (data_socket == -1) {
		printf ("error in creating socket\n");
		return 0;
	}

	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(0);
	client_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bound = bind(data_socket, (struct sockaddr*)&client_addr, sizeof(client_addr));
	if (bound < 0) {
		printf("bound < 0\n");
		goto exit;
	}
	
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	int res = inet_aton(SERVER_IP, &server_addr.sin_addr);
	if (res == 0) {
		printf("error inet_aton\n");
		goto exit;
	}
	
	char output_buff[] = "Hello from Client!\n";
	int send_res = sendto(data_socket, output_buff, sizeof(output_buff), 0, (struct sockaddr*) &server_addr, sizeof(server_addr));

	if (send_res < 0){
		printf("send_res < 0\n");
	}
exit:
	close(data_socket);
	return 0;
}

