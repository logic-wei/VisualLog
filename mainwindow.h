#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QObject>

#include "logviewer.h"
#include "finder.h"


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
    LogViewer *mLogViewer;
    Finder *mFinder;
};

#endif // MAINWINDOW_H
