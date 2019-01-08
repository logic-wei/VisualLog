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

#include "abstractlinefilter.h"


class LogFilter : public AbstractLineFilter
{
    Q_OBJECT

public:
    struct Rule {
    public:
        Rule() {}
        Rule(QString pattern, bool visible, QColor foreground, QColor background):
            pattern(pattern),
            visible(visible)
        {
            format.setForeground(QBrush(foreground));
            format.setBackground(QBrush(background));
        }

        QRegularExpression  pattern;
        bool                visible;
        QTextCharFormat     format;
    };

    LogFilter();

    void addRule(const Rule &rule);
    void clearRule();
    void setDefaultRule(const Rule &rule);

protected:
    virtual void onNextLine(const QString &line);

private:
    QVector<Rule>   mRules;
    Rule            mDefaultRule;
};

#endif // LOGFILTER_H
