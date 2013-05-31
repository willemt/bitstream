
#include <stdint.h>
#include <string.h>
#include <assert.h>

void bitstream_init(
    unsigned char *bytes,
    int size
)
{
    memset(bytes, 0, sizeof(unsigned char) * size);
}

void bitstream_write_ubyte(
    unsigned char **bytes,
    unsigned char value
)
{
    **bytes = value;
    *bytes += 1;
}

void bitstream_write_uint32(
    unsigned char **bytes,
    uint32_t value
)
{
    uint32_t *ptr;

    ptr = (uint32_t *) (*bytes);

    //*ptr = htonl(value);
    *ptr = value;

    *bytes += 4;
}

unsigned char bitstream_read_ubyte(
    unsigned char **bytes
)
{
    unsigned char val;

    val = **bytes;
    *bytes += 1;

    return val;
}

uint32_t bitstream_read_uint32(
    unsigned char **bytes
)
{
    uint32_t *ptr;

    ptr = (uint32_t *) (*bytes);

    *bytes += 4;

    //return ntohl(*ptr);
    return *ptr;
}

void bitstream_write_uint32_from_bitoffset(
    unsigned char **bytes,
    const uint32_t val,
    const unsigned int nbits,
    int* read_pos_bits
)
{
    int bit_offset, int_offset;
    uint32_t val1, *ptr;

    assert(nbits <= 32);

    /* position pointer */
    int_offset = (*read_pos_bits - *read_pos_bits % 32) / 32;
    bit_offset = *read_pos_bits % 32;
    ptr = (uint32_t*)*bytes + int_offset;

    /* write bytes out */
    val1 = val;
    val1 <<= 32 - nbits;
    val1 >>= bit_offset;

    //*ptr = htonl(ntohl(*ptr) | val1);
    *ptr = *ptr | val1;

    /* do right handside */
    if (32 < bit_offset + nbits)
    {
        int nbits2;
        
        nbits2 = (bit_offset + nbits) % 32;
        ptr++;
        *ptr = val << (32 - nbits2);
    }

    *read_pos_bits += nbits;
}

void bitstream_read_uint32_from_bitoffset(
    unsigned char **bytes,
    uint32_t * val,
    const unsigned int nbits,
    int* read_pos_bits
)
{
    int bit_offset, int_offset;
    uint32_t *ptr;

    assert(nbits <= 32);

    /* position pointer */
    int_offset = (*read_pos_bits - *read_pos_bits % 32) / 32;
    bit_offset = *read_pos_bits % 32;
    ptr = (uint32_t*)*bytes + int_offset;

    /* read bytes */
    //*val = ntohl(*ptr);
    //*val = l2b_endian(*ptr);
    *val = *ptr;
    *val <<= bit_offset;
    *val >>= 32 - nbits;

    /* do otherside */
    if (32 < bit_offset + nbits)
    {
        int nbits2;
        
        nbits2 = (bit_offset + nbits) % 32;
        ptr++;

        //*val |= ntohl(*ptr) >> (32 - nbits2);
        //*val |= l2b_endian(*ptr) >> (32 - nbits2);
        *val |= *ptr >> (32 - nbits2);
    }

    *read_pos_bits += nbits;
}

/**
 * read the next bit.
 * @return true if bit == 1 else false
 */
int bitstream_read_bit(
    unsigned char **bytes,
    int* read_pos_bits
)
{
    uint32_t *ptr;
    uint32_t val;
    int bit_offset, int_offset;

    /* position pointer */
    int_offset = (*read_pos_bits - *read_pos_bits % 32) / 32;
    bit_offset = *read_pos_bits % 32;
    ptr = (uint32_t*)*bytes + int_offset;

    //val = ntohl(*ptr);
    val = *ptr;
    val <<= bit_offset;
    val >>= 32 - 1;
    *read_pos_bits += 1;
    return val == 1;
}

#if 0
static int l2b_endian(int in)
{
    int out;

    ((unsigned char*)&out)[0] = ((unsigned char*)&in)[3];
    ((unsigned char*)&out)[1] = ((unsigned char*)&in)[2];
    ((unsigned char*)&out)[2] = ((unsigned char*)&in)[1];
    ((unsigned char*)&out)[3] = ((unsigned char*)&in)[0];

    return out;
}
#endif

void bitstream_write_string(
    unsigned char **bytes,
    const char* string,
    unsigned int len
)
{
    strncpy((char*)*bytes,string,len);
    *bytes += len;
}

void bitstream_read_string(
    unsigned char **bytes,
    char* out_string,
    unsigned int len
)
{
    strncpy(out_string,(char*)*bytes, len);
    *bytes += len;
}

