// ATC format http://forum.xda-developers.com/showthread.php?t=437777
#include <QtCore>
#include <QString>
#include "squish.h"
#include "BaseDef.h"
#include "ATCBufParser.h"

const unsigned ATCBufParser::MAX_COLOR_VAL = 255;

QString ATCBufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    const uint8_t *pTile = pSrc;

    for(int posY = 0; posY < height; posY += 4){
        for(int posX = 0; posX < width; posX += 4) {
            uint8_t tarRgba[16*4];
            DecompressATC(pTile, tarRgba);

            uint8_t *pSrcBlk = tarRgba;
            for(int y = 0; y < 4; y++) {
                for(int x = 0; x < 4; x++) {
                    int fX = posX + x;
                    int fY = posY + y;

                    if( fY < height && fX < width) { // Put block into the right place
                        uint8_t *tarPixel = pDst + (width * fY + fX ) * 4;
                        tarPixel[0] = pSrcBlk[2];
                        tarPixel[1] = pSrcBlk[1];
                        tarPixel[2] = pSrcBlk[0];
                        tarPixel[3] = pSrcBlk[3];
                    }
                    pSrcBlk += 4;
                }
            }

        pTile += 8; // 8Byte = 64bits/16 pixels = 4bpp
        }
    }

    return "ATC";
}

void ATCBufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {


    int bufW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
    int bufH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;

    rpDst = new uint8_t [(bufW * bufH)>>1]; // create the target buffer

    uint8_t *pTile = rpDst; // pointer to the given block


    for(int posY = 0; posY < height; posY += 4){
        for(int posX = 0; posX < width; posX += 4) {

            uint8_t srcRgba[16*4];// create a RGBA block

            uint8_t *pTarBlk = srcRgba;

            for(int y = 0; y < 4; y++) {
                for(int x = 0; x < 4; x++) {

                    int fX = posX + x;
                    int fY = posY + y;

                    if( fY < height && fX < width) { // copy to the cur blk.
                        const uint8_t *srcPixel = pSrc + (width * fY + fX ) * 4;
                        pTarBlk[0] = srcPixel[2];
                        pTarBlk[1] = srcPixel[1];
                        pTarBlk[2] = srcPixel[0];
                        pTarBlk[3] = srcPixel[3];
                    }
                    else {
                        pTarBlk[0] = 0;
                        pTarBlk[1] = 0;
                        pTarBlk[2] = 0;
                        pTarBlk[3] = 0;
                    }
                    pTarBlk += 4;
                }
            }

            squish::Compress(srcRgba, pTile, squish::kDxt1);
            DXTC2ATC(pTile);

            pTile += 8;

        }
    }

}

#define CLAMP(curV, minV, maxV) qMax((minV), qMin( (curV), (maxV)));

