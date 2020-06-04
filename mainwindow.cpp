#include "mainwindow.h"
#include "start.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "utility.h"
#include "audioplayer.h"
#include "tower.h"
#include "towerposition.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>

static const QPoint offsetPoint(0,-25);
static const QPoint offPoint(250,50);
static const int TowerCost = 300;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_waves(0),
    m_playerHp(5),
    m_playerGold(1000),
    m_gameEnd(false),
    m_gameWin(false)
{
    ui->setupUi(this);

    //loadWave();
    loadTower();
    loadTowerPosition();
    addWayPoints();

    //游戏背景音乐
    m_audioPlayer = new audioplayer(this);
    m_audioPlayer->BGM();

    // 设置200ms后游戏启动
    QTimer::singleShot(200, this, SLOT(gameStart()));


    //30毫秒重画一次达到动态效果
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//更新重画
void MainWindow::updateMap()
{

   foreach (enemy *enemy, m_enemyList)
        enemy->move();

    foreach (tower *tower, m_towersList)
        tower->checkEnemyInRange();

    update();
}

//加载塔
void MainWindow::loadTower()
{
  QPoint pos[]=
  {
    QPoint(50,50),
    QPoint(200,30),
    QPoint(350,20)
  };

  tower *Tower1=new tower(pos[0],this,QPixmap(":/image/tower1.png"));
  Tower1->setLevel(1);
  m_displayList.push_back(Tower1);
  tower *Tower2=new tower(pos[1],this,QPixmap(":/image/tower2.png"));
  Tower2->setLevel(2);
  m_displayList.push_back(Tower2);
  tower *Tower3=new tower(pos[2],this,QPixmap(":/image/tower3.png"));
  Tower3->setLevel(3);
  m_displayList.push_back(Tower3);

}

//加载塔的位置
void MainWindow::loadTowerPosition()
{
   QPoint pos[]=
   {
       QPoint(300,150),
       QPoint(400,150),
       QPoint(500,150),
       QPoint(600,150),
       QPoint(700,150),
       QPoint(950,150),
       QPoint(1050,150),
       QPoint(1150,150),

       QPoint(200,400),
       QPoint(400,400),
       QPoint(500,400),
       QPoint(600,400),
       QPoint(700,400),
       QPoint(800,400),
       QPoint(900,400),
       QPoint(1000,400),
       QPoint(1100,400)
   };

   int len=sizeof(pos)/sizeof(pos[0]);
   for(int i=0;i<len;i++)
   {
       m_towerPositionsList.push_back(pos[i]);
   }

}

//设置路线
void MainWindow::addWayPoints()
{
    waypoint *wayPoint1 = new waypoint(QPoint(1250,325));
    m_wayPointsList.push_back(wayPoint1);

    waypoint *wayPoint2 = new waypoint(QPoint(10, 325));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

   /* waypoint *wayPoint3 = new waypoint(QPoint(600, 325));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    waypoint *wayPoint4 = new waypoint(QPoint(445, 195));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    waypoint *wayPoint5 = new waypoint(QPoint(445, 100));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    waypoint *wayPoint6 = new waypoint(QPoint(35, 100));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5); */

}

void MainWindow::gameStart()
{
    loadWave();
    Is_ingame();

}

//加载敌人
void MainWindow::loadWave()
{
    waypoint *startWayPoint = m_wayPointsList.back();
    QPoint a;

    enemy *Enemy=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy);
    QTimer::singleShot(1000,Enemy, SLOT(doActivate()));

    enemy *Enemy2=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy2);
    //每隔2000毫秒出现一波敌人
    QTimer::singleShot(2000,Enemy2, SLOT(doActivate()));

    enemy *Enemy3=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy3);
    QTimer::singleShot(3000,Enemy3, SLOT(doActivate()));


    enemy *Enemy4=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy4->pos()+offsetPoint;
    Enemy4->setPos(a);
    m_enemyList.push_back(Enemy4);
    QTimer::singleShot(4000,Enemy4, SLOT(doActivate()));

}

