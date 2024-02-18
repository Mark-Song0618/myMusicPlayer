#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include <QObject>

// this class response to UI, and communicate with db to retrieve data
class MyController : public QObject
{
    Q_OBJECT
public:
    explicit MyController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MYCONTROLLER_H
