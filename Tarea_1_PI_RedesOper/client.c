#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include<stdlib.h>
#define SIZE 1024
 
 
int main(int arcg, char const * argv[]){
	
	const int port = atoi(argv[1]); 
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024]={0};
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0){
		printf("\n Socket creation error \n");
		return -1; 
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
		printf("\nInvalid address/ Address not suported \n");
		return -1;
	}

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
		printf("\nConnection FAILED \n");
		return -1; 
	}


	FILE *fp; 
	const char *file_name = argv[2];
	send(sock, file_name, strlen(file_name),0);
	//printf("%s", file_name);

	fp = fopen(file_name, "r");
	char data[SIZE] = {0};
	 
	if(fp==NULL){
		perror("File Error");
		exit(1);
	}
	

	int bytes = 0; 
	while(fgets(data, SIZE, fp) != NULL){

		if(send(sock, data, sizeof(data), 0)==-1){
			perror("Send Error");
			exit(1);
		}

		bytes++;
	}
	fseek(fp,0, SEEK_END);
	printf("File sent sucessfully, bytes sent = %ld", ftell(fp));
	printf("\n");
	bzero(data, SIZE);
	
	


	return 0; 

}
