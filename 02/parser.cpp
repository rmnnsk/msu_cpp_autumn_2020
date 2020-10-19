#include "parser.h"

std::vector<std::string> TokenParser::parse(const std::string &st)
{
    start_callback();
    std::vector<std::string> res;
    std::string cur;
    size_t cur_ind = 0;
    bool is_number = true;
    auto space_handler = [&]() {
        if (!cur.empty()) {
            res.push_back(cur);
            if (is_number) {
                number_token_callback(cur);
            } else {
                string_token_callback(cur);
            }
            cur = "";
            is_number = true;
        }
    };
    while (cur_ind < st.size()) {
        auto cur_sym = static_cast<unsigned char>(st[cur_ind]);
        if (isspace(cur_sym)) {
            space_handler();
            cur_ind++;
            continue;
        }
        cur += st[cur_ind];
        if (!isdigit(cur_sym)) {
            is_number = false;
        }
        cur_ind++;
    }
    space_handler();
    finish_callback();
    return res;
}

void TokenParser::SetStartCallback(const std::function<void()> &st_callback)
{
    start_callback = st_callback;
}

void TokenParser::SetNumberCallback(const std::function<void(std::string &token)> &num_callback)
{
    number_token_callback = num_callback;
}

void TokenParser::SetStringCallback(const std::function<void(std::string &token)> &str_callback)
{
    string_token_callback = str_callback;
}

void TokenParser::SetFinishCallback(const std::function<void()> &fin_callback)
{
    finish_callback = fin_callback;
}