class arg : public misc{
    public:
        arg(int argc, char *argv[])
        {
            args = argv;
            argn = argc;
        }
        void banner(void) {
            if(!option.suppress_banner) {
                cout << (option.is_colored ? LIGHT_GREEN : "")<< "           __  ___                  _     " 
                    << "{ " << (option.is_colored ? MAGENTA : "") << "V" << VERSION << (option.is_colored ? LIGHT_GREEN : "") << " }"
                    << endl << "  _ __ ___ \\ \\/ / |_ _ __ __ _  ___| |_ "
                    << endl << " | '_ ` _ \\ \\  /| __| '__/ _` |/ __| __|"
                    << endl << " | | | | | |/  \\| |_| | | (_| | (__| |_ "
                    << endl << " |_| |_| |_/_/\\_\\\\__|_|  \\__,_|\\___|\\__|  "
                    << (option.is_colored ? WHITE : "") << "https://github.com/rek7/mXtract"
                    << (option.is_colored ? NORMAL : "") << endl; // http://patorjk.com/software/taag/#p=display&f=Doom&t=mXtract
            }
        }
        
        void usage(void)
        {
            cout << "USAGE: " << args[0] << " -(args)" << endl
            << "\t-v\tEnable Verbose Output" << endl
            << "\t-s\tSuppress Banner" << endl
            << "\t-h\tHelp" << endl
            << "\t-c\tsuppress colored output" << endl
            << "\t-r=\tRegex DB" << endl
            << "\t-a\tScan all memory ranges not just heap/stack" << endl
            << "\t-w\tWrite raw memory to file Default directory is " << option.directory << endl
            << "\t-o\tWrite regex output to file" << endl
            << "\t-d=\tCustom Ouput Directory" << endl
            << "\t-p=\tSpecify single pid to scan" << endl
            << "\tEither -r= or -w needed" << endl
            << "Example usage: " << args[0] << " -w -a -d=/tmp/output/ -o -r=regex.db" << endl;
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
                    else if(arg == "-s") {
                        option.suppress_banner = true;
                    }
                    else if(arg == "-a") {
                        option.dump_all = true;
                    }
                    else if(arg == "-c") {
                        option.is_colored = false;
                    }
                    else if(arg == "-o") {
                        option.is_regex_write = true;
                    }
                    else if(arg == "-w") {
                        is_required = true;
                        option.is_write = true;
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
                format_print("Required args needed -h for help", RED, '-');
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
