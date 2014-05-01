
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
    memcpy(*bytes, &value, sizeof(uint32_t));
    *bytes += 4;
}

unsigned char bitstream_read_ubyte(
    unsigned char **bytes
)
{
    unsigned char val = **bytes;
    *bytes += 1;
    return val;
}

uint32_t bitstream_read_uint32(
    unsigned char **bytes
)
{
    uint32_t value;

    memcpy(&value, *bytes, sizeof(uint32_t));
    *bytes += sizeof(uint32_t);
    return value;
}

void bitstream_write_uint32_from_bitoffset(
    unsigned char **bytes,
    const uint32_t val,
    const unsigned int nbits,
    unsigned int* read_pos_bits
)
{
    unsigned int bit_offset, int_offset;
    uint32_t val_posting;

    assert(nbits <= 32);

    int_offset = (*read_pos_bits - *read_pos_bits % 32) / 32;
    bit_offset = *read_pos_bits % 32;

    memcpy(&val_posting, *bytes + (int_offset) * sizeof(uint32_t), sizeof(uint32_t));

    /* write bytes out */
    val_posting = val_posting | ((val << (32 - nbits)) >> bit_offset);
    //memcpy(*bytes, &val_posting, sizeof(uint32_t));
    memcpy(*bytes + (int_offset) * sizeof(uint32_t), &val_posting, sizeof(uint32_t));

    /* do right handside */
    if (32 < bit_offset + nbits)
    {
        int nbits2 = (bit_offset + nbits) % 32;
        val_posting = val << (32 - nbits2);
        //memcpy(*bytes, &val_posting, sizeof(uint32_t));
        memcpy(*bytes + (int_offset + 1) * sizeof(uint32_t), &val_posting, sizeof(uint32_t));
    }

    *read_pos_bits += nbits;
}

void bitstream_write_bit_from_bitoffset(
    unsigned char **bytes,
    const uint32_t val,
    unsigned int* read_pos_bits
)
{
    bitstream_write_uint32_from_bitoffset(bytes,val,1,read_pos_bits);
}

void bitstream_read_uint32_from_bitoffset(
    unsigned char **bytes,
    uint32_t * val_out,
    const unsigned int nbits,
    unsigned int* read_pos_bits
)
{
    unsigned int bit_offset, int_offset;

    assert(nbits <= 32);

    /* position pointer */
    int_offset = (*read_pos_bits - *read_pos_bits % 32) / 32;
    bit_offset = *read_pos_bits % 32;

    /* read bytes */
    //*val = ntohl(*ptr);
    //*val = l2b_endian(*ptr);
    memcpy(val_out, *bytes + int_offset * sizeof(uint32_t), sizeof(uint32_t));
    *val_out <<= bit_offset;
    *val_out >>= 32 - nbits;

    /* do otherside */
    if (32 < bit_offset + nbits)
    {
        int nbits2;
        uint32_t val;
        
        nbits2 = (bit_offset + nbits) % 32;
        memcpy(&val, *bytes + (int_offset + 1) * sizeof(uint32_t), sizeof(uint32_t));

        //*val |= ntohl(*ptr) >> (32 - nbits2);
        //*val |= l2b_endian(*ptr) >> (32 - nbits2);
        //*val_out |= *ptr >> (32 - nbits2);
        *val_out |= val >> (32 - nbits2);
    }

    *read_pos_bits += nbits;
}

/**
 * read the next bit.
 * @return true if bit == 1 else false
 */
int bitstream_read_bit(
    unsigned char **bytes,
    unsigned int* read_pos_bits
)
{
    uint32_t *ptr;
    uint32_t val;
    unsigned int bit_offset, int_offset;

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

