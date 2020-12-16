//#ifndef S22617_STUDENT_H
//#define S22617_STUDENT_H

#include <sstream>
#include <string>


struct Student {
    std::string const name, surname;
    int const index;
    int curr_term;
    double avg_grade;

    Student(std::string n, std::string sur_n, int i, int cur_t, double avg)
            : name{n}
            , surname{sur_n}
            , index{i}
            , curr_term{cur_t}
            , avg_grade{avg}
    {}

    auto to_string() const -> std::string;
};

//#endif
