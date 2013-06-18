#include <QtCore>
#include <QRunnable>
#include <QFileDialog>
#include <QSettings>
#include "BaseDef.h"
#include "ThreadWorker.h"
#include "InParse.h"
#include "InParserFac.h"
#include "FilterFac.h"
#include "OutParserFac.h"
#include "ThreadLogger.h"

int ThreadWorker::work() {

    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    int iType = settings.value("InType", 0).toInt();
    int oType = settings.value("OutType", 1).toInt();

    foreach(const QString &fn, m_asFileList) {
        MyRun* tmpR=new MyRun(iType, oType, fn);
        tmpR->setAutoDelete(true);
        QThreadPool::globalInstance()->start(tmpR);
    }

    settings.setValue("InType", iType);
    settings.setValue("OutType", oType);
    return 0;
}

void ThreadWorker::getFiles() {
    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    m_asFileList = QFileDialog::getOpenFileNames(
                0,
                QObject::tr("Select one or more files to open"),
                settings.value("dir", QDir::current().absolutePath()).toString(),
                QObject::tr("All files (*.*)"));
    if(m_asFileList.size() > 0)
    {
        g_cThreadLog.threadPrintf(QString("Directory: %1\n").
                                  arg(m_asFileList[0].left(m_asFileList[0].lastIndexOf('/')))
                                  );
        settings.setValue("dir",m_asFileList[0].left(m_asFileList[0].lastIndexOf('/')));
    }
}




void MyRun::run() {
    InParserFactory inFac;
    FilterFactory fFac;
    OutParserFactory oPFac;

    AbstractInParser* inP = inFac.createInParser(m_iInType);
    AbstractImageFilter *inF = fFac.createFilter(m_iInType, m_iOutType);
    AbstractOutParser *inO = oPFac.createOutParser(m_iOutType);

    QString logMessage = m_sFName.mid(m_sFName.lastIndexOf('/') + 1);
    logMessage += ":    ";
    int runStatus = SUCC_STATUS;

    if (inP && inF && inO) {
        m_ptInterPic.setInParser(inP);
        m_ptInterPic.construct(m_sFName);

        m_ptInterPic.setFilter(inF);
        m_ptInterPic.filter();

        m_ptInterPic.setOutParser(inO);
        m_ptInterPic.output(m_sFName);

        runStatus = m_ptInterPic.state();

    }
    else
        runStatus = ERR_NORMAL;

    g_cThreadLog.threadPrintfId(logMessage, runStatus);

    delete inP;
    delete inF;
    delete inO;
}
