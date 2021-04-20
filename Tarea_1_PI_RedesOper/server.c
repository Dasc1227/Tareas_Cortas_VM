#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#define SIZE 1024

void createDirectory(){
	
	struct stat st = {0};
	
	if(stat("directory", &st)==-1){
		mkdir("directory",0700);
	}
}

void SaveFile(int sockfd, char * buff){
	FILE *fp; 
	char dir [] = "directory/";
	char * fname = buff;
	strcat(dir, buff);
	//printf("%s\n", buff);
	//printf("%s\n",dir);
	char *file_name = dir;
	int received = 0;
	char buffer[SIZE];
	int fsize = 0; 
	fp = fopen(file_name, "w");
	//char data[1024] = {0};
	
	if(fp==NULL){
		perror("Error, Create the file is not possible");
		exit(1);
	}

	while(1){
		received= recv(sockfd, buffer, SIZE, 0);
		if(received <= 0){
			fseek(fp,0, SEEK_END);
			fsize = ftell(fp);
			break;
			return;
		}

		fprintf(fp, "%s", buffer);
		bzero(buffer, SIZE);
		
	}
	
	
	printf("%s" ,fname);
	printf(" has been copied, bytes copied = %d\n" ,fsize);
	return; 

}

int main(int arcg, char const * argv[]){
	
	const int port = atoi(argv[1]);
	char buffer[1024] = {0};
	int new_socket, valread;
	char *ip = "127.0.0.1"; //localhost
	int opt = 1;

	struct  sockaddr_in address;
	int addrlen = sizeof(address);
	char *hello="Hello from server";
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == 0){
		perror("socket failed");
		exit(1);
	}

	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockopt failed");
		exit(1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	//bind 
	if(bind(sockfd, (struct sockaddr *)&address,sizeof(address))<0){
		perror("bind failed");
		exit(1);		
	} 
	
	printf("[+] Server listening\n");
	while(1){


		if(listen(sockfd,3) < 0){
				perror("listen failed");
				exit(1);		
		}

		if(  (new_socket= accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen))<0  ){
			perror("accept failed");
			exit(1);
		}		
		valread= read(new_socket, buffer, 1024);
		//printf("Este es el primer buffer%s\n",buffer);

		createDirectory();

		SaveFile(new_socket, buffer);
		printf("File save successfully\n");
	}
	
}