#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSharedPointer>
#include <QSyntaxHighlighter>
#include <QDockWidget>
#include <QPushButton>
#include <QToolButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QVBoxLayout>

#include "abstractlinefilter.h"
#include "logfilter.h"


class Highlighter : public QDockWidget
{
    Q_OBJECT

public:
    explicit Highlighter(QWidget *parent = nullptr);

    QSharedPointer<AbstractLineFilter> logHighlighter();


signals:
    void logHighlighterChanged();

private:
    void setupUi();

private:
    // ui
    QWidget *mRootWidget;
    QLayout *mMainLayout;
    QLayout *mToolLayout;
    QLayout *mControlLayout;

    QComboBox       *mRuleBox;
    QToolButton     *mNewButton;
    QToolButton     *mDelButton;
    QToolButton     *mSaveButton;
    QPlainTextEdit  *mTextEdit;
    QToolButton     *mHighlightButton;
    QPushButton     *mFindPreButton;
    QPushButton     *mFindNxtButton;

    //others
    QSharedPointer<LogFilter> mFilter;
};

#endif // HIGHLIGHTER_H
