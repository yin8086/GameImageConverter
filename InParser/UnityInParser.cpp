#include <QtCore>
#include <QFile>
#include <QString>
#include "BaseDef.h"
#include "UnityInParser.h"
#include "BufParserFac/NorBufParFac.h"

UnityInParser::UnityInParser():AbstractInParser() {
    m_ptBufFac = new NormalBufParserFac();
    m_ptParser = NULL;

    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    m_iDefault16bpp = settings.value("Unity/Default16bpp", 0).toInt();
    settings.setValue("Unity/Default16bpp", m_iDefault16bpp);
}

UnityInParser::~UnityInParser() {
    delete m_ptParser;
    m_ptParser = NULL;
    delete m_ptBufFac;
    m_ptBufFac = NULL;
}


QString UnityInParser::getPixels(unsigned char *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return "";

    QString type;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);
    quint32 len;
    br>>len;

    m_ptOrigF.seek(m_ptOrigF.pos()+len);
    if(m_ptOrigF.pos()%4 != 0) {
        m_ptOrigF.seek((m_ptOrigF.pos()/4+1)*4);
    }

    quint32 imageDataSize;
    quint32 pixelSize;
    br>>m_iWidth>>m_iHeight>>imageDataSize>>pixelSize;

    try {
        if(m_ptOrigF.size() > imageDataSize + 20 && imageDataSize > 0) {
            if ( (1 <= pixelSize && pixelSize <=7 && pixelSize != 6) ||
                    ( pixelSize == 0x20 ||pixelSize == 0x21) ){

                quint32 imageSize = m_iWidth*m_iHeight*pixelSize;

                if(pixelSize == 1) {
                    type = "Alpha8";
                }
                else if(pixelSize == 2) {
                    if(m_iDefault16bpp == 0) {
                        type = "RGBA4444";
                    }
                    else if(m_iDefault16bpp == 1) {
                        type = "ARGB1555";
                    }
                    else if(m_iDefault16bpp == 2) {
                        type = "ARGB4444";
                    }

                }
                else if(pixelSize == 3) {
                    type = "RGB888";
                }
                else if(pixelSize == 4) {
                    type = "RGBA8888";
                }
                else if(pixelSize == 5) {
                    type = "ARGB8888";
                    imageSize = m_iWidth*m_iHeight*4;
                }
                else if(pixelSize == 7) {
                    type = "RGB565";
                    imageSize = m_iWidth*m_iHeight*2;
                }
                else if(pixelSize == 0x21 || pixelSize == 0x20) {
                    type = "PVRTC4";
                    imageSize = (m_iWidth*m_iHeight)>>1;
                }

                m_ptOrigF.seek(m_ptOrigF.size() - imageDataSize);

                rpDst = new uchar[imageSize];
                br.readRawData((char *)rpDst,imageSize);
                m_iState = SUCC_STATUS;

            }
            else {
                m_iState = ERR_UNKNOWN_FORM;
            }
        }
        else {
            m_iState = ERR_NOT_IMAGE;
        }
    }
    catch(std::exception) {
        m_iState = ERR_INVALID_FILE;
    }

    if(m_iState == SUCC_STATUS)
        return type;
    else
        return "";

}

void UnityInParser::getPals(unsigned char *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return;
    rpDst = NULL;
}

void UnityInParser::parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode) {
    if (m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        m_ptParser = m_ptBufFac->createBufParser(mode);
        m_ptParser->parse(pSrc, pDst, m_iWidth, m_iHeight);
        m_iState = SUCC_STATUS;
    }
}


