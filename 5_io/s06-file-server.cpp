#include <arpa/inet.h>
#include <fcntl.h>
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
    std::array<char, 4096> buf{0};
    auto message     = std::string{};
    auto file_output = std::string{};
    while (true) {
        memset(buf.data(), 0, sizeof(buf));
        auto bytesReceived = read(client_sock, buf.data(), sizeof(buf));

        if (bytesReceived == -1) {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0) {
            std::cout << "Client disconnected\n";
            break;
        }
        message = std::string(buf.data(), 0, bytesReceived);
        std::cout << message << std::endl;
        if (access(message.c_str(), F_OK) != 0) {
            auto alert = std::string{":("};
            write(client_sock, alert.data(), alert.length());
        } else {
            auto fd      = open(message.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
            auto const n = read(fd, buf.data(), sizeof(buf));
            if (n == -1) {
                perror("read(2)");
            } else {
                file_output = message + "\n"
                              + std::string{buf.data(), static_cast<size_t>(n)};
                write(
                    client_sock, file_output.data(), file_output.length() - 1);
            }
        }
    }

    shutdown(client_sock, SHUT_RDWR);
    close(client_sock);
    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}
