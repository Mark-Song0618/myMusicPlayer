#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget (parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setTopBar();
    setBottomBar();
    setTabWidget();
    setListWidgets();
    setAppearence();
    myDataBase::Instance().init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool
MainWindow::loadQss(QString fileName) {
    QFile qssFile(fileName);
    if (!qssFile.open(QFile::ReadOnly)) {
        return false;
    }

    this->setStyleSheet(qssFile.readAll());
    qssFile.close();
    return true;
}

#define EXPAND_RATIO 2
#define PLACEWIDGET(widget, w, h, x, y) \
        ui->widget->setFixedSize(w * EXPAND_RATIO, h * EXPAND_RATIO);  \
        ui->widget->move(x * EXPAND_RATIO, y * EXPAND_RATIO);

void
MainWindow::setAppearence() {
    loadQss(":qss//qss//myQssFile.qss");

    this->setFixedSize(600 * EXPAND_RATIO, 420 * EXPAND_RATIO);
    PLACEWIDGET(topBar, 600, 40, 0, 0)
    PLACEWIDGET(table_music, 100, 160, 0, 40)
    PLACEWIDGET(table_video, 100, 160, 0, 200)
    PLACEWIDGET(bottomBar, 600, 60, 0, 360)

}

void
MainWindow::setTopBar() {
    PLACEWIDGET(topBar_Lab1, 80, 30, 0, 5)
    PLACEWIDGET(topBar_pb_prev, 20, 20, 100, 10)
    PLACEWIDGET(topBar_pb_next, 20, 20, 122, 10)
    PLACEWIDGET(topBar_en_search, 200, 30, 145, 5)
    PLACEWIDGET(topBar_pb_min, 20, 20, 525, 10)
    PLACEWIDGET(topBar_pb_max, 20, 20, 550, 10)
    PLACEWIDGET(topBar_pb_close, 20, 20, 575, 10)

    ui->topBar_Lab1->setText("");
    ui->topBar_pb_prev->setText("");
    ui->topBar_pb_next->setText("");
    ui->topBar_pb_min->setText("");
    ui->topBar_pb_max->setText("");
    ui->topBar_pb_close->setText("");

    connect(ui->topBar_pb_min, &QPushButton::clicked, [&](){
        this->showMinimized();
        winStatus = WIN_MIN;
    });
    connect(ui->topBar_pb_max, &QPushButton::clicked, [&](){
        if (winStatus != WIN_MAX) {
            this->showMaximized();
            winStatus = WIN_MAX;
        } else {
            this->showNormal();
            winStatus = WIN_NOR;
        }
    });
    connect(ui->topBar_pb_close, &QPushButton::clicked, [&](){
        winStatus = WIN_NOR;
        this->close();
    });
}

void
MainWindow::setBottomBar() {
    PLACEWIDGET(bottom_Icon_song, 40, 40, 0, 0)
    PLACEWIDGET(bottomBar_lb_song, 80, 20, 45, 0)
    PLACEWIDGET(bottomBar_lb_singer, 80, 20, 45, 20)
    PLACEWIDGET(bottomBar_pb_prev, 20, 20, 260, 5)
    PLACEWIDGET(bottomBar_pb_play, 30, 30, 285, 0)
    PLACEWIDGET(bottomBar_pb_next, 20, 20, 320, 5)
    PLACEWIDGET(bottomBar_slder, 200, 10, 200, 30)
    PLACEWIDGET(bottomBar_lb_duration, 80, 30, 410, 5)

    ui->bottomBar_lb_song->setText("");
    ui->bottomBar_lb_singer->setText("");
    ui->bottomBar_pb_prev->setText("");
    ui->bottomBar_pb_play->setText("");
    ui->bottomBar_pb_next->setText("");
    ui->bottomBar_lb_duration->setText("");
}

void
MainWindow::setTabWidget() {
    m_media = new MyMediaPlayer();
    connect(ui->bottomBar_pb_play, &QPushButton::clicked, m_media, &MyMediaPlayer::Play);
    connect(m_media, &QMediaPlayer::durationChanged, [&](qint64 duration) {
        int total = qvariant_cast<int>(duration / 1000);
        int min = total / 60;
        int sec = total % 60;
        QString text = QString::asprintf("%d : %d", min, sec);
        ui->bottomBar_slder->setMaximum(total);
        ui->bottomBar_lb_duration->setText(text);

    });
    connect(m_media, &QMediaPlayer::positionChanged, [&](qint64 pos) {
        int left = qvariant_cast<int>(m_media->duration() - pos);
        int total = qvariant_cast<int>(left / 1000);
        int min = total / 60;
        int sec = total % 60;
        QString text = QString::asprintf("%d : %d", min, sec);
        ui->bottomBar_slder->setValue(qvariant_cast<int>(pos / 1000));
        ui->bottomBar_lb_duration->setText(text);

    });
    m_media->getVideoWidget()->setParent(this);
    m_media->getVideoWidget()->setFixedSize(500 * EXPAND_RATIO, 320 * EXPAND_RATIO);
    m_media->getVideoWidget()->move(100 * EXPAND_RATIO, 40 * EXPAND_RATIO);
}

void
MainWindow::setListWidgets() {
    myDataBase &db = myDataBase::Instance();
    bool music, video;
    db.getConnectStatus(music, video);
    // set music list
    ui->table_music->setColumnCount(1);
    ui->table_music->setRowCount(0);
    ui->table_music->setHorizontalHeaderLabels({"Music List"});
    ui->table_music->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_music->verticalHeader()->hide();
    ui->table_music->verticalHeader()->setDefaultSectionSize(20);
    if (music) {
        // use controller to query db
        // insert all items in table
    } else {
        //insert a mp3 music
    }

    // set video list
    ui->table_video->setColumnCount(1);
    ui->table_video->setRowCount(0);
    ui->table_video->setHorizontalHeaderLabels({"Video List"});
    ui->table_video->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_video->verticalHeader()->hide();
    ui->table_video->verticalHeader()->setDefaultSectionSize(20);
    if (video) {
        // use controller to query db
        // insert all items in table
    } else {
        ui->table_music->insertRow(0);
        QTableWidgetItem *item = new QTableWidgetItem("过去的回忆");
        item->setTextAlignment(Qt::AlignHCenter);
        ui->table_music->setItem(0, 0, item);
    }
}

void
MainWindow::mousePressEvent(QMouseEvent *event) {
    oriPos = event->pos();
}

void
MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint curPos = event->pos();
    move(pos() + curPos - oriPos);
}
