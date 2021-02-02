#include <fcntl.h>
#include <s22617/Student.h>
#include <unistd.h>
#include <array>
#include <iostream>
#include <sstream>

auto Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Imie: " << name << "\nNazwisko: " << surname << "\nIndeks ucznia: s"
        << index << "\nAktualny semestr: " << curr_term
        << "\nŚrednia ocen: " << avg_grade;
    return out.str();
}

auto main() -> int
{
    auto name = std::string{"./student.txt"};
    auto fd   = open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    std::array<char, 4096> buf{0};

    auto const n = read(fd, buf.data(), buf.size());

    if (n == -1) {
        perror("read(2)");
    } else {
        auto file_output = std::string{};
        file_output      = std::string{buf.data(), static_cast<size_t>(n)};
        std::istringstream ss(file_output);
        std::array<std::string, 5> info;

        for (int i = 0; i < 5; i++) {
            ss >> info[i];
        }
        auto student = Student{info[0],
                               info[1],
                               std::stoi(info[2]),
                               std::stoi(info[3]),
                               std::stod(info[4])};
        std::cout << student.to_string() << "\n";
    }

    close(fd);

    return 0;
}
