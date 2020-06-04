#include "bullet.h"
#include "enemy.h"
#include "tower.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize bullet::my_fixedSize(25,25);

bullet::bullet(QPoint startposition,QPoint targetPoint,int damage,enemy *target,MainWindow *game, const QPixmap &Bullet /*= QPixmap(":/image/bullet1.png")*/)
    :m_startposi(startposition)
    ,m_targetposi(targetPoint)
    ,m_Bullet(Bullet)
    ,m_currentposi(currentPosition())
    ,m_target(target)
    ,in_game(game)
    ,m_damage(damage)
{}

void bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentposi, m_Bullet);
}

void bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentposi");
    animation->setDuration(duration);
    animation->setStartValue(m_startposi);
    animation->setEndValue(m_targetposi);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void bullet::hitTarget()
{

    // 因此先判断下敌人是否还活着
    if (in_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(m_damage);
    in_game->removedBullet(this);
}

void bullet::setCurrentPosition(QPoint pos)
{
    m_currentposi = pos;
}

QPoint bullet::currentPosition() const
{
    return m_currentposi;
}














