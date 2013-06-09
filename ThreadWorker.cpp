#include <QtCore>
#include <QRunnable>
#include "ThreadWorker.h"
#include "InParse.h"
#include "InParserFac.h"
int ThreadWorker::work() {
    QList<QRunnable *> runList;

    foreach(const QString &fn, m_asFileList) {
        MyRun* tmpR=new MyRun;
        tmpR->setAutoDelete(true);
        QThreadPool::globalInstance()->start(tmpR);
        runList.append(tmpR);
    }
}

void MyRun::createPic() {
    AbstractInParser* inP = m_inFac.createInParser(m_iInType);
    m_ptInterPic = inP->createInterPic(m_sFName);
    //m_ptInterPic->m_ptFilter = m_filterFac.create....;

    // if iType == ?
    // fileIn =
    // filter =
    // if oType == ?
    // fileOut=
}


void MyRun::run() {
    // parseIn
    // filter
    // parseOut
}
