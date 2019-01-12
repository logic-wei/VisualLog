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
#include <QFontMetrics>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QString>
#include <QRegularExpression>
#include <QColor>

#include "../logviewer/abstractlinefilter.h"
#include "logfilter.h"
#include "jsonhighlighter.h"
#include "jsontextedit.h"


class Highlighter : public QDockWidget
{
    Q_OBJECT

public:
    explicit Highlighter(QWidget *parent = nullptr);

    QSharedPointer<AbstractLineFilter> logHighlighter();
    void setTabWidth(int nspace);

signals:
    void logHighlighterChanged();

private slots:
    void onJsonObjectUpdated(const QJsonObject &jsonObject);

private:
    void setupUi();
    void updateFilterRule(LogFilter::Rule *filterRule,
                        const QString &propName, const QJsonValue &propValue);
    bool isDoubleJsonArray(const QJsonArray &jsonArray);

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
    JsonTextEdit    *mJsonEdit;
    QToolButton     *mHighlightButton;
    QPushButton     *mFindPreButton;
    QPushButton     *mFindNxtButton;

    //others
    QSharedPointer<LogFilter>   mFilter;
    JsonHighlighter             *mJsonHighlighter;
};

#endif // HIGHLIGHTER_H
