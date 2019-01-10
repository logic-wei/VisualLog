#ifndef JSONTEXTEDIT_H
#define JSONTEXTEDIT_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTextBlock>

#include "jsonhighlighter.h"


class JsonTextEdit : public QPlainTextEdit
{
Q_OBJECT

public:
    JsonTextEdit(QWidget *parent);

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    void autoInsertSpace();

private:
    QRegularExpression  mSpacePattern;
};

#endif // JSONTEXTEDIT_H
