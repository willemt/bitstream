
void bitstream_init( unsigned char *bytes, int size);

void bitstream_write_ubyte( unsigned char **bytes, unsigned char value);

void bitstream_write_uint32( unsigned char **bytes, uint32_t value);

void bitstream_write_bit_from_bitoffset(
    unsigned char **bytes,
    const uint32_t val,
    int* read_pos_bits
);

unsigned char bitstream_read_ubyte( unsigned char **bytes);

uint32_t bitstream_read_uint32( unsigned char **bytes);

void bitstream_write_uint32_from_bitoffset( unsigned char **bytes, const uint32_t val, const unsigned int nbits, int* read_pos_bits);

void bitstream_read_uint32_from_bitoffset( unsigned char **bytes, uint32_t * val, const unsigned int nbits, int* read_pos_bits);

int bitstream_read_bit( unsigned char **bytes, int* read_pos_bits);

void bitstream_write_string(unsigned char **bytes, const char* string, unsigned int len);

void bitstream_read_string(unsigned char **bytes, char* out_string, unsigned int len);

