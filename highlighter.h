#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSharedPointer>
#include <QSyntaxHighlighter>


class Highlighter : public QObject
{
    Q_OBJECT

public:
    explicit Highlighter(QObject *parent = nullptr);

    QSharedPointer<QSyntaxHighlighter> logHighlighter();

signals:
    void logHighlighterChanged();

public slots:
};

#endif // HIGHLIGHTER_H
