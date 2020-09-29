#include <QDebug>
#include "../SerialController.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(SerialConnection, OpenCloseAvailableSerialPorts)
{
    SerialController *serialController = new SerialController;

    QList<QSerialPortInfo> portList = serialController->availablePorts();
    qDebug() << "No of ports: " << portList.count();
    QSerialPort serialPort;

    for( const QSerialPortInfo& portInfo: portList )
    {
        qDebug() << "Port name: " << portInfo.portName();
        serialPort.setPort(portInfo);
        bool isPortOpen = serialPort.open(QIODevice::ReadWrite);

        EXPECT_TRUE(isPortOpen);
    }
}
