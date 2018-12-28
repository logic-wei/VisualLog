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


class LogViewer : public QWidget
{
    Q_OBJECT

public:
    struct Viewport {
    public:
        Viewport(QString title, QPlainTextEdit *textEdit):
            title(title),
            textEdit(textEdit),
            highlighter(nullptr){}

        QString title;
        QPlainTextEdit *textEdit;
        QSharedPointer<QSyntaxHighlighter> highlighter;
    };

    LogViewer(QWidget *parent);
    virtual ~LogViewer();

    void addViewport(QString title = "default.txt");
    void setHighlighter(QSharedPointer<QSyntaxHighlighter> highlighter);

public slots:
    void find(const QString &exp, const QTextDocument::FindFlags &options, bool regMode);

private slots:
    void highlightCurrentLine();

private:
    QLayout *mRootLayout;
    QTabWidget *mMainTabWidget;
    QVector<Viewport *> *mViewportList;
    int mCurrentIndex;
};

#endif // LOGVIEWER_H
