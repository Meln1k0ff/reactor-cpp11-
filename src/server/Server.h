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

//ConnectionAcceptor

#include "threads/ConnectionAcceptor.h"
#include "reactor/ReactorInterface.h"
#include "reactor/ReactorSelectImpl.h"

#include <vector>

class Server {
    public:
       Server(std::thread acceptorThread);
/*
Server logic
  */
    void read_books_dir();
    void use_book(int sock_id, int book_id) ;

    private:
      ConnectionAcceptor m_conn_acceptor;
      std::thread aAcceptorThread;
      std::thread aTrafficManagerThread;

      std::vector<std::string> args; //request args
      std::vector<std::string> all_books; //books which are returned from the server
};
