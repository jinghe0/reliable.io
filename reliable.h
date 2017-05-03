/*
    reliable.io reference implementation

    Copyright © 2017, The Network Protocol Company, Inc.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

        1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer 
           in the documentation and/or other materials provided with the distribution.

        3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived 
           from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef RELIABLE_H
#define RELIABLE_H

#include <stdint.h>

#if    defined(__386__) || defined(i386)    || defined(__i386__)  \
    || defined(__X86)   || defined(_M_IX86)                       \
    || defined(_M_X64)  || defined(__x86_64__)                    \
    || defined(alpha)   || defined(__alpha) || defined(__alpha__) \
    || defined(_M_ALPHA)                                          \
    || defined(ARM)     || defined(_ARM)    || defined(__arm__)   \
    || defined(WIN32)   || defined(_WIN32)  || defined(__WIN32__) \
    || defined(_WIN32_WCE) || defined(__NT__)                     \
    || defined(__MIPSEL__)
  #define RELIABLE_LITTLE_ENDIAN 1
#else
  #define RELIABLE_BIG_ENDIAN 1
#endif

#define RELIABLE_LOG_LEVEL_NONE      0
#define RELIABLE_LOG_LEVEL_INFO      1
#define RELIABLE_LOG_LEVEL_ERROR     2
#define RELIABLE_LOG_LEVEL_DEBUG     3

#define RELIABLE_ENDPOINT_COUNTER_NUM_PACKETS_SENT                          0
#define RELIABLE_ENDPOINT_COUNTER_NUM_PACKETS_RECEIVED                      1
#define RELIABLE_ENDPOINT_COUNTER_NUM_PACKETS_ACKED                         2
#define RELIABLE_ENDPOINT_COUNTER_NUM_PACKETS_STALE                         3
#define RELIABLE_ENDPOINT_COUNTER_NUM_PACKETS_TOO_SMALL_TO_PROCESS          4
#define RELIABLE_ENDPOINT_COUNTER_NUM_ACKS_DROPPED                          5
#define RELIABLE_ENDPOINT_NUM_COUNTERS                                      6 

int reliable_init();

void reliable_term();

void reliable_log_level( int level );

struct reliable_config_t
{
    void * context;
    int index;
    int ack_buffer_size;
    int sent_packets_buffer_size;
    int received_packets_buffer_size;
    void (*transmit_packet_function)(void*,int,uint8_t*,int);
    int (*process_packet_function)(void*,int,uint8_t*,int);
};

struct reliable_endpoint_t * reliable_endpoint_create( struct reliable_config_t * config );

uint16_t reliable_endpoint_next_packet_sequence( struct reliable_endpoint_t * endpoint );

void reliable_endpoint_send_packet( struct reliable_endpoint_t * endpoint, uint8_t * packet_data, int packet_bytes );

void reliable_endpoint_receive_packet( struct reliable_endpoint_t * endpoint, uint8_t * packet_data, int packet_bytes );

void reliable_endpoint_free_packet( struct reliable_endpoint_t * endpoint, void * packet );

uint16_t * reliable_endpoint_get_acks( struct reliable_endpoint_t * endpoint, int * num_acks );

void reliable_endpoint_clear_acks( struct reliable_endpoint_t * endpoint );

void reliable_endpoint_update( struct reliable_endpoint_t * endpoint );

void reliable_endpoint_destroy( struct reliable_endpoint_t * endpoint );

#endif // #ifndef RELIABLE_H
