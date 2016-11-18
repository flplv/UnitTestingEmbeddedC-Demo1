/*
 *    Copyright (c) 2013 Felipe Lavratti (felipe@andradeneves.com)
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *    THE SOFTWARE.
 */

#ifndef RING_FIFO_H_
#define RING_FIFO_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ring_fifo_private.h"

typedef struct s_ring_fifo_private ring_fifo_t;

/*
 * Atomic Ring FIFO
 *
 * Can be used for multi-threaded process or in interrupt handlers as
 * a single producer and single consumer FIFO.
 *
 * It uses `element_size`, such as element wrapping is not possible, be aware if you
 * want elements with variable size you have to configure `element_size` to 1. In this
 * case do not peek nor use zero copy, only pop and push byte-per-byte.
 */


void ring_fifo_init_buffer(ring_fifo_t *, uint8_t * buffer, size_t buffer_size, size_t element_size);
void ring_fifo_deinit(ring_fifo_t *);

bool ring_fifo_is_full(ring_fifo_t *);
bool ring_fifo_is_empty(ring_fifo_t *);
size_t ring_fifo_count(ring_fifo_t *);
size_t ring_fifo_element_size(ring_fifo_t *);

uint8_t * ring_fifo_peek(ring_fifo_t *);
bool ring_fifo_pop(ring_fifo_t *, uint8_t * to);
bool ring_fifo_push(ring_fifo_t *, const uint8_t * copy_src);

/*
 * Zero copy family
 */
uint8_t * ring_fifo_peek_at(ring_fifo_t * cobj, int pos);

uint8_t * ring_fifo_zerocopy_pop_start(ring_fifo_t *);
void ring_fifo_zerocopy_pop_finish(ring_fifo_t *);

uint8_t * ring_fifo_zerocopy_push_start(ring_fifo_t *);
void ring_fifo_zerocopy_push_finish(ring_fifo_t *);

#endif /* RINGFIFO_H_ */
