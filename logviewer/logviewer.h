#ifndef LOGVIEWER_H
#define LOGVIEWER_H

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

#include "abstractlinefilter.h"
#include "logviewport.h"
#include "utils/logutil.h"


class LogViewer : public QWidget
{
    Q_OBJECT

public:
    LogViewer(QWidget *parent);
    virtual ~LogViewer();

    void setLineFilter(const QSharedPointer<AbstractLineFilter> &filter);
    void updateContent();
    void displayRawLog(int index);

public slots:
    void open(const QString &path);
    void close(int index);
    void closeCurrent();
    void closeAll();
    void find(const QString &exp, const QTextDocument::FindFlags &options, bool regMode);
    void onLineFilterTriggered();

private slots:
    void highlightCurrentLine();
    void onLineFilterUpdate();

private:
    void setupUi();

private:
    const QString           TAG;
    QLayout                 *mRootLayout;
    QTabWidget              *mMainTabWidget;
    QList<LogViewport *>    mViewportList;

    QSharedPointer<AbstractLineFilter>  mFilter;
};

#endif // LOGVIEWER_H
