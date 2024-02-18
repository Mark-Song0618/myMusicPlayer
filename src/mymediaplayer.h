#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H
#include <QMediaPlayer>
#include <QVideoWidget>
#include "basic.h"

class MyMediaPlayer : public QMediaPlayer
{
    Q_OBJECT
PUBLIC_FUNCTION
    MyMediaPlayer();
    ~MyMediaPlayer();
    void init();
    QVideoWidget *getVideoWidget() { return m_vw; }
PRIVATE_MEMBER
    QVideoWidget *m_vw = nullptr;
    bool m_playing = false;
SLT(public)
    void Play();
};

#endif // MYMEDIAPLAYER_H
