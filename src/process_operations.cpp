class process_operations : public misc{
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
                        if(string(m[2])[0] == 'r') { // checking if memory is readable
                            vector<string> info;
                            info.push_back(string(m[1]));
                            info.push_back(string(m[6]));
                            map.push_back(info);
                        }
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
