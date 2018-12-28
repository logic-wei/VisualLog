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


class Highlighter : public QDockWidget
{
    Q_OBJECT

public:
    explicit Highlighter(QWidget *parent = nullptr);

    QSharedPointer<QSyntaxHighlighter> logHighlighter();

signals:
    void logHighlighterChanged();

private:
    void setupUi();

private:
    QWidget *mRootWidget;
    QLayout *mMainLayout;
    QLayout *mToolLayout;
    QLayout *mControlLayout;

    QComboBox       *mRegulationBox;
    QToolButton     *mNewButton;
    QToolButton     *mDelButton;
    QToolButton     *mSaveButton;
    QPlainTextEdit  *mTextEdit;
    QToolButton     *mHighlightButton;
    QPushButton     *mFindPreButton;
    QPushButton     *mFindNxtButton;
};

#endif // HIGHLIGHTER_H
