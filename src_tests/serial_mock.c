#include <stdbool.h>
#include <string.h>
#include <CppUTest/TestHarness_c.h>

static char out[256] = {0,};

void serial_send (char c)
{
    char str[2] = {c, '\0'};
    strcat(out, str);
}

const char * serial_mock_get_outward ()
{
    return out;
}

void serial_mock_clear ()
{
    out[0] = '\0';
}
