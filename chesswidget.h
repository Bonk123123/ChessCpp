#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGridLayout>
#include <QMouseEvent>

#include "chessgamegraphics.h"

class ChessWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ChessWidget(ChessGameGraphics *chess, QWidget *parent = 0);

    ~ChessWidget();


signals:

private slots:
    // on resize function
    void onResize();

    // function to draw a board
    void drawBoard();
    // function to draw all figures
    void drawFigures();

    // function to delete all items from group on scene
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);

private:

    QColor _bg_color;

    QGraphicsScene      *_scene;
    QGraphicsItemGroup  *_board;
    QGraphicsItemGroup  *_figures;
    QGraphicsItemGroup  *_possible_moves;
    QTimer              *_timer;

    ChessGameGraphics *_chess;

    bool _isClicked = false;
    Point<int> _oldPos;

private:
    // click event handler
    void mousePressEvent(QMouseEvent *event);

    // resize event handler
    void resizeEvent(QResizeEvent *event);
};

#endif // CHESSWIDGET_H
