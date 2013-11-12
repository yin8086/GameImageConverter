#include <QtCore>
#include "BaseDef.h"
#include "rg_etc1.h"
#include "ETC1BufParser.h"

QString ETC1BufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    const uint8_t *pTile = pSrc;

    for(int posY = 0; posY < height; posY += 4){
        for(int posX = 0; posX < width; posX += 4) {
            uint32_t tarRgba[16];
            rg_etc1::unpack_etc1_block(pTile, tarRgba); // Decompress to a Blk

            uint8_t *pSrcBlk = (uint8_t *)tarRgba;
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

        pTile += 8;
        }
    }

    return "ETC1";
}

void ETC1BufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {

    int bufW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
    int bufH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;

    rpDst = new uint8_t [(bufW * bufH)>>1]; // create the target buffer

    uint8_t *pTile = rpDst; // pointer to the given block
    rg_etc1::pack_etc1_block_init(); // init
    rg_etc1::etc1_pack_params etcPara;

    for(int posY = 0; posY < height; posY += 4){
        for(int posX = 0; posX < width; posX += 4) {

            uint32_t srcRgba[16];// create a RGBA block

            uint8_t *pTarBlk = (uint8_t *)srcRgba;

            for(int y = 0; y < 4; y++) {
                for(int x = 0; x < 4; x++) {

                    int fX = posX + x;
                    int fY = posY + y;

                    if( fY < height && fX < width) { // copy to the cur blk.
                        const uint8_t *srcPixel = pSrc + (width * fY + fX ) * 4;
                        pTarBlk[0] = srcPixel[2];
                        pTarBlk[1] = srcPixel[1];
                        pTarBlk[2] = srcPixel[0];
                    }
                    else {
                        pTarBlk[0] = 0;
                        pTarBlk[1] = 0;
                        pTarBlk[2] = 0;
                    }

                    pTarBlk[3] = 255; // alpha is disabled.
                    pTarBlk += 4;
                }
            }

            rg_etc1::pack_etc1_block(pTile, srcRgba, etcPara);
            pTile += 8;
        }
    }
}


