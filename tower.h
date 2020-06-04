#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QtMath>

class QPainter;
class enemy;
class MainWindow;
class QTimer;

class tower: QObject
{
    Q_OBJECT

public:
    tower(QPoint pos, MainWindow *game, const QPixmap &sprite = QPixmap(":/image/tower1.png"));
    ~tower();
    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();
    void stopAttack();
    void setLevel(int l);
    int getLevel();

private slots:
    void shootWeapon();

private:
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    int             m_level;
    //qreal			m_rotationSprite;

    enemy *			m_chooseEnemy;
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;

    const QPoint	m_pos;
    const QPixmap	m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
