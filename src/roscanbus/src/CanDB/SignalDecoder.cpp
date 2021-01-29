#include "SignalDecoder.hpp"

int64_t SignalDecoder::two_complement(uint64_t & v, const int & bitlen)
{
    uint64_t value = v & ((1<<bitlen)-1);
    uint64_t mask = 1 << (bitlen-1);
    return (value & ~mask) - (value & mask);
}

int SignalDecoder::set_signal(struct signal *sig, uint64_t val)
{ 
	int byte_i = 0;
	int bit_i = 0;
	/* Loop through bit by bit */
    //	
	int j = sig->start_bit;
	for(int i = 0; i < sig->len; i++)
	{
		byte_i = (j & (~0x7)) / 8;
		
		bit_i = j & 0x7;
		
		/* Clear bit to set */
		this->data[byte_i] &= ~(1 << bit_i);

		/* If bit should be 1, set it */
		if((val >> i) & 1)
			this->data[byte_i] |= 1 << bit_i;

		// fprintf(stdout, "byte i  %i \n", this->data[byte_i]);

		if(sig->byte_order == MOTOROLA)
		{
			if((j & 0x7) == 7)
				j -= 15;
			else
				j++;
		}
		else /* INTEL */
			j++;  
	}
	return 0;
}

int SignalDecoder::get_signal(struct signal *sig, uint64_t *val)
{
	/* Loop through bit by bit */
	*val = 0;
	int j = sig->start_bit;
	for(int i = 0; i < sig->len; i++)
	{
		int byte_i = (j & (~0x7)) / 8;
		int bit_i = j & 0x7;

		int bit = this->data[byte_i] & (1 << bit_i);

		if(bit)
			*val |= (1 << i);

		if(sig->byte_order == MOTOROLA)
		{
			if((j & 0x7) == 7)
				j -= 15;
			else
				j++;
		}
		else /* INTEL */
			j++;
	}
    return 0;
}

int SignalDecoder::get_signal_signed(struct signal *sig, int64_t *sval)
{
	/* Loop through bit by bit */
	*sval = 0;
	uint64_t val = 0;
	int j = sig->start_bit;
	for(int i = 0; i < sig->len; i++)
	{
		int byte_i = (j & (~0x7)) / 8;
		int bit_i = j & 0x7;

		int bit = this->data[byte_i] & (1 << bit_i);

		if(bit)
			val |= (1 << i);

		if(sig->byte_order == MOTOROLA)
		{
			if((j & 0x7) == 7)
				j -= 15;
			else
				j++;
		}
		else /* INTEL */
			j++;
	}
	*sval = SignalDecoder::two_complement(val, sig->len);
    return 0;
}
