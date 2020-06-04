#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include"tower.h"
class waypoint;
class QPainter;
class MainWindow;
class tower;

class enemy : public QObject
{
    Q_OBJECT

public:
    enemy(waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/Monster1.png")*/);
    ~enemy();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(tower *attack);
    void gotLostSight(tower *attack);
    QPoint pos() const;
    QPoint operator+(const QPoint &offsetPoint) const;
    void setPos(QPoint point);

public slots:
    void doActivate();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;
    waypoint *		m_destinationWayPoint;
    MainWindow *	m_game;
    QList<tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;


};

#endif // ENEMY_H
