#include <string.h>
#include <ctype.h>

#include "hacker.h"
#include "checks.h"

struct hackable_char {
    char before;
    char after;
};

static const struct hackable_char hacking_table[] = {
        {'a', '4'},
        {'e', '3'},
        {'i', '1'},
        {'o', '0'},
        {0, 0} /* This is a terminator */
};

static char hack_char(char c)
{
    const struct hackable_char * ref = &hacking_table[0];

    while (ref->after != 0)
    {
        typeof(ref) r = ref;
        ref++;

        if (r->before != tolower(c))
            continue;

        return r->after;
    }

    return c;
}

int hacker_line(char * str_to_hackerize)
{
    check_ptr(str_to_hackerize, -1);

    size_t n = strlen(str_to_hackerize);

    while (n--)
        str_to_hackerize[n] = hack_char(str_to_hackerize[n]);

    return 0;
}

int hacker_fifo(ring_fifo_t * src, ring_fifo_t * dest)
{
    check_ptr(src, -1);
    check_ptr(dest, -1);
    check_assert(ring_fifo_element_size(src) == 1, -2);
    check_assert(ring_fifo_element_size(dest) == 1, -2);

    size_t n = ring_fifo_count(src);

    while (n--) {
        char c;
        bool success = ring_fifo_pop(src, (uint8_t *)&c);
        check_assert(success, -3);

        c = hack_char(c);

        success = ring_fifo_push(dest, (const uint8_t *)&c);
        check_assert(success, -3);

        if (c == '\0')
            break;
    }

    return 0;
}
