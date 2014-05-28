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
    uint8_t* srcBuf = NULL;
    QString mode = getPixels(srcBuf);
    if (m_iState == SUCC_STATUS) {
        rpDst = new uint8_t[m_iWidth*m_iHeight*4];

        uint8_t *indexedBuf = 0;
        if(m_bIndexed) { // index value to color value
            fromIndexed(indexedBuf, srcBuf); //dst src
        }
        else {
            indexedBuf = srcBuf;
        }

        // change color to RGBA(byte order)
        parsePixels(indexedBuf, rpDst, mode); //src dst

        if(m_bIndexed) {
            delete[] indexedBuf;
            indexedBuf = 0;
        }

        uint8_t *mappedBuf = 0;

        if(m_bMapped) { //map the RGBA image
            mappedBuf = new uint8_t[m_iWidth*m_iHeight*4];
            fromMapped(mappedBuf, rpDst); // dst src

            uint8_t *pTmp = rpDst;
            rpDst = mappedBuf;
            mappedBuf = pTmp;

            delete[] mappedBuf;
        }

    }
    else {
        rpDst = NULL;
        mode = "";
    }
    delete [] srcBuf;
    return mode;
}

void AbstractIOParser::fromARGB32(uint8_t *pSrc, const QString &mode){
    uint8_t* parsedBuf = NULL;
    if (m_iState == SUCC_STATUS) {
        uint8_t *mappedBuf = 0;

        if(m_bMapped) { //map the RGBA image
            mappedBuf = new uint8_t[m_iWidth*m_iHeight*4];
            toMapped(mappedBuf, pSrc);// dst, src
        }
        else {
            mappedBuf = pSrc;
        }

        //change RGBA color to destination
        invParsePixels(mappedBuf, parsedBuf, mode); // src, dst

        uint8_t *indexedBuf = 0;
        if(m_bIndexed) { // map it indexed
            toIndexed(indexedBuf, parsedBuf); // dst, src
        }
        else {
            indexedBuf = parsedBuf;
        }

        setPixels(indexedBuf);
        if(m_bMapped) {
            delete[] mappedBuf;
            mappedBuf = 0;
        }
        if(m_bIndexed) {
            delete[] indexedBuf;
            indexedBuf = 0;
        }

    }
    delete [] parsedBuf;
}
