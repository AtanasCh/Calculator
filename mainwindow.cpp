#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui-> pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui-> pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui-> pushButton_plusMinus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui-> pushButton_percentage,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui-> pushButton_add,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_substraction,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_devision,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui-> pushButton_multiplication,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pushButton_add->setCheckable(true);
    ui->pushButton_substraction->setCheckable(true);
    ui->pushButton_devision->setCheckable(true);
    ui->pushButton_multiplication->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    //qDebug() << "test";

    QPushButton * button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_add->isChecked() || ui->pushButton_substraction->isChecked() ||
            ui->pushButton_devision->isChecked() || ui->pushButton_multiplication->isChecked())
            && (!userIsTypingSecondNumber))
    {
        labelNumber = button->text().toDouble();
        userIsTypingSecondNumber = true;
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else{
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        } else{
            labelNumber = (ui->label->text() + button->text()).toDouble();
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }
    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    double labelNumber;
    QString newLabel;
    QPushButton * button = (QPushButton*) sender();

    if (button->text() == "+/-"){
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g', 15);
        ui->label->setText(newLabel);
    } else if (button->text() == "%"){

        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber,'g', 15);
        ui->label->setText(newLabel);

    }
}

void MainWindow::on_pushButton_C_released()
{

    ui->pushButton_add->setChecked(false);
    ui->pushButton_substraction->setChecked(false);
    ui->pushButton_multiplication->setChecked(false);
    ui->pushButton_devision->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");

}

void MainWindow::on_pushButton_equals_released()
{
    double labelNumber;
    double secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if(ui->pushButton_add->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }
    else if(ui->pushButton_substraction->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_substraction->setChecked(false);
    }
    else if(ui->pushButton_devision->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_devision->setChecked(false);
    }
    else if(ui->pushButton_multiplication->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g',15);
        ui->label->setText(newLabel);
        ui->pushButton_multiplication->setChecked(false);
    }

    userIsTypingSecondNumber = false;


}

void MainWindow::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    firstNum = ui->label->text().toDouble();

    button->setChecked(true);


}
