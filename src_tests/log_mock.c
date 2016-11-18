#include <stdio.h>
#include <string.h>
#include <CppUTest/TestHarness_c.h>

static char * last_log_msg = NULL;

void _platform_log (const char * msg, const char * file, int line)
{
    int n = snprintf (NULL, 0, "%s (%s:%d)", msg, file, line) + 1;
    if (n < 0) FAIL_C ();

    char * str = (char *)malloc ((size_t)n);
    if (!str) FAIL_C ();

    n = snprintf (str, (size_t)n, "%s (%s:%d)", msg, file, line);
    if (n < 0) FAIL_C ();

    if (last_log_msg)
        free (last_log_msg);
    last_log_msg = str;
}

void log_mock_clear()
{
    if (last_log_msg)
        free (last_log_msg);
    last_log_msg = NULL;
}

const char * log_mock_last_error()
{
    return last_log_msg;
}



