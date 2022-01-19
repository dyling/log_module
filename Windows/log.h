/**
 * @file log.h
 * @author duanyanling@saimo.ai
 * @brief ��־��ض���
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _VISSIM_LOG_H_
#define _VISSIM_LOG_H_


#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>



/********************************************** �궨�� ******************************************************/


#define MAX_SIZE_BYTE       10 * 1024
#define MAX_FILE_NUM        5

#define PRINT_LEVEL         D_VERBOSE
#define PRINT_INTO_FILE     true



// Copy from Common.h
#ifndef COMMON_H
#define COMMON_H

#define D_FATAL       (0)  /* ���½����˳� */
#define D_ERROR       (1)  /* ģ���� ���� �����½����˳��Ĵ���ʱ�� */
#define D_WARN        (2)  /* ����/�����Ǳ�ڴ��� */
#define D_INFO        (3)  /* �ڴ�������ͻ�����й��� */
#define D_DEBUG       (4)  /* ��ϸ�����ϵ��� */
#define D_VERBOSE     (5)  /* ��ӡ��ϸ������ */

#define isPrintLog(l) \
        is_print_log(l)



/* ����1��Log�ȼ�    ����2��ģ������    ����3����־����(�����������ͻ����ַ���) */
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


#define VISSIM_LOG_C(l, format, ...) \
        do { \
            DEBUG((l), "|VISSIM|%s|%d|%s|" format "\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__ );\
        } while (0) 


#define VISSIM_LOG_S(l, v)  \
    D_PRINT_MS((l), ("VISSIM"), (v))

#define VISSIM_LOG_W(v)  \
        std::wcout << L"Vissim err msg: " << v << std::endl;




/********************************************** �������� *******************************************************/


bool is_print_log(int l);
void print_into_file_s(const std::string s);
void print_into_file_c(const char * p, ...);
const char * level_info(int l);


class LOG_MODULE
{
private:
    static LOG_MODULE *instance;
    std::string _cur_file_name;
    boost::filesystem::path cur_file_path;
    boost::filesystem::ofstream out_stream;
    std::vector<std::string> file_name_list;
    std::string _log_root_path;

    char date_time_info[50] = {0};

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
