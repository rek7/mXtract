class process_operations : public misc {
    public:
        process_operations(pid_t proc_pid) {
            pid = proc_pid;
        }

        vector<vector<string>> get_ranges(void)
        {
            vector<vector<string>> map;
            ifstream maps_file("/proc/" + to_string(pid) + "/maps");
            regex parse("(\\S+-\\S+)\\s(.{4})\\s(\\d{8})\\s(\\d\\d:\\d\\d)\\s(\\d+)\\s+(\\S+)");
            if(maps_file.is_open()) {
                for(string line;getline(maps_file, line);)
                {
                    smatch m;
                    if(regex_search(line, m, parse)) {
                        vector<string> info;
                        if(string(m[2])[0] == 'r') { // checking if memory is readable
                            info.push_back(string(m[1]));
                            info.push_back(string(m[6]));
                        }
                        if(option.is_writable && string(m[2])[1] == 'w') {
                            //cout << "writable Memory: " << m[6] << endl;
                            info.push_back("true");
                            //format_print("Writable Memory Range: " + string(m[6]), YELLOW, '!', 1, true, false);
                        }
                        map.push_back(info);
                    }
                }
            }
            return map;
        }

        long read_data(void *addr)
        {
            long read = ptrace(PTRACE_PEEKTEXT, pid, addr, NULL);
            return ((read != -1) ? read : false);
        }

        void *start_read(void *from_addr, int len)
        {
            if ((len % sizeof(void *)) != 0) {
                format_print("MALFORMED MEMORY ADDRESS", RED, '-', 1);
                return NULL;
            }
            
            void *data = calloc(len, 1);
            if (!data) {
                return NULL;
            }
            errno = 0;
            for(size_t offset = 0; offset < len; offset += sizeof(long)) {
                long word = read_data((void *)(from_addr+offset));
                if (!word && errno) {
                    free(data);
                    return NULL;
                }
                memcpy((uint8_t *)data+offset, &word, sizeof(word));
            }
            return data;
        }

        string proc_env(void) 
        {
            string file_content;
            ifstream read_environ("/proc/" + to_string(pid) + "/environ"); 
            if(read_environ.is_open()) {
                getline(read_environ, file_content); // its a single line
            }
            return file_content;
        }

        string proc_info(void)
        {
            string content;
            struct stat st = {0};
            if (lstat(string("/proc/" + to_string(pid) + "/stat").c_str(), &st) != -1) {
                struct passwd *pw = getpwuid(st.st_uid);
                if(pw) {
                    content += string(string(pw->pw_name) + ":" + to_string(st.st_gid) + ":" + to_string(st.st_atime));
                    format_print(string("Being Run By: '" + string(pw->pw_name) + "' GUID: '" + to_string(st.st_gid) + 
                        "' Program Started: '" + formatted_time("%m/%d/%y %X", st.st_atime)) + "'", YELLOW, '!', 1, false, false);
                } else {
                    format_print("Unable to Get Process Info", RED, '-', 1, false, false);
                }
            }
            return content;
        }

        bool attach_pid(void)
        {
            return ((ptrace(PTRACE_ATTACH, pid, NULL, NULL) >= 0) ? true : false);
        }

        bool detach_pid(void)
        {
            return ((ptrace(PTRACE_DETACH, pid, NULL, NULL) >= 0) ? true : false);
        }

        ~process_operations(void) {
            detach_pid();
        }
    private:
        pid_t pid;
};