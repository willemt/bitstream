#include <string.h>
#include "CuTest.h"
#include <stdint.h>
#include "bitstream.h"
#include <stdio.h>

void TestBitStream_WriteBitIncreasesBitOffset(
    CuTest * tc
)
{
    unsigned char bits[1000];
    unsigned char *cptr_write;
    unsigned int bo;

    bo = 0;
    cptr_write = &bits[0];
    bitstream_init(bits, 1000);

    bitstream_write_bit_from_bitoffset(&cptr_write, 1, &bo);
    CuAssertTrue(tc, 1 == bo);
}

void TestBitStream_ReadBitNothing(
    CuTest * tc
)
{
    unsigned char bits[1000];
    unsigned char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);
    bo = 0;
    CuAssertTrue(tc, 0 == bitstream_read_bit(&cptr_read, &bo));
}

void TestBitStream_ReadBit(
    CuTest * tc
)
{
    unsigned char bits[1000];
    unsigned char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

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

void TestBitStream_WriteBit(
    CuTest * tc
)
{
    unsigned char bits[1000];
    unsigned char *cptr_write, *cptr_read;
    unsigned int bo;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

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

void TestBitstream_ReadUByteWithNothingResultsInZero(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_read;
    unsigned char val;

    memset(num, 0, sizeof(char) * 10);
    cptr_read = &num[0];

    val = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, val == 0);
}

void TestBitstream_UbyteWriteAndRead(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_write, *cptr_read;
    unsigned char val;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0x0FF);
    val = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, val == 0x0FF);

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

void TestBitstream_UbyteWriteAndRead2(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_write, *cptr_read;
    unsigned char val;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0x05);
    val = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, val == 0x05);
}

void TestBitstream_UbyteWriteWith4BitOffset(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_write, *cptr_read;
    unsigned char val;
    unsigned int bo;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0xFF);
    bo = 4;
    bitstream_write_ubyte_from_bitoffset(&cptr_write, 0x0, &bo);

    val = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, val == 0xF0);
}

void TestBitstream_Uint32WriteRead(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_write, *cptr_read;
    uint32_t val;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_uint32(&cptr_write, 0x0F070301);
    val = bitstream_read_uint32(&cptr_read);
    CuAssertTrue(tc, val == 0x0F070301);
}

void TestBitstream_MiscWriteRead(
    CuTest * tc
)
{
    unsigned char num[10];
    unsigned char *cptr_write, *cptr_read;
    unsigned char cval;
    uint32_t ival;

    memset(num, 0, sizeof(char) * 10);
    cptr_write = &num[0];
    cptr_read = &num[0];

    bitstream_write_ubyte(&cptr_write, 0xFF);
    bitstream_write_uint32(&cptr_write, 0x0F070301);
    bitstream_write_ubyte(&cptr_write, 0xFF);
    cval = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, cval == 0xFF);
    ival = bitstream_read_uint32(&cptr_read);
    CuAssertTrue(tc, ival == 0x0F070301);
    cval = bitstream_read_ubyte(&cptr_read);
    CuAssertTrue(tc, cval == 0xFF);
}

void TestBitStream_WriteFirstUint32(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteFirstUint32II(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteTwo(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteThree(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteFive(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteCrossBoundary(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteCrossBoundaryII(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteCrossBoundaryIII(
    CuTest * tc
)
{
    unsigned char bits[1000];
    uint32_t val;
    unsigned char *cptr_write, *cptr_read;
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

void TestBitStream_WriteString(
    CuTest * tc
)
{
    char output[100];
    unsigned char bits[1000];
    unsigned char *cptr_write, *cptr_read;

    cptr_write = &bits[0];
    cptr_read = &bits[0];

    bitstream_init(bits, 1000);

    bitstream_write_string(&cptr_write, "testing", strlen("testing"));

    bitstream_read_string(&cptr_read, output, strlen("testing"));
    CuAssertTrue(tc, 0 == strncmp(output,"testing",strlen("testing")));
}
