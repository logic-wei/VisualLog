#include "jsonhighlighter.h"

JsonHighlighter::JsonHighlighter(QTextDocument *doc):
    QSyntaxHighlighter(doc)
{
    initKeyWordsRules();
    initSpecialRules();
}

void JsonHighlighter::initKeyWordsRules()
{
    // init all the pattern
    mStringPattern = R"("[A-Za-z0-9_]*"|(?<=:)\s*".*")";
    mBoolPattern = R"(\b(true|false)\b)";
    mNumberPattern = R"(\b\d+\b)";
    mCommentPattern = R"(//.*)";

    // init all the format
    mStringFormat.setForeground(QColor(0, 200, 0)); // green
    mStringFormat.setBackground(QColor(255, 255, 255));

    mBoolFormat.setForeground(QColor(0, 0, 220)); // blue
    mBoolFormat.setBackground(QColor(255, 255, 255));

    mNumberFormat.setForeground(QColor(0, 0, 200)); // blue
    mNumberFormat.setBackground(QColor(255, 255, 255));

    mCommentFormat.setForeground(QColor(150, 150, 150)); // gray
    mCommentFormat.setBackground(QColor(255, 255, 255));

    // gather all the rules
    mKeyWordsRules.append(Rule(mStringPattern, mStringFormat));
    mKeyWordsRules.append(Rule(mBoolPattern, mBoolFormat));
    mKeyWordsRules.append(Rule(mNumberPattern, mNumberFormat));
    mKeyWordsRules.append(Rule(mCommentPattern, mCommentFormat));
}

void JsonHighlighter::initSpecialRules()
{
    mColorPattern = QRegularExpression(QString(R"(\[\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\])"));
}

void JsonHighlighter::highlightBlock(const QString &text)
{
    // highlight key words
    foreach(const Rule &rule, mKeyWordsRules) {
        auto matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            auto match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // highlight color value
    auto matchIterator = mColorPattern.globalMatch(text);
    while (matchIterator.hasNext()) {
        auto match = matchIterator.next();
        int r = match.captured(1).toInt() % 256;
        int g = match.captured(2).toInt() % 256;
        int b = match.captured(3).toInt() % 256;
        QTextCharFormat fmt;
        fmt.setForeground(QColor(255-r, 255-g, 255-b));
        fmt.setBackground(QColor(r, g, b));
        setFormat(match.capturedStart(), match.capturedLength(), fmt);
    }
}
