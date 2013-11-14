#include<QtCore>
#include<zlib.h>
#include"BaseDef.h"
#include"GzipGimIOParser.h"
#include "utility/swizzleUtility.h"


GzipGimIOParser::GzipGimIOParser():AbstractIOParser() {
    m_bIndexed= true;
    m_bMapped = true;
}

void GzipGimIOParser::GzipUncomp(const uint8_t *inBuf,
                                 uint8_t *&outBuf,
                                 uint32_t *pSize) {
    if (m_iState != SUCC_STATUS)
        return;

    uint32_t gzipNum = *(uint32_t *)inBuf;

    char header[4] = {0};
    *pSize = 0;

    uint32_t firstAddr = *(uint32_t *)(inBuf + 4);
    strncpy(header, (const char *)(inBuf + firstAddr + 0x10), 3);
    if(gzipNum > 0 && strcmp(header, "\x1f\x08\x8b")) {
        ChunkDesc *descTab = new ChunkDesc[gzipNum];
        int offs = 4;

        for(int i = 0; i < gzipNum; ++i) {
            descTab[i].start = *(uint32_t *)(inBuf + offs);
            descTab[i].end = *(uint32_t *)(inBuf + offs + 4);
            descTab[i].decomLen = *(uint32_t *)(inBuf + descTab[i].start);
            *pSize += descTab[i].decomLen;
            offs += 4;
        }

        outBuf = new uint8_t[*pSize];
        uint32_t uncompOff = 0;
        for(int i = 0; i < gzipNum; ++i) {
            z_stream strm;
            strm.next_in = (Bytef *) (inBuf + descTab[i].start + 0x10);
            strm.avail_in = descTab[i].end - descTab[i].start - 0x10;
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            inflateInit2(&strm, 16 + MAX_WBITS);

            strm.next_out = (Bytef *)(outBuf + uncompOff);
            strm.avail_out = descTab[i].decomLen;

            int status_do = inflate(&strm, Z_FINISH);
            int status_end = inflateEnd(&strm);

            if (status_do != Z_STREAM_END || status_end != Z_OK) {
                m_iState = ERR_NORMAL;
            }

            uncompOff += descTab[i].decomLen;


        }

        delete []descTab;
    }
    else {
        outBuf = 0;
        m_iState = ERR_NORMAL;
    }
}

QString GzipGimIOParser::getPixels(uint8_t *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return "";

    QString type;
    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);
    if(m_ptOrigF.size() > 0x1800) {
        //Pal
        char palBuf[4*256] = {0};
        m_ptOrigF.seek(0);
        br.readRawData(palBuf, 256*4);

        //type
        m_ptOrigF.seek(0x400);
        char header[4] = {0};
        br.readRawData(header, 4);
        if(strcmp(header, "MAP\x00") == 0)
            type = "MAP";
        else
            type = "REG";

        //decompress
        uint8_t *compBuf = new uint8_t[m_ptOrigF.size() - 0x1800];
        m_ptOrigF.seek(0x1800);
        br.readRawData((char *)compBuf, m_ptOrigF.size() - 0x1800);
        uint8_t *uncompBuf = 0;
        uint32_t uncompSize = 0;
        GzipUncomp(compBuf, uncompBuf, &uncompSize);

        if(m_iState == SUCC_STATUS) { //return indexed pixels
            rpDst = uncompBuf;

            if(type == "MAP") {
                m_ptOrigF.seek(0x400);
                char mapBuf[0x30] = {0};

                br.readRawData(mapBuf,0x30);
                m_iWidth = *(uint16_t *)(mapBuf + 0x1c);
                m_iHeight = *(uint16_t *)(mapBuf + 0x1e);

                if(*(uint16_t *)(mapBuf + 0x1a) != 0)
                    type = "FACE";

            }
            else {
                m_iWidth = 512;
                m_iHeight = 272;
            }

        }
        else {
            delete [] uncompBuf;
        }
        delete [] compBuf;
    }
    else
        m_iState = ERR_NOT_IMAGE;

    if(m_iState == SUCC_STATUS)
        return type;
    else
        return "";
}


void GzipGimIOParser::fromIndexed(uint8_t *&rpDst, uint8_t *pSrc) {

    if (m_iState != SUCC_STATUS)
        return;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);

    m_ptOrigF.seek(0);
    uint8_t *pPal = new uint8_t[4*256];
    br.readRawData((char*)pPal, 4*256);

    rpDst = new uint8_t[m_iWidth*m_iHeight*4];
    uint8_t *srcL = pSrc, *srcP = 0;
    uint32_t *dstP = 0, *dstL = (uint32_t *)rpDst;

    uint8_t index = 0;
    for(int y = 0; y < m_iHeight; y++) {
        srcP = srcL; dstP = dstL;
        for(int x = 0; x < m_iWidth; ++x) {
            index = *srcP++;
            //*dstP++ = *((uint32_t *)pPal + index);
            *((uint8_t *)dstP + 0) = pPal[index*4 + 2];
            *((uint8_t *)dstP + 1) = pPal[index*4 + 1];
            *((uint8_t *)dstP + 2) = pPal[index*4 + 0];
            *((uint8_t *)dstP + 3) = pPal[index*4 + 3];

            dstP++;
        }
        srcL += m_iWidth;
        dstL += m_iWidth;
    }

}

void GzipGimIOParser::toIndexed(uint8_t *&rpDst, uint8_t *pSrc) {
    // todo

}


void GzipGimIOParser::parsePixels(uint8_t *pSrc,
                                  uint8_t *pDst,
                                  const QString &) {
    if (m_iState != SUCC_STATUS)
        return;

    memcpy(pDst, pSrc, m_iWidth * m_iHeight * 4);
}

void GzipGimIOParser::setPixels(uint8_t *pSrc) {
    if (m_iState != SUCC_STATUS)
        return;
}

void GzipGimIOParser::invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString &) {
    if (m_iState != SUCC_STATUS)
        return;
}

QString GzipGimIOParser::exportName(const QString &origName, QString &mode) const {
    if (m_iState != SUCC_STATUS)
        return "";

    QString testStr = origName.left(origName.length() - 4);
    QString binName = testStr.left(testStr.lastIndexOf("."));
    mode = testStr.right(testStr.length() - binName.length() - 1);
    return binName;
}

void GzipGimIOParser::fromMapped(uint8_t *pDst, uint8_t *pSrc) {
    if (m_iState != SUCC_STATUS)
        return;
    unswizzleARGB(pDst, pSrc, m_iWidth, m_iHeight);

}

void GzipGimIOParser::toMapped(uint8_t *pDst, uint8_t *pSrc) {
    if (m_iState != SUCC_STATUS)
        return;
    swizzleARGB(pDst, pSrc, m_iWidth, m_iHeight);
}



