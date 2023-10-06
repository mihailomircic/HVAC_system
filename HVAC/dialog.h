#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <stdlib.h>
#include <QWidget>
#include <QTime>
#include <QMessageBox>
#include <QDateTime>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <wiringPi.h>
#include <QTimer>
#include <QCoreApplication>
#include <QLineEdit>
#include <QRandomGenerator>



class Dialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    


private slots:
    void toggleFan();
    void incrementHeating();
    void decrementHeating();
    void incrementCooling();
    void decrementCooling();
    void updateTime();

private:
    void fanOn();
    void fanOff();
    void heatingOn();
    void heatingOff();
    void coolingOn();
    void coolingOff();
    double getCurrentTemperature();

    const int fanPin = 17;
    const int heatingPin = 27;
    const int coolingPin = 23;

    bool fanActive = false;
    bool heatingActive = false;
    bool coolingActive = false;

    double heatingTarget = 20.0; // Initial target temperatures
    double coolingTarget = 25.0; // Initial target temperatures

    QLabel *heatingLabel;
    QLabel *coolingLabel;
    QLabel *clockLabel;
    QTimer *clockTimer;
    
    QTimer *fanStatusLabel;
    QTimer *heatingStatusLabel;
    QTimer *coolingStatusLabel;
    
};

#endif // DIALOG_H




