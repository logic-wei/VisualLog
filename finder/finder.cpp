#include "finder.h"

Finder::Finder(QWidget *parent):
    QDockWidget("finder", parent),
    TAG("Finder"),
    mRootWidget(new QWidget(this)),
    mMainLayout(new QHBoxLayout()),
    mRegModeBox(new QCheckBox("regular mode", mRootWidget)),
    mCaseSenseBox(new QCheckBox("case sensitively", mRootWidget)),
    mWholeWordBox(new QCheckBox("whole word", mRootWidget)),
    mExpressionEdit(new QLineEdit(mRootWidget)),
    mFindButton(new QPushButton("find", mRootWidget)),
    mFindPreButton(new QPushButton("find pre", mRootWidget))
{
    // ui
    mMainLayout->addWidget(mRegModeBox);
    mMainLayout->addWidget(mCaseSenseBox);
    mMainLayout->addWidget(mWholeWordBox);
    mMainLayout->addWidget(mExpressionEdit);
    mMainLayout->addWidget(mFindButton);
    mMainLayout->addWidget(mFindPreButton);

    mRootWidget->setLayout(mMainLayout);

    setWidget(mRootWidget);

    // setting
    connect(mFindButton, &QPushButton::clicked, this, &Finder::onFindButtonClicked);
    connect(mFindPreButton, &QPushButton::clicked, this, &Finder::onFindPreButtonClicked);
    connect(mExpressionEdit, &QLineEdit::editingFinished, this, &Finder::onFindButtonClicked);
}

Finder::~Finder()
{
}

void Finder::onFindButtonClicked()
{
    onFindTriggered(false);
}

void Finder::onFindPreButtonClicked()
{
    onFindTriggered(true);
}

void Finder::onFindTriggered(bool backward)
{
    QTextDocument::FindFlags options;

    options.setFlag(QTextDocument::FindFlag::FindBackward, backward);
    options.setFlag(QTextDocument::FindFlag::FindWholeWords, mWholeWordBox->isChecked());
    options.setFlag(QTextDocument::FindFlag::FindCaseSensitively, mCaseSenseBox->isChecked());

    emit findTriggered(mExpressionEdit->text(), options, mRegModeBox->isChecked());
}




