#ifndef NEWTIMEDIALOG_H
#define NEWTIMEDIALOG_H

#include <QDialog>
#include <QLCDNumber>
#include <QDialogButtonBox>
#include <QTime>
#include <QVBoxLayout>
#include <QShortcut>
#include <QLabel>

class newTimeDialog : public QDialog
{
    Q_OBJECT

public:
    newTimeDialog(QWidget *parent);
    int getMinute(void);

protected:
    virtual void showEvent(QShowEvent *event);

private:
    QDialogButtonBox *buttonBox;
    QLCDNumber *lcdNumber;
    QLabel *labelMaxMinute;
    QTime countdownTemporaryValue;

    void shiftLeft(int newNumber);

private slots:
    void shortcutNumber0(void);
    void shortcutNumber1(void);
    void shortcutNumber2(void);
    void shortcutNumber3(void);
    void shortcutNumber4(void);
    void shortcutNumber5(void);
    void shortcutNumber6(void);
    void shortcutNumber7(void);
    void shortcutNumber8(void);
    void shortcutNumber9(void);
};

#endif // NEWTIMEDIALOG_H
