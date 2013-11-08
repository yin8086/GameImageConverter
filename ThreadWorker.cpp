#include <QtCore>
#include <QRunnable>
#include <QFileDialog>
#include <QSettings>
#include "BaseDef.h"
#include "ThreadWorker.h"
#include "IOParserFac.h"
#include "FilterFac.h"
#include "ThreadLogger.h"

int ThreadWorker::work() {

    QSettings settings("GIConverter.ini", QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    int iType = settings.value("InType", 0).toInt();
    int oType = settings.value("OutType", 1).toInt();
    int threadNum = QThread::idealThreadCount();

    for(int i=0; i < threadNum; ++i) {
        m_threadPool.append(new ImgThread(iType, oType));
        m_threadPool.back()->waitForReady();
    }

    foreach(const QString &fn, m_asFileList) {
        ImgThread::addImg(fn);
    }
    ImgThread::addImg(END_MARK);
    for(int i=0; i < threadNum; ++i) {
        delete m_threadPool[i];
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


QWaitCondition ImgThread::m_added;
QQueue<QString> ImgThread::m_imgList;
QMutex ImgThread::m_Mutex;


ImgThread::ImgThread(int iMode, int oMode):
            QThread(),m_iInType(iMode), m_iOutType(oMode) {
    IOParserFactory inFac;
    FilterFactory fFac;
    IOParserFactory oPFac;

    m_InParser = inFac.createIOParser(m_iInType);
    m_Filter = fFac.createFilter(m_iInType, m_iOutType);
    m_OutParser = oPFac.createIOParser(m_iOutType);

    start();
}

ImgThread::~ImgThread() {
    wait();

    delete m_InParser;
    delete m_Filter;
    delete m_OutParser;
}

void ImgThread::addImg(const QString &fName) {
    QMutexLocker locker(&m_Mutex);
    m_imgList.enqueue(fName);
    m_added.wakeOne();
}

void ImgThread::waitForReady() {
    QMutexLocker locker(&m_Mutex);
    m_ready.wait(&m_Mutex);
}


void ImgThread::run() {
    m_ready.wakeOne();
    forever {
        {
            QMutexLocker locker(&m_Mutex);

            if(m_imgList.isEmpty())
                m_added.wait(&m_Mutex);
            m_curImgName = m_imgList.dequeue();
            if(m_curImgName == "\\ \\ \\") {
                m_imgList.enqueue("\\ \\ \\");
                m_added.wakeOne();
                break;
            }
        }
        //处理一个图片

        m_logMessage = m_curImgName.mid(m_curImgName.lastIndexOf('/') + 1);
        m_logMessage += ":    ";
        m_runStatus = SUCC_STATUS;

        if (m_InParser && m_OutParser) {
            InterPic interPic;
            interPic.setInParser(m_InParser);
            interPic.construct(m_curImgName);

            if(m_Filter) {
                interPic.setFilter(m_Filter);
                interPic.filter();
            }

            interPic.setOutParser(m_OutParser);
            interPic.output(m_curImgName);

            m_runStatus = interPic.state();
            m_InParser->reset();
            m_OutParser->reset();

        }
        else
            m_runStatus = ERR_NORMAL;

        g_cThreadLog.threadPrintfId(m_logMessage, m_runStatus);
    }

}


