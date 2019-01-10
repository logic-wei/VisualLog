#include "highlighter.h"

Highlighter::Highlighter(QWidget *parent):
    QDockWidget("highlighter", parent),
    mRootWidget(new QWidget(parent)),
    mMainLayout(new QVBoxLayout()),
    mToolLayout(new QHBoxLayout()),
    mControlLayout(new QHBoxLayout()),
    mRuleBox(new QComboBox(mRootWidget)),
    mNewButton(new QToolButton(mRootWidget)),
    mDelButton(new QToolButton(mRootWidget)),
    mSaveButton(new QToolButton(mRootWidget)),
    mJsonEdit(new JsonTextEdit(mRootWidget)),
    mHighlightButton(new QToolButton(mRootWidget)),
    mFindPreButton(new QPushButton(mRootWidget)),
    mFindNxtButton(new QPushButton(mRootWidget))
{
    setupUi();
    mFilter = QSharedPointer<LogFilter>(new LogFilter());
}

void Highlighter::setupUi()
{
    // widget setting
    mRuleBox->setEditable(true);
    mNewButton->setText("+");
    mDelButton->setText("-");
    mSaveButton->setText("<<");
    mHighlightButton->setText("H");
    mFindPreButton->setText("find pre");
    mFindNxtButton->setText("find next");

    // layout setting
    mToolLayout->addWidget(mRuleBox);
    mToolLayout->addWidget(mNewButton);
    mToolLayout->addWidget(mDelButton);
    mToolLayout->addWidget(mSaveButton);

    mControlLayout->addWidget(mHighlightButton);
    mControlLayout->addWidget(mFindPreButton);
    mControlLayout->addWidget(mFindNxtButton);

    mMainLayout->addItem(mToolLayout);
    mMainLayout->addWidget(mJsonEdit);
    mMainLayout->addItem(mControlLayout);

    // parent setting
    mRootWidget->setLayout(mMainLayout);
    setWidget(mRootWidget);

    setTabWidth(4);
}

void Highlighter::setTabWidth(int nspace)
{
    QFontMetrics metrics(mJsonEdit->font());
    mJsonEdit->setTabStopDistance(nspace * metrics.width(' '));
}

QSharedPointer<AbstractLineFilter> Highlighter::logHighlighter()
{
    return mFilter;
}
