#include <stdio.h>
#include <stdlib.h>

int main(void){
	char* serverName = getenv("SERVER_NAME");
	if(serverName == NULL)
		/*
		 	The SERVER_NAME environment variable was not set.
			Use the default
		 */
		serverName = "server.my-company.com";
	printf("accesing server %s\n", serverName);
	// Access the server here...

	return 0;
}
