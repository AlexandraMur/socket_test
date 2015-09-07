#include <sys/tupes.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4444
#define LISTENERS 10

int main(void){
	int tcp_socket = socket(PF_INET, SOCK_DGRAM, 0);
	
	if (tcp_socket == -1) {
		return -1;
	} 
	
	struct sockaddr_in socket_addr;
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(PORT);
	socket_addr.sin_addr.s_addr = INADDR_ANY;

	bzero(&socket_addr.sin_zero, sizeof(socket_addr.sin_zero));
	bind(tcp_socket, (struct sockaddr*)&socket_addr, sizeof(struct sockaddr));
	
	int listen_result = listen(tcp_socket, LISTENERS);
	if (listen_result == -1) {
		goto exit;
	}
	
	int addr_size = sizeof(struct sockaddr_in);
	int data_socket = accept(tcp_socket, (struct sockaddr*)&remote_addr,&addr_size);
	
	if (data_socket == -1){
		goto exit;
	}
exit:
	if (tcp_socket) {
		close(tcp_socket);
	}
	if (data_socket) {
		close(data_socket);
	}
	return 0;
}
