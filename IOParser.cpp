#include "BaseDef.h"
#include "IOParser.h"
#include <QFile>

AbstractIOParser::AbstractIOParser() {
    m_iState = SUCC_STATUS;
    m_iWidth = -1;
    m_iHeight = -1;
}

void AbstractIOParser::openFile(const QString& fName) {
    if (m_iState != SUCC_STATUS)
        return;

    m_ptOrigF.setFileName(fName);
    if(m_ptOrigF.open(QIODevice::ReadWrite)){
        m_iState = SUCC_STATUS;
    }
    else {
        m_iState = ERR_NOT_EXIST;
    }
}

void AbstractIOParser::closeFile() {
    uint64_t fSize = -1;
    if(m_ptOrigF.isOpen()) {
        fSize = m_ptOrigF.size();
        m_ptOrigF.close();
    }
    if(fSize == 0)
        m_ptOrigF.remove();
}

int AbstractIOParser::state() {
    return m_iState;
}
void AbstractIOParser::reset() {
    m_iState = SUCC_STATUS;
}

void AbstractIOParser::getWH(int &width, int &height) const {
    if (m_iState != SUCC_STATUS)
        return;

    width = m_iWidth;
    height = m_iHeight;

}


QString AbstractIOParser::toARGB32(uint8_t *&rpDst) {
    uchar* tmpBuf = NULL;
    QString mode = getPixels(tmpBuf);
    if (m_iState == SUCC_STATUS) {
        rpDst = new uint8_t[m_iWidth*m_iHeight*4];
        uint8_t *palBuf = 0;
        getPals(palBuf);
        if(palBuf) {
            uint8_t *tmpBuf2 = 0;
            parsePals(tmpBuf2, tmpBuf, palBuf, mode);
            parsePixels(tmpBuf2, rpDst, mode);
            delete [] tmpBuf2;
        }
        else {
            parsePixels(tmpBuf, rpDst, mode);
        }

    }
    else {
        rpDst = NULL;
        mode = "";
    }
    delete [] tmpBuf;
    return mode;
}

void AbstractIOParser::fromARGB32(uint8_t *pSrc, const QString &mode){
    uchar* tmpBuf = NULL;
    if (m_iState == SUCC_STATUS) {
        invParsePixels(pSrc, tmpBuf, mode);
        setPixels(tmpBuf);
    }
    delete [] tmpBuf;
}
