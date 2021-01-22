#include <cstdlib>
#include <sstream>
#include <string>

enum class TIME_OF_DAY { rano, dzien, wieczor, noc };

struct Time {
    unsigned hour, minute, second;

    Time(unsigned h, unsigned m, unsigned s)
    {
        hour   = h;
        minute = m;
        second = s;
    }

    auto to_string() const -> std::string;
    auto check_time() -> void;
    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;

    auto time_of_day() -> enum TIME_OF_DAY;
    static auto to_string(TIME_OF_DAY) -> std::string;

    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Time;

    auto operator+(Time const& time) const -> Time;
    auto operator-(Time const& time) const -> Time;
    auto operator<(Time const& time) const -> bool;
    auto operator>(Time const& time) const -> bool;
    auto operator==(Time const& time) const -> bool;
    auto operator!=(Time const& time) const -> bool;
};
