#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
private:
   double storedNum;
   bool trigger;
   double factorial(double);
   Q_OBJECT

public:
   explicit Calculator(QWidget *parent = nullptr);
   ~Calculator();

private:
   Ui::Calculator *ui;

private slots:
   void digit_pressed();
   void on_pushButton_decimal_released();
   void unary_operation_pressed();
   void on_pushButton_clear_released();
   void on_pushButton_equals_released();
   void binary_operation_pressed();
};



template<typename T>
class smart_ptr {
   T *_obj;
public:
   smart_ptr(T *obj) : _obj(obj) {}
   ~smart_ptr() { delete _obj; }
  
   T* operator->() { return _obj; }
   T& operator*() { return _obj; }
};

#endif // CALCULATOR_H

Реализация заголовочного файла calculator.h:
#include "calculator.h"
#include "ui_calculator.h"

#include <QDebug>

Calculator::Calculator(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::Calculator)
{
   ui->setupUi(this);

   connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
   connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

   connect(ui->pushButton_root, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
   connect(ui->pushButton_sinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
   connect(ui->pushButton_cosinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
   connect(ui->pushButton_factor, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
   connect(ui->pushButton_plusMinus, SIGNAL(released()), this, SLOT(unary_operation_pressed()));
   connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operation_pressed()));

   connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
   connect(ui->pushButton_subtract, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
   connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
   connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
   connect(ui->pushButton_pow, SIGNAL(released()), this, SLOT(binary_operation_pressed()));

   ui->pushButton_add->setCheckable(true);
   ui->pushButton_subtract->setCheckable(true);
   ui->pushButton_multiply->setCheckable(true);
   ui->pushButton_divide->setCheckable(true);
   ui->pushButton_pow->setCheckable(true);
}

Calculator::~Calculator()
{
   delete ui;
}

double Calculator::factorial(double n) {
   if (n == 1) {
       return 1;
   } else {
       return n * factorial(n - 1);
   }
}

void Calculator::digit_pressed() {
   QPushButton *button = (QPushButton*)sender();
   QString newLabel = nullptr;
   double labelNumber = 0;

   if ((ui->pushButton_add->isChecked() || ui->pushButton_subtract->isChecked() ||
           ui->pushButton_divide->isChecked() || ui->pushButton_multiply->isChecked() ||
           ui->pushButton_pow->isChecked()) && (!trigger)) {
       labelNumber = button->text().toDouble();
       newLabel = QString::number(labelNumber, 'g', 15);
       trigger = true;
   } else {
       if (ui->label->text().contains(".") && button->text() == "0") {
           newLabel = ui->label->text() + button->text();
       } else {
           labelNumber = (ui->label->text() + button->text()).toDouble();
           newLabel = QString::number(labelNumber, 'g', 15);
       }
   }

   ui->label->setText(newLabel);
}

void Calculator::on_pushButton_decimal_released() {
   if (!ui->label->text().contains(".")) {
       ui->label->setText(ui->label->text() + ".");
   }
}

void Calculator::unary_operation_pressed() {
   QPushButton *button = (QPushButton*)sender();
   double labelNumber = ui->label->text().toDouble();
   QString newLabel = nullptr;

   if (button->text() == "+/-") {
       labelNumber *= -1;
   } else if (button->text() == "sinx") {
       labelNumber = sin(labelNumber);
   } else if (button->text() == "cosx") {
       labelNumber = cos(labelNumber);
   } else if (button->text() == "n!") {
       labelNumber = factorial(labelNumber);
   } else if (button->text() == "sqrt") {
       labelNumber = sqrt(labelNumber);
   } else if (button->text() == "%") {
       labelNumber *= 0.01;
   }

   newLabel = QString::number(labelNumber, 'g', 15);
   ui->label->setText(newLabel);
}

void Calculator::on_pushButton_clear_released() {
   ui->pushButton_add->setChecked(false);
   ui->pushButton_subtract->setChecked(false);
   ui->pushButton_multiply->setChecked(false);
   ui->pushButton_divide->setChecked(false);
   ui->pushButton_pow->setChecked(false);

   trigger = false;
   ui->label->setText("0");
   storedNum = 0;
}

void Calculator::on_pushButton_equals_released() {
   double labelNumber = 0;
   double number = ui->label->text().toDouble();

   if (ui->pushButton_add->isChecked()) {
       labelNumber = storedNum + number;
       ui->pushButton_add->setChecked(false);
   } else if (ui->pushButton_subtract->isChecked()) {
       labelNumber = storedNum - number;
       ui->pushButton_subtract->setChecked(false);
   } else if (ui->pushButton_multiply->isChecked()) {
       labelNumber = storedNum * number;
       ui->pushButton_multiply->setChecked(false);
   } else if (ui->pushButton_divide->isChecked()) {
       labelNumber = storedNum / number;
       ui->pushButton_divide->setChecked(false);
   } else if (ui->pushButton_pow->isChecked()) {
       labelNumber = pow(storedNum, number);
       ui->pushButton_pow->setChecked(false);
   }

   trigger = false;
   QString newLabel = QString::number(labelNumber, 'g', 15);
   ui->label->setText(newLabel);
}

void Calculator::binary_operation_pressed() {
   trigger = false;
   QPushButton *button = (QPushButton*)sender();
   storedNum = ui->label->text().toDouble();
   button->setChecked(true);
}

код модуля main.cpp:

#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   Calculator w;
   w.show();

   return a.exec();
}
