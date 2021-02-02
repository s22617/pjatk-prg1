#include <fcntl.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <sstream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }

    auto fname = std::string{argv[1]};

    if (access(fname.c_str(), F_OK) != 0) {
        std::cout << "File does not exist"
                  << "\n";
        return 1;
    }

    auto fd = open(fname.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("?");
        return 1;
    }

    std::cout << std::string{buf.data(), static_cast<size_t>(n)};

    close(fd);
    return 0;
}
