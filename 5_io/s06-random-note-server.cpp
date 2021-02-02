#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <unistd.h>
#include <vector>

auto main() -> int
{
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Can't create a socket");
        return 1;
    }
    auto const ip = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};

    sockaddr_in addr;
    //prepare the address
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);
    //server
    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(sock, SOMAXCONN);
     
    auto client_sock = accept(sock, nullptr, nullptr);
    
    close(sock);

    std::vector<std::string> messages {};
    char buf[4096];
    while (true){

        memset(buf, 0, 4096);
        int bytesReceived = read(client_sock, buf, 4096);
        
        if (bytesReceived == -1)
        {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected\n";
            break;
        }
        auto message = std::string(buf, 0, bytesReceived);
        std::cout << message
                    << std::endl;
        messages.push_back(message);
        auto random = messages[rand() % messages.size()];
        
        std::cout << random << "\n";
        
        write(client_sock, buf, bytesReceived + 1);
    }
   
    shutdown(sock, SHUT_RDWR);
    close(client_sock);

    return 0;
}
