#include "logfilter.h"

LogFilter::LogFilter():
    mRules(0)
{
    setDefaultRule(Rule(".*", true, QColor(0 ,0 ,0), QColor(255, 255, 255)));
}

void LogFilter::addRule(const Rule &rule)
{
    mRules.append(rule);
}

void LogFilter::clearRule()
{
    mRules.clear();
}

void LogFilter::onNextLine(const QString &line)
{
    // match the rules
    foreach(const Rule &rule, mRules) {
        QRegularExpressionMatch match = rule.pattern.match(line);
        if(match.hasMatch()) {
            setVisible(rule.visible);
            setFormat(rule.format);
            return;
        }
    }

    // default
    setVisible(mDefaultRule.visible);
    setFormat(mDefaultRule.format);
}

void LogFilter::setDefaultRule(const Rule &rule)
{
    mDefaultRule = rule;
}
