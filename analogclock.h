#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>
#include <QTime>
#include "newtimedialog.h"

class AnalogCountdown : public QWidget
{
    Q_OBJECT

public:
    AnalogCountdown(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTime countdownCurrentValue, countdownSetValue;
    QTimer *timer;
    bool topWindow = false;
    newTimeDialog *timeDialog;

    void soundAlert(void);
    void resetTimerValue(int newMinute);

private slots:
    void timerTrigger(void);
    void shortcutReset(void);
    void shortcutStartStop(void);
    void shortcutTopWindow(void);
    void shortcutAboutDialog(void);
    void shortcutZoomIn(void);
    void shortcutZoomOut(void);
    void shortcutFullScreen(void);
    void shortcutSetTimer(void);
};

#endif
