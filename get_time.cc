#include "iostream"
#include "ctime"
#include "time.h"
#include "map"

// enum could also be used maybe?? dunno how string from user will be translated to the enum code.
// map of month_codes -> implement 0-based month codes that can be intuitive to the USER

int main() {
    std::cout << "\033[1;35mWelcome to Unix epoch converter.\033[0m" << std::endl;
    std::cout << "\033[1;36m(currently no support for Daylight Savings)\033[0m" << std::endl;
    std:: cout << std::endl;

    std::map<std::string, int> month_codes = {
        {"JAN",  0},
        {"FEB",  1},
        {"MAR",  2},
        {"APR",  3},
        {"MAY",  4},
        {"JUN",  5},
        {"JUL",  6},
        {"AUG",  7},
        {"SEP",  8},
        {"OCT",  9},
        {"NOV", 10},
        {"DEC", 11},
    };

    u_int year = 0;
    u_int month = 0;
    u_int day = 0;
    u_int hour = 0;
    u_int min = 0;
    u_int sec = 0;

    char offset_req = ' ';
    bool is_offset = false;
    char offset_type = ' ';
    int offset_h = 0;
    int offset_m = 0;
    int total_offset = 0;

    std::string offset_time = " GMT +0000";

    std::cout << "enter year: "; std::cin >> year;
    std::cout << "enter month (0-11): "; std::cin >> month;
    std::cout << "enter day (1-31): "; std::cin >> day;
    std::cout << "enter hour (0-23): "; std::cin >> hour;
    std::cout << "enter minutes (0-59): "; std::cin >> min;
    std::cout << "enter seconds (0-60): "; std::cin >> sec;

    std::cout << "does this time have a difference from GMT/UTC? (y/n) "; std::cin >> offset_req;
    if ('y' == offset_req) {
        is_offset = true;
        std::cout << "where is your timezone? (+ for east OR - for west) "; std::cin >> offset_type;
        std::cout << "enter the differnce in hours of your timezone from GMT/UTC (include negative sign if reqd.): "; std::cin >> offset_h;
        std::cout << "enter the differnce in minutes of your timezone from GMT/UTC (include negative sign if reqd.): "; std::cin >> offset_m;

        total_offset = ( ((offset_h * 60) + (offset_m)) * 60 );

        if ('+' == offset_type) {
            offset_time = " GMT +" + std::to_string(offset_h) + ":" + std::to_string(offset_m);
            std::cout << "total offset in Unix epoch: " << total_offset << std::endl;
        } else if ('-' == offset_type) {
            offset_time = " GMT -" + std::to_string(abs(offset_h)) + ":" + std::to_string(abs(offset_m));
            std::cout << "total offset in Unix epoch: " << total_offset << std::endl;
        } else {
            std::cerr << "\033[37;41mmake sure you gave the correct location of your timezone\033[0m\n";
        }
    }

    // get Unix epoch for current GMT & get the date for it.
    // std::tm *date;
    // std::time_t timestamp;
    // time(&timestamp);
    // date = gmtime(&timestamp);

    // convert date to Unix timestamp - depends on what is the machine's timezone...
    std::tm user_date = {};
    user_date.tm_year = year - 1900;
    user_date.tm_mon = month;
    user_date.tm_mday = day;
    user_date.tm_hour = hour;
    user_date.tm_min = min;
    user_date.tm_sec = sec;
    user_date.tm_isdst = 0;  // daylight saving off
    std::time_t timestamp = mktime(&user_date);

    // std::cout << timestamp << std::endl;

    char time_buf[80];

    if (-1 == timestamp) std::cerr << "\033[4;31mfailed to convert\033[0m" << std::endl;
    else {
        strftime(time_buf, sizeof(time_buf), "%a %Y-%m-%d %H:%M:%S", &user_date);
        std::cout << "Unix timestamp for \033[4;33m" << time_buf << offset_time << "\033[0m : " << timestamp - total_offset << std::endl;
    }

    return 0;
}
