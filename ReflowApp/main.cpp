#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QThread>
#include <QTranslator>

#include "ReflowController/SerialPortController.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::font().setHintingPreference(QFont::PreferVerticalHinting);
    QApplication::setDesktopSettingsAware(false);
    QApplication::setStyle("Windows");
    QApplication::setQuitOnLastWindowClosed(true);

    QThread* serialThread = new QThread;
    serialThread->setObjectName("serialThread");
    SerialPortController* serialPortController = new class SerialPortController("ttyUSB0");

    serialPortController->moveToThread(serialThread);
    serialPortController->open();

    serialThread->start();
    return QApplication::exec();
}
