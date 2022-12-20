
#if defined WIN32
#include <winsock.h>
#else
#include <netdb.h>
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <string.h>



int main(int argc,char*argv[]) {
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
	int vet;
	char echoString[30];
	char echoStringres[30];
	struct in_addr*ina;
	int port;
    char canonical[30];
	int len;
	printf("inserire il nome del server UDP da contattare\n");
	scanf("%s",canonical);
	printf("inserire il numero di porta del server UDP da contattare(8080)\n");
	scanf("%d",&port);
	struct hostent *host;
	host = gethostbyname(canonical);
	char ipstring[20]="";

	if (host == NULL) {
		fprintf(stderr, "gethostbyname() failed.\n");
		exit(EXIT_FAILURE);
	}

	else {
		ina = (struct in_addr*) host->h_addr_list[0];
		printf("Risultato di gethostbyname(%s): %s\n",canonical,inet_ntoa(*ina));
		sprintf(ipstring, "%s", inet_ntoa(*ina));
	}

	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		return -1;
	}

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = PF_INET;
	echoServAddr.sin_port = htons(port);
	echoServAddr.sin_addr.s_addr=inet_addr(ipstring);

		printf("Inserisci una stringa a piacere da inviare al server\n");
		char stringadainviare[40]={"\0"};
		scanf("%s",stringadainviare);
		if(sendto(sock, stringadainviare, sizeof(stringadainviare), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
			return -1;
		}

		len=sizeof(echoStringres);

		if(recvfrom(sock, echoStringres, sizeof(echoStringres), 0, (struct sockaddr*)&echoServAddr,&len)<0){
			return -1;
		}

		printf("%s\n",echoStringres);

		printf("inserire una stringa di caratteri alfanumerici(max 30)\n");
		char caratterialfanumerici[31];
		scanf("%s",caratterialfanumerici);

		vet=sizeof(caratterialfanumerici);

		char carattere[5];
		char nuovocarattere;
		for (int i=0; i<vet; i++){

			switch(caratterialfanumerici[i]){

			case 'a':
				carattere[0]=caratterialfanumerici[i];
				if(sendto(sock,carattere, sizeof(carattere), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
				    return -1;
				}

				if(recvfrom(sock, &nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoServAddr,&len)<0){
					return -1;
				}

				printf("%c",nuovocarattere);

				break;

			case 'e':
				carattere[0]=caratterialfanumerici[i];
				if(sendto(sock,carattere, sizeof(carattere), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
					return -1;
				}

				if(recvfrom(sock, &nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoServAddr,&len)<0){
									return -1;
								}


				printf("%c",nuovocarattere);

				break;

			case 'i':
				carattere[0]=caratterialfanumerici[i];
				if(sendto(sock,carattere, sizeof(carattere), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
					return -1;
				}

				if(recvfrom(sock, &nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoServAddr,&len)<0){
									return -1;
								}


				printf("%c",nuovocarattere);

				break;

			case 'o':
				carattere[0]=caratterialfanumerici[i];
				if(sendto(sock,carattere, sizeof(carattere), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
					return -1;
				}

				if(recvfrom(sock, &nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoServAddr,&len)<0){
									return -1;
								}

				printf("%c",nuovocarattere);

				break;

			case 'u':
				carattere[0]=caratterialfanumerici[i];
				if(sendto(sock,carattere, sizeof(carattere), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
					return -1;
				}

				if(recvfrom(sock, &nuovocarattere, sizeof(nuovocarattere), 0, (struct sockaddr*)&echoServAddr,&len)<0){
									return -1;
								}


				printf("%c",nuovocarattere);

				break;


			default:
				break;

		}

//		if(strcmp(echoStringres,msgexit)!=0){
//			memset(echoStringres,'\0',30);
//		}

}
		char fineswitch[5]="fine";
		if(sendto(sock,fineswitch, sizeof(fineswitch), 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr))<0){
							return -1;
						}
		printf("\nfine programma\n");
		system("pause");
}