void MainWindow::loadWave2()
{
    waypoint *startWayPoint = m_wayPointsList.back();
    QPoint a;

    enemy *Enemy=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy);
    QTimer::singleShot(1000,Enemy, SLOT(doActivate()));

    enemy *Enemy2=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy2);
    QTimer::singleShot(2000,Enemy2, SLOT(doActivate()));

    enemy *Enemy3=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy3);
    QTimer::singleShot(3000,Enemy3, SLOT(doActivate()));


    enemy *Enemy4=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy4->pos()+offsetPoint;
    Enemy4->setPos(a);
    m_enemyList.push_back(Enemy4);
    QTimer::singleShot(4000,Enemy4, SLOT(doActivate()));

    enemy *Enemy5=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy5->pos()+offsetPoint;
    Enemy5->setPos(a);
    m_enemyList.push_back(Enemy5);
    QTimer::singleShot(5000,Enemy5, SLOT(doActivate()));

}

void MainWindow::loadWave3()
{
    waypoint *startWayPoint = m_wayPointsList.back();
    QPoint a;

    enemy *Enemy=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy);
    QTimer::singleShot(1000,Enemy, SLOT(doActivate()));

    enemy *Enemy2=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy2);
    QTimer::singleShot(2000,Enemy2, SLOT(doActivate()));

    enemy *Enemy3=new enemy(startWayPoint,this,QPixmap(":/image/Monster1.png"));//一号怪物
    m_enemyList.push_back(Enemy3);
    QTimer::singleShot(3000,Enemy3, SLOT(doActivate()));


    enemy *Enemy4=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy4->pos()+offsetPoint;
    Enemy4->setPos(a);
    m_enemyList.push_back(Enemy4);
    QTimer::singleShot(4000,Enemy4, SLOT(doActivate()));

    enemy *Enemy5=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy5->pos()+offsetPoint;
    Enemy5->setPos(a);
    m_enemyList.push_back(Enemy5);
    QTimer::singleShot(5000,Enemy5, SLOT(doActivate()));

    enemy *Enemy6=new enemy(startWayPoint,this,QPixmap(":/image/Monster2.png"));//二号怪物
    a=Enemy6->pos()+offsetPoint;
    Enemy6->setPos(a);
    m_enemyList.push_back(Enemy6);
    QTimer::singleShot(6000,Enemy6, SLOT(doActivate()));

}

bool MainWindow::Is_ingame()
{
    if (m_waves >=3)
      {
        return false;
      }
    else
       {
        return true;
       }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (m_gameEnd || m_gameWin)
    {
        if(m_gameEnd)
        {
            QPainter painter(this);
            painter.drawPixmap(rect(), QPixmap(":/image/Lose.png"));
        }
        else if(m_gameWin)
        {
            QPainter painter(this);
            painter.drawPixmap(rect(), QPixmap(":/image/Win.png"));
        }
        return;
    }

    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/image/Sence1.png"));

    foreach ( tower *Tower, m_displayList)
        Tower->draw(&painter);

   /* foreach (const waypoint *Waypoint, m_wayPointsList)
        Waypoint->draw(&painter);*/

    foreach (const towerposition &towerpos, m_towerPositionsList)
        towerpos.draw(&painter);

    foreach ( tower *Tower, m_towersList)
        Tower->draw(&painter);

    foreach (const bullet *Bullet, m_bulletList)
        Bullet->draw(&painter);

    foreach (const enemy *Enemy, m_enemyList)
        Enemy->draw(&painter);

    drawWave(&painter);
    drawHP(&painter);
    drawGold(&painter);

}

//左击鼠标建塔
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
   {
     QPoint pressPos = event->pos();
     auto it = m_towerPositionsList.begin();
     while (it != m_towerPositionsList.end())
     {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_playerGold -= TowerCost;
            it->setHasTower();

            tower *Tower = new tower(it->centerPos(), this);
            m_towersList.push_back(Tower);
            update();
            break;
        }

        ++it;
     }
   }
}

