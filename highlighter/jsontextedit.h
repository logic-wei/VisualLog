#ifndef JSONTEXTEDIT_H
#define JSONTEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTextBlock>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

#include "jsonhighlighter.h"


class JsonTextEdit : public QPlainTextEdit
{
Q_OBJECT

public:
    JsonTextEdit(QWidget *parent);

    QString jsonString();
    QJsonObject & jsonObject();

signals:
    void updated(const QJsonObject &json);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void autoInsertSpace();

private slots:
    void updateJsonObject();

private:
    QRegularExpression  mSpacePattern;
    QJsonObject         mJsonObject;
};

#endif // JSONTEXTEDIT_H
