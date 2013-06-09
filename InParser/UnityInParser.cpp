#include <QtCore>
#include <QFile>
#include <QString>
#include "BaseDef.h"
#include "UnityInParser.h"
#include "BufParserFac/NorBufParFac.h"

UnityInParser::UnityInParser():AbstractInParser() {
    m_ptBufFac = new NormalBufParserFac();
    m_ptParser = NULL;
    //m_defaultBpp = 0;
}

UnityInParser::~UnityInParser() {
    delete m_ptParser;
    m_ptParser = NULL;
    delete m_ptBufFac;
    m_ptBufFac = NULL;
}


QString UnityInParser::getPixels(unsigned char *&rpDst) {
    QString type;

    QDataStream br(&srcf);
    br.setByteOrder(QDataStream::LittleEndian);
    quint32 len;
    br>>len;

    srcf.seek(srcf.pos()+len);
    if(srcf.pos()%4 != 0) {
        srcf.seek((srcf.pos()/4+1)*4);
    }

    quint32 imageDataSize;
    quint32 pixelSize;
    br>>m_iWidth>>m_iHeight>>imageDataSize>>pixelSize;

    try {
        if(srcf.size() > imageDataSize + 20 && imageDataSize > 0) {
            if ( (1 <= pixelSize && pixelSize <=7 && pixelSize != 6) ||
                    ( pixelSize == 0x20 ||pixelSize == 0x21) ){

                quint32 imageSize = width*height*pixelSize;

                if(pixelSize == 1) {
                    type = "Alpha8";
                }
                else if(pixelSize == 2) {
                    if(m_default16bpp == 0) {
                        type = "RGBA4444";
                    }
                    else if(m_default16bpp == 1) {
                        type = "ARGB1555";
                    }
                    else if(m_default16bpp == 2) {
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
                    imageSize = width*height*4;
                }
                else if(pixelSize == 7) {
                    type = "RGB565";
                    imageSize = width*height*2;
                }
                else if(pixelSize == 0x21 || pixelSize == 0x20) {
                    type = "PVRTC4";
                    imageSize = (width*height)>>1;
                }

                srcf.seek(srcf.size() - imageDataSize);

                rpDst = new uchar[imageSize];
                br.readRawData(rpDst,imageSize);
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

}

int UnityInParser::getPals(unsigned char *&rpDst) {
   return 0;
}

int UnityInParser::parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode) {
    if(!pSrc || m_iState > 0) {
        m_iState = m_iState > 0 ? m_iState : ERR_NORMAL;
    }
    else {
        m_ptParser = m_ptBufFac->createBufParser(mode);
        m_ptParser->parse(pSrc, pDst, width, height);
    }
}


