#include <QFile>
#include <QDataStream>
#include "BaseDef.h"
#include "TDXTIOParser.h"
#include "NorBufParFac.h"


TDXTIOParser::TDXTIOParser():AbstractIOParser() {
    m_ptBufFac = new NormalBufParserFac();
    m_ptParser = NULL;
}

QString TDXTIOParser::getPixels(uint8_t *&rpDst)
{
    if(m_iState != SUCC_STATUS)
        return "";
    else
    {
        QDataStream br(&m_ptOrigF);
        br.setByteOrder(QDataStream::LittleEndian);

        {
            QScopedArrayPointer<char> header(new char[5]);
            br.readRawData(header.data(), 4);
            header[4] = '\0';
            if(qstrcmp(header.data(), "TDXT") != 0)
            {
                m_iState = ERR_UNKNOWN_FORM;
                return "";
            }
        }

        m_ptOrigF.seek(0x0c);
        quint32 fileLen;
        quint16 width, height;
        br >> fileLen >> width >> height;

        if(width == 0 || height == 0)
        {
            m_iState = ERR_INVALID_FILE;
            return "";
        }

        m_iWidth = width;
        m_iHeight = height;
        m_ptOrigF.seek(0x40);

        int bpp = (fileLen - 0x40) / (width * height);
        QString type;
        if(bpp == 1)
        {
            // DXT5?
            rpDst = new uint8_t[width*height*bpp];
            br.readRawData((char *)rpDst, width*height*bpp);
            m_iState = SUCC_STATUS;
            type = "DXT5";
        }
        else if(bpp == 4)
        {
            // RGBA8888
            rpDst = new uint8_t[width*height*bpp];
            br.readRawData((char *)rpDst, width*height*bpp);
            m_iState = SUCC_STATUS;
            type = "RGBA8888";
        }
        else
        {
            m_iState = ERR_INVALID_FILE;
        }
        if(m_iState == SUCC_STATUS)
        {
            return type;
        }
        else
        {
            return "";
        }

    }
}

void TDXTIOParser::setPixels(uint8_t *pSrc)
{
    if(m_iState != SUCC_STATUS)
        return;

    QDataStream br(&m_ptOrigF);
    br.setByteOrder(QDataStream::LittleEndian);

    // do not modify width and height
    m_ptOrigF.seek(0x0c);
    quint32 fileLen;
    br >> fileLen;

    quint32 bufSize = (fileLen - 0x40);
    m_ptOrigF.seek(0x40);
    br.writeRawData((const char*)pSrc, bufSize);
    m_iState = SUCC_STATUS;

}

void TDXTIOParser::parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode)
{
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

void TDXTIOParser::invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString& mode)
{
    if (m_iState != SUCC_STATUS)
        return;
    else if(!pSrc) {
        m_iState = ERR_NORMAL;
    }
    else {
        m_ptParser = m_ptBufFac->createBufParser(mode);
        if (m_ptParser) {
            m_ptParser->invParse(pSrc, rpDst, m_iWidth, m_iHeight);
            m_iState = SUCC_STATUS;
        }
        else
            m_iState = ERR_BUFFER_PARSER_ERROR;
    }

}

QString TDXTIOParser::exportName(const QString& origName, QString& mode) const
{
    if (m_iState != SUCC_STATUS)
        return "";

    QString testStr = origName.left(origName.length() - 4);
    QString binName = testStr.left(testStr.lastIndexOf("."));
    mode = testStr.right(testStr.length() - binName.length() - 1);
    return binName;
}
