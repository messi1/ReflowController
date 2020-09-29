#include "tst_SerialConnection.h"
#include <QCoreApplication>
#include <QTimer>

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    QTimer exitTimer;
    constexpr int timerIntervall = 2000;
    exitTimer.setInterval(timerIntervall);

    QObject::connect(&exitTimer, &QTimer::timeout, &app, &QCoreApplication::quit);
    exitTimer.start();
    app.exec();

    return ret;
}
