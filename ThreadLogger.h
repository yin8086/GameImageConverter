#ifndef THREADLOGGER_H
#define THREADLOGGER_H
#include <QtCore>
class ThreadLogger {
    QMutex m_cMutex;
public:
    void threadPrintf(const QString& message);
    void threadPrintfId(const QString &prefix, int status);
};

extern ThreadLogger g_cThreadLog;

#endif // THREADLOGGER_H
