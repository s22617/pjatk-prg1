#include <s22617/Student.h>

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
    std::cout << student.to_string() << "\n";
    return 0;
}
