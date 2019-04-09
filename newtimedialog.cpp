#include "newtimedialog.h"

newTimeDialog::newTimeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Set value"));
    resize(200,200);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    lcdNumber = new QLCDNumber(5);
    lcdNumber->setMinimumHeight(60);

    labelMaxMinute = new QLabel("Set countdown timer minutes (<60)\nMinute:Second");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setMargin(20);
    vLayout->addWidget(labelMaxMinute);
    vLayout->addWidget(lcdNumber);
    vLayout->addWidget(buttonBox);

    setLayout(vLayout);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    new QShortcut(QKeySequence(Qt::Key_0), this, SLOT(shortcutNumber0()));
    new QShortcut(QKeySequence(Qt::Key_1), this, SLOT(shortcutNumber1()));
    new QShortcut(QKeySequence(Qt::Key_2), this, SLOT(shortcutNumber2()));
    new QShortcut(QKeySequence(Qt::Key_3), this, SLOT(shortcutNumber3()));
    new QShortcut(QKeySequence(Qt::Key_4), this, SLOT(shortcutNumber4()));
    new QShortcut(QKeySequence(Qt::Key_5), this, SLOT(shortcutNumber5()));
    new QShortcut(QKeySequence(Qt::Key_6), this, SLOT(shortcutNumber6()));
    new QShortcut(QKeySequence(Qt::Key_7), this, SLOT(shortcutNumber7()));
    new QShortcut(QKeySequence(Qt::Key_8), this, SLOT(shortcutNumber8()));
    new QShortcut(QKeySequence(Qt::Key_9), this, SLOT(shortcutNumber9()));
}
//----------------------------------------
int newTimeDialog::getMinute()
{
    return countdownTemporaryValue.minute();
}
//----------------------------------------
void newTimeDialog::showEvent(QShowEvent *event)
{
    countdownTemporaryValue.setHMS(0,0,0);
    lcdNumber->display(countdownTemporaryValue.toString("mm:ss"));
    QDialog::showEvent(event);
}
//----------------------------------------
void newTimeDialog::shiftLeft(int newNumber)
{
    int newMinute = 0;
    int minuteH = countdownTemporaryValue.minute() % 10;
    if (minuteH < 6)
        newMinute = minuteH * 10 + newNumber;
    else
        newMinute = newNumber;

    countdownTemporaryValue.setHMS(0,newMinute,0);
    lcdNumber->display(countdownTemporaryValue.toString("mm:ss"));
}
//----------------------------------------
void newTimeDialog::shortcutNumber0()
{
    shiftLeft(0);
}
//----------------------------------------
void newTimeDialog::shortcutNumber1()
{
    shiftLeft(1);
}
//----------------------------------------
void newTimeDialog::shortcutNumber2()
{
    shiftLeft(2);
}
//----------------------------------------
void newTimeDialog::shortcutNumber3()
{
    shiftLeft(3);
}
//----------------------------------------
void newTimeDialog::shortcutNumber4()
{
    shiftLeft(4);
}
//----------------------------------------
void newTimeDialog::shortcutNumber5()
{
    shiftLeft(5);
}
//----------------------------------------
void newTimeDialog::shortcutNumber6()
{
    shiftLeft(6);
}
//----------------------------------------
void newTimeDialog::shortcutNumber7()
{
    shiftLeft(7);
}
//----------------------------------------
void newTimeDialog::shortcutNumber8()
{
    shiftLeft(8);
}
//----------------------------------------
void newTimeDialog::shortcutNumber9()
{
    shiftLeft(9);
}
//----------------------------------------
