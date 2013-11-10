#include<QtCore>
#include<zlib.h>
#include"BaseDef.h"
#include"GzipGimIOParser.h"


void GzipGimIOParser::GzipUncomp(const char *inBuf,
                                 char *&outBuf,
                                 uint32_t *pSize) {
    if (m_iState != SUCC_STATUS)
        return;

    uint32_t gzipNum = *(uint32_t *)inBuf;

    char header[4] = {0};
    *pSize = 0;

    uint32_t firstAddr = *(uint32_t *)(inBuf + 4);
    strncpy(header, inBuf + firstAddr + 0x10, 3);
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

        outBuf = new char[*pSize];
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

QString GzipGimIOParser::getPals(unsigned char *&rpDst) {
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
        char *compBuf = new char[m_ptOrigF.size() - 0x1800];
        m_ptOrigF.seek(0x1800);
        br.readRawData(compBuf, m_ptOrigF.size() - 0x1800);
        char *uncompBuf = 0;
        uint32_t uncompSize = 0;
        GzipUncomp(compBuf, uncompBuf, &uncompSize);

        if(m_iState == SUCC_STATUS) {
            rpDst = new unsigned char[4*256+uncompSize];
            memcpy(rpDst, palBuf, 4*256);
            memcpy(rpDst+4*256, uncompBuf, uncompSize);
        }
        delete [] compBuf;
        delete [] uncompBuf;
    }
    else
        m_iState = ERR_NOT_IMAGE;

    if(m_iState == SUCC_STATUS)
        return type;
    else
        return "";
}
