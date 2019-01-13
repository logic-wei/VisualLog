#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QString>
#include <utils/logutil.h>

const QString TAG = "main";


void checkHomePath()
{
    LogUtil::i(TAG, "init working directory");
    QDir wd = QDir::home();

    if (!wd.exists(".VisualLog")) {
        if (wd.mkdir(".VisualLog"))
            wd.cd(".VisualLog");
    } else {
        wd.cd(".VisualLog");
    }

    if (QDir::setCurrent(wd.path())) {
        LogUtil::i(TAG, "cd to dir:"+wd.path());
    }
}

int main(int argc, char *argv[])
{
    checkHomePath();
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
