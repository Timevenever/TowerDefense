#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>


const QSize tower::ms_fixedSize(50, 50);

tower::tower(QPoint pos, MainWindow *game, const QPixmap &sprite/* = QPixmap(":/image/tower.png"*/)
    : m_attacking(false)
    , m_attackRange(200)
    , m_damage(5)
    , m_fireRate(1000)
    , m_level(1)
    , m_chooseEnemy(NULL)
    , m_game(game)
    , m_pos(pos)
    , m_sprite(sprite)
{
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

tower::~tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = NULL;
}

void tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 向量标准化
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
       /* m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;*/

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
        QList<enemy *> enemyList = m_game->enemyList();
        foreach (enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void tower::draw(QPainter *painter) const
{
    painter->save();
  /*  painter->setPen(Qt::white);
    // 绘制攻击范围
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);*/

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    // 绘制炮塔并选择炮塔
    painter->translate(m_pos+offsetPoint);
    //painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void tower::chooseEnemyForAttack(enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void tower::shootWeapon()
{
    bullet *Bullet = new bullet(m_pos, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game);
    Bullet->move();
    m_game->addBullet(Bullet);
}

void tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
    //m_rotationSprite = 0.0;
}

void tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = NULL;

    m_fireRateTimer->stop();
   // m_rotationSprite = 0.0;
}

void tower::stopAttack()
{

    m_fireRateTimer->stop();

}

void tower::setLevel(int l)
{
    this->m_level=l;
}
int tower::getLevel()
{
    return m_level;
}








