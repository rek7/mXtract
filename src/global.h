#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define GREEN "\e[32m"
#define LIGHT_GREEN "\e[92m"
#define YELLOW "\e[33m"
#define RED "\e[31m"
#define MAGENTA "\e[35m"
#define WHITE "\e[97m"
#define NORMAL "\e[39m"

#define VERSION 1.2

struct options {
    string regex_db;
    string regex_result_filename = "regex_results.txt";
    string directory = "pid/";
    pid_t pid = 0;
    bool suppress_banner = false;
    bool dump_all = false;
    bool is_proc_info = false;
    bool is_write_proc_info = false;
    bool is_verbose = false;
    bool is_write = false;
    bool is_colored = true;
    bool is_env_scan = false;
    bool is_regex_write = false;
};

#endif