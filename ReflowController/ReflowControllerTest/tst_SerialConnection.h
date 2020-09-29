#include "../SerialPortController.h"
#include <QDebug>

#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

using namespace testing;

TEST(SerialConnection, OpenCloseAvailableSerialPorts)
{
    SerialPortController* serialPortController = new SerialPortController;

    QList<QSerialPortInfo> portList = serialPortController->availablePorts();
    qDebug() << "No of ports: " << portList.count();
    QSerialPort serialPort;

    for (const QSerialPortInfo& portInfo : portList)
    {
        qDebug() << "Port name: " << portInfo.portName();
        serialPort.setPort(portInfo);
        bool isPortOpen = serialPort.open(QIODevice::ReadWrite);

        EXPECT_TRUE(isPortOpen);
    }
}
