/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtWidgets>

#include "analogclock.h"
//----------------------------------------
AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    topWindow = true;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTrigger()));

    timer->stop();
    countdownSetValue.setHMS(0,10,0);
    countdownTemporaryValue = countdownCurrentValue = countdownSetValue;

    setWindowTitle(tr("Fenikkusu Countdown timer"));
    resize(600, 600);

// Shortcuts
    new QShortcut(QKeySequence(Qt::Key_R), this, SLOT(shortcutReset()));
    new QShortcut(QKeySequence(Qt::Key_Space), this, SLOT(shortcutStartStop()));
    new QShortcut(QKeySequence(Qt::Key_T), this, SLOT(shortcutTopWindow()));
    new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(shortcutAboutDialog()));
    new QShortcut(QKeySequence(Qt::Key_Plus), this, SLOT(shortcutZoomIn()));
    new QShortcut(QKeySequence(Qt::Key_Minus), this, SLOT(shortcutZoomOut()));
    new QShortcut(QKeySequence(Qt::Key_F), this, SLOT(shortcutFullScreen()));

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
void AnalogClock::soundAlert()
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
void AnalogClock::timerTrigger()
{
    if (countdownCurrentValue.minute() == 0 and countdownCurrentValue.second() <= 0)
        timer->stop();
    else
        countdownCurrentValue = countdownCurrentValue.addSecs(-60);

    this->soundAlert();
    this->update();
}
//----------------------------------------
void AnalogClock::shortcutReset()
{
    int ret = QMessageBox::warning(this, tr("Timer reset"),
                                    tr("Are you sure to reset your timer?"),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        countdownCurrentValue = countdownSetValue;
        timer->stop();
    }
}
//----------------------------------------
void AnalogClock::shortcutStartStop()
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
void AnalogClock::shortcutTopWindow()
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
void AnalogClock::shortcutAboutDialog()
{
    QString aboutTxt("Fenikkusu Countdown Timer\n"
                     "Version 0.1 BETA\n"
                     "April 2019\n"
                     "Powered by Qt 5.12\n"
                     "Written by: Amir Hossein Mandegar\n"
                     "\n---- Shortcuts ----\n"
                     "Space: Start/Stop timer\n"
                     "R: Reset timer\n"
                     "D: Digital Timer hide/show\n"
                     "+/-: Resize window\n"
                     "F: Toogle full screen\n"
                     "T: Toggle Always on Top\n");

    QMessageBox::about(this, "About", aboutTxt);
}
//----------------------------------------
void AnalogClock::shortcutZoomOut()
{
    QSize additionalSize(100,100);
    this->resize(this->size() - additionalSize);
}
//----------------------------------------
void AnalogClock::shortcutFullScreen()
{
    if (this->windowState().testFlag(Qt::WindowMaximized))
        this->showNormal();
    else
        this->showMaximized();
}
//----------------------------------------
void AnalogClock::shortcutZoomIn()
{
//    this->showFullScreen();
//    this->resize(400,400);
//    this->showMaximized();

   QSize additionalSize(100,100);
   this->resize(this->size() + additionalSize);
}
//----------------------------------------
void AnalogClock::paintEvent(QPaintEvent *)
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
void AnalogClock::shortcutNumber0()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber1()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber2()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber3()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber4()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber5()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber6()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber7()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber8()
{

}
//----------------------------------------
void AnalogClock::shortcutNumber9()
{

}
//----------------------------------------
