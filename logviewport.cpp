#include "logviewport.h"

LogViewport::LogViewport(const QString &path, QWidget *parent):
    QPlainTextEdit(parent),
    mPath(path),
    mByteBuffer(nullptr)
{
    loadFile(mPath);
}

void LogViewport::setTitle(const QString &title)
{
    mTitle = title;
    emit titleChanged(mTitle);
}

QString & LogViewport::title()
{
    return mTitle;
}

void LogViewport::loadFile(const QString &path)
{
    mPath = path;
    setTitle(mPath);

    QFile file(mPath);
    file.open(QIODevice::OpenModeFlag::ReadOnly);
    mByteBuffer = file.readAll();
    file.close();
    mBuffer = QSharedPointer<QBuffer>(new QBuffer(&mByteBuffer));
}

QSharedPointer<QBuffer> & LogViewport::buffer()
{
    return mBuffer;
}

void LogViewport::showBuffer()
{
    clear();
    insertPlainText(QString(mByteBuffer));
}
