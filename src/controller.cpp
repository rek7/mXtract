class controller : public misc {
    public:
    controller(void)
    {
        if(option.is_write || option.is_regex_write) {
            if(!is_dir(option.directory)) {
                if(mkdir(option.directory.c_str(), 0755)) {
                    format_print("ERROR CREATING OUTPUT DIRECTORY", RED, '-');
                    exit(errno);
                }
            }
        }
        format_print((r.load_regex() ? "Successfully Loaded Regex DB: '" + option.regex_db + "'" : "No Regexes Loaded"), YELLOW, '!');
    }
    
    bool is_read_section(string section) 
    {
        if(!option.dump_all) {
            return((section.find("heap") != -1 || section.find("stack") != -1) ? true : false);
        }
        return true;
    }
    
    bool process_pid(pid_t pid) 
    {
        process_operations process(pid);
        vector<vector<string>> ranges = process.get_ranges();
        if(!ranges.empty()) {
            string name = pid_to_name(to_string(pid));
            format_print("Scanning PID: '" + to_string(pid) + "' (" + name + ")", GREEN, '+');
            if(!process.attach_pid()) {
                format_print("ERROR ATTACHING TO PROCESS", RED, '-', 1, false, false);
                return false;
            }
            wait(NULL);
            for(auto &value: ranges) {
                if(value.size() > 1 && is_read_section(value[1])) {
                    format_print("Scanning Address Range: '" +  value[0] + "' Name: '" + value[1] + "'", GREEN, '+', 1, true, false);
                    vector<string> range = tokenize(value[0], '-');
                    long start_addr = strtol(range[0].c_str(), NULL, 16);
                    long end_addr = strtol(range[1].c_str(), NULL, 16);
                    if(start_addr > 0xFFFFFFFFFFFF) {
                        continue;
                    }
                    size_t len = end_addr-start_addr;
                    void *data = process.start_read((void *)start_addr, len);
                    if(data) {
                        stringstream tmp_buff;
                        tmp_buff.write((char *)data, len);
                        free(data);
                        string info = tmp_buff.str();
                        strip_unicode(info);
                        vector<string> results = r.regex_match(info);
                        if(option.is_regex_write && results.size() > 0)
                        {
                            for(auto &result: results) {
                                write_dump(name + ":" + result, "regex_results");
                            }
                        }
                        if(option.is_write) {
                            write_dump(value[0] + ": " + info, to_string(pid));
                        }
                    }
                    else {
                        format_print("ERROR SCANNING MEMORY RANGE", RED, '-', (option.is_verbose ? 2 : 1), false, false);
                    }
                }
            }
            return true;
        }
        format_print("PID Killed or Permission Denied: " + to_string(pid), RED, '-');
        return false;
    }
    
    void inter_pids(void)
    {
        DIR *proc_handle = opendir("/proc/");
        struct dirent *pids = {0};
        
        while((pids = readdir(proc_handle)))
        {
            if(pids->d_type == DT_DIR && isdigit(pids->d_name[0]) && atoi(pids->d_name) != getpid()) {
                pid_t pid = stoi(pids->d_name);
                process_pid(pid);
            }
        }
        closedir(proc_handle);  
    }
    
    void begin_scan(void)
    {
        if(option.pid) {
            process_pid(option.pid);
        }
        else {
            inter_pids();
        }
    }
    
    private:
        regex_lookup r;
};
