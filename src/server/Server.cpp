#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <pthread.h>
#include <dirent.h>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>

std::map<int, int> used_books; //store socket till the end

std::vector<std::string> books;
std::string response;

char client_message[12];
std::string client_request;
char buffer[1024];

pthread_mutex_t lock;
std::vector<std::string> args; //request args
std::vector<std::string> all_books; //books which are returned from the server


Server::Server() {
  auto aTrafficManager = std::make_shared<reactor::ReactorSelectImpl>();
  m_conn_acceptor{"localhost", "4747", aTrafficManager};
    aAcceptorThread(aConnectionAcceptor);
    aTrafficManagerThread(*aTrafficManager);

    aAcceptorThread.join();
    aTrafficManagerThread.join();
}

void Server::read_books_dir() {
      std::cout << " read_books_dir" ;
      int i = 1;
      DIR *d;
      struct dirent *dir;
      d = opendir(BOOKS_DIR);
      if (d)
      {
        while ((dir = readdir(d)) != NULL)
        {
          //ignore ./  ../
          if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) {

          }
          else  {
          std::cout << "dir->d_name = " << dir->d_name << std::endl;
            books_map.insert({i, dir->d_name});
            i++;
          }
        }
        closedir(d);
      }

      for (auto book : books_map) {
          std::string new_book = std::to_string(book.first) +  "." + book.second;
          all_books.push_back(new_book);
      }
}
