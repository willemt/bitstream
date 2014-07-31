#include <string.h>
#include "CuTest.h"
#include <stdint.h>
#include "bitstream.h"
#include <stdio.h>

void Test_WriteBitIncreasesBitOffset(
    CuTest * tc
)
{
    char bits[1000];
    char *cptr_write;
    unsigned int bo;

    bo = 0;
    cptr_write = &bits[0];
    bitstream_init(bits, 1000);

    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);
    CuAssertTrue(tc, 1 == bo);
}

void Test_ReadBitNothing(
    CuTest * tc
)
{
    char bits[1000];
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);
    bo = 0;
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
}

void Test_ReadBit(
    CuTest * tc
)
{
    char bits[1000];
    unsigned int bo;

    char *cptr_write = &bits[0];
    char *cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);

    bo = 0;
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
}

void Test_WriteBit(
    CuTest * tc
)
{
    char bits[1000];
    unsigned int bo;

    char *cptr_write = &bits[0];
    char *cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 0, &bo);
    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);

    bo = 0;
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read,&bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read,&bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read,&bo));
}

void Test_ReadUByteWithNothingResultsInZero(
    CuTest * tc
)
{
    char num[10];

    memset(num, 0, sizeof(char) * 10);
    char *cptr_read = &num[0];

    CuAssertTrue(tc, 0 == bitstream_read_byte(&cptr_read));
}

void Test_UbyteWriteAndRead(
    CuTest * tc
)
{
    char num[10];
    memset(num, 0, sizeof(char) * 10);
    char *cptr_write = &num[0];
    char *cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0x0FF);
    CuAssertTrue(tc, 0x0FF == (unsigned char)bitstream_read_byte(&cptr_read));

    unsigned int bo = 0;
    cptr_read = &num[0];
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
}

void Test_UbyteWriteAndRead2(
    CuTest * tc
)
{
    char num[10];
    memset(num, 0, sizeof(char) * 10);
    char *cptr_write = &num[0];
    char *cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0x05);
    CuAssertTrue(tc, 0x05 == bitstream_read_byte(&cptr_read));
}

void Test_UbyteWriteWith4BitOffset(
    CuTest * tc
)
{
    char num[10];
    unsigned int bo;

    memset(num, 0, sizeof(char) * 10);
    char *cptr_write = &num[0];
    char *cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0xFF);
    CuAssertTrue(tc, 0xFF == (unsigned char)bitstream_read_byte(&cptr_read));

    bo = 4;
    cptr_write = &num[0];
    bitstream_write_ubyte_from_bitoffset(&cptr_write, 0x0, &bo);
    cptr_read = &num[0];
    bo = 0;
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 1 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));

    cptr_read = &num[0];
    CuAssertTrue(tc, 0xF0 == (unsigned char)bitstream_read_byte(&cptr_read));
    CuAssertTrue(tc, 0x00 == bitstream_read_byte(&cptr_read));
}

void Test_UbyteWriteWith8BitOffset(
    CuTest * tc
)
{
    char num[10];
    memset(num, 0, sizeof(char) * 10);
    char *cptr_write = &num[0];
    char *cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0x05);
    unsigned int bo = 8;
    cptr_write = &num[0];
    bitstream_write_ubyte_from_bitoffset(&cptr_write, 0xAF, &bo);
    CuAssertTrue(tc, 0x05 == (unsigned char)bitstream_read_byte(&cptr_read));
    CuAssertTrue(tc, 0xAF == (unsigned char)bitstream_read_byte(&cptr_read));
}

void Test_Uint32WriteRead(
    CuTest * tc
)
{
    char num[10];
    char *cptr_write, *cptr_read;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_uint32(&cptr_write, 0x0F070301);
    CuAssertTrue(tc, 0x0F070301 == bitstream_read_uint32(&cptr_read));
}

void Test_MiscWriteRead(
    CuTest * tc
)
{
    char num[10];
    char *cptr_write, *cptr_read;
    char cval;
    uint32_t ival;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0xFF);
    bitstream_write_uint32(&cptr_write, 0x0F070301);
    bitstream_write_ubyte(&cptr_write, 0xFF);
    cval = bitstream_read_byte(&cptr_read);
    CuAssertTrue(tc, (unsigned char)cval == 0xFF);
    ival = bitstream_read_uint32(&cptr_read);
    CuAssertTrue(tc, ival == 0x0F070301);
    cval = bitstream_read_byte(&cptr_read);
    CuAssertTrue(tc, (unsigned char)cval == 0xFF);
}

void Test_WriteFirstUint32(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 9, 32, &bo);
    CuAssertTrue(tc, bo == 32);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 32, &bo);
    CuAssertTrue(tc, bo == 32);
    CuAssertTrue(tc, val == 9);
}

void Test_WriteFirstUint32II(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 32768, 32, &bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 32, &bo);
    CuAssertTrue(tc, val == 32768);
}

void Test_WriteTwo(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 32768, 16,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 255, 16,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 16, &bo);
    CuAssertTrue(tc, val == 32768);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 16, &bo);
    CuAssertTrue(tc, val == 255);
}

void Test_WriteThree(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];
    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 32768, 16,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 255, 8,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 138, 8,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 16, &bo);
    CuAssertTrue(tc, val == 32768);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 8, &bo);
    CuAssertTrue(tc, val == 255);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 8, &bo);
    CuAssertTrue(tc, val == 138);
}

void Test_WriteFive(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 230, 9,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 255, 9,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 31, 5,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 17, 6,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 2, 3,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 9, &bo);
    CuAssertTrue(tc, val == 230);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 9, &bo);
    CuAssertTrue(tc, val == 255);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 5, &bo);
    CuAssertTrue(tc, val == 31);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 6, &bo);
    CuAssertTrue(tc, val == 17);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 3, &bo);
    CuAssertTrue(tc, val == 2);
}

void Test_WriteCrossBoundary(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 230, 18,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 32333, 32,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 18, &bo);
    CuAssertTrue(tc, val == 230);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 32, &bo);
    CuAssertTrue(tc, val == 32333);
}

void Test_WriteCrossBoundaryII(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 230, 17,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 2888, 17,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 32678, 32,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 17, &bo);
    CuAssertTrue(tc, val == 230);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 17, &bo);
    CuAssertTrue(tc, val == 2888);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 32, &bo);
    CuAssertTrue(tc, val == 32678);
}

void Test_WriteCrossBoundaryIII(
    CuTest * tc
)
{
    char bits[1000];
    uint32_t val;
    char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bo = 0;
    bitstream_write_uint32_from_bitoffset(&cptr_write, 23000, 29,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 288800, 30,&bo);
    bitstream_write_uint32_from_bitoffset(&cptr_write, 31678, 21,&bo);

    bo = 0;
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 29, &bo);
    CuAssertTrue(tc, val == 23000);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 30, &bo);
    CuAssertTrue(tc, val == 288800);
    bitstream_read_uint32_from_bitoffset(&cptr_read, &val, 21, &bo);
    CuAssertTrue(tc, val == 31678);
}

void Test_WriteString(
    CuTest * tc
)
{
    char output[100];
    char bits[1000];
    char *cptr_write, *cptr_read;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bitstream_write_string(&cptr_write, "testing", strlen("testing"));

    bitstream_read_string(&cptr_read, output, strlen("testing"));
    CuAssertTrue(tc, 0 == strncmp(output,"testing",strlen("testing")));
}
