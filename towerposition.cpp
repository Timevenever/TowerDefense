#include "towerposition.h"
#include <QPainter>

const QSize towerposition::ms_fixedSize(100, 100);

void towerposition::draw(QPainter *painter) const
{
    painter->setPen(QPen(Qt::blue, 1, Qt::DotLine, Qt::RoundCap));
    painter->drawEllipse(m_pos.x(), m_pos.y(),ms_fixedSize.width(),ms_fixedSize.height());
    //painter->drawPixmap(m_pos.x(), m_pos.y(), m_sprite);
}

towerposition::towerposition(QPoint pos):m_pos(pos)
{
    m_hasTower=false;
}

const QPoint towerposition::centerPos() const
{
    QPoint offsetPoint(ms_fixedSize.width() / 2, ms_fixedSize.height() / 2);
    return m_pos + offsetPoint;
}

bool towerposition::containPoint(const QPoint &pos) const
{
    bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
    bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + ms_fixedSize.height());
    return isXInHere && isYInHere;
}

bool towerposition::hasTower() const
{
    return m_hasTower;
}

void towerposition::setHasTower(bool hasTower/* = true*/)
{
    m_hasTower = hasTower;
}

void towerposition::setnoTower()
{
    m_hasTower = false;
}

QPoint towerposition::Pos()
{
    return m_pos;
}
