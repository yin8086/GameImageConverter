#include <QtCore>
#include <QRunnable>
#include <QFileDialog>
#include <QSettings>
#include "ThreadWorker.h"
#include "InParse.h"
#include "InParserFac.h"
int ThreadWorker::work() {
    QList<QRunnable *> runList;

    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    int iType = settings.value("InType", 0).toInt();
    int oType = settings.value("OutType", 1).toInt();

    foreach(const QString &fn, m_asFileList) {
        MyRun* tmpR=new MyRun(iType, oType, fn);
        tmpR->setAutoDelete(true);
        QThreadPool::globalInstance()->start(tmpR);
        runList.append(tmpR);
    }

    settings.setValue("InType", iType);
    settings.setValue("OutType", oType);
}

void ThreadWorker::getFiles() {
    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    m_asFileList = QFileDialog::getOpenFileNames(
                0,
                QObject::tr("Select one or more files to open"),
                settings.value("dir", QDir::current().absolutePath()).toString(),
                QObject::tr("All files (*.*)"));
    settings.setValue("dir",m_asFileList[0].left(m_asFileList[0].lastIndexOf('/')));
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
    InParserFactory inFac;
    AbstractInParser* inP = inFac.createInParser(m_iInType);
    m_ptInterPic->setInParser(inP);
    m_ptInterPic->construct(m_sFName);

    delete inP;
    // parseIn
    // filter
    // parseOut
}
