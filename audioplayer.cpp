#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <iostream>
using namespace std;

audioplayer::audioplayer(QObject *parent)
    :QObject(parent)
    ,m_backgroundMusic(NULL)
{
    QUrl backgroundMusicUrl = QUrl::fromLocalFile("file:///C:/Qtprojects/TowerDefense/music/BGM.mp3");

    if (QFile::exists(backgroundMusicUrl.toLocalFile()))
    {
        m_backgroundMusic = new QMediaPlayer(this);
        QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();

        QMediaContent media(backgroundMusicUrl);
        backgroundMusicList->addMedia(media);
        backgroundMusicList->setCurrentIndex(0);
        // 设置背景音乐循环播放
        backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_backgroundMusic->setPlaylist(backgroundMusicList);
    }
}

void audioplayer::BGM()
{
    if (m_backgroundMusic)
        m_backgroundMusic->play();
}
