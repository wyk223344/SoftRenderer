#ifndef LOG_UTIL_H
#define LOG_UTIL_H

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <vector>

class LogUtil {
public:
    static void LogInfo(const char *format, ...) {
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
        str = str + "\n";
        printf(str.c_str());
    };
    static void LogWarning(const char *format, ...) {
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
        str = str + "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);//设置红色和绿色相加
        printf(str.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    };
    static void LogError(const char *format, ...) {
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
        str = str + "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//设置红色
        printf(str.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    };
    
};




#endif