void ATCBufParser::DecompressATC(const uint8_t* block, uint8_t *rgba)
{
    const uint8_t *colorBlk = block;

    uint8_t codeBook[16];
    uint8_t r1,g1,b1,r2,b2,g2,gBit;

    // 1. Decompresss color, codeBook in RGBA
    uint16_t tmpVal = *(uint16_t *)(colorBlk);

    gBit = (tmpVal >> 15) & 0x1;
    r1 = (tmpVal >> 10) & 0x1f;
    g1 = (tmpVal >> 5) & 0x1f;
    b1 = tmpVal & 0x1f;

    tmpVal = *(uint16_t *)(colorBlk + 2);

    r2 = (tmpVal >> 11) & 0x1f;
    g2 = (tmpVal >> 5) & 0x3f;
    b2 = tmpVal & 0x1f;


    if(gBit == 0)
    {
        codeBook[0] = (r1 << 3) | (r1 >> 2);
        codeBook[1] = (g1 << 3) | (g1 >> 2);
        codeBook[2] = (b1 << 3) | (b1 >> 2);

        codeBook[12 + 0] = (r2 << 3) | (r2 >> 2);
        codeBook[12 + 1] = (g2 << 2) | (g2 >> 4);
        codeBook[12 + 2] = (b2 << 3) | (b2 >> 2);
    }
    else
    {
        codeBook[8 + 0] = (r1 << 3) | (r1 >> 2);
        codeBook[8 + 1] = (g1 << 3) | (g1 >> 2);
        codeBook[8 + 2] = (b1 << 3) | (b1 >> 2);

        codeBook[12 + 0] = (r2 << 3) | (r2 >> 2);
        codeBook[12 + 1] = (g2 << 2) | (g2 >> 4);
        codeBook[12 + 2] = (b2 << 3) | (b2 >> 2);
    }


    int s, e;
    for(int channel = 0; channel < 3; ++channel)
    {
        if(gBit == 0)
        {
            s = codeBook[channel];
            e = codeBook[12 + channel];

            codeBook[4 + channel] =  (uint8_t)((2*s+e)/3);
            codeBook[8 + channel] = (uint8_t)((s+2*e)/3);
        }
        else
        {
            s = codeBook[8 + channel];
            e = codeBook[12 + channel];

            codeBook[channel] =  0;
            codeBook[4 + channel] = (uint8_t)CLAMP(((4*s-e)/4), 0, 0xff);

        }
    }

    uint8_t indices[16];
    for(int i=0; i<4; ++i)
    {
        uint8_t* ind = indices + 4*i;
        uint8_t packed = colorBlk[4 + i];

        ind[0] = packed & 0x3;
        ind[1] = ( packed >> 2 ) & 0x3;
        ind[2] = ( packed >> 4 ) & 0x3;
        ind[3] = ( packed >> 6 ) & 0x3;
    }

    for(int i=0; i<16; ++i)
    {
        rgba[i*4 + 0] = codeBook[ indices[i]*4 + 0];
        rgba[i*4 + 1] = codeBook[ indices[i]*4 + 1];
        rgba[i*4 + 2] = codeBook[ indices[i]*4 + 2];
        rgba[i*4 + 3] = 255;  // all alpha set to 255
    }

}


/// if color1 < color2, dxt is punch through alpha
/// from the src of squinsh, we can know that squinsh
/// will never compress the texture to punch through alpha
/// that is to say, the output block is always: color1 > color2
void ATCBufParser::DXTC2ATC(uint8_t* block)
{
    uint8_t *colorBlk = block;

    uint16_t color1 = *(uint16_t *)(colorBlk);
    uint16_t color2 = *(uint16_t *)(colorBlk+2);

    Q_ASSERT(color1 >= color2);

    // 1.modify start color from 565 to 555
    uint8_t r1 = (color1 >> 11) & 0x1f;
    uint8_t g1 = (color1 >> 5) & 0x3f;
    uint8_t b1 = color1 & 0x1f;
    // Formula http://www.stardrad.com/blog/%E6%97%A0%E6%8D%9F%E9%9D%9E%E5%8E%8B%E7%BC%A9%E5%9B%BE%E7%89%87%E5%AD%98%E5%82%A8%E6%A0%BC%E5%BC%8F%E4%BB%8B%E7%BB%8D%EF%BC%88%E4%B8%80%EF%BC%89-%E5%83%8F%E7%B4%A0%E8%A1%A8%E7%A4%BA/
    g1 = (g1*31+31)/63;
    *(uint16_t *)(colorBlk) = (0 << 15)|(r1 << 10)|(g1 << 5)|b1;

    // 2.remap indices
    uint8_t remapped[16];
    for(int i=0; i<4; ++i) // iterate 4 bytes
    {
        for(int j=0; j<4; ++j) // iterate 4 indices in one byte
        {
            remapped[i*4 + j] = (colorBlk[4+i] >> (j*2)) & 0x3;
            if(1 == remapped[i*4 + j])
            {
                remapped[i*4 + j] = 3;
            }
            else if(2 == remapped[i*4 + j])
            {
                remapped[i*4 + j] = 1;
            }
            else if(3 == remapped[i*4 + j])
            {
                remapped[i*4 + j] = 2;
            }
        }
        colorBlk[4+i] = remapped[i*4] | (remapped[i*4 + 1] << 2) |
                        (remapped[i*4 + 2] << 4) | (remapped[i*4 + 3] << 6);
    }


}
