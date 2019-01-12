#include "jsontextedit.h"

JsonTextEdit::JsonTextEdit(QWidget *parent):
    QPlainTextEdit(parent)
{
    new JsonHighlighter(document());
    mSpacePattern = QRegularExpression(R"(^\s*)");

    connect(this, &QPlainTextEdit::textChanged,
            this, &JsonTextEdit::updateJsonObject);
}

void JsonTextEdit::keyPressEvent(QKeyEvent *event)
{
    QPlainTextEdit::keyPressEvent(event);

    switch (event->key()) {
        case Qt::Key::Key_Return:
            autoInsertSpace();
        break;
    }
}

void JsonTextEdit::autoInsertSpace()
{
    int currentLineNumber = textCursor().blockNumber();

    if (currentLineNumber > 0) {
        auto lastLineBlock = document()->findBlockByLineNumber(currentLineNumber - 1);
        auto match = mSpacePattern.match(lastLineBlock.text());
        if (match.hasMatch()) {
            insertPlainText(match.captured(0));
        }
    }
}

QJsonObject & JsonTextEdit::jsonObject()
{
    return mJsonObject;
}

void JsonTextEdit::updateJsonObject()
{
    QJsonDocument jsonDoc;

    jsonDoc = QJsonDocument::fromJson(jsonString().toUtf8());

    if (!jsonDoc.isNull()) {
        mJsonObject = jsonDoc.object();
        emit updated(mJsonObject);
    }
}

QString JsonTextEdit::jsonString()
{
    return document()->toRawText().simplified();
}
