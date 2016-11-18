#include <CppUTest/TestHarness.h>

extern "C"
{
    #include "log_mock.h"
}

TEST_GROUP(Log)
{
    void setup ()
    {
    }

    void teardown ()
    {
        log_mock_clear();
    }
};

TEST(Log, periodic)
{
    int l = __LINE__; log_error("oops!");
    STRCMP_NOCASE_CONTAINS("Error", log_mock_last_error());
    STRCMP_NOCASE_CONTAINS("oops!", log_mock_last_error());
    STRCMP_NOCASE_CONTAINS(__FILE__, log_mock_last_error());

    char line[5];
    snprintf(line, 5, ":%d", l);
    STRCMP_NOCASE_CONTAINS(line, log_mock_last_error());
}

