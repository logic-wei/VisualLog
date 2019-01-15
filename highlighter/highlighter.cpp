#include "highlighter.h"

Highlighter::Highlighter(QWidget *parent):
    QDockWidget("highlighter", parent),
    TAG("Highlighter"),
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
    mFindNxtButton(new QPushButton(mRootWidget)),
    mFileSystemWatcher(new QFileSystemWatcher(this)),
    mEditorState(BROWSING)
{
    setupUi();
    mFilter = QSharedPointer<LogFilter>(new LogFilter());
    emit logFilterChanged(mFilter);
    connect(mJsonEdit, &JsonTextEdit::updated, this, &Highlighter::onJsonObjectUpdated);
    initDir();
    initFSWatcher();
    onRulesDirChanged();
}

void Highlighter::setupUi()
{
    // widget setting
    mNewButton->setText("+");
    mDelButton->setText("-");
    mSaveButton->setText("<<");
    mHighlightButton->setText("H");
    mFindPreButton->setText("find pre");
    mFindNxtButton->setText("find next");
    mRuleBox->setDuplicatesEnabled(false);

    // layout setting
    mToolLayout->addWidget(mRuleBox);
    mToolLayout->addWidget(mNewButton);
    mToolLayout->addWidget(mDelButton);
    mToolLayout->addWidget(mSaveButton);
    mToolLayout->addWidget(mHighlightButton);

    mControlLayout->addWidget(mFindPreButton);
    mControlLayout->addWidget(mFindNxtButton);

    mMainLayout->addItem(mToolLayout);
    mMainLayout->addWidget(mJsonEdit);
    mMainLayout->addItem(mControlLayout);

    // parent setting
    mRootWidget->setLayout(mMainLayout);
    setWidget(mRootWidget);

    connect(mNewButton, &QToolButton::clicked, this, &Highlighter::onNewButtonClicked);
    connect(mDelButton, &QToolButton::clicked, this, &Highlighter::onDelButtonClicked);
    connect(mSaveButton, &QToolButton::clicked, this, &Highlighter::onSaveButtonClicked);
    connect(mRuleBox, &QComboBox::currentTextChanged, this, &Highlighter::onRuleSelectedChanged);
    connect(mRuleBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Highlighter::onRulesBoxIndexChanged);
    connect(mHighlightButton, &QToolButton::clicked, this, &Highlighter::onHighlightButtonClicked);
    connect(mJsonEdit, &JsonTextEdit::edittingCompleted, this, &Highlighter::onJsonEdittingCompleted);
    connect(mFindNxtButton, &QPushButton::clicked, this, &Highlighter::onFindNexClicked);
    connect(mFindPreButton, &QPushButton::clicked, this, &Highlighter::onFindPreClicked);
}

void Highlighter::initDir()
{
    QDir dir = QDir::home();

    if (dir.cd(VLOG_CFG_HOME_NAME)) {
        if (!dir.exists(VLOG_CFG_HIGHLIGHTER_RULE_HOME)) {
            if (!dir.mkdir(VLOG_CFG_HIGHLIGHTER_RULE_HOME))
                LogUtil::e(TAG, "failed to mkdir for rules");
        }
        if (!dir.cd(VLOG_CFG_HIGHLIGHTER_RULE_HOME))
            LogUtil::e(TAG, "failed to cd to rules");
    } else {
       LogUtil::e(TAG, "failed to cd to home");
    }

    mRulesDir = dir;
}

void Highlighter::initFSWatcher()
{
    LogUtil::i(TAG, "initFSWatcher: dir:"+mRulesDir.path());

    mFileSystemWatcher->addPath(mRulesDir.path());
    connect(mFileSystemWatcher, &QFileSystemWatcher::directoryChanged,
            this, &Highlighter::onRulesDirChanged);
}

QSharedPointer<AbstractLineFilter> Highlighter::logHighlighter()
{
    return mFilter;
}

