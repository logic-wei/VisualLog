#include "jsontextedit.h"

JsonTextEdit::JsonTextEdit(QWidget *parent):
    QPlainTextEdit(parent)
{
    new JsonHighlighter(document());
    mSpacePattern = QRegularExpression(R"(^\s*)");
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
