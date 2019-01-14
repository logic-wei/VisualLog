#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSharedPointer>
#include <QSyntaxHighlighter>
#include <QDockWidget>
#include <QPushButton>
#include <QToolButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLayout>
#include <QVBoxLayout>
#include <QFontMetrics>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QString>
#include <QRegularExpression>
#include <QColor>
#include <QFileSystemWatcher>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QShortcut>
#include <QKeySequence>

#include "../logviewer/abstractlinefilter.h"
#include "logfilter.h"
#include "jsonhighlighter.h"
#include "jsontextedit.h"
#include "utils/config.h"
#include "utils/logutil.h"


class Highlighter : public QDockWidget
{
    Q_OBJECT

public:
    enum EditorState {
        BROWSING = 0,
        EDITING
    };

    explicit Highlighter(QWidget *parent = nullptr);

    QSharedPointer<AbstractLineFilter> logHighlighter();
    void setTabWidth(int nspace);

signals:
    void logHighlighterChanged();

private slots:
    void onJsonObjectUpdated(const QJsonObject &jsonObject);
    void onRulesDirChanged();
    void onNewButtonClicked();
    void onDelButtonClicked();
    void onSaveButtonClicked();
    void onRuleSelectedChanged(const QString &rule);
    void onRulesBoxIndexChanged(int index);
    void onHighlightButtonClicked();

private:
    void setupUi();
    void initDir();
    void initFSWatcher();
    void updateFilterRule(LogFilter::Rule *filterRule,
                        const QString &propName, const QJsonValue &propValue);
    bool isDoubleJsonArray(const QJsonArray &jsonArray);
    void loadRuleFile(const QString &fileName);
    void saveAsRuleFile(const QString &fileName, const QString &content);

private:
    const QString TAG;
    // ui
    QWidget *mRootWidget;
    QLayout *mMainLayout;
    QLayout *mToolLayout;
    QLayout *mControlLayout;

    QComboBox       *mRuleBox;
    QToolButton     *mNewButton;
    QToolButton     *mDelButton;
    QToolButton     *mSaveButton;
    JsonTextEdit    *mJsonEdit;
    QToolButton     *mHighlightButton;
    QPushButton     *mFindPreButton;
    QPushButton     *mFindNxtButton;

    //others
    QSharedPointer<LogFilter>   mFilter;
    JsonHighlighter             *mJsonHighlighter;
    QFileSystemWatcher          *mFileSystemWatcher;
    QDir                        mRulesDir;
    EditorState                 mEditorState;
};

#endif // HIGHLIGHTER_H
