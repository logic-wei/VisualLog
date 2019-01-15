#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QObject>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>

#include "logviewer/logviewer.h"
#include "finder/finder.h"
#include "highlighter/highlighter.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();

private slots:
    void onOpenClicked();
    void onCloseClicked();
    void onCloseAllClicked();
    void onAboutClicked();
    void onAboutQtClicked();
    void onFinderVisibleChanged(bool visible);
    void onHighlighterVisibleChanged(bool visible);

private:
    LogViewer   *mLogViewer;
    Finder      *mFinder;
    Highlighter *mHighlighter;
};

#endif // MAINWINDOW_H
