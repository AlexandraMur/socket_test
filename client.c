#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#define PORT 4444
#define SERVER_IP "192.168.4.67"

int main(void)
{
	int data_socket = socket(PF_INET, SOCK_DGRAM, 0);
	if (data_socket == -1) {
		return 0;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = PORT;
	
	struct in_addr server_ip;
	inet_aton(SERVER_IP, &server_ip);
	server_addr.sin_addr.s_addr = server_ip.s_addr;
	bzero(&server_addr.sin_zero, sizeof(server_addr.sin_zero));

	connect(data_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));

	char *output_buff = "Hi! From Client\n";
	char input_buff[1024];
	
	send(data_socket, (void*)&output_buff, sizeof(output_buff), 0);
	recv(data_socket, (void*)&input_buff, sizeof(input_buff), 0); 

	close(data_socket);
	return 0;
}

