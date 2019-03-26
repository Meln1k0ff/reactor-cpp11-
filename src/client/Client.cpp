#include <signal.h>
#include <cstdio>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>
#include <sstream>


int main(int argc, char *argv[])
{

  int i = 0;
 pthread_t client_thr;

   // Create the socket.
   clientSocket = socket(PF_INET, SOCK_STREAM, 0);
   //Configure settings of the server address
  // Address family is Internet
   serverAddr.sin_family = AF_INET;
   //Set port number, using htons function
   serverAddr.sin_port = htons(7799);
  //Set IP address to localhost
   serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
     //Connect the socket to the server using the address
    addr_size = sizeof(serverAddr);
    if (connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)) {
        std::cout << "connection error";
    }
    else {
          printf("Connection established \n");
          std::string request;

          struct sigaction act;
          act.sa_handler = signal_handler;
          sigaction(SIGINT, &act, NULL);

          while (clientRunning) {
              std::cout << "clientSocket = " << clientSocket;
              std::cout << "input:";
              std::getline(std::cin, request);
              const char *message = request.c_str(); //full string with spaces
              line_len = strlen(message);

              if (write(clientSocket, message,  line_len) < 0) {
                  printf("Send failed\n");
              }
              //block
               if (read(clientSocket, &buffer, 4095) < 0)
               {
                  printf("Receive failed\n");
               }
                  printf("Data received: %s\n", buffer);
          }
    }
  return EXIT_SUCCESS;
}
