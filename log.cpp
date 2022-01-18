
#include "./log.h"
// #include <string>
// #include <string.h>
// #include <dirent.h>


#include "../simpro_function_safety/Runtime/Vissim/VissimTcpServer/VissimTcpServer/VissimTcpComm.h"


const std::string log_root_path = "/home/saimo/dyling/git_lib/log/logs/";


bool is_print_log(int l)
{
    if (l > PRINT_LEVEL)
    {
        return false;
    }

    return true;
}


const char * level_info(int l)
{
    const char *p = NULL;

    switch (l)
    {
        case D_FATAL:
        {
            p = "FATAL";
            break;
        }
        case D_ERROR:
        {
            p = "ERROR";
            break;
        }
        case D_WARN:
        {
            p = "WARN";
            break;
        }
        case D_INFO:
        {
            p = "INFO";
            break;
        }
        case D_DEBUG:
        {
            p = "DEBUG";
            break;
        }
        case D_VERBOSE:
        {
            p = "VERBOSE";
            break;
        }        
        default:
        {
            p = "UNKNOW";
            break;
        }
    }

    return p;
}


void print_into_file_s(const std::string s)
{
    LOG_MODULE::getInstance()->write_s(s);
    return;
}

void print_into_file_c(const char * p, ...)
{
    char buffer[256] = "";

    va_list args;
    va_start(args, p);
    vsnprintf(buffer, sizeof(buffer), p, args);
    va_end(args);

    LOG_MODULE::getInstance()->write_s(std::string(buffer));

    return;
}



LOG_MODULE * LOG_MODULE::instance = NULL;


LOG_MODULE::LOG_MODULE()
{
    _log_root_path = log_root_path;

    clear_file();
    open_file();
}


LOG_MODULE::~LOG_MODULE()
{
    close_file();
    destory();
}


LOG_MODULE *LOG_MODULE::getInstance()
{
    if (NULL == instance)
    {
        instance = new LOG_MODULE();
    }
    
    return instance;
}


void LOG_MODULE::destory()
{
    if (NULL != instance)
    {
        delete instance;
        instance = NULL;
    }
}



bool LOG_MODULE::open_file()
{
    gen_file_name();

    cur_file_path = boost::filesystem::path(get_file_full_name(_cur_file_name));

    std::cout << std::endl;
    std::cout << "open file: " << cur_file_path.c_str() << std::endl;

    if (true == out_stream.is_open())
    {
        close_file();
    }

    out_stream.open(cur_file_path, std::ios::out);

    if (true == out_stream.is_open())
    {
        std::cout << "open file ok." << std::endl;
        return true;
    }

    std::cout << "open file err." << std::endl;

    return false;
}



bool LOG_MODULE::close_file()
{
    if (true == out_stream.is_open())
    {
        std::cout << "close file: " << cur_file_path.c_str() << std::endl;
        out_stream.close();
    }

    return true;
}


void LOG_MODULE::write_s(std::string s)
{
    if (true != out_stream.is_open())
    {
        open_file();
    }

    out_stream << s << std::endl;

    if (true == file_is_full())
    {
        close_file();
        open_file();
    }

    check_file_num();

    return;
}


void LOG_MODULE::write_c(const char* format, ...)
{
    char buffer[256] = "";

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    write_s(std::string(buffer));
}



bool LOG_MODULE::file_is_full()
{
    if (true != boost::filesystem::exists(cur_file_path))
    {
        return false;
    }

    if (boost::filesystem::is_regular_file(cur_file_path))
    {
        unsigned int size = boost::filesystem::file_size(cur_file_path);

        if (MAX_SIZE_BYTE < size)
        {
            return true;
        }
    }

    return false;
}


void LOG_MODULE::gen_file_name()
{
    struct timespec time_temp = {0};

    clock_gettime(CLOCK_REALTIME, &time_temp);
    timespec2timeinfo(time_temp, date_time_info, sizeof(date_time_info));
    replace_substring();

    _cur_file_name = std::string(date_time_info);
    file_name_list.push_back(_cur_file_name);

    return;
}


