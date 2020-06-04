#ifndef START_H
#define START_H

#include <QDialog>
#include <QMainWindow>
#include<QTime>
#include <QList>
#include <vector>
namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = nullptr);
    ~Start();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Start *ui;
};

#endif // START_H
