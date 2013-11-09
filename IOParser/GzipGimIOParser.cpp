#include<QtCore>
#include<zlib.h>
#include"BaseDef.h"
#include"GzipGimIOParser.h"


QString GzipGimIOParser::getPals(unsigned char *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return "";

    QString type;
    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);

    const quint32 startAddr = 0x1800;
    m_ptOrigF.seek(startAddr);
    quint32 gzipNum, firstAdd;
    br >> gzipNum >> firstAdd;
    m_ptOrigF.seek(startAddr + firstAdd + 0x10);

    char header[4] = {0};
    br.readRawData(header, 3);
    if(gzipNum > 0 && QString(header) == "\x1f\x8b\x08") {
        m_ptOrigF.seek(startAddr+0x04);
        quint32 curAddr,nextAddr;
        for(int i=0; i < gzipNum; ++i) {
            br >> curAddr >> nextAddr;
            m_ptOrigF.seek(m_ptOrigF.pos()-4);
            //读取Gzip，合并
        }
    }
    else
        m_iState = ERR_NOT_IMAGE;

    if(m_iState == SUCC_STATUS)
        return type;
    else
        return "";
}
