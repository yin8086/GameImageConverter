#include <QtCore>
#include <QFile>
#include <QString>
#include <QImage>
#include "BaseDef.h"
#include "UnityIOParser.h"
#include "BufParserFac/NorBufParFac.h"

UnityIOParser::UnityIOParser():AbstractIOParser() {
    m_ptBufFac = new NormalBufParserFac();
    m_ptParser = NULL;
    m_ptOriBuf = NULL;

    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    m_iDefault16bpp = settings.value("Unity/Default16bpp", 0).toInt();
    settings.setValue("Unity/Default16bpp", m_iDefault16bpp);
}

UnityIOParser::~UnityIOParser() {
    delete m_ptParser;
    m_ptParser = NULL;
    delete m_ptBufFac;
    m_ptBufFac = NULL;
    delete [] m_ptOriBuf;
    m_ptOriBuf = NULL;
}


QString UnityIOParser::getPixels(unsigned char *&rpDst) {
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
                    ( pixelSize == 0x20 ||pixelSize == 0x21 || pixelSize == 0x0c) ){

                quint32 imageSize = m_iWidth*m_iHeight*pixelSize;

                if(pixelSize == 1) {
                    type = "ALPHA8";
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
                else if(pixelSize == 0x0c) {
                    type = "DXT5";
                    imageSize = imageDataSize;
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

void UnityIOParser::setPixels(unsigned char *pSrc) {
    if(m_iState != SUCC_STATUS)
        return;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);
    quint32 len;
    br>>len;

    m_ptOrigF.seek(m_ptOrigF.pos()+len);
    if(m_ptOrigF.pos()%4 != 0) {
        m_ptOrigF.seek((m_ptOrigF.pos()/4+1)*4);
    }

    quint32 width,height;
    quint32 imageDataSize;
    quint32 pixelSize;

    bool modifyWH = false;
    qint64 addrWH = 0;
    quint32 newSize = 0;
    br>>width>>height>>imageDataSize>>pixelSize;

    if(m_ptOrigF.size() > imageDataSize + 20 && imageDataSize > 0) {
        if ( (1 <= pixelSize && pixelSize <=7 && pixelSize != 6) ||
                ( pixelSize == 0x20 ||pixelSize == 0x21 || pixelSize == 0x0c) ){

            quint32 oriImageSize = width*height*pixelSize;
            quint32 imageSize;

            if (pixelSize == 0x05)
                oriImageSize = (width*height)<<2;
            else if(pixelSize == 0x07)
                oriImageSize = (width*height)<<1;
            else if(pixelSize == 0x0c) {
                quint32 newW = (width % 4) ? (((width >> 2) <<2) + 1):((width >> 2) <<2);
                quint32 newH = (height % 4) ? (((height >> 2) <<2) + 1):((height >> 2) <<2);
                oriImageSize = newW*newH;
            }
            else if(pixelSize ==0x20 || pixelSize == 0x21) {
                oriImageSize = (width*height)>>1;
            }

            if (width != m_iWidth || height != m_iHeight) {
                modifyWH = true;
                addrWH = m_ptOrigF.pos() - 16;

                width = m_iWidth;
                height = m_iHeight;

                imageSize = width*height*pixelSize;

                if (pixelSize == 0x05)
                    imageSize = (width*height)<<2;
                else if(pixelSize == 0x07)
                    imageSize = (width*height)<<1;
                else if(pixelSize == 0x0c){
                    quint32 newW = (width % 4) ? (((width >> 2) <<2) + 1):((width >> 2) <<2);
                    quint32 newH = (height % 4) ? (((height >> 2) <<2) + 1):((height >> 2) <<2);
                    oriImageSize = newW*newH;
                }
                else if(pixelSize ==0x20 || pixelSize == 0x21)
                    imageSize = (width*height)>>1;

            }
            else {
                imageSize = oriImageSize;
            }

            quint64 addrData = m_ptOrigF.size() - imageDataSize;
            m_ptOrigF.seek(addrData);

            br.writeRawData((const char*)pSrc, imageSize);
            newSize += imageSize;

            if(oriImageSize != imageDataSize && pixelSize != 0x0c) { //mipmap
                const QImage oriIm(m_ptOriBuf, width, height, QImage::Format_ARGB32);
                while(width/2 >=1 && height/2 >=1) {
                    width /= 2;
                    height /= 2;
                    const QImage im = oriIm.scaledToWidth(width,Qt::SmoothTransformation);
                    uchar* tarBuf = NULL;
                    imageSize /= 4;
                    m_ptParser->invParse(im.bits(), tarBuf, width, height);
                    br.writeRawData((const char*)tarBuf, imageSize);
                    delete[] tarBuf;
                    newSize += imageSize;
                }
            }
            if(modifyWH) {
                m_ptOrigF.seek(addrWH);
                br <<m_iWidth <<m_iHeight <<newSize;
                m_ptOrigF.seek(addrData - 4);
                br <<newSize;
            }
            m_iState = SUCC_STATUS;
        }
        else
            m_iState = ERR_UNKNOWN_FORM;
    }
    else
        m_iState = ERR_NOT_IMAGE;

}


void UnityIOParser::getPals(unsigned char *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return;
    rpDst = NULL;
}

void UnityIOParser::parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode) {
    if (m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        m_ptParser = m_ptBufFac->createBufParser(mode);
        if (m_ptParser) {
            m_ptParser->parse(pSrc, pDst, m_iWidth, m_iHeight);
            m_iState = SUCC_STATUS;
        }
        else
            m_iState = ERR_BUFFER_PARSER_ERROR;
    }
}

void UnityIOParser::invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString &mode) {
    if (m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        m_ptOriBuf = new unsigned char[m_iWidth * m_iHeight * 4];
        memcpy(m_ptOriBuf, pSrc, m_iWidth * m_iHeight * 4);
        m_ptParser = m_ptBufFac->createBufParser(mode);
        if (m_ptParser) {
            m_ptParser->invParse(pSrc, rpDst, m_iWidth, m_iHeight);
            m_iState = SUCC_STATUS;
        }
        else
            m_iState = ERR_BUFFER_PARSER_ERROR;
    }
}


QString UnityIOParser::exportName(const QString &origName, QString &mode) const {
    QString testStr = origName.left(origName.length() - 4);
    QString binName = testStr.left(testStr.lastIndexOf("."));
    mode = testStr.right(testStr.length() - binName.length() - 1);
    return binName;
}
