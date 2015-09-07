#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4444
#define LISTENERS 10

int main(void){
	int udp_socket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if (udp_socket == -1) {
		printf ("smt goes wrong");
		return 0;
	} 
	
	struct sockaddr_in socket_addr;
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(PORT);
	socket_addr.sin_addr.s_addr = INADDR_ANY;

	bzero(&socket_addr.sin_zero, sizeof(socket_addr.sin_zero));
	bind(udp_socket, (struct sockaddr*)&socket_addr, sizeof(struct sockaddr));
	
	int listen_result = listen(udp_socket, LISTENERS);
	if (listen_result == -1) {
		goto exit;
	}
	
	int addr_size = sizeof(struct sockaddr_in);
	struct sockaddr_in remote_addr;
	int data_socket = accept(udp_socket, (struct sockaddr*)&remote_addr,&addr_size);
	
	if (data_socket == -1){
		goto exit;
	}

	char *output_buff = "Hi! Write smth...\n";
	char input_buff[1024];

	send (data_socket, (void*)&output_buff, sizeof(output_buff), 0);
	recv (data_socket, (void*)&input_buff, sizeof(input_buff), 0);
	
	printf("%s", input_buff);
	
exit:
	if (udp_socket) {
		close(udp_socket);
	}
	if (data_socket) {
		close(data_socket);
	}
	printf("finishes!\n");
	return 0;
}
