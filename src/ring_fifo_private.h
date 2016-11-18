/*
 * ring_fifo_private.h
 *
 *  Created on: 10 de nov de 2016
 *      Author: fanl
 */

#ifndef RING_FIFO_PRIVATE_H_
#define RING_FIFO_PRIVATE_H_


struct s_ring_fifo_private
{
    uint8_t * client_buffer;
    uint8_t * own_buffer;
    uint8_t * buffer;
    size_t buffer_size;
    size_t element_size;
    size_t num_fifo_slots;
    bool full;
    size_t rd;
    size_t wr;
    bool nocp_pop_started;
    bool nocp_push_started;
};


#endif /* SRC_RING_FIFO_PRIVATE_H_ */
