#include "start.h"
#include "ui_start.h"
#include <QPainter>
#include <mainwindow.h>

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
    MainWindow *w=new MainWindow;
    w->show();
}

void Start::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/image/Begin.png"));
}
