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

    // menu{
    QMenuBar *menuBar = this->menuBar();
    QMenu *menu;
    QAction *action;

    // file
    menu = new QMenu("file", menuBar);
    menuBar->addMenu(menu);

    action = new QAction("open", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onOpenClicked);
    action = new QAction("close", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onCloseClicked);
    action = new QAction("close all", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onCloseAllClicked);
    // }menu

    mLogViewer->setLineFilter(mHighlighter->logHighlighter());

    // others
    connect(mFinder, &Finder::findTriggered, mLogViewer, &LogViewer::find);
}

void MainWindow::onOpenClicked()
{
    QString log = QFileDialog::getOpenFileName();

    mLogViewer->open(log);
    mLogViewer->updateContent();
}

void MainWindow::onCloseClicked()
{
    mLogViewer->closeCurrent();
}

void MainWindow::onCloseAllClicked()
{
    mLogViewer->closeAll();
}
