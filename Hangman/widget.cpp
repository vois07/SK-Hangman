#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui -> plainTextEdit -> clear();
    s.encode();
    std::string str = s.getLine();
    setLine(str);
    showPic();
    ui -> pushButton_27 -> setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Reset()
{
    s.Reset();
    ui -> plainTextEdit -> clear();
    s.encode();
    std::string str = s.getLine();
    setLine(str);
    showPic();
    ui -> pushButton_27 -> setEnabled(false);
    enableButtons();
    ui ->lcdNumber -> display(3);
}

void Widget::setLine(std::string str)
{
    if (s.checkWon()) {str += " !!!WYGRANA!!!"; disableButtons();}
    ui -> plainTextEdit -> clear();
    ui-> plainTextEdit-> appendPlainText(QString::fromStdString(str));
}

void Widget::showPic()
{
    QString filename = QString::fromStdString(picspath + std::to_string(s.steps2die++) + ".png");
    QImage image(filename);
    ui-> label->setPixmap(QPixmap::fromImage(image));
}

void Widget::disableButtons()
{
    for (auto but: QObject::findChildren<QPushButton*>())
    {
        but -> setEnabled(false);
    }
    ui -> pushButton_27 -> setEnabled(true);
}

void Widget::enableButtons()
{
    for (auto but: QObject::findChildren<QPushButton*>())
    {
        but -> setEnabled(true);
        but ->setChecked(false);
    }
}

void Widget::loseLife()
{
    int val = ui ->lcdNumber -> intValue(); --val;
    ui ->lcdNumber -> display(val);
    if (val == 0)
    {
        disableButtons();
    }
    showPic();

}


void Widget::on_pushButton_clicked()
{
    if (!(s.decode('A'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}
void Widget::on_pushButton_2_clicked()
{
    if (!(s.decode('B'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}
void Widget::on_plainTextEdit_destroyed()
{
}

void Widget::on_pushButton_3_clicked()
{
    if (!(s.decode('C'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_4_clicked()
{
    if (!(s.decode('D'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_5_clicked()
{
    if (!(s.decode('E'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_6_clicked()
{
    if (!(s.decode('F'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_7_clicked()
{
    if (!(s.decode('G'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_8_clicked()
{
    if (!(s.decode('H'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_9_clicked()
{
    if (!(s.decode('I'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_10_clicked()
{
    if (!(s.decode('J'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_11_clicked()
{
    if (!(s.decode('K'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_12_clicked()
{
    if (!(s.decode('L'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_13_clicked()
{
    if (!(s.decode('M'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_14_clicked()
{
    if (!(s.decode('N'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_15_clicked()
{
    if (!(s.decode('O'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_16_clicked()
{
    if (!(s.decode('P'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_17_clicked()
{
    if (!(s.decode('Q'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_18_clicked()
{
    if (!(s.decode('R'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_19_clicked()
{
    if (!(s.decode('S'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_20_clicked()
{
    if (!(s.decode('T'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_21_clicked()
{
    if (!(s.decode('U'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_22_clicked()
{
    if (!(s.decode('V'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_23_clicked()
{
    if (!(s.decode('W'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_24_clicked()
{
    if (!(s.decode('X'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_25_clicked()
{
    if (!(s.decode('Y'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_26_clicked()
{
    if (!(s.decode('Z'))) loseLife();
    std::string str = s.getLine();
    setLine(str);
}

void Widget::on_pushButton_27_clicked()
{\
    Reset();
}
