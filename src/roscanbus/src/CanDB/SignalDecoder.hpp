#pragma once

#include <stdint.h>

class SignalDecoder
{
public:
    enum byte_order { MOTOROLA, INTEL };

    struct signal
    {
        uint8_t start_bit, len;
        enum byte_order byte_order;
    };

    static int64_t two_complement(uint64_t & v, const int & bitlen );

    int set_signal(struct signal *sig, uint64_t val);
    int get_signal(struct signal *sig, uint64_t *val);
    
    
    uint8_t dlc;		/* Data Length Code */
    uint8_t rtr;		/* Remote Transmission Request */
    uint8_t ide;		/* Identifier Exstension */
    uint32_t id;		/* CAN id */
    uint8_t data[8];	/* CAN data */
};


