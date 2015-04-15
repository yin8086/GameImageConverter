#include <QtCore>
#include <QFile>
#include <QString>
#include <QImage>
#include "BaseDef.h"
#include "UnityIOParser.h"
#include "NorBufParFac.h"

UnityIOParser::UnityIOParser():AbstractIOParser() {
    m_ptBufFac = new NormalBufParserFac();
    m_ptParser = NULL;
    m_ptOriBuf = NULL;
    m_bMapped = true;

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


QString UnityIOParser::getPixels(uint8_t *&rpDst) {
    if (m_iState != SUCC_STATUS)
        return "";

    QString type;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);
    uint32_t len;
    br>>len;

    m_ptOrigF.seek(m_ptOrigF.pos()+len);
    if(m_ptOrigF.pos()%4 != 0) {
        m_ptOrigF.seek((m_ptOrigF.pos()/4+1)*4);
    }

    uint32_t imageDataSize;
    uint32_t pixelSize;
    br>>m_iWidth>>m_iHeight>>imageDataSize>>pixelSize;

    try {
        if(m_iWidth > 0 && m_iHeight > 0
            && m_ptOrigF.size() > imageDataSize + 20 && imageDataSize > 0) {
            if ( (1 <= pixelSize && pixelSize <=7 && pixelSize != 6) ||
                    ( pixelSize == 0x20 ||pixelSize == 0x21 ||
                      pixelSize == 0x22 || pixelSize == 0x0c ||
                      pixelSize == 0x0a || pixelSize == 0x0d ||
                      pixelSize == 0x24 || pixelSize == 0x2e) ){

                uint32_t imageSize = m_iWidth*m_iHeight*pixelSize;

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
                else if(pixelSize == 0x0a) {
                    type = "DXT1";
                    uint32_t newW = ((m_iWidth % 4) ? (m_iWidth/4+1) : (m_iWidth /4) ) << 2;
                    uint32_t newH = ((m_iHeight % 4) ? (m_iHeight/4+1) : (m_iHeight /4) ) << 2;
                    imageSize = (newW * newH) >> 1;
                }
                else if(pixelSize == 0x0c ) {
                    type = "DXT5";
                    uint32_t newW = ((m_iWidth % 4) ? (m_iWidth/4+1) : (m_iWidth /4) ) << 2;
                    uint32_t newH = ((m_iHeight % 4) ? (m_iHeight/4+1) : (m_iHeight /4) ) << 2;
                    imageSize = newW * newH;
                }
                else if(pixelSize == 0x0d) {
                    type = "RGBA4444";
                    imageSize = (m_iWidth*m_iHeight)<<1;
                }
                else if(pixelSize == 0x21 || pixelSize == 0x20) {
                    type = "PVRTC4";
                    imageSize = (m_iWidth*m_iHeight)>>1;
                }
                else if(pixelSize == 0x22) {
                    type = "ETC1";
                    imageSize = (m_iWidth*m_iHeight)>>1;
                }
                else if(pixelSize == 0x24)
                {
                    type = "ATCI";
                    uint32_t newW = ((m_iWidth % 4) ? (m_iWidth/4+1) : (m_iWidth /4) ) << 2;
                    uint32_t newH = ((m_iHeight % 4) ? (m_iHeight/4+1) : (m_iHeight /4) ) << 2;
                    imageSize = newW * newH;
                }
                else if(pixelSize == 0x2e)
                {
                    type = "ATC";
                    uint32_t newW = ((m_iWidth % 4) ? (m_iWidth/4+1) : (m_iWidth /4) ) << 2;
                    uint32_t newH = ((m_iHeight % 4) ? (m_iHeight/4+1) : (m_iHeight /4) ) << 2;
                    imageSize = (newW * newH) >> 1;
                }

                m_ptOrigF.seek(m_ptOrigF.size() - imageDataSize);

                rpDst = new uint8_t[imageSize];
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

void UnityIOParser::setPixels(uint8_t *pSrc) {
    if(m_iState != SUCC_STATUS)
        return;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);
    uint32_t len;
    br>>len;

    m_ptOrigF.seek(m_ptOrigF.pos()+len);
    if(m_ptOrigF.pos()%4 != 0) {
        m_ptOrigF.seek((m_ptOrigF.pos()/4+1)*4);
    }

    uint32_t width,height;
    uint32_t imageDataSize;
    uint32_t pixelSize;

    bool modifyWH = false;
    qint64 addrWH = 0;
    uint32_t newSize = 0;
    br>>width>>height>>imageDataSize>>pixelSize;

    if(m_ptOrigF.size() > imageDataSize + 20 && imageDataSize > 0) {
        if ( (1 <= pixelSize && pixelSize <=7 && pixelSize != 6) ||
             ( pixelSize == 0x20 ||pixelSize == 0x21 ||
               pixelSize == 0x22 || pixelSize == 0x0c ||
               pixelSize == 0x0a || pixelSize == 0x0d ||
               pixelSize == 0x24 || pixelSize == 0x2e) ){

            uint32_t oriImageSize = width*height*pixelSize;
            uint32_t imageSize;

            if (pixelSize == 0x05)
                oriImageSize = (width*height)<<2;
            else if(pixelSize == 0x07)
                oriImageSize = (width*height)<<1;
            else if(pixelSize == 0x0a || pixelSize == 0x2e || pixelSize ==0x22) { //dxt3, etc1, ATC
                uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                oriImageSize = (newW*newH)>>1;
            }
            else if(pixelSize == 0x0c || pixelSize == 0x24) { //dxt5, ATCI
                uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                oriImageSize = newW*newH;
            }
            else if(pixelSize == 0x0d)
                oriImageSize = (width*height)<<1;
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
                else if(pixelSize == 0x0a || pixelSize == 0x2e || pixelSize ==0x22) { //dxt3, etc1, ATC
                    uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                    uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                    imageSize = (newW*newH)>>1;
                }
                else if(pixelSize == 0x0c || pixelSize == 0x24){
                    uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                    uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                    imageSize = newW*newH;
                }
                else if(pixelSize == 0x0d)
                    imageSize = (width*height)<<1;
                else if(pixelSize ==0x20 || pixelSize == 0x21)
                    imageSize = (width*height)>>1;

            }
            else {
                imageSize = oriImageSize;
            }

            if(imageSize >= oriImageSize) {
                uint64_t addrData = m_ptOrigF.size() - imageDataSize;
                m_ptOrigF.seek(addrData);

                br.writeRawData((const char*)pSrc, imageSize);
                newSize += imageSize;


                if(oriImageSize != imageDataSize) { //mipmap ?
                    // test mipmap
                    uint64_t estimateSize = imageSize;
                    uint64_t testImageSize = imageSize;
                    int tW = width, tH = heigth;
                    while(tW/2 >=1 && tH/2 >=1) {
                        tW /= 2;
                        tH /= 2;

                        if(pixelSize == 0x0c || pixelSize == 0x24) { //dxt5 ATCI 8bpp
                            uint32_t newW = ((tW % 4) ? (tW/4+1) : (tW /4) ) << 2;
                            uint32_t newH = ((tH % 4) ? (tH/4+1) : (tH /4) ) << 2;
                            testImageSize = newW * newH;
                        }
                        else if(pixelSize == 0x0a || pixelSize == 0x22 || pixelSize == 0x2e) { //dxt3,etc1,atc 4bpp
                            uint32_t newW = ((tW % 4) ? (tW/4+1) : (tW /4) ) << 2;
                            uint32_t newH = ((tH % 4) ? (tH/4+1) : (tH /4) ) << 2;
                            testImageSize = (newW * newH)>>1;
                        }
                        else {
                            testImageSize = width * height;
                        }
                        estimateSize += testImageSize;
                    }

                    if(estimateSize == imageDataSize) {
                        const QImage oriIm(m_ptOriBuf, width, height, QImage::Format_ARGB32);
                        while(width/2 >=1 && height/2 >=1) {
                            width = width/2;
                            height = height/2;
                            const QImage im = oriIm.scaledToWidth(width,Qt::SmoothTransformation);
                            uint8_t* tarBuf = NULL;
                            if(pixelSize == 0x0c || pixelSize == 0x24) { //dxt5 ATCI 8bpp
                                uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                                uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                                imageSize = newW * newH;
                            }
                            else if(pixelSize == 0x0a || pixelSize == 0x22 || pixelSize == 0x2e) { //dxt3,etc1,atc 4bpp
                                uint32_t newW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
                                uint32_t newH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;
                                imageSize = (newW * newH)>>1;
                            }
                            else {
                                imageSize = width * height;
                            }
                            m_ptParser->invParse(im.bits(), tarBuf, width, height);
                            br.writeRawData((const char*)tarBuf, imageSize);
                            delete[] tarBuf;
                            newSize += imageSize;
                        }
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
                m_iState = ERR_IMAGE_SMALL;
        }
        else
            m_iState = ERR_UNKNOWN_FORM;
    }
    else
        m_iState = ERR_NOT_IMAGE;

}



void UnityIOParser::parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString &mode) {
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

void UnityIOParser::invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString &mode) {
    if (m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        m_ptOriBuf = new uint8_t[m_iWidth * m_iHeight * 4];
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

void UnityIOParser::fromMapped(uint8_t *pDst, uint8_t *pSrc) {
    if (m_iState != SUCC_STATUS)
        return;

    QImage im(pSrc, m_iWidth, m_iHeight, QImage::Format_ARGB32);
    im = im.mirrored(false,true);
    memcpy(pDst, im.bits(), sizeof(uint8_t) * m_iWidth * m_iHeight * 4);
}

void UnityIOParser::toMapped(uint8_t *pDst, uint8_t *pSrc) {
    if (m_iState != SUCC_STATUS)
        return;

    QImage im(pSrc, m_iWidth, m_iHeight, QImage::Format_ARGB32);
    im = im.mirrored(false,true);
    memcpy(pDst, im.bits(), sizeof(uint8_t) * m_iWidth * m_iHeight * 4);
}
