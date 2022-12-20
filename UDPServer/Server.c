
#if defined WIN32
#include <winsock.h>
#else
#include <netdb.h>
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define PORT 8080


void errorhandler(char *errorMessage);
void ClearWinSock();

int main() {
#if defined WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2 ,2), &wsaData);
	if (iResult != 0) {
		printf ("error at WSASturtup\n");
		return EXIT_FAILURE;
	}
#endif
	int sock;
	struct sockaddr_in echoServAddr;
	struct sockaddr_in echoClntAddr;
	int cliAddrLen;
	char echoBuffer[31];


	// CREAZIONE DELLA SOCKET
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		return -1;
	}

	// COSTRUZIONE DELL'INDIRIZZO DEL SERVER
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_port = htons(PORT);
	echoServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// BIND DELLA SOCKET
	if ((bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr))) < 0){
		return -1;
	}
// RICEZIONE DELLA STRINGA ECHO DAL CLIENT
	while(1) {
		cliAddrLen = sizeof(echoClntAddr);
		recvfrom(sock, echoBuffer, sizeof(echoBuffer), 0, (struct sockaddr*)&echoClntAddr, &cliAddrLen);
		char ip[20]="";
	    struct hostent *host;
	    struct in_addr addr;
		sprintf(ip,"%s",inet_ntoa(echoClntAddr.sin_addr));
		addr.s_addr=inet_addr(ip);
		host = gethostbyaddr((char *) &addr, 4, AF_INET);
		printf("'%s' ricevuto dal client con nomehost %s \n",echoBuffer,host->h_name);
		char *stringadiok={"OK!"};
		if(sendto(sock,stringadiok,sizeof(stringadiok), 0, (struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr))<0){
			return -1;
			}
		char stringaricevuto[5];
		char nuovocarattere[5]="iniz";
		char caratteredainviare;
		char msgexit[5]="fine";
		stringaricevuto[0]="c";
		while(strcmp(nuovocarattere,msgexit)!=0){
			recvfrom(sock,nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoClntAddr, &cliAddrLen);
			caratteredainviare=toupper(nuovocarattere[0]);
			if(strcmp(nuovocarattere,msgexit)!=0){
			if(sendto(sock,&caratteredainviare,sizeof(caratteredainviare), 0, (struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr))<0){
						return -1;
						}
			}
		}

}

void errorhandler(char *errorMessage) {
	printf(errorMessage);
}
void ClearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}
}
