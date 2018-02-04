#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    disableButtons();
    ui -> plainTextEdit -> clear();
    receivedStr = "";
    howManySteps = "0";
    //setLine(receivedStr);
    //showPic();

    for(int i=0;i<30;i++) tries[i]=0;

   // connect(ui->connHost, &QLineEdit::returnPressed, this, &MainWindow::doConnect);
   // connect(ui->talkInput, &QLineEdit::returnPressed, this, &MainWindow::sendData);
    doConnect();
}

Widget::~Widget()
{
    delete ui;
}

std::string Widget::makeLine()
{
    std::string ans = "";
    int i=0;
    while (receivedStr[i] != '.')
    {
        ans += receivedStr[i];
        i++;
    }
    i++;
    howManySteps=""; howManySteps +=receivedStr[i];
    if(howManySteps == "6") {ans += " !!!PRZEGRANA!!!"; disableButtons(); ui -> pushButton_27 -> setEnabled(true);}
    showPic();
    i++;
    ifOkay = receivedStr[i];
    if (ifOkay=='0') loseLife();
    if(checkWon()) {ans += " !!!WYGRANA!!!"; disableButtons();  ui -> pushButton_27 -> setEnabled(true); }
    i++;
    while(receivedStr[i])
    {
        tries[(receivedStr[i]-'A')+1] = 1;
        i++;
    }
    disableSome();
    return ans;
}

void Widget::disableSome()
{
    int i = 0;
    for (auto but: QObject::findChildren<QPushButton*>())
    {
        if(tries[i]) {but -> setChecked(true); but-> setEnabled(false);}
        i++;
        //qDebug() << but->isChecked();
    }
}


void Widget::Reset()
{
    for(int i=0;i<30;i++) tries[i]=0;
    sendData('1');
    enableButtons();
    ui -> pushButton_27 -> setEnabled(false);

    ui -> plainTextEdit -> clear();
    ui ->lcdNumber -> display(3);
}

bool Widget::checkWon()
{
    for(int i=0;i<receivedStr.length();i++) if(receivedStr[i] == '-') return false;
    return true;
}

void Widget::loseLife()
{
    qDebug()<< "losing life ";
    int val = ui ->lcdNumber -> intValue(); --val;
    ui ->lcdNumber -> display(val);
    if (val == 0)
    {
        disableButtons();
    }

}

void Widget::doConnect() {
    //QMessageBox::information(this, "title", "text");

    sock = new QTcpSocket(this);

    connect(sock, &QTcpSocket::connected, this, &Widget::connSucceeded);
    connect(sock, &QTcpSocket::readyRead, this, &Widget::dataAvail);

    connect(sock,
            (void (QTcpSocket::*) (QTcpSocket::SocketError))
            &QTcpSocket::error, this, &Widget::someerror);

    sock->connectToHost(host, port);

}

void Widget::connSucceeded() {
    qDebug() << "Connection succesfull!";
    enableButtons();

}

void Widget::dataAvail() {
    auto data = sock ->readAll();
    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    QString qstring = codec->toUnicode(data);
    receivedStr = qstring.toStdString();
    setLine();
    qDebug() << receivedStr.c_str();
}

void Widget::sendData(char c) {
    QString str = ""; str +=c;
    auto data = (str).toUtf8();

    sock->write(data);

}

void Widget::someerror(QTcpSocket::SocketError) {
    QMessageBox::critical(this, "Error", sock->errorString());
}


void Widget::setLine()
{
    ui -> plainTextEdit -> clear();
    ui-> plainTextEdit-> appendPlainText(QString::fromStdString(makeLine()));
}

void Widget::showPic()
{
    QString filename = QString::fromStdString(picspath + howManySteps + ".png");
    QImage image(filename);
    ui-> label->setPixmap(QPixmap::fromImage(image));
}

void Widget::disableButtons()
{
    for (auto but: QObject::findChildren<QPushButton*>())
    {
        but -> setEnabled(false);
    }
}

void Widget::enableButtons()
{
    for (auto but: QObject::findChildren<QPushButton*>())
    {
        but -> setEnabled(true);
        but ->setChecked(false);
        but -> setCheckable(true);
    }
    ui -> pushButton_27 -> setEnabled(false);
}



void Widget::on_plainTextEdit_destroyed()
{
}

void Widget::on_pushButton_clicked()
{
    sendData('A');
}

void Widget::on_pushButton_2_clicked()
{
    sendData('B');
}

void Widget::on_pushButton_3_clicked()
{
    sendData('C');
}

void Widget::on_pushButton_4_clicked()
{
    sendData('D');
}

void Widget::on_pushButton_5_clicked()
{
    sendData('E');
}

void Widget::on_pushButton_6_clicked()
{
    sendData('F');
}

void Widget::on_pushButton_7_clicked()
{
    sendData('G');
}

void Widget::on_pushButton_8_clicked()
{
    sendData('H');
}

void Widget::on_pushButton_9_clicked()
{
    sendData('I');
}

void Widget::on_pushButton_10_clicked()
{
    sendData('J');
}

void Widget::on_pushButton_11_clicked()
{
    sendData('K');
}

void Widget::on_pushButton_12_clicked()
{
    sendData('L');
}

void Widget::on_pushButton_13_clicked()
{
    sendData('M');
}

void Widget::on_pushButton_14_clicked()
{
    sendData('N');
}

void Widget::on_pushButton_15_clicked()
{
    sendData('O');
}

void Widget::on_pushButton_16_clicked()
{
    sendData('P');
}

void Widget::on_pushButton_17_clicked()
{
    sendData('Q');
}

void Widget::on_pushButton_18_clicked()
{
    sendData('R');
}

void Widget::on_pushButton_19_clicked()
{
    sendData('S');
}

void Widget::on_pushButton_20_clicked()
{
    sendData('T');
}

void Widget::on_pushButton_21_clicked()
{
    sendData('U');
}

void Widget::on_pushButton_22_clicked()
{
    sendData('V');
}

void Widget::on_pushButton_23_clicked()
{
    sendData('W');
}

void Widget::on_pushButton_24_clicked()
{
    sendData('X');
}

void Widget::on_pushButton_25_clicked()
{
    sendData('Y');
}

void Widget::on_pushButton_26_clicked()
{
    sendData('Z');
}

void Widget::on_pushButton_27_clicked()
{\
    Reset();
}
