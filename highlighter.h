#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSharedPointer>
#include <QSyntaxHighlighter>
#include <QDockWidget>


class Highlighter : public QDockWidget
{
    Q_OBJECT

public:
    explicit Highlighter(QWidget *parent = nullptr);

    QSharedPointer<QSyntaxHighlighter> logHighlighter();

signals:
    void logHighlighterChanged();

public slots:
};

#endif // HIGHLIGHTER_H
