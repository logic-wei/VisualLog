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

    // QMenuBar:menuBar{
    QMenuBar *menuBar = this->menuBar();
    QMenu *menu;
    QAction *action;

    // QMenu:file{
    menu = new QMenu("File", menuBar);
    menuBar->addMenu(menu);

    action = new QAction("Open", menu);
    action->setShortcut(tr("CTRL+O"));
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onOpenClicked);

    action = new QAction("Close", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onCloseClicked);

    action = new QAction("Close All", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onCloseAllClicked);
    // }QMenu:file

    // QMenu:tools{
    menu = new QMenu("Tools", menuBar);
    menuBar->addMenu(menu);

    action = new QAction("Finder", menu);
    action->setCheckable(true);
    action->setShortcut(tr("CTRL+F"));
    menu->addAction(action);
    connect(action, &QAction::toggled, mFinder, &QDockWidget::setVisible);
    connect(mFinder, &QDockWidget::visibilityChanged, action, &QAction::setChecked);

    action = new QAction("Highlighter", menu);
    action->setCheckable(true);
    action->setShortcut(tr("CTRL+H"));
    menu->addAction(action);
    connect(action, &QAction::toggled, mHighlighter, &QDockWidget::setVisible);
    connect(mHighlighter, &QDockWidget::visibilityChanged, action, &QAction::setChecked);
    // }QMenu:tools

    // QMenu:help{
    menu = new QMenu("Help", menuBar);
    menuBar->addMenu(menu);

    action = new QAction("About", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onAboutClicked);
    action = new QAction("About Qt", menu);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &MainWindow::onAboutQtClicked);
    // }QMenu:help
    // }QMenuBar:menuBar

    mLogViewer->setLineFilter(mHighlighter->logHighlighter());
    mFinder->hide();
    mHighlighter->hide();

    // others
    connect(mFinder, &Finder::findTriggered,
            mLogViewer, &LogViewer::find);
    connect(mHighlighter, &Highlighter::logHighlighterTriggered,
            mLogViewer, &LogViewer::onLineFilterTriggered);
    connect(mHighlighter, &Highlighter::findTriggered,
            mLogViewer, &LogViewer::find);
    connect(mHighlighter, &Highlighter::logFilterChanged,
            mLogViewer, &LogViewer::setLineFilter);
}

void MainWindow::onOpenClicked()
{
    QString log = QFileDialog::getOpenFileName();

    if (log.isNull() || log == "") return;

    mLogViewer->open(log);
}

void MainWindow::onCloseClicked()
{
    mLogViewer->closeCurrent();
}

void MainWindow::onCloseAllClicked()
{
    mLogViewer->closeAll();
}

void MainWindow::onAboutClicked()
{
    QString msg;

    QMessageBox::about(this, tr("About VisualLog"),
        tr("<b>VisualLog</b> is an open source tool for analyzing log."
        "If you have any idea for making this better,just commit issue to me :)<br><br>"
        "github:<br>"
        "<a href = https://github.com/logic-wei/VisualLog>https://github.com/logic-wei/VisualLog</a>"));
}

void MainWindow::onAboutQtClicked()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::onFinderVisibleChanged(bool visible)
{
    mFinder->setVisible(visible);
}

void MainWindow::onHighlighterVisibleChanged(bool visible)
{
    mHighlighter->setVisible(visible);
}
