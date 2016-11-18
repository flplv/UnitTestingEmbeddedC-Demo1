#include <CppUTest/TestHarness.h>

extern "C"
{
    #include <string.h>
    #include "ring_fifo.h"
    #include "hacker.h"
    #include "log_mock.h"
}

ring_fifo_t fifo_src;
uint8_t buffer_src[256];
const size_t buffer_src_size = sizeof(buffer_src) / sizeof(*buffer_src);

ring_fifo_t fifo_dest;
uint8_t buffer_dest[256];
const size_t buffer_dest_size = sizeof(buffer_dest) / sizeof(*buffer_dest);

TEST_GROUP(TestHacker)
{
    void setup()
    {
        ring_fifo_init_buffer(&fifo_src, buffer_src, buffer_src_size, 1);
        ring_fifo_init_buffer(&fifo_dest, buffer_dest, buffer_dest_size, 1);
    }

    void teardown()
    {

        ring_fifo_deinit(&fifo_src);
        ring_fifo_deinit(&fifo_dest);
        log_mock_clear();
    }
};

TEST(TestHacker, str1)
{
    char str[] = "hackerize me if you can";
    char expected[] = "h4ck3r1z3 m3 1f y0u c4n";

    int r = hacker_line(str);

    CHECK_EQUAL(0, r);
    STRCMP_EQUAL(expected, str);
}

TEST(TestHacker, str2)
{
    char str[] = "aeiou";
    char expected[] = "4310u";

    int r = hacker_line(str);

    CHECK_EQUAL(0, r);
    STRCMP_EQUAL(expected, str);
}

TEST(TestHacker, str3)
{
    char str[] = "AEIOU";
    char expected[] = "4310U";

    int r = hacker_line(str);

    CHECK_EQUAL(0, r);
    STRCMP_EQUAL(expected, str);
}

TEST(TestHacker, boundries)
{
    char str[] = "\0aeiou\0e";

    int r = hacker_line(str + 1);

    CHECK_EQUAL(0, r);
    CHECK_EQUAL(0, str[0]);
    CHECK_EQUAL(0, str[6]);
    CHECK_EQUAL('e', str[7]);
}

TEST(TestHacker, invalid_arg)
{
    char str[] = "\0";

    int r = hacker_line(str);

    CHECK_EQUAL(0, r);
}

TEST(TestHacker, invalid_arg2)
{
    int r = hacker_line(NULL);

    CHECK_EQUAL(-1, r);
}

void fifo_push_string (ring_fifo_t * fifo, const char * str)
{
    bool r;

    while (*str) {
        r = ring_fifo_push(fifo, (const uint8_t *)str++);
        CHECK_TRUE (r);
    }

    r = ring_fifo_push(fifo, (const uint8_t *)str);
    CHECK_TRUE (r);
}

char * fifo_pop_string (ring_fifo_t * fifo)
{
    bool r;
    char c = 1;
    char str[ring_fifo_count(fifo)];
    char * p = str;

    while (c) {
        r = ring_fifo_pop(fifo, (uint8_t *)&c);
        CHECK_TRUE (r);
        *p++ = c;
    }

    char * new_str = (char *)malloc (strlen(str) + 1);
    strcpy(new_str, str);

    return new_str;
}

TEST(TestHacker, fifo)
{
    fifo_push_string(&fifo_src, "Load-load load me!");
    int r = hacker_fifo(&fifo_src, &fifo_dest);
    CHECK_EQUAL(0, r);

    char * str = fifo_pop_string(&fifo_dest);
    STRCMP_EQUAL("L04d-l04d l04d m3!", str);

    free (str);
}
