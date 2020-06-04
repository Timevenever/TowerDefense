#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<iostream>
#include <QMainWindow>
#include<QTime>
#include <QList>
#include <vector>
#include "towerposition.h"
#include "tower.h"
#include "start.h"
namespace Ui {
class MainWindow;
}
class waypoint;
class enemy;
class bullet;
class audioplayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void getHpDamage(int damage=1);
    void removedEnemy(enemy *Enemy);
    void removedBullet(bullet *Bullet);
    void addBullet(bullet *Bullet);
    void awardGold(int Gold);
    audioplayer* audioPlayer() const;
    QList<enemy *> enemyList() const;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    int m_waves;
    int m_playerHp;
    int m_playerGold;
    bool m_gameEnd;
    bool m_gameWin;
    audioplayer * m_audioPlayer;
    QList<QVariant>  m_wavesInfo;
    QList<towerposition> m_towerPositionsList;
    QList<tower *> m_towersList;
    QList<tower *> m_displayList;
    QList<waypoint *> m_wayPointsList;
    QList<enemy *> m_enemyList;
    QList<bullet *> m_bulletList;

 private slots:
    void updateMap();
    void gameStart();
    void on_MainWindow_customContextMenuRequested(const QPoint &pos);
    void updateTower();
    void removeTower();

private:
    void loadTowerPosition();
    void addWayPoints();
    void loadWave();
    void loadWave2();
    void loadWave3();
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawGold(QPainter *painter);
    void gameOver();
    void loadTower();
    bool Is_ingame();

};

#endif // MAINWINDOW_H
