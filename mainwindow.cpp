#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // main window init
    ui->setupUi(this);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(400);
    this->setMinimumWidth(400);

    this->setMaximumWidth(2560);
    this->setMaximumHeight(1440);

    ui->gridLayout->setGeometry(QRect(0, 0, this->width(), this->height()));

    ui->gridLayout->setAlignment(Qt::AlignCenter);
    //

    // chess initialization
    const qreal boardWidth = std::min(this->width(), this->height());
    this->chess = new ChessGameGraphics(new ChessGame(), boardWidth);

    this->chess->defaultPlacementOfFigures();

    this->chessWidget = new ChessWidget(this->chess, this);
    ui->gridLayout->addWidget(this->chessWidget);
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

// resize event
void MainWindow::resizeEvent(QResizeEvent*)
{
    // resize window and grid layout
    this->resize(QWidget::width(), QWidget::height());
    ui->gridLayoutWidget->resize(QWidget::width(), QWidget::height());
    //
}
//


