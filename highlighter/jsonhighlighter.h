#ifndef JSONHIGHLIGHTER_H
#define JSONHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QTextCharFormat>
#include <QVector>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QString>
#include <QDebug>


class JsonHighlighter : public QSyntaxHighlighter
{
public:
    struct Rule {
    public:
        Rule() {}

        Rule(const QString &pattern, const QColor &forground, const QColor &background):
            pattern(pattern)
        {
            format.setForeground(forground);
            format.setBackground(background);
        }

        Rule(const QString &pattern, const QTextCharFormat &format):
            pattern(pattern), format(format)
        {
        }

        QRegularExpression  pattern;
        QTextCharFormat     format;
    };

    JsonHighlighter(QTextDocument *doc);

protected:
    virtual void highlightBlock(const QString &text);

private:
    void initKeyWordsRules();
    void initSpecialRules();

private:
    QVector<Rule>   mKeyWordsRules;

    // common key words rules:
    QString         mStringPattern;
    QString         mBoolPattern;
    QString         mNumberPattern;
    QString         mCommentPattern;

    QTextCharFormat mStringFormat;
    QTextCharFormat mBoolFormat;
    QTextCharFormat mNumberFormat;
    QTextCharFormat mCommentFormat;

    // special rules:
    QRegularExpression  mColorPattern;
};

#endif // JSONHIGHLIGHTER_H
