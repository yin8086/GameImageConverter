#include <QApplication>
#include "ThreadWorker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadWorker tw;
    if (argc > 1)
        tw.addTo(QString(argv[1]));
    else
        tw.getFiles();
    return tw.work();
}
