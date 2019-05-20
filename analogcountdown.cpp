#include <QtWidgets>

#include "analogcountdown.h"
//----------------------------------------
AnalogCountdown::AnalogCountdown(QWidget *parent)
    : QWidget(parent)
{
    timeDialog = new newTimeDialog(this);

    this->setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    topWindow = true;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTrigger()));

    timer->stop();
    countdownSetValue.setHMS(0,10,0);
    countdownCurrentValue = countdownSetValue;

    setWindowTitle(tr("Countdown timer"));
    resize(600, 600);

// Shortcuts
    new QShortcut(QKeySequence(Qt::Key_R), this, SLOT(shortcutReset()));
    new QShortcut(QKeySequence(Qt::Key_Space), this, SLOT(shortcutStartStop()));
    new QShortcut(QKeySequence(Qt::Key_T), this, SLOT(shortcutTopWindow()));
    new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(shortcutAboutDialog()));
    new QShortcut(QKeySequence(Qt::Key_Plus), this, SLOT(shortcutZoomIn()));
    new QShortcut(QKeySequence(Qt::Key_Minus), this, SLOT(shortcutZoomOut()));
    new QShortcut(QKeySequence(Qt::Key_F), this, SLOT(shortcutFullScreen()));
    new QShortcut(QKeySequence(Qt::Key_S), this, SLOT(shortcutSetTimer()));
}

void AnalogCountdown::resetTimerValue(int newMinute)
{
    countdownSetValue.setHMS(0,newMinute,0);
    countdownCurrentValue = countdownSetValue;
    timer->stop();
}
//----------------------------------------
void AnalogCountdown::soundAlert()
{
// 3 minutes alert
    if (countdownCurrentValue.minute() == 3 and countdownCurrentValue.second() == 0)
        QApplication::beep();

// 2 minutes alert
    if (countdownCurrentValue.minute() == 2 and countdownCurrentValue.second() == 0)
        QApplication::beep();

// 1 minute alert
    if (countdownCurrentValue.minute() == 1 and countdownCurrentValue.second() == 0)
    {
        QApplication::beep();
        this->activateWindow();
    }

// <10 second alert
    if (countdownCurrentValue.minute() == 0 and countdownCurrentValue.second() <= 10)
        QApplication::beep();
}
//----------------------------------------
void AnalogCountdown::timerTrigger()
{
    if (countdownCurrentValue.minute() == 0 and countdownCurrentValue.second() <= 0)
        timer->stop();
    else
        countdownCurrentValue = countdownCurrentValue.addSecs(-1);

    this->soundAlert();
    this->update();
}
//----------------------------------------
void AnalogCountdown::shortcutReset()
{
    int ret = QMessageBox::warning(this, tr("Timer reset"),
                                    tr("Are you sure to reset your timer?"),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::Yes)
        resetTimerValue(countdownSetValue.minute());
}
//----------------------------------------
void AnalogCountdown::shortcutStartStop()
{
    if(timer->isActive())
    {
        timer->stop();
        this->update();
    }
    else
    {
        this->update();
        timer->start(1000);
    }
}
//----------------------------------------
void AnalogCountdown::shortcutTopWindow()
{
    if (!topWindow)
    {
        this->setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
        topWindow = true;
    }
    else
    {
        this->setWindowFlags(windowFlags() ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
        topWindow = false;
    }
    show();
}
//----------------------------------------
void AnalogCountdown::shortcutAboutDialog()
{
    QString aboutTxt("Countdown Timer\n"
                     "Version 0.1 BETA\n"
                     "April 2019\n"
                     "Powered by Qt 5.12\n"
                     "Written by: Amir Hossein Mandegar\n"
                     "\n---- Shortcuts ----\n"
                     "Space: Start/Stop timer\n"
                     "S: Set Timer Value\n"
                     "R: Reset timer\n"
                     "D: Digital Timer hide/show\n"
                     "+/-: Resize window\n"
                     "F: Toogle full screen\n"
                     "T: Toggle Always on Top\n");

    QMessageBox::about(this, "About", aboutTxt);
}
//----------------------------------------
void AnalogCountdown::shortcutZoomOut()
{
    QSize additionalSize(100,100);
    this->resize(this->size() - additionalSize);
}
//----------------------------------------
void AnalogCountdown::shortcutFullScreen()
{
    if (this->windowState().testFlag(Qt::WindowMaximized))
        this->showNormal();
    else
        this->showMaximized();
//        this->showFullScreen();
}
//----------------------------------------
void AnalogCountdown::shortcutSetTimer()
{
    if (timeDialog->exec())
        resetTimerValue(timeDialog->getMinute());
}
//----------------------------------------
void AnalogCountdown::shortcutZoomIn()
{
   QSize additionalSize(100,100);
   this->resize(this->size() + additionalSize);
}
//----------------------------------------
void AnalogCountdown::paintEvent(QPaintEvent *)
{
    const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    const QRectF rectangle(-100.0, -100.0, 200.0, 200.0);

    const QColor hourColor = Qt::darkMagenta;
    const QColor minuteColor = Qt::green;
    const QColor pieColor = Qt::red;
    const QColor pieInactiveColor = Qt::gray;

    int side = qMin(width(), height());

// Painter configuration
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

// Draw Pie
    painter.setPen(Qt::NoPen);
    if (timer->isActive())
        painter.setBrush(pieColor);
    else {
        painter.setBrush(pieInactiveColor);
        timer->stop();
    }

    painter.save();
    double start = 16.0 * 90.0;
    double end = -16.0 * 6.0 * (countdownCurrentValue.minute() + countdownCurrentValue.second() / 60.0);
    painter.drawPie(rectangle, start, end);
    painter.restore();

// Draw hour lines
    painter.setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

// Draw minute arrow
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();
    painter.rotate(6.0 * (countdownCurrentValue.minute() + countdownCurrentValue.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

// Draw minute lines
    painter.setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }

// Digital countdown
    painter.setPen(hourColor);

    QFont font = painter.font();
    font.setPixelSize(32);
    painter.setFont(font);

    painter.drawText(QRect(-40, 20, 100, 50), 0, countdownCurrentValue.toString("mm:ss"));

    font.setPixelSize(4);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(QRect(-100,95, 100, 50), 0, "Press (A) for about page");
}
//----------------------------------------
