#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

extern "C"
{
    #include "log_mock.h"
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
        log_mock_clear();
        serial_mock_clear();
        mock().clear();
    }
};

TEST(Echo, periodic)
{

    char str[] = "abracadabra!";
    test_echo_load(str);

    mock().expectNCalls(5, "leds_toggle");
    echo_periodic();
    mock().checkExpectations();

    hacker_line(str);
    STRCMP_EQUAL(str, serial_mock_get_outward());
}

TEST(Echo, periodic2steps)
{
    char str[] = "abracadabra!";
    char str1[] = "abrac";
    char str2[] =      "adabra!";

    mock().expectNCalls(5, "leds_toggle");

    test_echo_load(str1);
    echo_periodic();
    test_echo_load(str2);
    echo_periodic();

    mock().checkExpectations();

    hacker_line(str);
    STRCMP_EQUAL(str, serial_mock_get_outward());
}

