#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>

class QPainter;

class waypoint
{
public:
    waypoint(QPoint pos);
    void setNextWayPoint(waypoint *nextPoint);
    waypoint* nextWayPoint() const;
    const QPoint pos() const;

    void draw(QPainter *painter) const;

private:
    const QPoint		m_pos;
    waypoint *			m_nextWayPoint;
};

#endif // WAYPOINT_H
