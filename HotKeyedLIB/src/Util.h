#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

namespace Util {
	static inline bool isNumber(const std::string& s) {
		return !s.empty() && std::find_if(s.begin(),
										  s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
	}
    static inline bool caseInsensitiveEquals(const std::string& s1, const std::string& s2) {
        return std::ranges::equal(s1, s2, [](auto a, auto b) {return std::tolower(a) == std::tolower(b); });
    }
    static inline std::vector<std::string> split(std::string& s, const std::string& delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }
    //taken from https://stackoverflow.com/a/24315631
    static inline std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        return str;
    }
}