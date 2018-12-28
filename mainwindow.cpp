#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mLogViewer(new LogViewer(this)),
    mFinder(new Finder(this)),
    mHighlighter(new Highlighter(this))
{
    setupUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi()
{
    // MainWindow settings
    setWindowTitle("VisualLog");
    setCentralWidget(mLogViewer);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, mFinder);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, mHighlighter);

    // children settings
    mLogViewer->addViewport();

    // others
    connect(mFinder, &Finder::findTriggered, mLogViewer, &LogViewer::find);
}
