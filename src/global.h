#ifndef __INFO_STRUCTS_H__
#define __INFO_STRUCTS_H__

#define GREEN "\e[32m"
#define LIGHT_GREEN "\e[92m"
#define YELLOW "\e[33m"
#define RED "\e[31m"
#define NORMAL "\e[39m"

struct options {
    string regex_db;
    string directory = "pid/";
    pid_t pid = 0;
    bool dump_all = false;
    bool is_verbose = false;
    bool is_write = false;
    bool is_colored = true;
    bool is_regex_write = false;
    bool suppress_banner = false;
}; options option;

#endif
