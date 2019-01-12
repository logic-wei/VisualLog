#include "highlighter.h"

Highlighter::Highlighter(QWidget *parent):
    QDockWidget("highlighter", parent),
    mRootWidget(new QWidget(parent)),
    mMainLayout(new QVBoxLayout()),
    mToolLayout(new QHBoxLayout()),
    mControlLayout(new QHBoxLayout()),
    mRuleBox(new QComboBox(mRootWidget)),
    mNewButton(new QToolButton(mRootWidget)),
    mDelButton(new QToolButton(mRootWidget)),
    mSaveButton(new QToolButton(mRootWidget)),
    mJsonEdit(new JsonTextEdit(mRootWidget)),
    mHighlightButton(new QToolButton(mRootWidget)),
    mFindPreButton(new QPushButton(mRootWidget)),
    mFindNxtButton(new QPushButton(mRootWidget))
{
    setupUi();
    mFilter = QSharedPointer<LogFilter>(new LogFilter());
    connect(mJsonEdit, &JsonTextEdit::updated, this, &Highlighter::onJsonObjectUpdated);
}

void Highlighter::setupUi()
{
    // widget setting
    mRuleBox->setEditable(true);
    mNewButton->setText("+");
    mDelButton->setText("-");
    mSaveButton->setText("<<");
    mHighlightButton->setText("H");
    mFindPreButton->setText("find pre");
    mFindNxtButton->setText("find next");

    // layout setting
    mToolLayout->addWidget(mRuleBox);
    mToolLayout->addWidget(mNewButton);
    mToolLayout->addWidget(mDelButton);
    mToolLayout->addWidget(mSaveButton);

    mControlLayout->addWidget(mHighlightButton);
    mControlLayout->addWidget(mFindPreButton);
    mControlLayout->addWidget(mFindNxtButton);

    mMainLayout->addItem(mToolLayout);
    mMainLayout->addWidget(mJsonEdit);
    mMainLayout->addItem(mControlLayout);

    // parent setting
    mRootWidget->setLayout(mMainLayout);
    setWidget(mRootWidget);

    setTabWidth(4);
}

void Highlighter::setTabWidth(int nspace)
{
    QFontMetrics metrics(mJsonEdit->font());
    mJsonEdit->setTabStopDistance(nspace * metrics.width(' '));
}

QSharedPointer<AbstractLineFilter> Highlighter::logHighlighter()
{
    return mFilter;
}

void Highlighter::onJsonObjectUpdated(const QJsonObject &jsonObject)
{
    mFilter->clearRule();
    qDebug()<<"jsonUpdate";
    // traverse every rules
    foreach (const QString &ruleName, jsonObject.keys()) {
        QJsonValue value = jsonObject.value(ruleName);
        qDebug()<<"key="<<ruleName;
        if (value.isObject()) {
            QJsonObject propsObject = value.toObject();
            LogFilter::Rule filterRule(true, QColor(0, 0, 0), QColor(255, 255, 255));

            // traverse every properties
            foreach (const QString &propName, propsObject.keys()) {
                QJsonValue propValue = propsObject.value(propName);
                if (propValue.isNull()) continue;

                updateFilterRule(&filterRule, propName, propValue);
            }

            // set properties to filter
            if (ruleName != "default") {
                mFilter->addRule(filterRule);
            } else {
                mFilter->setDefaultRule(filterRule);
            }
        }
    }

    mFilter->update();
}

void Highlighter::updateFilterRule(LogFilter::Rule *filterRule,
                                 const QString &propName, const QJsonValue &propValue)
{
    if (propName == "pattern") {
        if (propValue.isString()) {
            filterRule->pattern = QRegularExpression(propValue.toString());
        }
    } else if (propName == "visible") {
        if (propValue.isBool()) {
            filterRule->visible = propValue.toBool();
        }
    } else if (propName == "foreground") {
        if (propValue.isArray()) {
            QJsonArray propArrayValue = propValue.toArray();
            if (propArrayValue.size() == 3 && isDoubleJsonArray(propArrayValue)) {

                int r = propArrayValue.at(0).toInt() % 256;
                int g = propArrayValue.at(1).toInt() % 256;
                int b = propArrayValue.at(2).toInt() % 256;

                filterRule->format.setForeground(QColor(r, g, b));
            }
        }
    } else if (propName == "background") {
        if (propValue.isArray()) {
            QJsonArray propArrayValue = propValue.toArray();
            if (propArrayValue.size() == 3 && isDoubleJsonArray(propArrayValue)) {

                int r = propArrayValue.at(0).toInt() % 256;
                int g = propArrayValue.at(1).toInt() % 256;
                int b = propArrayValue.at(2).toInt() % 256;

                filterRule->format.setBackground(QColor(r, g, b));
            }
        }
    }
}

bool Highlighter::isDoubleJsonArray(const QJsonArray &jsonArray)
{
    foreach (const QJsonValue jsonValue, jsonArray) {
        if (jsonValue.type() != QJsonValue::Type::Double)
            return false;
    }
    return true;
}
