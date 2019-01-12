#include "logviewer.h"

LogViewer::LogViewer(QWidget *parent):
    QWidget(parent),
    mRootLayout(new QHBoxLayout(this)),
    mMainTabWidget(new QTabWidget(this)),
    mViewportList()
{
    setupUi();
}

LogViewer::~LogViewer()
{

}

void LogViewer::setupUi()
{
    mRootLayout->addWidget(mMainTabWidget);

    // MainTabWidget
    mMainTabWidget->setTabsClosable(true);

    connect(mMainTabWidget, &QTabWidget::tabCloseRequested,
            this, &LogViewer::close);
}

void LogViewer::find(const QString &exp, const QTextDocument::FindFlags &options, bool regMode)
{
    QPlainTextEdit *txtEdit;
    QTextDocument *txtDoc;
    QTextCursor txtCurPre;
    QTextCursor txtCurNow;

    if (mViewportList.length() <= 0) return;

    txtEdit = mViewportList.at(mMainTabWidget->currentIndex());
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

void LogViewer::open(const QString &path)
{
    LogViewport *viewport = new LogViewport(path, mMainTabWidget);
    mMainTabWidget->addTab(viewport, viewport->title());
    mViewportList.append(viewport);
}

void LogViewer::close(int index)
{
    mMainTabWidget->removeTab(index);
    mViewportList.at(index)->close();
    mViewportList.removeAt(index);
}

void LogViewer::closeCurrent()
{
    if(mViewportList.length() <= 0) return;

    close(mMainTabWidget->currentIndex());
}

void LogViewer::closeAll()
{
    for(int i = 0; i < mViewportList.length(); i += 1) {
        closeCurrent();
    }
}

void LogViewer::highlightCurrentLine()
{
    QPlainTextEdit *txtEdit;
    QList<QTextEdit::ExtraSelection> exSelections;
    QTextEdit::ExtraSelection exSelection;
    QTextCharFormat txtChrFmt;

    if (mViewportList.length() <= 0) return;

    txtEdit = mViewportList.at(mMainTabWidget->currentIndex());

    txtChrFmt.setBackground(QColor(230, 230, 255));
    exSelection.cursor = txtEdit->textCursor();
    exSelection.format = txtChrFmt;
    exSelection.cursor.clearSelection();
    exSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
    exSelections << exSelection;

    txtEdit->setExtraSelections(exSelections);
}

void LogViewer::onLineFilterUpdate()
{
    updateContent();
}

void LogViewer::updateContent()
{
    if (mViewportList.length() <= 0) return;

    if (mFilter.isNull()) {
        displayRawLog();
        return;
    }

    QPlainTextEdit *textEdit;
    QByteArray byteLine;
    QString line;
    QBuffer *buffer;

    textEdit = mViewportList.at(mMainTabWidget->currentIndex());
    buffer = mViewportList.at(mMainTabWidget->currentIndex())->buffer().get();

    textEdit->clear();

    buffer->open(QIODevice::OpenModeFlag::ReadOnly);{
        byteLine = buffer->readLine();
        while (!byteLine.isNull()) {
            line = QString(byteLine);

            // handle every line
            mFilter->onNextLine(line);
            if (mFilter->visible()) {
                textEdit->setCurrentCharFormat(mFilter->format());
                textEdit->insertPlainText(line);
            }

            byteLine = buffer->readLine();
        }
    }buffer->close();
}

void LogViewer::setLineFilter(const QSharedPointer<AbstractLineFilter> &filter)
{
    mFilter = filter;

    connect(mFilter.get(), &AbstractLineFilter::updated,
            this, &LogViewer::onLineFilterUpdate);
    updateContent();
}

void LogViewer::displayRawLog()
{
    if (mViewportList.length() <= 0) return;

    mViewportList.at(mMainTabWidget->currentIndex())->showBuffer();
}
