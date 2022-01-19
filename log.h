/**
 * @file log.h
 * @author duanyanling@saimo.ai
 * @brief 日志相关定义
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


/********************************************** 宏定义 ******************************************************/


#define MAX_SIZE_BYTE       10 * 1024
#define MAX_FILE_NUM        5

#define PRINT_LEVEL         D_VERBOSE
#define PRINT_INTO_FILE     true



// Copy from Common.h
#ifndef COMMON_H
#define COMMON_H

#define D_FATAL       (0)  /* 导致进程退出 */
#define D_ERROR       (1)  /* 模块内 或者 不导致进程退出的错误时间 */
#define D_WARN        (2)  /* 警告/会出现潜在错误 */
#define D_INFO        (3)  /* 在粗粒度上突出运行过程 */
#define D_DEBUG       (4)  /* 在细粒度上调试 */
#define D_VERBOSE     (5)  /* 打印详细的数据 */

#define isPrintLog(l) \
        is_print_log(l)



/* 参数1：Log等级    参数2：模块名称    参数3：日志内容(基本数据类型或者字符串) */
#define D_PRINT_MS(l, m, v) \
    do              \
    {                   \
        if (isPrintLog(l)) { \
            std::cout << "|" << (m) << "|" << __FILE__ << "|" << __LINE__ << "|" << __FUNCTION__ << "|[" << level_info(l) << "]:" << (v) << std::endl; \
            if (PRINT_INTO_FILE) {      \
                print_into_file_c("|%s|%s|%d|%s|[%s]:%s", (m), __FILE__, __LINE__, __FUNCTION__, level_info(l), (v));       \
            }           \
        }                   \
    } while (false);



#endif // COMMON_H




#define DYL_LOG(l, s) \
    do              \
    {                   \
        if (true == is_print_log(l)) \
        { \
            std::cout << (s) << std::endl;  \
            if (PRINT_INTO_FILE) {          \
                print_into_file_s(s); \
            }           \
        }               \
    } while (false);
    


#define DEBUG(l, format, ...) \
    do          \
    {               \
        if(isPrintLog(l)) { \
            printf(format, ##__VA_ARGS__); \
            if (PRINT_INTO_FILE) {      \
                print_into_file_c(format, ##__VA_ARGS__);       \
            }           \
        }               \
    } while (false);



// log interface 
#define PRINT_LOG_C(l, format, ...) \
        do { \
            DEBUG((l), "|MODULE|%s|%d|%s|[%s]:" format, \
                    __FILE__, __LINE__, __func__, level_info(l), ##__VA_ARGS__ );  \
        } while (false) 


#define PRINT_LOG_S(l, v)  \
    D_PRINT_MS((l), ("MODULE"), (v))


#ifdef VISSIM
#define VISSIM_LOG_C(l, format, ...) \
        do { \
            DEBUG((l), "|VISSIM|%s|%d|%s|" format "\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__ );\
        } while (0) 


#define VISSIM_LOG_S(l, v)  \
    D_PRINT_MS((l), ("VISSIM"), (v))

#define VISSIM_LOG_W(v)  \
        std::wcout << L"Vissim err msg: " << v << std::endl;

#endif

/********************************************** 函数定义 *******************************************************/


bool is_print_log(int l);
void print_into_file_s(const std::string s);
void print_into_file_c(const char * p, ...);
const char * level_info(int l);

void timespec2timeinfo(const struct timespec ts, char *time_string, const std::size_t max_len);

class LOG_MODULE
{
private:
    static LOG_MODULE *instance;
    std::string _cur_file_name;
    boost::filesystem::path cur_file_path;
    boost::filesystem::ofstream out_stream;
    std::vector<std::string> file_name_list;
    std::string _log_root_path;

    char date_time_info[50];

public:
    LOG_MODULE();
    ~LOG_MODULE();
    static LOG_MODULE *getInstance();
    void write_s(std::string s);
    void write_c(const char *format, ...);

private:
    void destory();
    bool open_file();
    void clear_file();
    bool close_file();
    bool file_is_full();
    void gen_file_name();
    // void delele_file();
    void check_file_num();
    void replace_substring();
    std::string get_file_full_name(const std::string file_name);
};



#endif