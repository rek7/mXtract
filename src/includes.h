#ifndef __INCLUDES_H__
#define __INCLUDES_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cerrno>

extern "C" {
    #include <dirent.h>
    #include <sys/ptrace.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
}

#endif
