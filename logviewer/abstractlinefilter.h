#ifndef ABSTRACTLINEFILTER_H
#define ABSTRACTLINEFILTER_H

#include <QObject>
#include <QString>
#include <QTextCharFormat>


class LogViewer;

class AbstractLineFilter : public QObject
{
    Q_OBJECT

public:
    explicit AbstractLineFilter(QObject *parent = nullptr):QObject(parent){}

    friend class LogViewer;

    void update() {emit updated();}
    QTextCharFormat & format() {return mFormat;}
    bool visible() {return mVisible;}

protected:
    virtual void onNextLine(const QString &line) = 0;

    void setFormat(const QTextCharFormat &format) {mFormat = format;}
    void setVisible(bool visible) {mVisible = visible;}

signals:
    void updated();

private:
    QTextCharFormat mFormat;
    bool            mVisible;
};

#endif // ABSTRACTLINEFILTER_H
