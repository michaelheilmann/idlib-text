# Code Point to UTF-8

UTF-8 an efficient encoding for Unicode code points.

UTF-8 spreads out a single code point over one to four Bytes depending.
More precisely, there are four code point ranges and depending of the code point range a code point belongs to it is encoded into one to four Bytes. 

The table below, each line describes one of the four codepoint ranges.
The column range name contains the name of the code point range.
The columns range (hex) and range (bin) its range in hexadecimal and binary, respectively.
The last four columns show of the Bits of the codepoint are encoded.

|range name | range (hex)        | range (bin)                                                                        | Byte 1    | Byte 2    |	Byte 3    | Byte 4    |
|-----------|--------------------|------------------------------------------------------------------------------------|-----------|-----------|-----------|-----------|
|           | 0000   - 007F      | 0000.0000.0000.0000.0000.0000.0000.0000  - 0000.0000.0000.0000.0000.0000.0111.1111 | 0xxx.xxxx |	          |           |	          |	
|           | 0080   - 07FF      | 0000.0000.0000.0000.0000.0000.1000.0000  - 0000.0000.0000.0000.0000.0111.1111.1111 | 110x.xxxx | 10xx.xxxx | 		      |           |
|           | 0800   - FFFF      | 0000.0000.0000.0000.0000.1000.0000.0000  - 0000.0000.0000.0000.1111 1111 1111 1111 | 1110.xxxx | 10xx.xxxx | 10xx.xxxx |           |	
|           | 010000 - 10FFFF    | 0000.0000.0000.0001.0000.0000.0000.0000  - 0000.0000.0001.0000.1111.1111.1111.1111 | 1111.0xxx | 10xx.xxxx | 10xx.xxxx | 10xx.xxxx |

To convert a Code Point to UTF-8 the following algorithm may be applied.

## Encoding of a Unicode Code Point in Range 1
From the binary representation we observe that there are in total
7 Bits to encode ignoring leading zeroes. In this situation, the
conversion is simply

```
w[0] = (uint8_t)x;
```
where `x` is the `uint32_t` Unicode Code Point value.


## Encoding of a Unicode Code Point in Range 2
From the binary representation we observe that there are in total
3 + 4 + 4 = 11 Bits to encode ignoring leading zeroes.
Bit 1 is is ignored.
The Bits 1 to 5 (five Bits) are stored in Byte 1 at 110y.yyyy.
The Bits 6 to 11 (six Bits) are stored in Byte 2 at 10yy.yyyy.


Firstly, we can now determine the Bit masks required to mask our Bits:

```
uint32_t u[2];
                  // We do not write down the leading zeroes in the following.
u[0] = x & 0x7C0; // 0111.1100.0000 is stored in Byte 1
u[1] = x & 0x03F; // 0000.0011.1111 is stored in Byte 2 
```
where `x` is the `uint32_t` Unicode Code Point value.

Secondly we can determine the shift
```
uint8_t v[2];
v[0] = (uint8_t)(u[0] >> 6); // 0111.1100.0000 >> 6 ~ 0000.0001.1111
v[1] = (uint8_t)(u[1] >> 0); // 0000.0011.1111 >> 0 ~ 0000.0011.1111
````

Add the leading Bytes
```
w[0] = 0xC0 | v[0]; // 0xC0 = 1100.0000 
w[1] = 0x80 | v[1]; // 0x80 = 1000.0000
```
  
## Encoding of a Unicode Code Point in Range 3
From the binary representation we observe that there are in total
4 + 4 + 4 + 4 = 16 Bits to encode.

The Bits 1 to 4 (four Bits) are stored in Byte 1 at 110.yyyy.

The Bits 5 to 10 (six Bits) are stored in Byte 2 at 10yy.yyyy.
The Bits 11 to 16 (six Bits) are stored in Byte 3 at 10yy.yyyy.

Firstly, we can now determine the Bit masks required to mask our Bits:

```
uint32_t u[3];
                   // We do not write down the leading zeroes in the following.
u[0] = x & 0xF000; // 1111.0000.0000.0000
u[1] = x & 0x0FC0; // 0000.1111.1100.0000
u[2] = x & 0x003F; // 0000.0000.0011.1111
```
where `x` is the `uint32_t` Unicode Code Point value.

Secondly we can determine the shift
```
uint8_t v[5];
v[0] = (uint8_t)(u[0] >> 12); // 1111.0000.0000.0000 >> 12 ~ 0000.0000.0000.1111
v[1] = (uint8_t)(u[1] >> 6);  // 0000.1111.1100.0000 >> 6  ~ 0000.0000.0011.1111 
v[2] = (uint8_t)(u[2] >> 0);  // 0000.0000.0011.1111 >> 0  ~ 0000.0000.0011.1111
```

Add the leading Bytes
```
w[0] = 0xE0 | v[0]; // 0xE0 = 1110.0000
w[1] = 0x80 | v[1]; // 0x80 = 1000.0000
w[2] = 0x80 | v[2];
```

#ä Encoding of a Unicode Code Point in Range 4
From the binary representation we observe that there are in total
1 + 4 + 4 + 4 + 4 + 4 = 1 + 5\*4 = 21 Bits to encode ignoring leading zeroes.

The Bits 1 to 3 (three Bits) are stored in Byte 1 at 1111.0yyy.
The Bits 4 to 9 (six Bits) are stored in Byte 2 at 110yy.yyyy.
The Bits 10 to 15 (six Bits) are stored in Byte 3 at 10yy.yyy.
The Bits 16 to 21 (six Bits) are stored in Byte 4 at 10yy.yyy.

Firstly, we can now determine the Bit masks required to mask our Bits:

```
uint32_t u[4];
                     // We do not write down the leading zeroes in the following.
u[0] = x & 0x1C0000; // 0001.1100.0000.0000.0000.0000
u[1] = x & 0x03F000; // 0000.0011.1111.0000.0000.0000
u[2] = x & 0x000FC0; // 0000.0000.0000.1111.1100.0000
u[3] = x & 0x00003F; // 0000.0000.0000.0000.0011.1111
```
where `x` is the `uint32_t` Unicode Code Point value.

Secondly we can determine the shift
```
uint8_t v[5];
v[0] = (uint8_t)(u[0] >> 18); // 0001.1100.0000.0000.0000.0000 >> 18 ~ ß000.0111
v[1] = (uint8_t)(u[1] >> 12); // 0000.0011.1111.0000.0000.0000 >> 12 ~ 0011.1111 
v[2] = (uint8_t)(u[2] >> 6);  // 0000.0000.0000.1111.1100.0000 >> 6  ~ 0011.1111
v[3] = (uint8_t)(u[2] >> 0);  // 0000.0000.0000.0000.0011.1111 >> 0  ~ 0011.1111
```

Add the leading Bytes
```
w[0] = 0xF0 | v[0]; // 0xF0 = 1111.0000
w[1] = 0x80 | v[1]; // 0x80 = 1000.0000
w[2] = 0x80 | v[2];
w[3] = 0x80 | v[3]
```
