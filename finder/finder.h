#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QDockWidget>
#include <QBoxLayout>
#include <QLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextDocument>
#include <QFlags>
#include <QString>

#include "utils/logutil.h"


class Finder : public QDockWidget
{
    Q_OBJECT

public:
    Finder(QWidget *parent);
    ~Finder();

signals:
    void findTriggered(const QString &exp, const QTextDocument::FindFlags &options, bool regMode);

private slots:
    void onFindButtonClicked();
    void onFindPreButtonClicked();
    void onVisibilityChanged(bool visible);

private:
    void onFindTriggered(bool backward);

private:
    const QString TAG;

    QWidget     *mRootWidget;
    QLayout     *mMainLayout;

    QCheckBox   *mRegModeBox;
    QCheckBox   *mCaseSenseBox;
    QCheckBox   *mWholeWordBox;
    QLineEdit   *mExpressionEdit;
    QPushButton *mFindButton;
    QPushButton *mFindPreButton;

};

#endif // FINDER_H
