#include "mymediaplayer.h"
#include <QMediaPlayer>
#include <QMediaCaptureSession>

MyMediaPlayer::MyMediaPlayer()
{
    init();
}

MyMediaPlayer::~MyMediaPlayer(){}

void
MyMediaPlayer::init() {
    //initial song;
    setSource(QUrl("qrc:/music/music/video.mp4"));
    if (m_vw == nullptr) {
        m_vw = new QVideoWidget();
        setVideoOutput(m_vw);
        m_vw->show();
    }
}

void
MyMediaPlayer::Play() {
    if (m_playing) {
        pause();
        m_playing = false;
    } else {
        play();
        m_playing = true;
    }
}
