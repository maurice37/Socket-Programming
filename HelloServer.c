#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
	/* Make sure you include "arpa/inet.h" because if you will not use it then it will consider
		the inet_ntoa() as int and gives error since printf() expect it to be a string.
	*/
main()
{

	int sock,cli; //socket descripter for client
	struct sockaddr_in server,client;
	unsigned int len;
	char mesg[] = "Hello to the world of Socket Programming! ";
	int sent;		
	if((sock = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("socket: ");
		exit(-1);
	}

	server.sin_family  = AF_INET;

	//as some system uses Big Endian while some uses Big htons() is used to convert all into Network Order
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);
	
	len = sizeof(struct sockaddr_in);
	
	//Just to check that no error is there while binding

	if((bind(sock,(struct sockaddr *)&server,len)) == -1){
		perror("bind: ");
		exit(-1);
	}

	//Error checking while calling listen()
	if((listen(sock,5)) == -1)
	{
		perror("listen: ");
		exit(-1);
	}
	while(1){
		if((cli = accept(sock,(struct sockaddr *)& client, &len))== -1)
		{
			perror("accept: ");
			exit(-1);	
		}
		sent = send(cli,mesg,strlen(mesg),0);

		printf("Sent %d bytes to client : %s \n",sent,(inet_ntoa(client.sin_addr)));
		
		close(cli);


 
	}


}

