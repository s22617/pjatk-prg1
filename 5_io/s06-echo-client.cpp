#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <unistd.h>

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
    //client
    auto server_sock = connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (server_sock == -1)
    {
        return 1;
    }

    char buf[4096];
    auto input = std::string{};

    while (true){
        
        std::cout << "> ";
        getline(std::cin, input);
        
        // send to server
        int writeRes = write(sock, input.c_str(), input.size() + 1);
        if (writeRes == -1)
        {
            perror("Error. Quitting\n");
            continue;
        }
        memset(buf, 0, 4096);
        int bytesReceived = read(sock, buf, 4096);
        if (bytesReceived == -1)
        {
            std::cout << "Error 2.\n";
        } else {
            std::cout << "Server: " << std::string(buf, bytesReceived) << "\n";
        }
    }
   
    close(sock);

    return 0;
}