#include "InParse.h"
#include <QFile>

int AbstractInParser::openFile(const QString& fName) {
    m_ptOrigF.setFileName(fName);
    if(m_ptOrigF.open(QIODevice::ReadOnly)){
        m_iState = 0;
        return 0;
    }
    else {
        m_iState = ERR_NOT_EXIST;
        return ERR_NOT_EXIST;
    }
}

int AbstractInParser::closeFile() {
    if(m_ptOrigF.isOpen())
        m_ptOrigF.close();
}

int AbstractInParser::state() {
    return m_iState;
}

void AbstractInParser::getWH(int &width, int &height) {
    width = m_iWidth;
    height = m_iHeight;
}
