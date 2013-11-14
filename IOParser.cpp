#include <QFile>
#include "BaseDef.h"
#include "IOParser.h"


AbstractIOParser::AbstractIOParser() {
    m_iState = SUCC_STATUS;
    m_iWidth = -1;
    m_iHeight = -1;
    m_bIndexed = false;
    m_bMapped = false;
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
    uint8_t* tmpBuf = NULL;
    QString mode = getPixels(tmpBuf);
    if (m_iState == SUCC_STATUS) {
        rpDst = new uint8_t[m_iWidth*m_iHeight*4];

        uint8_t *tmpBuf2 = 0;
        if(m_bIndexed) { // index value to color value
            fromIndexed(tmpBuf2, tmpBuf);
        }
        else {
            tmpBuf2 = tmpBuf;
        }

        // change color to RGBA(byte order)
        parsePixels(tmpBuf2, rpDst, mode);

        if(m_bIndexed)
            delete[] tmpBuf2;

        uint8_t *tmpBuf3;

        if(m_bMapped) { //map the RGBA image
            tmpBuf3 = new uint8_t[m_iWidth*m_iHeight*4];
            fromMapped(tmpBuf3, rpDst);

            uint8_t *pTmp = rpDst;
            rpDst = tmpBuf3;
            tmpBuf3 = pTmp;

            delete[] tmpBuf3;
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
    uint8_t* tmpBuf = NULL;
    if (m_iState == SUCC_STATUS) {
        uint8_t *tmpBuf2 = 0;

        if(m_bMapped) { //map the RGBA image
            tmpBuf2 = new uint8_t[m_iWidth*m_iHeight*4];
            toMapped(tmpBuf2, pSrc);
        }
        else {
            tmpBuf2 = pSrc;
        }

        //change RGBA color to destination
        invParsePixels(tmpBuf2, tmpBuf, mode);

        uint8_t *tmpBuf3 = 0;
        if(m_bIndexed) { // map it indexed
            toIndexed(tmpBuf3, tmpBuf2);
        }
        else {
            tmpBuf3 = tmpBuf2;
        }

        setPixels(tmpBuf3);
        if(m_bMapped)
            delete[] tmpBuf2;
        if(m_bIndexed)
            delete[] tmpBuf3;

    }
    delete [] tmpBuf;
}
