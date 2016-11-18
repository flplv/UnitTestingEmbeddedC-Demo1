#ifndef SRC_ECHO_H_
#define SRC_ECHO_H_

void echo_init();
void echo_deinit(); /* Not ISR safe, don't call deinit with echo_received_byte being called */
void echo_periodic();

#include "checks.h"
#include "ring_fifo.h"

extern ring_fifo_t * _echo_inward;

/* Thread safe, use in ISR*/
static inline void echo_received_byte(char c)
{
    /* Ignore null byte, no need termination when using FIFOs */
    if (!c)
        return;
    check_ptr (_echo_inward);
    ring_fifo_push(_echo_inward, (uint8_t*) &c);
}



#endif /* SRC_ECHO_H_ */
