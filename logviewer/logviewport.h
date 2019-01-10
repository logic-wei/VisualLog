#ifndef LOGVIEWPORT_H
#define LOGVIEWPORT_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTabWidget>
#include <QList>
#include <QString>
#include <QPlainTextEdit>
#include <QMargins>
#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextBlock>
#include <QTextFormat>
#include <QSharedPointer>
#include <QByteArray>
#include <QBuffer>
#include <QFile>
#include <QDebug>


class LogViewport : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit LogViewport(const QString &path, QWidget *parent = nullptr);

    void setTitle(const QString &title);
    QString & title();
    QSharedPointer<QBuffer> & buffer();

    void loadFile(const QString &path);
    void showBuffer();


signals:
    void titleChanged(const QString & title);

private:
    // ui
    QString mTitle;

    // others
    QString                 mPath;
    QByteArray              mByteBuffer;
    QSharedPointer<QBuffer> mBuffer;
};

#endif // LOGVIEWPORT_H
