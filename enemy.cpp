#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "mainwindow.h"
#include "audioplayer.h"
#include "utility.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Hp_Bar_Width = 50;

const QSize enemy::ms_fixedSize(50, 50);

enemy::enemy(waypoint *startWayPoint, MainWindow *game, const QPixmap &sprite /*= QPixmap(":/image/Monster1.png")*/)
   :QObject(nullptr)
   , m_active(false)
   , m_maxHp(40)
   , m_currentHp(40)
   , m_walkingSpeed(1.0)
   , m_rotationSprite(0.0)
   ,m_pos(startWayPoint->pos())
   ,m_destinationWayPoint(startWayPoint->nextWayPoint())
   , m_game(game)
   , m_sprite(sprite)
{

}

enemy::~enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void enemy::doActivate()
{
    m_active = true;
}

void enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos,1,m_destinationWayPoint->pos(),1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向
    // 默认图片向左,需要修正180度转右
   //m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) + 180;
}

void enemy::draw(QPainter *painter) const
{
    if (!m_active)
        return;

    painter->save();
    //偏移量
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);

    QPoint healthBarPoint = m_pos+offsetPoint + QPoint(-Hp_Bar_Width / 2+5+ms_fixedSize.width() / 2, -ms_fixedSize.height()*4 / 5);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Hp_Bar_Width, 2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Hp_Bar_Width, 2));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    painter->translate(m_pos+offsetPoint);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void enemy::getDamage(int damage)
{

    m_currentHp -= damage;


    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {
        m_game->awardGold(200);
        getRemoved();
    }
}

void enemy::getAttacked(tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void enemy::gotLostSight(tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint enemy::pos() const
{
    return m_pos;
}

QPoint enemy::operator+(const QPoint &offsetPoint) const
{
    QPoint a(m_pos+offsetPoint);
    return a;

}

void enemy::setPos(QPoint point)
{
    m_pos=point;
}
