#ifndef LOGUTIL_H
#define LOGUTIL_H

#include <QDebug>
#include <QString>


class LogUtil
{
public:
    static void i(const QString &tag, const QString &msg);
    static void d(const QString &tag, const QString &msg);
    static void e(const QString &tag, const QString &msg);

private:
    LogUtil();

private:
    static const bool sDebug = true;
};

#endif // LOGUTIL_H
