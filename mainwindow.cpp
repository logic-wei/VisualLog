#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mLogViewer(new LogViewer(parent)),
    mFinder(new Finder(parent))
{
    setWindowTitle("VisualLog");
    mLogViewer->addViewport();
    setCentralWidget(mLogViewer->rootWidget());
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, mFinder->dockWidget());

    connect(mFinder, &Finder::findTriggered, mLogViewer, &LogViewer::find);
}

MainWindow::~MainWindow()
{

}
