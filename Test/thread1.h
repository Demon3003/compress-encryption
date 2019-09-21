#ifndef THREAD_H
#define THREAD_H
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
    public:
    explicit MyThread(char t,QString s,QString e);
    void run();
    signals:
    void send(bool);
    private:
    char algorithm;
    QString name,key="";


};
#endif // THREAD_H

