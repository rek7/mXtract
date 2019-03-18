#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>

extern "C" {
    #include <dirent.h>
    #include <sys/ptrace.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdbool.h>
}

#endif