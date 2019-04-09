#include "newtimedialog.h"

newTimeDialog::newTimeDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Set countdown value"));

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

//    new QShortcut(QKeySequence(Qt::Key_0), this, SLOT(shortcutNumber0()));
//    new QShortcut(QKeySequence(Qt::Key_1), this, SLOT(shortcutNumber1()));
//    new QShortcut(QKeySequence(Qt::Key_2), this, SLOT(shortcutNumber2()));
//    new QShortcut(QKeySequence(Qt::Key_3), this, SLOT(shortcutNumber3()));
//    new QShortcut(QKeySequence(Qt::Key_4), this, SLOT(shortcutNumber4()));
//    new QShortcut(QKeySequence(Qt::Key_5), this, SLOT(shortcutNumber5()));
//    new QShortcut(QKeySequence(Qt::Key_6), this, SLOT(shortcutNumber6()));
//    new QShortcut(QKeySequence(Qt::Key_7), this, SLOT(shortcutNumber7()));
//    new QShortcut(QKeySequence(Qt::Key_8), this, SLOT(shortcutNumber8()));
//    new QShortcut(QKeySequence(Qt::Key_9), this, SLOT(shortcutNumber9()));
}
//----------------------------------------
void newTimeDialog::addAndShiftLeft(int newNumber)
{
    int newMinute = (countdownTemporaryValue.minute() % 10) * 10  + newNumber;
//    qDebug() << newMinute;
//    countdownTemporaryValue.setHMS(0,newMinute,0);
}
//----------------------------------------
void newTimeDialog::shortcutNumber0()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber1()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber2()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber3()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber4()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber5()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber6()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber7()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber8()
{

}
//----------------------------------------
void newTimeDialog::shortcutNumber9()
{

}

