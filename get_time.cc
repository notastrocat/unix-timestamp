#include "iostream"
#include "ctime"

int main() {
    std::tm date = {};  // structure to hold date & time info

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int sec = 0;

    std::cout << "enter year: "; std::cin >> year;
    std::cout << "enter month (0-11): "; std::cin >> month;
    std::cout << "enter day (1-31): "; std::cin >> day;
    std::cout << "enter hour (0-23): "; std::cin >> hour;
    std::cout << "enter minutes (0-59): "; std::cin >> min;
    std::cout << "enter seconds (0-60): "; std::cin >> sec;

    date.tm_year = year - 1900;
    date.tm_mon = month;
    date.tm_mday = day;
    date.tm_hour = hour;
    date.tm_min = min;
    date.tm_sec = sec;
    date.tm_isdst = 0;  // daylight saving off

    // learn how to use these params...
    // date.tm_gmtoff = -19800;
    // date.tm_zone = "ind";

    // Convert the tm structure to time_t (Unix timestamp)
    std::time_t timestamp = std::mktime(&date);
    char time_buf[80];

    if (-1 == timestamp) std::cerr << "\033[4;31mfailed to convert\033[0m" << std::endl;
    else {
        strftime(time_buf, sizeof(time_buf), "%a %Y-%m-%d %H:%M:%S %Z", &date);
        std::cout << "Unix timestamp for \033[4;33m" << time_buf << "\033[0m : " << timestamp - 19800 << std::endl;;
    }

    return 0;
}
