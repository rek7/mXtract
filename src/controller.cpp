class controller : public misc {
    public:
    controller(void)
    {
        if(option.is_write || option.is_regex_write || option.is_xml || option.is_html) {
            if(!is_dir(option.directory)) {
                if(mkdir(option.directory.c_str(), 0755)) {
                    format_print("ERROR CREATING OUTPUT DIRECTORY", RED, '-');
                    exit(errno);
                }
            }
        }
        format_print((r.load_regex() ? "Successfully Loaded Regex Database: '" + option.regex_db + "'" : "No Regexes Loaded"), YELLOW, '!');
    }
    
    bool is_read_section(string section) 
    {
        if(!option.dump_all) {
            return((section.find("heap") != -1 || section.find("stack") != -1) ? true : false);
        }
        return true;
    }
    
    void handle_data(string data, string proc_name, string found_location, string file_name)
    {
        if(!option.regex_db.empty()) {
            vector<string> results = r.regex_match(data);
            if((option.is_regex_write || option.is_html || option.is_xml) && !results.empty()) {
                for(auto &result: results) {
                    if(option.is_xml) {
                        write_dump("\t<result>\n\t\t<rname>" + proc_name + "</rname>", "results.xml");
                        write_dump("\t\t<range>" + found_location + "</range>", "results.xml");
                        write_dump("\t\t<regex_result>" + result + "</regex_result>\n\t<result>", "results.xml");
                    } else if(option.is_html) {
                        write_dump("<tr><td>" + proc_name + "</td>", "results.html");
                        write_dump("<td>" + found_location + "</td>", "results.html");
                        write_dump("<td>" + result + "</td></tr>", "results.html");
                    } else {
                        write_dump(proc_name + ":" + result, option.regex_result_filename);
                    }
                }
            }
        }
        if(option.is_write) {
            write_dump(found_location + ":" + data, "mem_" + file_name + ".dmp");
        }
    }
    
    bool process_pid(pid_t pid) 
    {
        process_operations process(pid);
        vector<vector<string>> ranges = process.get_ranges();
        if(!ranges.empty()) {
            string name = pid_to_name(to_string(pid));
            format_print("Scanning PID: '" + to_string(pid) + "' (" + name + ")", YELLOW, '!');
            if(option.is_proc_info) {
                string proc_info = process.proc_info();
                if(option.is_write_proc_info && !proc_info.empty()) {
                    write_dump(proc_info, "mem_" + to_string(pid) + ".dmp");
                }
            }
            if(option.is_env_scan) {
                string content = process.proc_env();
                format_print("Scanning Environment file", YELLOW, '!', 1, true, false);
                if(!content.empty()) {
                    handle_data(content, name, "environ", to_string(pid));
                } else {
                    format_print("ENV FILE EMPTY OR UNABLE TO READ", RED, '-', (option.is_verbose ? 2 : 1), false, false);
                }
            }
            if(!process.attach_pid()) {
                format_print("ERROR ATTACHING TO PROCESS", RED, '-', 1, false, false);
                return false;
            }
            wait(NULL);
            for(auto &value: ranges) {
                if(!value.empty() && is_read_section(value[1])) {
                    format_print("Scanning Address Range: '" +  value[0] + "' Name: '" + value[1] + "'", YELLOW, '!', 1, true, false);
                    if(value.size() == 3 && option.is_writable) {
                        format_print("Writable Memory Range" + (!option.is_verbose ? ": '" + value[0] + "'" : ""), YELLOW, '!', (option.is_verbose ? 2 : 1), false, false);
                    }
                    vector<string> range = tokenize(value[0], '-');
                    long start_addr = strtol(range[0].c_str(), NULL, 16);
                    long end_addr = strtol(range[1].c_str(), NULL, 16);
                    if(start_addr > 0xFFFFFFFFFFFF) {
                        format_print("MALFORMED MEMORY RANGE", RED, '-', (option.is_verbose ? 2 : 1), false, false);
                        continue;
                    }
                    size_t len = end_addr-start_addr;
                    void *data = process.start_read((void *)start_addr, len);
                    if(data) {
                        string info((char *)data, len);
                        free(data);
                        strip_unicode(info);
                        handle_data(info, name, value[0], to_string(pid));
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
                pid_t pid = atoi(pids->d_name);
                process_pid(pid);
            }
        }
        closedir(proc_handle);  
    }
    
    void begin_scan(void)
    {
        if(option.is_xml) {
            write_dump("<results>\n\t<time>" + formatted_time("%x") + "</time>", "results.xml");
        } else if(option.is_html) {
            write_dump(top_section, "results.html");
            write_dump("<h2>Scan Results For: " + formatted_time("%x, %X") + "</h2>", "results.html");
            write_dump(body, "results.html");
        }

        if(option.pid) {
            process_pid(option.pid);
        } else {
            inter_pids();
        }

        if(option.is_xml) {
            write_dump("</results>", "results.xml");
        } else if(option.is_html) {
            write_dump(footer, "results.html");
        }

        format_print("Finished", YELLOW, '!');
    }
    
    private:
        regex_lookup r;
};
