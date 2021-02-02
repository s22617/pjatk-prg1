#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <unistd.h>

#include <fcntl.h>
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
        if (access(message.c_str(), F_OK) != 0){
            auto alert = std::string{":("};
            strcpy(buf, alert.c_str());
            write(client_sock, buf, alert.length());
        }
        else {
            auto fd = open(message.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
            auto const n = read(fd, buf, 4096);
            if (n == -1) {
                perror("read(2)");
            }
            else{
                auto file_output = std::string{};
                file_output = message + "\n" + std::string{buf, static_cast<size_t>(n)};
                strcpy(buf, file_output.c_str());
                write(client_sock, buf, file_output.length() - 1);
                
                //std::cout << file_output << "\n";
            }
        }
        
    }

    shutdown(sock, SHUT_RDWR);
    close(client_sock);

    return 0;
}
