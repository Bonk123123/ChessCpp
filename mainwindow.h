#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chessgame.h"
#include "figures.h"

#include <chesswidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void resizeEvent(QResizeEvent*);

private slots:

private:
    // main widget
    Ui::MainWindow *ui;

    // chess (all logic here)
    ChessGameGraphics *chess;

    // chess widget
    ChessWidget *chessWidget;
};
#endif // MAINWINDOW_H
