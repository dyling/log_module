#include "log.h"


int main()
{
    std::cout << "hello" << std::endl;

    for (int i = 0; i < 1000; i++)
    {
        // print_into_file_c("abcddd%d", i);
        PRINT_LOG_C(D_DEBUG, "abc%d", i);
        break;
        PRINT_LOG_S(D_DEBUG, "abcdddddd");
    }

    return 0;
}


