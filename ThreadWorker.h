#ifndef THREADWORKER_H
#define THREADWORKER_H
#include <QtCore>
#include <QStringList>
#include "InterPic.h"
#define END_MARK "\\ \\ \\"

class ImgThread: public QThread {
    int m_iInType;
    int m_iOutType;
    QString m_curImgName;
    QString m_logMessage;
    int m_runStatus;
    QWaitCondition m_ready;

    AbstractIOParser* m_InParser;
    AbstractImageFilter *m_Filter;
    AbstractIOParser *m_OutParser;

    static QQueue<QString> m_imgList;
    static QWaitCondition m_added;
    static QMutex m_Mutex;
public:
    ImgThread(int iMode, int oMode);
    void waitForReady();
    static void addImg(const QString &fName);
    ~ImgThread();
protected:
    void run();
};



class ThreadWorker {
    QStringList m_asFileList;
    QList<ImgThread *> m_threadPool;

public:
    void addTo(QStringList& rhs) { m_asFileList.append(rhs); }
    int work();
    void getFiles();
    void addTo(const QString& rhs) { m_asFileList.append(rhs); }
};

#endif // THREADWORKER_H
