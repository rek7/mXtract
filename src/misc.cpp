class misc {
    public:
    vector <string> tokenize(string parse_str, char schar)
    {
        vector <string> results;
        stringstream ssline(parse_str);
        for(string split; getline(ssline, split, schar);)
        {
            results.push_back(split);
        }
        return results;
    }

    bool write_dump(string data, string name)
    {
        ofstream dump(option.directory + name, ios::app);
        if(dump.is_open()) {
            dump << data << endl;
            dump.close();
            return true;
        }
        return false;
    }

    bool is_dir(string dir)
    {
        struct stat st;
        if(!stat(dir.c_str(), &st)) {
            if(st.st_mode & S_IFDIR) {
                return true;
            }
        }
        return false;
    }

    int str_to_int(string convert)
    {
        try {
            return stoi(convert);
        } catch(...) {
            return 0;
        }
    }

    string formatted_time(char *time_format, time_t current = time(NULL))
    {
        struct tm current_time = *localtime(&current);
        char buf[80];
        strftime(buf, sizeof(buf), time_format, &current_time);
        return buf;
    }

    void format_print(string print, string color, char status, int indent_level=0, bool is_verbose=false, bool is_time=true) {
        if(is_verbose && !option.is_verbose) {
            return;
        }
        string time = formatted_time("%X");
        cout << string(indent_level, ' ') << (indent_level > 1 ? "│" : "")
        << (indent_level ? " ├" : "") << (option.is_colored ? color : "") //https://www.copypastecharacter.com/all-characters
        << (is_time ? "[" + time + "] " : "") << "[" << status << "] " << print
        << NORMAL << endl << flush;
    }

    string pid_to_name(string pid)
    {
        ifstream cmdline("/proc/" + pid + "/cmdline");
        string name;
        getline(cmdline, name);
        return name;
    }

    static bool invalid_char(char c) 
    {
        return !(c >= 32 && c <= 127);   
    }

    void strip_unicode(string &str) //https://stackoverflow.com/questions/10178700/c-strip-non-ascii-characters-from-string/15813530
    { 
        str.erase(remove_if(str.begin(),str.end(), invalid_char), str.end());  
    }

};