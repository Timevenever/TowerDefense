#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class enemy;
class MainWindow;

class bullet: QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentposi READ currentPosition() WRITE setCurrentPosition)

public:
    bullet(QPoint startposition,QPoint targetPoint,int damage,enemy *target,MainWindow *game, const QPixmap &Bullet = QPixmap(":/image/bullet1.png"));
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPosition(QPoint position);
    QPoint currentPosition() const;

private slots:
    void hitTarget();

private:
    const QPoint m_startposi;
    const QPoint m_targetposi;
    const QPixmap m_Bullet;
    QPoint m_currentposi;
    enemy * m_target;
    MainWindow * in_game;
    int m_damage;

    static const QSize my_fixedSize;
};

#endif // BULLET_H
