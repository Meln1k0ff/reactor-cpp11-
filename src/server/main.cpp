#include "Server.h"



int main() {
    std::thread aAcceptorThread;
    std::thread aTrafficManagerThread;
    Server server(aAcceptorThread, aTrafficManagerThread);


}
