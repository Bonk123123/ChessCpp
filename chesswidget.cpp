#include "chesswidget.h"


ChessWidget::ChessWidget(ChessGameGraphics *chess, QWidget *parent) : QGraphicsView(parent)
{
    // game initialization
    this->_chess = chess;

    // start
    this->_chess->start();
    //



    // widget initialization
    this->_bg_color = QColor(30, 30, 30);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    this->setMaximumWidth(2560);
    this->setMaximumHeight(1440);

    QPalette pal;
    pal.setColor(this->backgroundRole(), this->_bg_color);
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    //



    // scene and groups initialization
    _scene = new QGraphicsScene();
    this->setScene(_scene);


    this->_board = new QGraphicsItemGroup();
    this->_figures = new QGraphicsItemGroup();
    this->_possible_moves = new QGraphicsItemGroup();

    this->_board->setZValue(1);
    this->_figures->setZValue(2);
    this->_possible_moves->setZValue(3);

    _scene->addItem(this->_board);
    _scene->addItem(this->_figures);
    _scene->addItem(this->_possible_moves);
    //


    // onResize event initialization
    _timer = new QTimer();
    _timer->setSingleShot(true);

    connect(_timer, SIGNAL(timeout()), this, SLOT(onResize()));
    _timer->start(50);
    //
}

ChessWidget::~ChessWidget() {}

// mouse event
void ChessWidget::mousePressEvent(QMouseEvent *event)
{
    // get position
    this->deleteItemsFromGroup(this->_possible_moves);

    Point<int> figurePos(this->_chess->getFigureIndexFromPos(Point<int>(event->pos().x(), event->pos().y())));
    //


    // move figure
    if (this->_isClicked && (int)this->_chess->getPossibleMoves(this->_oldPos)[figurePos.x][figurePos.y] > 0)
    {
        this->_isClicked = false;

        this->_chess->move(this->_oldPos, figurePos);

        this->deleteItemsFromGroup(this->_figures);
        this->drawFigures();

        return;
    }
    //

    // get possible moves
    Point<float> boardPos(this->_chess->getBoardBeginPos(QWidget::width(), QWidget::height()));

    for (std::pair<Point<float>, MOVE_TYPE> point : this->_chess->getPossibleMovesPos(figurePos))
    {

        QString imgpath = QString::fromStdString("Figures/Move.png");
        if (point.second == MOVE_TYPE::KILL_MOVE) imgpath = QString::fromStdString("Figures/Kill.png");
        if (point.second == MOVE_TYPE::CASTLING_MOVE) imgpath = QString::fromStdString("Figures/Castling.png");
        QGraphicsPixmapItem *img = _scene->addPixmap( QPixmap(imgpath) );
        this->_possible_moves->addToGroup(img);
        img->setPos(boardPos.x + point.first.x, boardPos.y + point.first.y);
        img->setScale(this->_chess->getSpritesScale());
    }
    //


    this->_isClicked = true;
    this->_oldPos = figurePos;


}
//

// function onResize
void ChessWidget::onResize()
{
    // delete all from groups
    this->deleteItemsFromGroup(this->_board);
    this->deleteItemsFromGroup(this->_figures);
    this->deleteItemsFromGroup(this->_possible_moves);
    //


    // get width and heigth
    int width = QWidget::width();
    int height = QWidget::height();
    //

    // get board width
    const qreal boardWidth = std::min(width, height);
    //


    // restart chess board and scene
    this->_chess->setBoardWidth(boardWidth);

    this->_chess->restartFiguresPos();

    _scene->setSceneRect(0, 0, width, height);

    this->drawBoard();
    this->drawFigures();
    //
}
//


// event handler onResize Function
void ChessWidget::resizeEvent(QResizeEvent *event)
{
    _timer->start(50);
//    this->onResize();
    QGraphicsView::resizeEvent(event);
}
//

// function to draw a board
void ChessWidget::drawBoard()
{
    Point<float> boardPos(this->_chess->getBoardBeginPos(QWidget::width(), QWidget::height()));

    float cellWidth = this->_chess->getBoardCellWidth();

    for (size_t i = 0; i < BOARD_SIZE; i++) {
        for (size_t j = 0; j < BOARD_SIZE; j++) {
            QString imgpath;
            if ((i + j) % 2 == 0)
            {
                imgpath = QString::fromStdString("Figures/Cell.png");
            }
            else
            {
                imgpath = QString::fromStdString("Figures/Dark_Cell.png");
            }

            QGraphicsPixmapItem *img = _scene->addPixmap( QPixmap(imgpath) );
            this->_board->addToGroup(img);

            img->setPos(boardPos.x + i * cellWidth, boardPos.y + j * cellWidth);
            img->setScale(this->_chess->getSpritesScale());

        }
    }
}
//


// function to draw all figures
void ChessWidget::drawFigures()
{
    std::vector<std::pair<Point<float>*, std::string>> figures(this->_chess->getFiguresPos());

    Point<float> boardPos(this->_chess->getBoardBeginPos(QWidget::width(), QWidget::height()));

    for (std::pair<Point<float>*, std::string> figure : figures)
    {
        QString imgpath = QString::fromStdString(figure.second);
        QGraphicsPixmapItem *img = _scene->addPixmap( QPixmap(imgpath) );
        this->_figures->addToGroup(img);

        img->setPos(boardPos.x + figure.first->x, boardPos.y + figure.first->y);
        img->setScale(this->_chess->getSpritesScale());
    }
}
//


// function to delete all items from group on scene
void ChessWidget::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    for (QGraphicsItem *item : group->childItems())
    {
        delete item;
    }
}
//
