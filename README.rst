How does it work?
-----------------

See bitstream.h for documentation.

:code:`

char* bits[100];

bitstream_init(bits, 100);

/* write 0x5 as a byte to the stream. Move pointer by 1 byte */
bitstream_write_ubyte(&b, 0x5);

/* write out an 32bit unsigned int to the stream. Move pointer by 4 bytes */
bitstream_write_uint32(&b, 0xFF00FF00);

/* write out 1 bit. Record that we've "moved" forward one bit */
unsigned int bit_offset = 0;
bitstream_write_bit_from_bitoffset(&b, 1, &bit_offset);

`/* write out 31 bits of a uint32. Move pointer 4 bytes forward */
bitstream_write_bit_from_bitoffset(&b, 32, &bit_offset);
bitstream_write_uint32_from_bitoffset(&b, 0xFF00FF00, 31, &bit_offset);
`

Building
--------
$make

