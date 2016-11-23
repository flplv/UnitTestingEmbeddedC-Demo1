#include <CppUTestExt/MockSupport.h>

extern "C"
void _platform_log (const char * msg, const char * file, int line)
{
    /*
     * We want to use CppUTest Mock system in this function,
     * this way tests will fail if any code under tests print
     * an error message.
     */
    mock().actualCall("_platform_log")
            .withStringParameter("msg", msg)
            .withStringParameter("file", file)
            .withIntParameter("line", line);
}
