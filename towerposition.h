#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class towerposition
{
public:
    towerposition(QPoint pos);
    void setHasTower(bool hasTower = true);
    void setnoTower();
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;
    QPoint Pos();

private:
    bool		m_hasTower;
    QPoint		m_pos;
    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
