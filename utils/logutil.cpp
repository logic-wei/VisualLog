#include "logutil.h"

LogUtil::LogUtil()
{
}

void LogUtil::i(const QString &tag, const QString &msg)
{
    if (sDebug && !tag.isNull()) {
        qInfo()<<qPrintable(QString("[%1]: %2").arg(tag).arg(msg));
    }
}

void LogUtil::d(const QString &tag, const QString &msg)
{
    if (sDebug && !tag.isNull()) {
        qDebug()<<qPrintable(QString("[%1]: %2").arg(tag).arg(msg));
    }
}

void LogUtil::e(const QString &tag, const QString &msg)
{
    if (sDebug && !tag.isNull()) {
        qWarning()<<qPrintable(QString("[%1]: %2").arg(tag).arg(msg));
    }
}