// void LOG_MODULE::delele_file()
// {
//     int fileNum=0;
//     DIR *pDir = NULL;
//     struct dirent* ptr = NULL;
//     std::string first_file_name = "";

//     if(!(pDir = opendir(log_root_path.c_str())))
//     {
//         std::cout << "open log root path err." << std::endl;
//         return;
//     }

//     while((ptr = readdir(pDir)) != 0){
//         if(strcmp(ptr->d_name, ".") !=0 && strcmp(ptr->d_name, "..") != 0)
//         {
//             fileNum++;

//             std::cout << "name: " << ptr->d_name << ", type: " << ptr->d_type << ", info: " << ptr->d_ino << std::endl;

//             if (first_file_name.empty())
//             {
//                 first_file_name = std::string(ptr->d_name);
//             }
//         }
//     }

//     std::cout << "file num = " << fileNum << std::endl;

//     if (fileNum > MAX_FILE_NUM)
//     {
//         std::cout << "To del: " << log_root_path << "/" 
//                 << first_file_name << std::endl;

//         if(remove((log_root_path + first_file_name).c_str())==0)
//         {
//             std::cout << "delete ok: " << (log_root_path + first_file_name).c_str() << std::endl;
//         }
//         else
//         {
//             std::cout << "delete err: " << (log_root_path + first_file_name).c_str() << std::endl;
//         }
//     }

//     closedir(pDir);

//     return;
// }


void LOG_MODULE::check_file_num()
{
    boost::filesystem::path del_file_path;

    if (file_name_list.size() <= MAX_FILE_NUM)
    {
        return;
    }

    del_file_path = boost::filesystem::path(get_file_full_name(file_name_list.front()));

    std::cout << "to del: " << del_file_path.c_str() << std::endl;

    if (true == boost::filesystem::exists(del_file_path))
    {
        if(true == boost::filesystem::is_regular_file(del_file_path))	//推断是否为普通文件
        {
            boost::filesystem::remove(del_file_path);
        }
        else
        {
            std::cout << "the file is not regular file: " << del_file_path.c_str() << std::endl;
        }
    }
    else
    {
        std::cout << "the file is not exist: " << del_file_path.c_str() << std::endl;
    }

    file_name_list.erase(file_name_list.begin());

}


std::string LOG_MODULE::get_file_full_name(const std::string file_name)
{
    if (true == _log_root_path.empty())
    {
        std::cout << "log root path is empty." << std::endl;
        return file_name;
    }

    return (boost::filesystem::path(_log_root_path) / file_name.c_str()).c_str();
}


void LOG_MODULE::replace_substring()
{
    for (int i = 0; i < strlen(date_time_info); i++)
    {
        if (' ' == date_time_info[i] 
            || '-' == date_time_info[i] 
            || ':' == date_time_info[i])
        {
            date_time_info[i] = '_';
        }
    }
}


void LOG_MODULE::clear_file()
{
    boost::filesystem::path path_temp = boost::filesystem::path(_log_root_path);

    if (true != boost::filesystem::exists(path_temp))
    {
        std::cout << std::endl;
        std::cout << "create dir: " << path_temp.c_str() << std::endl;
        if (true != boost::filesystem::create_directory(path_temp))
        {
            std::cout << "create dir err." << std::endl;
        }

        return;
    }

    if (true != boost::filesystem::is_directory(path_temp))
    {
        std::cout << std::endl;
        std::cout << "create dir: " << path_temp.c_str() << std::endl;
        if (true != boost::filesystem::create_directory(path_temp))
        {
            std::cout << "create dir err." << std::endl;
        }

        return;
    }

    boost::filesystem::recursive_directory_iterator it_begin(path_temp);
    boost::filesystem::recursive_directory_iterator it_end;

    for (; it_begin != it_end; it_begin++)
    {
        if (true == boost::filesystem::is_regular_file(*it_begin))
        {
            file_name_list.push_back(it_begin->path().filename().c_str());
        }
    }

    std::sort(file_name_list.begin(), file_name_list.end());

}

