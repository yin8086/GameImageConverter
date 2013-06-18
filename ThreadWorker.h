#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QStringList>
#include "InterPic.h"
#include "InParserFac.h"


class MyRun : public QRunnable {
    int m_iInType;
    int m_iOutType;
    QString m_sFName;
    InterPic *m_ptInterPic;

public:
    MyRun(int iMode, int oMode, const QString &fName):
        QRunnable(),m_iInType(iMode), m_iOutType(oMode), m_sFName(fName){}
    void createPic();
    void run();
};

class ThreadWorker {
    QStringList m_asFileList;

public:
    void addTo(QStringList& rhs) { m_asFileList.append(rhs); }
    int work();
    void getFiles();
};

#endif // THREADWORKER_H
