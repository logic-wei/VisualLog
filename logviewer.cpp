#include "logviewer.h"

LogViewer::LogViewer(QWidget *parent):
    mRootWidget(new QWidget(parent)),
    mRootLayout(new QGridLayout(mRootWidget)),
    mMainTabWidget(new QTabWidget(mRootWidget)),
    mViewportList(new QVector<Viewport *>()),
    mCurrentIndex(0)
{
    // set layout
    mMainTabWidget->setContentsMargins(QMargins());
    mRootLayout->addWidget(mMainTabWidget);
    mRootLayout->setContentsMargins(QMargins());
    mRootWidget->setLayout(mRootLayout);
}

LogViewer::~LogViewer()
{
    foreach (Viewport *vp, *mViewportList) {
        delete vp;
        // QWidget can be delete by parent automatically
    }
    delete mViewportList;
}

QWidget *LogViewer::rootWidget()
{
    return mRootWidget;
}

void LogViewer::addViewport(QString title)
{
    Viewport *viewport;

    viewport = new Viewport(title, new QPlainTextEdit(mRootWidget));

    mViewportList->append(viewport);
    mMainTabWidget->addTab(viewport->textEdit, viewport->title);

    mCurrentIndex = mViewportList->length() - 1;

    connect(viewport->textEdit, &QPlainTextEdit::cursorPositionChanged,
            this, &LogViewer::highlightCurrentLine);
}

void LogViewer::setHighlighter(QSyntaxHighlighter *highlighter)
{
    QPlainTextEdit *txtEdit;
    QTextDocument *txtDoc;

    txtEdit = mViewportList->at(mCurrentIndex)->textEdit;
    txtDoc = txtEdit->document();

    // todo
}

void LogViewer::find(const QString &exp, const QTextDocument::FindFlags &options, bool regMode)
{
    QPlainTextEdit *txtEdit;
    QTextDocument *txtDoc;
    QTextCursor txtCurPre;
    QTextCursor txtCurNow;

    txtEdit = mViewportList->at(mCurrentIndex)->textEdit;
    txtDoc = txtEdit->document();
    txtCurPre = txtEdit->textCursor();

    // find
    if (regMode) {
        QRegularExpression::PatternOptions regOpt(QRegularExpression::NoPatternOption);

        //case sensitive feature depends on QRegularExpression setting
        regOpt.setFlag(QRegularExpression::CaseInsensitiveOption,
                       options.testFlag(QTextDocument::FindCaseSensitively));

        txtCurNow = txtDoc->find(QRegularExpression(exp, regOpt), txtCurPre, options);
    } else {
        txtCurNow = txtDoc->find(exp, txtCurPre, options);
    }

    // move cursor
    txtEdit->setTextCursor(txtCurNow);
}

void LogViewer::highlightCurrentLine()
{
    QPlainTextEdit *txtEdit;
    QList<QTextEdit::ExtraSelection> exSelections;
    QTextEdit::ExtraSelection exSelection;
    QTextCharFormat txtChrFmt;

    txtEdit = mViewportList->at(mCurrentIndex)->textEdit;

    txtChrFmt.setBackground(QColor(230, 230, 255));
    exSelection.cursor = txtEdit->textCursor();
    exSelection.format = txtChrFmt;
    exSelection.cursor.clearSelection();
    exSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
    exSelections << exSelection;

    txtEdit->setExtraSelections(exSelections);
}

