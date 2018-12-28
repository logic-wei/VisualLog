#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mLogViewer(new LogViewer(parent)),
    mFinder(new Finder(parent))
{
    setWindowTitle("VisualLog");
    mLogViewer->addViewport();
    setCentralWidget(mLogViewer);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, mFinder);

    connect(mFinder, &Finder::findTriggered, mLogViewer, &LogViewer::find);
}

MainWindow::~MainWindow()
{

}
