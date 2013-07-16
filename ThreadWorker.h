#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QStringList>
#include "InterPic.h"



class MyRun : public QRunnable {
    int m_iInType;
    int m_iOutType;
    QString m_sFName;
    InterPic m_ptInterPic;

public:
    MyRun(int iMode, int oMode, const QString &fName):
        QRunnable(),m_iInType(iMode), m_iOutType(oMode), m_sFName(fName){}
    void run();
};

class ThreadWorker {
    QStringList m_asFileList;

public:
    void addTo(QStringList& rhs) { m_asFileList.append(rhs); }
    int work();
    void getFiles();
    void addTo(const QString& rhs) { m_asFileList.append(rhs); }
};

#endif // THREADWORKER_H
