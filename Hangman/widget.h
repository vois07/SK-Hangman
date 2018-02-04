#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <stdio.h>
#include <QtGui>
#include <QMainWindow>
#include<QtWidgets>
#include<QtNetwork>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:

    QString host = "192.168.0.108";
    int port = 1234;

    explicit Widget(QWidget *parent = 0);
    ~Widget();

    std::string receivedStr;
    void setLine();
    void loseLife();
    void showPic();
    void Reset();
    bool checkWon();
    std::string makeLine();
    std::string howManySteps;
    char ifOkay;
    bool tries[30];


    void disableButtons();
    void enableButtons();

    //connective
    void doConnect();
    void connSucceeded();
    void dataAvail();
    void sendData(char);
    void someerror(QTcpSocket::SocketError);
    void disableSome();

    QTcpSocket * sock = 0;

private slots:
    void on_plainTextEdit_destroyed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::Widget *ui;
    std::string picspath = "./pics/";
};

#endif // WIDGET_H
