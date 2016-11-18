#ifndef FW_HACKER_H_
#define FW_HACKER_H_

#include "ring_fifo.h"

int hacker_line(char * str_to_hackerize);
int hacker_fifo(ring_fifo_t * src, ring_fifo_t * dest);

#endif /* SRC_HACKER_H_ */
