#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fcntl.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>


auto runFileServer(int client_sock) -> void {
    std::array<char, 4096> buf{0};
    std::cout << "Client connected to FileServer\n";
    
    auto fileOutput = std::string{};
    auto fileLocation = std::string{};
    while(true){
        memset(buf.data(), 0, sizeof(buf));
        auto bytesReceived = read(client_sock, buf.data(), sizeof(buf));
        if (bytesReceived == -1)
        {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected from FileServer\n";
            break;
        }
        fileLocation = std::string(buf.data(), 0, bytesReceived);
        if (access(fileLocation.c_str(), F_OK) != 0)
        {
            auto alert = std::string{":("};
            write(client_sock, alert.data(), alert.length());
        } else {
            auto fd = open(fileLocation.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
            auto const n = read(fd, buf.data(), sizeof(buf));
            if (n == -1)
            {
                perror("read(2)");
            } else {    
                fileOutput = fileLocation + "\n" + std::string{buf.data(), static_cast<size_t>(n)};
                write(client_sock, fileOutput.data(), fileOutput.length() - 1);
            }
        }   
    }
    close(client_sock);
}

auto runEchoServer(int client_sock) -> void {
    std::array<char, 4096> buf{0};
    std::cout << "Client connected to EchoServer\n";
    
    while(true){
        memset(buf.data(), 0, sizeof(buf));
        auto bytesReceived = read(client_sock, buf.data(), sizeof(buf));
        if (bytesReceived == -1)
        {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0)
        {
            std::cout << "Client diconnected from EchoServer\n";
            break;
        }
        write(client_sock, buf.data(), bytesReceived + 1);
    }
    close(client_sock);
}

auto runRandomNoteServer(int client_sock) -> void {
    std::vector<std::string> messages{};
    std::array<char, 4096> buf{0};
    std::cout << "Client connected to RandomNoteServer\n";
    while (true)
    {
        memset(buf.data(), 0, sizeof(buf));
        auto bytesReceived = read(client_sock, buf.data(), sizeof(buf));
        if (bytesReceived == -1)
        {
            perror("Error. Quitting\n");
            break;
        }
        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected from RandomNoteServer\n";
            break;
        }
        auto message = std::string(buf.data(), 0, bytesReceived);
        messages.push_back(message);
        std::cout << message << "\n";
        auto random = messages[rand() % messages.size()];
        write(client_sock, random.data(), random.length());
    }
    close(client_sock);
    
}

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
    
    
    auto message = std::string{};
    while (true) {

        auto client_sock = accept(sock, nullptr, nullptr);
        std::array<char, 32> buf{0};
        
        while (true){
            
            memset(buf.data(), 0, sizeof(buf));
            auto bytesReceived = read(client_sock, buf.data(), sizeof(buf));

            if (bytesReceived == -1) {
                perror("Error. Quitting\n");
                break;
            }
            if (bytesReceived == 0) {
                std::cout << "Client disconnected\n";
                close(client_sock);
                break;
            }
            auto input = std::string(buf.data(), 0, bytesReceived);
            if (input == "rns")
            {
                message = "Connected to Random Note Server";
                write(client_sock, message.data(), message.length());
                runRandomNoteServer(client_sock);
                break;
            }
            if (input == "es")
            {
                message = "Connected to Echo Server";
                write(client_sock, message.data(), message.length());
                runEchoServer(client_sock);
                break;
            }
            if (input == "fs")
            {
                message = "Connected to File Server. Provide your file's location";
                write(client_sock, message.data(), message.length());
                runFileServer(client_sock);
                break;
            }
            else {
                message = "Wrong input, try again\n";
                write(client_sock, message.data(), message.length());
            }
        }
    }

    close(sock);
    shutdown(sock, SHUT_RDWR);

    return 0;
}
