#include "includes.h"

using namespace std;

#include "info_structs.h"
#include "misc.cpp"
#include "regex_lookup.cpp"
#include "process_operations.cpp"
#include "arg.cpp"
#include "controller.cpp"

int main(int argc, char *argv[]) {
    arg a(argc, argv);
    a.parse_args();
    a.banner();
    a.warn_user();
    controller c;
    c.begin_scan();
    
    return EXIT_SUCCESS;
}