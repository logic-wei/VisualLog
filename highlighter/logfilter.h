#ifndef LOGFILTER_H
#define LOGFILTER_H

#include <QObject>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QColor>
#include <QVector>
#include <QTextCharFormat>
#include <QBrush>
#include <QDebug>

#include "../logviewer/abstractlinefilter.h"


class LogFilter : public AbstractLineFilter
{
    Q_OBJECT

public:
    struct Rule {
    public:
        Rule() {}
        Rule(QString pattern, bool visible, QColor foreground, QColor background):
            pattern(pattern),
            visible(visible) {
            format.setForeground(QBrush(foreground));
            format.setBackground(QBrush(background));
        }

        Rule(bool visible, QColor foreground, QColor background) {
            Rule("", visible, foreground, background);
        }

        QRegularExpression  pattern;
        bool                visible;
        QTextCharFormat     format;
    };

    LogFilter();

    void addRule(const Rule &rule);
    void clearRule();
    void setDefaultRule(const Rule &rule);
    QString comboVisiblePattern();

protected:
    virtual void onNextLine(const QString &line);

private:
    QVector<Rule>   mRules;
    Rule            mDefaultRule;
};

#endif // LOGFILTER_H
