#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C"
{
    #include "serial_mock.h"
    #include "echo.h"
    #include "hacker.h"
}

void test_echo_load (char * str)
{
    while (*str)
        echo_received_byte(*str++);
}

TEST_GROUP(Echo)
{
    void setup()
    {
        echo_init();
    }

    void teardown()
    {
        echo_deinit();
        serial_mock_clear();
        mock().clear();
    }
};

TEST(Echo, periodic)
{

    char str[] = "abracadabra!";
    test_echo_load(str);

    echo_periodic();

    hacker_line(str);
    STRCMP_EQUAL(str, serial_mock_get_outward());
}

TEST(Echo, periodic2steps)
{
    char str[] = "abracadabra!";
    char str1[] = "abrac";
    char str2[] =      "adabra!";

    test_echo_load(str1);
    echo_periodic();
    test_echo_load(str2);
    echo_periodic();

    hacker_line(str);
    STRCMP_EQUAL(str, serial_mock_get_outward());
}

