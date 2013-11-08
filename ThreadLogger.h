#ifndef THREADLOGGER_H
#define THREADLOGGER_H

class ThreadLogger {
    QMutex m_cMutex;
    QFile m_logFile;
public:
    ThreadLogger();
    ~ThreadLogger();
    void threadPrintf(const QString& message);
    void threadPrintfId(const QString &prefix, int status);
};

extern ThreadLogger g_cThreadLog;

#endif // THREADLOGGER_H
