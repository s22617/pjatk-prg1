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
    auto to_string(TIME_OF_DAY) -> std::string;

    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Time;

    auto operator+(Time const& time) const -> Time
    {
        Time new_time =
            Time(hour + time.hour, minute + time.minute, second + time.second);
        if (new_time.second >= 60) {
            new_time.second -= 60;
            new_time.minute++;
        }
        if (new_time.minute >= 60) {
            new_time.minute -= 60;
            new_time.hour++;
        }
        if (new_time.hour >= 24)
            new_time.hour -= 24;

        return new_time;
    }
    auto operator-(Time const& time) const -> Time
    {
        Time new_time = Time(abs(hour - time.hour),
                             abs(minute - time.minute),
                             abs(second - time.second));

        return new_time;
    }

    auto operator<(Time const& time) const -> bool
    {
        return hour < time.hour
                   ? true
                   : (hour == time.hour && minute < time.minute
                          ? true
                          : (hour == time.hour && minute == time.minute
                                     && second < time.second
                                 ? true
                                 : false));
    }

    auto operator>(Time const& time) const -> bool
    {
        return hour > time.hour
                   ? true
                   : (hour == time.hour && minute > time.minute
                          ? true
                          : (hour == time.hour && minute == time.minute
                                     && second > time.second
                                 ? true
                                 : false));
    }
    auto operator==(Time const& time) const -> bool
    {
        return hour == time.hour && minute == time.minute
                       && second == time.second
                   ? true
                   : false;
    }
    auto operator!=(Time const& time) const -> bool
    {
        return hour != time.hour || minute != time.minute
                       || second != time.second
                   ? true
                   : false;
    }
};
