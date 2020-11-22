//#ifndef S22617_STUDENT_H
//#define S22617_STUDENT_H

#include <string>
#include <sstream>


struct Student {
    std::string name, surname;
    int index, curr_term;
    double avg_grade;
    
    Student(std::string n, std::string sur_n, int i, int cur_t, double avg_g) {
        name = n;
        surname = sur_n;
        index = i;
        curr_term = cur_t;
        avg_grade = avg_g;
    }

    auto to_string() const -> std::string;
};

//#endif
