#include <QApplication>
#include "ThreadWorker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThreadWorker tw;
    tw.getFiles();
    return tw.work();
}
