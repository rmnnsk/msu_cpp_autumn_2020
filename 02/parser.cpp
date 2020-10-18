#include "parser.h"

std::vector<std::string> TokenParser::parse(const std::string& st)
{
    start_callback();
    std::vector<std::string> res;
    std::string cur;
    size_t cur_ind = 0;
    int cur_mode = 0; // 0 - number, 1 - string.
    while (cur_ind < st.size()) {
        int cur_sym = static_cast<int>(st[cur_ind]);
        if (isspace(cur_sym)) {
            if (!cur.empty()) {
                res.push_back(cur);
                if (cur_mode == 0) {
                    number_token_callback(cur);
                } else {
                    string_token_callback(cur);
                }
                cur = "";
                cur_mode = 0;
            }
            cur_ind++;
            continue;
        }
        cur += st[cur_ind];
        if (!isdigit(cur_sym)) {
            cur_mode = 1;
        }
        cur_ind++;
    }
    if (!cur.empty()) {
        res.push_back(cur);
        if (cur_mode == 0) {
            number_token_callback(cur);
        } else {
            string_token_callback(cur);
        }
    }
    finish_callback();
    return res;
}

void TokenParser::SetStartCallback(const std::function<void()>& st_callback)
{
    start_callback = st_callback;
}

void TokenParser::SetNumberCallback(const std::function<void(std::string token)>& num_callback)
{
    number_token_callback = num_callback;
}

void TokenParser::SetStringCallback(const std::function<void(std::string token)>& str_callback)
{
    string_token_callback = str_callback;
}

void TokenParser::SetFinishCallback(const std::function<void()>& fin_callback)
{
    finish_callback = fin_callback;
}