void Highlighter::onJsonObjectUpdated(const QJsonObject &jsonObject)
{
    mFilter->clearRule();

    if (jsonObject.isEmpty()) {
        LogUtil::i(TAG, "empty jsonObject");
        mFilter->update();
        return;
    }

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

void Highlighter::onRulesDirChanged()
{
    LogUtil::i(TAG, QString("onRulesDirChanged.mEditorState=%1").arg(mEditorState));

    switch (mEditorState) {
    case EditorState::EDITING:
        break;
    case EditorState::BROWSING:
        LogUtil::i(TAG, QString("clear rule item"));
        mRuleBox->clear();
        foreach (QDir dir, mRulesDir.entryList(QDir::Filter::Files, QDir::SortFlag::Name)) {
            LogUtil::i(TAG, QString("add rule item:%1").arg(dir.dirName()));
            mRuleBox->addItem(dir.dirName());
        }
        break;
    }
}

void Highlighter::onNewButtonClicked()
{
    LogUtil::i(TAG, QString("onNewButtonClicked.mEditorState=%1").arg(mEditorState));

    switch (mEditorState) {
    case EditorState::EDITING:
        break;
    case EditorState::BROWSING:
        mEditorState = EditorState::EDITING;
        mRuleBox->setEditable(true);
        mRuleBox->update();
        mRuleBox->setEditText("NewRule");
        mJsonEdit->clear();
        break;
    }
}

void Highlighter::onDelButtonClicked()
{
    LogUtil::i(TAG, QString("onDelButtonClicked.mEditorState=%1").arg(mEditorState));

    switch (mEditorState) {
    case EditorState::EDITING:
        mEditorState = EditorState::BROWSING;
        mJsonEdit->clear();
        mRuleBox->removeItem(mRuleBox->currentIndex());
        mRuleBox->setEditable(false);
        mRuleBox->update();
        break;
    case EditorState::BROWSING:
        if (!mRuleBox->currentText().isNull() && !mRulesDir.remove(mRuleBox->currentText()))
            LogUtil::e(TAG, QString("failed to remove rule file:%1").arg(mRuleBox->currentText()));
        break;
    }
}

void Highlighter::onSaveButtonClicked()
{
    LogUtil::i(TAG, QString("onSaveButtonClicked.mEditorState=%1").arg(mEditorState));

    switch (mEditorState) {
    case EditorState::BROWSING:
        saveAsRuleFile(mRuleBox->currentText(), mJsonEdit->document()->toRawText());
        break;
    case EditorState::EDITING:
        if (!mRulesDir.exists(mRuleBox->currentText())) {
            mEditorState = EditorState::BROWSING;
            saveAsRuleFile(mRuleBox->currentText(), mJsonEdit->document()->toRawText());
            mRuleBox->setEditable(false);
            mRuleBox->update();
        } else {
            LogUtil::i(TAG, "reduplicative file name");
            QMessageBox::warning(this, "error", "reduplicative file name");
        }
        break;
    }
}

void Highlighter::onRuleSelectedChanged(const QString &rule)
{
    LogUtil::i(TAG, QString("onRuleSelectedChanged.mEditorState=%1").arg(mEditorState));

    if (rule.isNull() || rule == "") return;

    switch (mEditorState) {
    case EditorState::BROWSING:
        loadRuleFile(mRuleBox->currentText());
        break;
    case EditorState::EDITING:
        break;
    }
}

void Highlighter::loadRuleFile(const QString &fileName)
{
    LogUtil::i(TAG, QString("loadRuleFile.fileName=%1").arg(fileName));

    if (fileName.isNull() || fileName == "") return;

    QFile ruleFile(mRulesDir.absoluteFilePath(fileName));

    ruleFile.open(QIODevice::OpenModeFlag::ReadOnly); {
        mJsonEdit->clear();
        mJsonEdit->insertPlainText(ruleFile.readAll());
    } ruleFile.close();
}

void Highlighter::onRulesBoxIndexChanged(int index)
{
    (void)index;

    switch (mEditorState) {
    case EditorState::BROWSING:
        break;
    case EditorState::EDITING:
        mEditorState = EditorState::BROWSING;
        mJsonEdit->clear();
        mRuleBox->setEditable(false);
        break;
    }
}

void Highlighter::saveAsRuleFile(const QString &fileName, const QString &content)
{
    QFile ruleFile(mRulesDir.absoluteFilePath(fileName));
    ruleFile.open(QIODevice::OpenModeFlag::WriteOnly);
    ruleFile.write(content.toUtf8());
    ruleFile.close();
}

void Highlighter::onHighlightButtonClicked()
{
    LogUtil::i(TAG, "onHighlightButtonClicked");
    emit logHighlighterTriggered();
}

void Highlighter::onJsonEdittingCompleted()
{
    LogUtil::i(TAG, "onJsonEdittingCompleted");
    emit logHighlighterTriggered();
}

void Highlighter::onFindNexClicked()
{
    QString comboPattern = mFilter->comboVisiblePattern();

    if (comboPattern.isNull()) return;

    emit findTriggered(comboPattern,
                       QTextDocument::FindFlag::FindCaseSensitively,
                       true);
}

void Highlighter::onFindPreClicked()
{
    QString comboPattern = mFilter->comboVisiblePattern();

    if (comboPattern.isNull()) return;

    emit findTriggered(comboPattern,
                       QTextDocument::FindFlag::FindCaseSensitively
                       |QTextDocument::FindFlag::FindBackward,
                       true);
}
