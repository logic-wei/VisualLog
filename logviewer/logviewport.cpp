#include "logviewport.h"

LogViewport::LogViewport(const QString &path, QWidget *parent):
    QPlainTextEdit(parent),
    mPath(path),
    mByteBuffer(nullptr)
{
    loadFile(mPath);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &LogViewport::highlightCurrentLine);
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
    setPlainText(QString(mByteBuffer));
}

void LogViewport::highlightCurrentLine()
{
    QPlainTextEdit *txtEdit = this;
    QList<QTextEdit::ExtraSelection> exSelections;
    QTextEdit::ExtraSelection exSelection;
    QTextCharFormat txtChrFmt;

    txtChrFmt.setBackground(QColor(230, 230, 255));
    exSelection.cursor = txtEdit->textCursor();
    exSelection.format = txtChrFmt;
    exSelection.cursor.clearSelection();
    exSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
    exSelections << exSelection;

    txtEdit->setExtraSelections(exSelections);
}
