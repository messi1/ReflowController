#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QThread>
#include <QTranslator>

#include "ReflowController/SerialController.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::font().setHintingPreference(QFont::PreferVerticalHinting);
    QApplication::setDesktopSettingsAware(false);
    QApplication::setStyle("Windows");
    QApplication::setQuitOnLastWindowClosed(true);

    QThread* serialThread = new QThread;
    serialThread->setObjectName("serialThread");
    SerialController* serialController = new SerialController("ttyUSB0");

    serialController->moveToThread(serialThread);
    serialController->open();

    serialThread->start();
    return QApplication::exec();
}
