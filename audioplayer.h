#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class QMediaPlayer;

class audioplayer: public QObject
{
public:
    explicit audioplayer(QObject *parent = NULL);
    void BGM();

private:
    QMediaPlayer *m_backgroundMusic;
};

#endif // AUDIOPLAYER_H
