#include "myDatabase.h"
#include <iostream>
#include <QSqlQuery>
#include <QString>
#include <QVariant>

myDataBase::myDataBase()
{
    init();
}

bool myDataBase::insertItem(MEDIA_TYPE type, QString content) {
    QSqlQuery qry(m_db);
    switch (type) {
        case (MUSIC): {
            return qry.exec(QString::asprintf("insert into music %s", content.toStdString().c_str()));
        }
        case (VIDEO): {
            return qry.exec(QString::asprintf("insert into video %s", content.toStdString().c_str()));
        }
        default:
            return false;
    }

}

bool myDataBase::deleteItem(MEDIA_TYPE type, QString item) {
    QSqlQuery qry(m_db);
    switch (type) {
        case (MUSIC): {
            return qry.exec(QString::asprintf("delete from music where %s", item.toStdString().c_str()));
        }
        case (VIDEO): {
            return qry.exec(QString::asprintf("delete from video where %s", item.toStdString().c_str()));
        }
        default:
            return false;
    }
}

bool myDataBase::getInfo(MEDIA_TYPE type, QString content, std::vector<QVariant> &result) {
    QSqlQuery qry(m_db);
    bool query = true;
    switch (type) {
        case (MUSIC): {
            query = qry.exec(QString::asprintf("delete from music where %s", content.toStdString().c_str()));
            break;
        }
        case (VIDEO): {
            query = qry.exec(QString::asprintf("delete from video where %s", content.toStdString().c_str()));
            break;
        }
        default:
            return false;
    }
    if (!query) return false;
    while (qry.next()) {
        result.emplace_back(qry.value(0));
    }
    return true;
}

bool myDataBase::init() {
    m_db = QSqlDatabase::addDatabase("QSQLITE", "MusicDatabase");
    m_db.setHostName("localhost");
    m_db.setPort(3306);
    m_db.setDatabaseName("mysql");
    m_db.setUserName("Mark");
    m_db.setPassword("sjtu519519");
    m_db.open();
    if(!m_db.open())
    {
        std::cout << "connect failed" << std::endl;
        return false;
    }
    else
    {
        std::cout << "connect success" << std::endl;
        /*
         *  check music table and video table
         *  if not exit, create tables;
        */
        QSqlQuery qry(m_db);
        qry.exec("show tables");
        while (qry.next()) {
            QString rst = qry.value(0).toString();
            if (rst == "music") {
                m_music_online = true;
            } else if (rst == "video") {
                m_video_online = true;
            }
        }
        if (m_music_online && m_video_online) {
            std::cout << "database setup success" << std::endl;
            return true;
        }
        QString fmt =
                        "create table %s (\
                            `index` int(30) NOT NULL PRIMARY KEY AUTO_INCREMENT,\
                            `singer` char(50) NULL,\
                            itemName char(255) NULL\
                        )";
        if (!m_music_online) {
            // create music table
            std::cout << "create music database" << std::endl;
            QString cmd = QString::asprintf(fmt.toStdString().c_str(), "music");
            qry.exec(cmd);
        }
        if (!m_video_online) {
            // create video table
            std::cout << "create video database" << std::endl;
            QString cmd = QString::asprintf(fmt.toStdString().c_str(), "video");
            qry.exec(cmd);
        }
        qry.exec("show tables");
        while (qry.next()) {
            QString rst = qry.value(0).toString();
            if (rst == "music") {
                m_music_online = true;
            } else if (rst == "video") {
                m_video_online = true;
            }
        }
        if (!m_music_online) {
            std::cout << "music database not available" << std::endl;

        }
        if (!m_video_online) {
            std::cout << "video database not available" << std::endl;
        }
        return m_music_online && m_video_online;
    }
}