//鼠标右击菜单
void MainWindow::on_MainWindow_customContextMenuRequested(const QPoint &pos)
{
    auto it = m_towerPositionsList.begin();
    while (it!=m_towerPositionsList.end())
    {
      if(it->containPoint(pos)&&it->hasTower())
      {

        //创建菜单对象
        QMenu *pMenu = new QMenu(this);

        QAction *pNewTask = new QAction(tr("升级"), this);
        QAction *pDeleteTask = new QAction(tr("拆塔"), this);

        //1:升级 2:拆塔
        pNewTask->setData(1);
        pDeleteTask ->setData(2);

        //把QAction对象添加到菜单上
        pMenu->addAction(pNewTask);
        pMenu->addAction(pDeleteTask);

        //连接鼠标右键点击信号
        connect(pNewTask, SIGNAL(triggered()), this, SLOT(updateTower()));
        connect(pDeleteTask, SIGNAL(triggered()), SLOT(removeTower()));

        //在鼠标右键点击的地方显示菜单
        pMenu->exec(pos+offPoint);

        //释放内存
        QList<QAction*> list = pMenu->actions();
        foreach (QAction* pAction, list) delete pAction;
        delete pMenu;
      }
      ++it;
    }

}

 //升级，没写完
void MainWindow::updateTower()
{
    auto it=m_towerPositionsList.begin();
    while (it!=m_towerPositionsList.end())
    {
        if(m_playerGold>=200&&it->hasTower()&&m_towersList.back()->getLevel()==1)
        {
            m_playerGold-=200;
            m_towersList.back()->stopAttack();
            m_towersList.pop_back();
            it->setnoTower();

            it->setHasTower();

        }
    }
}

//拆塔
void MainWindow::removeTower()
{
    auto it = m_towerPositionsList.begin();
    while (it!=m_towerPositionsList.end())
    {
        if(it->hasTower())
        {
            m_playerGold+=100;
            it->setnoTower();

            m_towersList.back()->stopAttack();
            m_towersList.pop_back();

            update();
            break;
        }
        ++it;
    }

}

//画敌人波数
void MainWindow::drawWave(QPainter *painter)
{
    QFont font("MV Boli",10,QFont::Bold,true);
    painter->setFont(font);
    painter->setPen(QPen(QColor(0xFF)));
    painter->drawText(QRect(1150,0, 150, 25), QString("WAVE : %1").arg(m_waves + 1));
}

//画血量
void MainWindow::drawHP(QPainter *painter)
{
    QFont font("MV Boli",10,QFont::Bold,true);
    painter->setFont(font);
    painter->setPen(QPen(QColor(0xFF)));
    painter->drawText(QRect(1000, 0, 150, 25), QString("HP : %1").arg(m_playerHp));
}

//画金币数
void MainWindow::drawGold(QPainter *painter)
{
    QFont font("MV Boli",10,QFont::Bold,true);
    painter->setFont(font);
    painter->setPen(QPen(QColor(0xFF)));
    painter->drawText(QRect(800, 0, 200, 25), QString("GOLD : %1").arg(m_playerGold));
}

//判断是否有足够金额买塔
bool MainWindow::canBuyTower() const
{
    if (m_playerGold >= TowerCost)
        return true;
    return false;
}

//奖励金币
void MainWindow::awardGold(int gold)
{
    m_playerGold += gold;
    update();
}

//敌人攻击成功
void MainWindow::getHpDamage(int damage/* = 1*/)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        gameOver();
}

void MainWindow::gameOver()
{
    if (!m_gameEnd)
    {
        m_gameEnd = true;
        // 游戏结束
    }
}

void MainWindow::removedEnemy(enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if(m_waves==1)
        {
            loadWave2();
        }
        else if(m_waves==2)
        {
            loadWave3();
        }
        if (!Is_ingame())
        {
            m_gameWin = true;
            // 游戏胜利
        }
    }
}

void MainWindow::removedBullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

QList<enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}



