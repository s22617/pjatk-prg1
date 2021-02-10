#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>

auto main() -> int
{
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Can't create a socket");
        return 1;
    }
    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};

    sockaddr_in addr;
    // prepare the address

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);
    // server
    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(sock, SOMAXCONN);


    auto client_sock = accept(sock, nullptr, nullptr);

    close(sock);

    std::array<char, 4096> buf{0};
    while (true) {
        memset(buf.data(), 0, sizeof(buf));
        int bytesReceived = read(client_sock, buf.data(), sizeof(buf));

        if (bytesReceived == -1) {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0) {
            std::cout << "Client disconnected\n";
            break;
        }

        std::cout << std::string(buf.data(), 0, bytesReceived) << std::endl;

        write(client_sock, buf.data(), bytesReceived + 1);
    }

    shutdown(sock, SHUT_RDWR);
    close(client_sock);

    return 0;
}
