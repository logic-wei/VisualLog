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

#include "logviewer.h"
#include "finder.h"
#include "highlighter.h"


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

private:
    LogViewer   *mLogViewer;
    Finder      *mFinder;
    Highlighter *mHighlighter;
};

#endif // MAINWINDOW_H
