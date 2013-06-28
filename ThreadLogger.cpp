#include "ThreadLogger.h"
#include "BaseDef.h"
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
}

void ThreadLogger::threadPrintf(const QString &message) {
    m_cMutex.lock();
    printf(message.toLocal8Bit().data());
    m_cMutex.unlock();
}

ThreadLogger g_cThreadLog;
