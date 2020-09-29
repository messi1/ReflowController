#include "SerialPortController.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaObject>
#include <cassert>

constexpr int timerInterval = 5000;

SerialPortController::SerialPortController(const QString& serialPortName, QObject* parent)
    : QObject(parent), m_standardOutput(stdout)
{
    qRegisterMetaType<QSerialPort::SerialPortError>();

    qDebug() << QSerialPortInfo::standardBaudRates();

    for (const QSerialPortInfo& portInfo : QSerialPortInfo::availablePorts())
    {
        if (portInfo.portName() == serialPortName)
        {
            qDebug() << "Port name: " << portInfo.portName();
            m_serialPort.setPort(portInfo);
            qDebug() << "Port name: " << m_serialPort.portName();
            break;
        }
    }

    assert("Name of the serial port is not available" && m_serialPort.portName().length() > 0);

    m_writeTimer.setSingleShot(true);
    connect(&m_serialPort, &QSerialPort::bytesWritten, this, &SerialPortController::handleBytesWritten);
    connect(&m_serialPort, &QSerialPort::readyRead, this, &SerialPortController::handleReadyRead);
    connect(&m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortController::handleError);
    connect(&m_writeTimer, &QTimer::timeout, this, &SerialPortController::handleWriteTimeout);
    connect(&m_readTimer, &QTimer::timeout, this, &SerialPortController::handleReadTimeout);
}

void SerialPortController::handleReadyRead()
{
    m_readData.append(m_serialPort.readAll());

    if (!m_readTimer.isActive())
    {
        m_readTimer.start(timerInterval);
    }
}

void SerialPortController::handleBytesWritten(qint64 bytes)
{
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_writeData.size())
    {
        m_bytesWritten = 0;
        m_standardOutput << QObject::tr("Data successfully sent to port %1").arg(m_serialPort.portName())
                         << "\n";
        QCoreApplication::quit();
    }
}

void SerialPortController::handleWriteTimeout()
{
    m_standardOutput << QObject::tr("Operation timed out for port %1, error: %2")
                            .arg(m_serialPort.portName())
                            .arg(m_serialPort.errorString())
                     << "\n";
    QCoreApplication::exit(1);
}

void SerialPortController::handleReadTimeout()
{
    if (m_readData.isEmpty())
    {
        m_standardOutput << QObject::tr("No data was currently available "
                                        "for reading from port %1")
                                .arg(m_serialPort.portName())
                         << "\n";
    }
    else
    {
        m_standardOutput
            << QObject::tr("Data successfully received from port %1").arg(m_serialPort.portName()) << "\n";
        m_standardOutput << m_readData << "\n";
    }

    QCoreApplication::quit();
}

void SerialPortController::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::WriteError)
    {
        m_standardOutput << QObject::tr("An I/O error occurred while writing"
                                        " the data to port %1, error: %2")
                                .arg(m_serialPort.portName())
                                .arg(m_serialPort.errorString())
                         << "\n";
        QCoreApplication::exit(1);
    }

    if (serialPortError == QSerialPort::ReadError)
    {
        m_standardOutput << QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                                .arg(m_serialPort.portName())
                                .arg(m_serialPort.errorString())
                         << "\n";
        QCoreApplication::exit(1);
    }
}

void SerialPortController::open()
{
    // TODO: Set Baudrate before open the port.
    bool isSerialPortOpen = m_serialPort.open(QIODevice::ReadWrite);
    qDebug() << "Serial port " << m_serialPort.portName() << " is " << (isSerialPortOpen ? "open" : "close");
    //    QString name("/dev/ttyS0");
    //    m_serialPort.setPortName(name);
    //    m_serialPort.setBaudRate(9600);
    //    m_serialPort.open(QIODevice::ReadWrite);
    //    m_readTimer.start(5000);
}

void SerialPortController::write(const QByteArray& writeData)
{
    if (m_serialPort.isOpen())
    {
        m_writeData = writeData;

        const qint64 bytesWritten = m_serialPort.write(writeData);

        if (bytesWritten == -1)
        {
            m_standardOutput << QObject::tr("Failed to write the data to port %1, error: %2")
                                    .arg(m_serialPort.portName())
                                    .arg(m_serialPort.errorString())
                             << "\n";
            QCoreApplication::exit(1);
        }
        else if (bytesWritten != m_writeData.size())
        {
            m_standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2")
                                    .arg(m_serialPort.portName())
                                    .arg(m_serialPort.errorString())
                             << "\n";
            QCoreApplication::exit(1);
        }

        m_writeTimer.start(timerInterval);
    }
}

void SerialPortController::close()
{
    if (m_serialPort.isOpen())
    {
        m_serialPort.close();
    }
}

QList<QSerialPortInfo> SerialPortController::availablePorts()
{
    return QSerialPortInfo::availablePorts();
}
