#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <vector>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include "pig.h"
#include "shot.h"
#include "wall.h"
#include "boom.h"
#include "yellowbird.h"
#include "rockbird.h"
#include "backbird.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void next_bird();
    void dead();
    void Wait();
    void on_reStart_clicked();

    void on_Quit_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;

    void GameSet();


    Land *land;
    shot *Shot;

    QList<Bird *> Bird_List;
    QList<Pig *> Pig_List;
    QList<wall *> Wall_List;
    QTimer timer;
    QPoint start;
    QPoint end;

    int count;
    int chance;
    int enemy;
    int wait;
    int score;
};

#endif // MAINWINDOW_H
