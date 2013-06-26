#include "IOParser.h"
#include "BaseDef.h"
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
    if(m_ptOrigF.isOpen())
        m_ptOrigF.close();
}

int AbstractIOParser::state() {
    return m_iState;
}

void AbstractIOParser::getWH(int &width, int &height) {
    if (m_iState != SUCC_STATUS)
        return;

    width = m_iWidth;
    height = m_iHeight;

}
