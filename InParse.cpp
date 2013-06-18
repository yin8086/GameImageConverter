#include "InParse.h"
#include "BaseDef.h"
#include <QFile>

AbstractInParser::AbstractInParser() {
    m_iState = SUCC_STATUS;
    m_iWidth = -1;
    m_iHeight = -1;
}

void AbstractInParser::openFile(const QString& fName) {
    if (m_iState != SUCC_STATUS)
        return;

    m_ptOrigF.setFileName(fName);
    if(m_ptOrigF.open(QIODevice::ReadOnly)){
        m_iState = SUCC_STATUS;
    }
    else {
        m_iState = ERR_NOT_EXIST;
    }
}

void AbstractInParser::closeFile() {
    if(m_ptOrigF.isOpen())
        m_ptOrigF.close();
}

int AbstractInParser::state() {
    return m_iState;
}

void AbstractInParser::getWH(int &width, int &height) {
    if (m_iState != SUCC_STATUS)
        return;

    width = m_iWidth;
    height = m_iHeight;

}
