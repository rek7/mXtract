class regex_lookup : public misc {
    public:
        vector<string> search_regex(string info, regex search)
        {
            vector<string> regex_results;
            smatch m;
            string::const_iterator start( info.cbegin() );
            while(regex_search(start, info.cend(), m, search))
            {
                if (find(regex_results.begin(), regex_results.end(), m[0]) == regex_results.end()) { // no duplicates
                    format_print("Matching Regex Entry: '" + string(m[0]) + "'", GREEN, '+', 1, false, false);
                    regex_results.push_back(m[0]);
                }
                start = m.suffix().first;
            }
            
            return regex_results;
        }

        vector<string> regex_match(string info)
        {
            vector<string> results;
            for(auto &regex_string: regexes) {
                vector<string> result = search_regex(info, regex_string);   
                move(result.begin(), result.end(), back_inserter(results));
            }
            
            return results;
        }

        bool load_regex(void)
        {
            if(!option.regex_db.empty()) {
                ifstream read_regex(option.regex_db);
                if(read_regex.is_open()) {
                    for(string line; getline(read_regex, line);) {
                        regexes.push_back(regex(line));
                    }
                    return true;
                }
                format_print("ERROR OPENING REGEX DB: " + option.regex_db, RED, '-');
                exit(EXIT_FAILURE);
            }
            else {
                //regexes.push_back("(\\d{1,3}(\\.\\d{1,3}){3})");
            }
            return false;
        }
        
    private:
        vector<regex> regexes;
};
