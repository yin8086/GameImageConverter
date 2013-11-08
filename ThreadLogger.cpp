#include <QtCore>
#include <QFile>
#include <QTextStream>
#include "ThreadLogger.h"
#include "BaseDef.h"

ThreadLogger::ThreadLogger() {
    m_logFile.setFileName("GIConverter.log");
    m_logFile.open(QIODevice::WriteOnly);
}
ThreadLogger::~ThreadLogger() {
    m_logFile.close();
}

void ThreadLogger::threadPrintfId(const QString &prefix, int status) {
    if (status == SUCC_STATUS) {
        threadPrintf(prefix + "Succeed\n");
    }
    else if(status == ERR_NORMAL) {
        threadPrintf(prefix + "Normal Error\n");
    }
    else if(status == ERR_UNKNOWN_FORM) {
        threadPrintf(prefix + "Unknown Format\n");
    }
    else if(status == ERR_NOT_IMAGE) {
        threadPrintf(prefix + "Not an image\n");
    }
    else if(status == ERR_INVALID_FILE) {
        threadPrintf(prefix + "Invalid File\n");
    }
    else if(status == ERR_NOT_EXIST) {
        threadPrintf(prefix + "File not Exist\n");
    }
    else if(status == ERR_BUFFER_PARSER_ERROR) {
        threadPrintf(prefix + "Buffer Parser Error\n");
    }
    else if(status == ERR_IMAGE_SMALL) {
        threadPrintf(prefix + "Image Become Small\n");
    }
}

void ThreadLogger::threadPrintf(const QString &message) {
    QMutexLocker locker(&m_cMutex);
    printf(message.toLocal8Bit().data());
    QTextStream writer(&m_logFile);
    writer << message.toLocal8Bit().data();
}

ThreadLogger g_cThreadLog;
