#include "includes.h"

using namespace std;

#include "global.h"

options option; // creating instance of options struct to fill in with user data

#include "misc.cpp"
#include "regex_lookup.cpp"
#include "process_operations.cpp"
#include "arg.cpp"
#include "controller.cpp"

int main(int argc, char *argv[]) {
    arg a(argc, argv);
    if(!a.parse_args()) {
        exit(EXIT_FAILURE);
    }
    a.banner();
    a.warn_user();
    controller c;
    c.begin_scan();
    return EXIT_SUCCESS;
}
