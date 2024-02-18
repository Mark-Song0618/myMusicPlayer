#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "basic.h"
#include "util.h"
#include "mymediaplayer.h"
#include "myDatabase.h"
#include <QWidget>
#include <QFile>
#include <QMouseEvent>
#include <QHeaderView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

PUBLIC_FUNCTION
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool loadQss(QString fileName);

INHERITA_FUNCTION
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

PRIVATE_MEMBER
    enum winSize { WIN_MIN, WIN_MAX, WIN_NOR};
    winSize winStatus = WIN_NOR;
    QPoint oriPos;  //record the position when mouse pressed
    MyMediaPlayer * m_media;
    Ui::MainWindow *ui;

PRIVATE_FUNCTION
    void setAppearence();
    void setTopBar();
    void setBottomBar();
    void setTabWidget();
    void setListWidgets();
};

#endif // MAINWINDOW_H
