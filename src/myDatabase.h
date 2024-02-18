#ifndef MYDATABASE_H
#define MYDATABASE_H
#include "basic.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <vector>

class myDataBase
{
PUBLIC_MEMBER
    enum MEDIA_TYPE { MUSIC = 0, VIDEO };
PUBLIC_FUNCTION
    static myDataBase &Instance() {static myDataBase m_database; return m_database; }
    bool init();
    bool insertItem(MEDIA_TYPE type, QString content);
    bool deleteItem(MEDIA_TYPE type, QString item);
    bool getInfo(MEDIA_TYPE type, QString content, std::vector<QVariant> &result);
    myDataBase(const myDataBase&) = delete;
    myDataBase &operator=(const myDataBase&) = delete;
    void getConnectStatus(bool &music, bool &video) { music = m_music_online; m_video_online = m_video_online;}
INHERITA_FUNCTION
    myDataBase();
PRIVATE_MEMBER
    QSqlDatabase m_db;
    bool m_music_online = false;
    bool m_video_online = false;
};

#endif // MYDATABASE_H
