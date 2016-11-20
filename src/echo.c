#include "log.h"
#include "echo.h"
#include "ring_fifo.h"
#include "serial.h"
#include "hacker.h"
#include "leds.h"

static ring_fifo_t inward;
static ring_fifo_t outward;

#ifdef TEST_BUILD
static uint8_t inward_buffer[32];
static uint8_t outward_buffer[32];
#else
static uint8_t inward_buffer[8];
static uint8_t outward_buffer[8];
#endif

/* External pointer to be user in static inline functions
 * Set and unset on init/deinit to protect ring_fifo_t access. */
ring_fifo_t * _echo_inward = NULL;

void echo_init()
{
    ring_fifo_init_buffer(&inward, inward_buffer, sizeof (inward_buffer), 1);
    ring_fifo_init_buffer(&outward, outward_buffer, sizeof (outward_buffer), 1);

    _echo_inward = &inward;
}

void echo_deinit()
{
    _echo_inward = NULL;

    ring_fifo_deinit(&outward);
    ring_fifo_deinit(&inward);
}

static void pop_fifo(ring_fifo_t* f)
{
    while (ring_fifo_count(f) > 0)
    {
        char c;

        bool r = ring_fifo_pop(f, (uint8_t*) &c);

        if (!r)
        {
            log_error("Unable to pop from outward FIFO.");
            break;
        }

        serial_send(c);
    }
}

void echo_periodic()
{
    int n = hacker_fifo(&inward, &outward);
    pop_fifo(&outward);
    while (n--)
        leds_toggle();
}

//Funciton optimized to the header
//void echo_received_byte(char c)
//{
//    /* Ignore null byte, no need termination when using FIFOs */
//    if (!c)
//        return;
//
//    ring_fifo_push(&inward, (uint8_t*) &c);
//}




