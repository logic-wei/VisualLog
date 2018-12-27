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


class LogViewer : public QObject
{
    Q_OBJECT

public:
    struct Viewport {
    public:
        Viewport(QString title, QPlainTextEdit *textEdit) {
            this->title = title;
            this->textEdit = textEdit;
        }
        QString title;
        QPlainTextEdit *textEdit;
    };

    LogViewer(QWidget *parent);
    virtual ~LogViewer();

    QWidget *rootWidget();
    void addViewport(QString title = "default.txt");
    void setHighlighter(QSyntaxHighlighter *highlighter);

public slots:
    void find(const QString &exp, const QTextDocument::FindFlags &options, bool regMode);

private slots:
    void highlightCurrentLine();

private:
    QWidget *mRootWidget;
    QLayout *mRootLayout;
    QTabWidget *mMainTabWidget;
    QVector<Viewport *> *mViewportList;
    int mCurrentIndex;
};

#endif // LOGVIEWER_H
