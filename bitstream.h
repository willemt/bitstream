#ifndef BITSTREAM_H
#define BITSTREAM_H

void bitstream_init(
    unsigned char *b,
    unsigned int size);

/**
 * Write out byte value to bitstream. Increment b by 1 */
void bitstream_write_ubyte(
    unsigned char **b,
    unsigned char value);

/**
 * Write out byte value to bitstream. Increment b by 4 */
void bitstream_write_uint32(
    unsigned char **b,
    uint32_t value);

/**
 * Write out bit value to bitstream.
 * Only increment b by 1 when bit_pos will be 8
 * @param bit_pos Current bit offset within bitstream */
void bitstream_write_bit_from_bitoffset(
    unsigned char **b,
    const uint32_t val,
    unsigned int* bit_pos
);

/**
 * Write out bit value to bitstream.
 * Only increment b by 1 when bit_pos will be 8
 * @param bit_pos Current bit offset within bitstream */
void bitstream_write_uint32_from_bitoffset(
    unsigned char **b,
    const uint32_t val,
    const unsigned int nbits,
    unsigned int* read_pos_bits);

void bitstream_write_string(
    unsigned char **b,
    const char* string,
    unsigned int len);

void bitstream_read_uint32_from_bitoffset(
    unsigned char **b,
    uint32_t * val,
    const unsigned int nbits,
    unsigned int* bit_pos);

int bitstream_read_bit(
    unsigned char **b,
    unsigned int* read_pos_bits);

void bitstream_read_string(
    unsigned char **b,
    char* out_string,
    unsigned int len);

unsigned char bitstream_read_ubyte(
    unsigned char **b);

uint32_t bitstream_read_uint32(
    unsigned char **b);

#endif /* BITSTREAM_H */
