#include <s22617/Time.h>

#include <iostream>

auto Time::count_seconds() const -> uint64_t
{
    return hour * 3600 + minute * 60 + second;
}

auto Time::count_minutes() const -> uint64_t
{
    return hour * 60 + minute;
}

auto Time::time_to_midnight() const -> Time
{
    Time new_time = Time(minute != 0 ? 23 - hour : 24 - hour,
                         second != 0 ? 59 - minute : 60 - minute,
                         60 - second);

    return new_time;
}

auto Time::time_of_day() -> enum TIME_OF_DAY {
    if (hour > 4 && hour < 12) return TIME_OF_DAY::rano;
    else if (hour > 11 && hour < 18) return TIME_OF_DAY::dzien;
    else if (hour > 17 && hour < 23) return TIME_OF_DAY::wieczor;
    else return TIME_OF_DAY::noc;
}

auto Time::to_string(TIME_OF_DAY time) -> std::string
{
    switch (time) {
    case TIME_OF_DAY::rano:
        return "Rano";
    case TIME_OF_DAY::dzien:
        return "Dzień";
    case TIME_OF_DAY::wieczor:
        return "Wieczor";
    default:
        return "Noc";
    }
}

auto Time::check_time() -> void
{
    if (second > 59) {
        second = 0;
        minute++;
    }
    if (minute > 59) {
        minute = 0;
        hour++;
    }
    if (hour > 23) {
        hour = 0;
    }
}

auto Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << hour << ":" << minute << ":" << second;

    return out.str();
}

auto Time::next_hour() -> void
{
    hour++;
    check_time();
}

auto Time::next_minute() -> void
{
    minute++;
    check_time();
}

auto Time::next_second() -> void
{
    second++;
    check_time();
}

auto main() -> int
{
    Time test = Time(23, 59, 58);
    test.next_second();

    // zadanie - czas

    std::cout << "(test)\nGodzina: " << test.to_string() << "\n";

    // zadanie - pora dnia

    std::cout << "(test)\nPora dnia: " << test.to_string(test.time_of_day())
              << "\n";
    Time test_2 = Time(11, 2, 4);
    std::cout << "(test_2)\nPora dnia: "
              << test_2.to_string(test_2.time_of_day()) << "\n";

    // zadanie - Arytmetyka

    Time result = test_2 - test;
    std::cout << "test_2 - test = " << result.to_string() << "\n";

    if (test_2 != test)
        std::cout << "test_2 != test -> TRUE"
                  << "\n";

    // zadanie - Sekundy do Północy

    std::cout << "test_2 - passed seconds: " << test_2.count_seconds() << "\n";
    std::cout << "test_2 - minutes to midnight: "
              << result.time_to_midnight().to_string() << "\n";

    // time_to_midnight

    Time test_3 = Time(23, 59, 59);
    std::cout << test_3.time_to_midnight().to_string() << "\n";


    return 0;
}
