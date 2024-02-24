#include "customboardwidget.h"

CustomBoardWidget::CustomBoardWidget(ChessGameGraphics *chess, QWidget *parent)
    : QWidget{parent}
{
    this->chess = chess;
}


void CustomBoardWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
