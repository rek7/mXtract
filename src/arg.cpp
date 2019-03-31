class arg : public misc{
    public:
        arg(int argc, char *argv[])
        {
            args = argv;
            argn = argc;
        }

        void banner(void) {
            if(!option.suppress_banner) {
                cout << (option.is_colored ? LIGHT_GREEN : "") << "           __  ___                  _     " 
                << "{ " << (option.is_colored ? MAGENTA : "") << "V" << VERSION << (option.is_colored ? LIGHT_GREEN : "") << " }"
                << endl << "  _ __ ___ \\ \\/ / |_ _ __ __ _  ___| |_ "
                << endl << " | '_ ` _ \\ \\  /| __| '__/ _` |/ __| __|"
                << endl << " | | | | | |/  \\| |_| | | (_| | (__| |_ "
                << endl << " |_| |_| |_/_/\\_\\\\__|_|  \\__,_|\\___|\\__|  "
                << (option.is_colored ? WHITE : "") << "https://github.com/rek7/mXtract"
                << (option.is_colored ? NORMAL : "") << endl; // http://patorjk.com/software/taag/#p=display&f=Standard&t=mXtract
            }
        }
        
        void usage(void)
        {
            cout << "Usage: " << args[0] << " [args]" << endl
            << "General:" << endl
            << "\t-v\tEnable Verbose Output" << endl
            << "\t-s\tSuppress Banner" << endl
            << "\t-h\tHelp" << endl
            << "\t-c\tSuppress Colored Output" << endl
            << "Target and Regex:" << endl
            << "\t-i\tShow Detailed Process/User Info" << endl
            << "\t-a\tScan all Memory Ranges not just Heap/Stack" << endl
            << "\t-e\tScan Process Environment Files" << endl
            << "\t-w\tCheck if Memory Range is Writable" << endl
            << "\t-r=\tRegex Database to Use" << endl
            << "\t-p=\tSpecify Single PID to Scan" << endl
            << "Output:" << endl
            << "\t-x\tFormat Regex Results to XML" << endl
            << "\t-r\tFormat Regex Results to an HTML Document" << endl
            << "\t-wm\tWrite Raw Memory to File Default Directory is: '" << option.directory << "'" << endl
            << "\t-wi\tWrite Process Info to Beginning of File (Used in Conjunction with -w)" << endl
            << "\t-wr\tWrite Regex Output to File (Will Appear in the Output Directory)" << endl
            << "\t-f=\tRegex Results Filename Default is: '" << option.regex_result_filename << "'" << endl
            << "\t-d=\tCustom Ouput Directory" << endl
            << "Either -r= or -wm needed" << endl
            << "Example usage: '" << args[0] << " -wm -wr -e -i -d=/tmp/output/ -r=example_regexes.db'" << endl;
        }
        bool parse_args(void) // returns false when program isnt able to be run
        {
            bool is_required = false;
            for (int i = 1; i < argn; ++i) {
                if(strlen(args[i]) >= 2) {
                    string arg = string(args[i]).substr(0, (strlen(args[i]) == 2 ? 2 : 3));
                    if(arg == "-v") {
                        option.is_verbose = true;
                    }
                    else if(arg == "-d=") {
                        option.directory = string(args[i]).substr(3, string(args[i]).size());
                    }
                    else if(arg == "-p=") {
                        int convert = str_to_int(string(args[i]).substr(3, string(args[i]).size()));
                        if(!convert) {
                            banner();
                            format_print("NUMBER NEEDED AS PROCESS ID", RED, '-');
                            return false;
                        }
                        option.pid = convert;
                    }
                    else if(arg == "-r=") {
                        is_required = true;
                        option.regex_db = string(args[i]).substr(3, string(args[i]).size());
                    }
                    else if(arg == "-f=") {
                        option.regex_result_filename = string(args[i]).substr(3, string(args[i]).size());
                    }
                    else if(arg == "-wr") {
                        option.is_regex_write = true;
                    }
                    else if(arg == "-wi") {
                        option.is_write_proc_info = true;
                    }
                    else if(arg == "-wm") {
                        is_required = true;
                        option.is_write = true;
                    }
                    else if(arg == "-s") {
                        option.suppress_banner = true;
                    }
                    else if(arg == "-w") {
                        option.is_writable = true;
                    }
                    else if(arg == "-r") {
                        option.is_html = true;
                    }
                    else if(arg == "-a") {
                        option.dump_all = true;
                    }
                    else if(arg == "-i") {
                        option.is_proc_info = true;
                    }
                    else if(arg == "-c") {
                        option.is_colored = false;
                    }
                    else if(arg == "-x") {
                        option.is_xml = true;
                    }
                    else if(arg == "-e") {
                        option.is_env_scan = true;
                    }
                    else if(arg == "-h") {
                        banner();
                        usage();
                        return false;
                    }
                }
            }
            if(!is_required)
            {
                banner();
                format_print("Required Args Needed -h For help", RED, '-');
                return false;
            }
            return true;
        }
        
        void warn_user(void)
        {
            if(geteuid() != 0) {
                format_print("Running as root is recommended as not all PIDs will be scanned", YELLOW, '!');
            }
        }
        
    protected:
        char **args;
        int argn;
};