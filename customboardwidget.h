#ifndef CUSTOMBOARDWIDGET_H
#define CUSTOMBOARDWIDGET_H

#include <QWidget>
#include "chessgamegraphics.h"
#include "figures.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>


class CustomBoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomBoardWidget(ChessGameGraphics *chess, QWidget *parent = nullptr);

signals:


private:
    // resize event handler
    void resizeEvent(QResizeEvent *event);

private:
    ChessGameGraphics *chess;

    QGridLayout *gridLayout;

};

#endif // CUSTOMBOARDWIDGET_H
