#include <QApplication>
#include <QDir>
#include <QString>

#include "mainwindow.h"
#include "utils/logutil.h"
#include "utils/config.h"

const QString TAG = "main";


void checkHomePath()
{
    LogUtil::i(TAG, "init working directory");
    QDir wd = QDir::home();

    if (!wd.exists(VLOG_CFG_HOME_NAME)) {
        if (wd.mkdir(VLOG_CFG_HOME_NAME))
            wd.cd(VLOG_CFG_HOME_NAME);
    } else {
        wd.cd(VLOG_CFG_HOME_NAME);
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
    w.showMaximized();

    return a.exec();
}
