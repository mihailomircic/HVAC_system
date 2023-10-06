#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QWidget(parent) {
    // Initialize WiringPi
    wiringPiSetup();
    pinMode(fanPin, OUTPUT);
    pinMode(heatingPin, OUTPUT);
    pinMode(coolingPin, OUTPUT);
    fanOff();
    heatingOff();
    coolingOff();

    setupUi(this);
    // UI Setup
    QPushButton *fanButton = new QPushButton("Fan");
  
    QLabel *heatingTitle = new QLabel("Heating Control");
    heatingTitle->setAlignment(Qt::AlignCenter);
    heatingLabel = new QLabel("Target Temperature: " + QString::number(heatingTarget) + "°C");
    QPushButton *heatingIncrementButton = new QPushButton("Increment Heating");
    QPushButton *heatingDecrementButton = new QPushButton("Decrement Heating");
    
    QLabel *coolingTitle = new QLabel("Cooling Control");
    coolingTitle->setAlignment(Qt::AlignCenter);
    coolingLabel = new QLabel("Target Temperature: " + QString::number(coolingTarget) + "°C");
    QPushButton *coolingIncrementButton = new QPushButton("Increment Cooling");
    QPushButton *coolingDecrementButton = new QPushButton("Decrement Cooling");
  
  
    QTimer *clockTimer = new QTimer(this);
    updateTime();
    clockTimer->start(1000);    
    
    
    
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(fanButton);
    layout->addWidget(heatingTitle);
    layout->addWidget(heatingLabel);
    layout->addWidget(heatingIncrementButton);
    layout->addWidget(heatingDecrementButton);
    layout->addWidget(coolingTitle);
    layout->addWidget(coolingLabel);
    layout->addWidget(coolingIncrementButton);
    layout->addWidget(coolingDecrementButton);
    
    layout->addWidget(fanStatusLabel);
    layout->addWidget(heatingStatusLabel);
    layout->addWidget(coolingStatusLabel);


    layout->addWidget(clockLabel);
    
    setLayout(layout);

    fanStatusLabel = new QLabel("Fan: OFF");
    heatingStatusLabel = new QLabel("Heating: OFF");
    coolingStatusLabel = new QLabel("Cooling: OFF");
    
    
    // Connect signals and slots
    connect(fanButton, &QPushButton::clicked, this, &Dialog::toggleFan);
    connect(heatingIncrementButton, &QPushButton::clicked, this, &Dialog::incrementHeating);
    connect(heatingDecrementButton, &QPushButton::clicked, this, &Dialog::decrementHeating);
    connect(coolingIncrementButton, &QPushButton::clicked, this, &Dialog::incrementCooling);
    connect(coolingDecrementButton, &QPushButton::clicked, this, &Dialog::decrementCooling);
      
    clockLabel->setAlignment(Qt::AlignCenter);
    updateTime();
    clockTimer->start(1000);


}

void Dialog::toggleFan() {
    fanActive = !fanActive;

    if (fanActive) {
        fanOn();
    } else {
        fanOff();
    }
}

void Dialog::incrementHeating() {
    heatingTarget += 1.0; // Increment heating target by 1°C
    heatingLabel->setText("Heating Target: " + QString::number(heatingTarget) + "°C");
}

void Dialog::decrementHeating() {
    heatingTarget -= 1.0; // Decrement heating target by 1°C
    heatingLabel->setText("Heating Target: " + QString::number(heatingTarget) + "°C");
}

void Dialog::incrementCooling() {
    coolingTarget += 1.0; // Increment cooling target by 1°C
    coolingLabel->setText("Cooling Target: " + QString::number(coolingTarget) + "°C");
}

void Dialog::decrementCooling() {
    coolingTarget -= 1.0; // Decrement cooling target by 1°C
    coolingLabel->setText("Cooling Target: " + QString::number(coolingTarget) + "°C");
}

void Dialog::fanOn() {
    digitalWrite(fanPin, HIGH);
    fanStatusLabel->setText("Fan: ON");
}

void Dialog::fanOff() {
    digitalWrite(fanPin, LOW);
    fanStatusLabel->setText("Fan: OFF");
}

void Dialog::heatingOn() {
    digitalWrite(heatingPin, HIGH);
    heatingStatusLabel->setText("Heating: ON");
}

void Dialog::heatingOff() {
    digitalWrite(heatingPin, LOW);
    heatingStatusLabel->setText("Heating: OFF");
}

void Dialog::coolingOn() {
    digitalWrite(coolingPin, HIGH);
    coolingStatusLabel->setText("Cooling: ON");
}

void Dialog::coolingOff() {
    digitalWrite(coolingPin, LOW);
    coolingStatusLabel->setText("Cooling: OFF");
}
    
double Dialog::getCurrentTemperature()
{
    double randomDec = QRandomGenerator::global()->bounded(10) / 10.0;
    return 20.0 + randomDec;
}

void Dialog::updateTime() 
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeText = currentTime.toString("hh:mm:ss");
    clockLabel->setText("Current Time: " + timeText);
}
  

    
