#ifndef STRING_UTIL_H
#define STRING_UTIL_H


class StringUtil {
public:
    static std::string Format(const char *format, ...) {
        std::string str;
        va_list args;
        va_start(args, format);
        {
            int nLength = _vscprintf(format, args);
            nLength += 1;  //上面返回的长度是包含\0，这里加上
            std::vector<char> vectorChars(nLength);
            _vsnprintf(vectorChars.data(), nLength, format, args);
            str.assign(vectorChars.data());
        }
        va_end(args);
        return str;
    }
};


#endif