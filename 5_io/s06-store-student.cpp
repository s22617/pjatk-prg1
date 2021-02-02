#include <fcntl.h>
#include <s22617/Student.h>
#include <unistd.h>

#include <iostream>
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
    auto student = Student{"Daniel", "Wirzba", 22617, 1, 0};

    auto name = std::string{"./student.txt"};
    auto fd   = open(name.c_str(), O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);

    auto buf = std::string{student.name} + "\n" + std::string{student.surname}
               + "\n" + std::to_string(student.index) + "\n"
               + std::to_string(student.curr_term) + "\n"
               + std::to_string(student.avg_grade) + "\n";
    auto n = write(fd, buf.data(), buf.size());
    if (n == -1) {
        perror("write(2)");
    }

    close(fd);


    return 0;
}
