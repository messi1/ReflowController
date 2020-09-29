#pragma once

#include <QByteArray>
#include <QList>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>
#include <QTimer>

class SerialController : public QObject
{
    Q_OBJECT

public:
    explicit SerialController() = default;
    explicit SerialController(const QString& serialPortName, QObject *parent = nullptr);
    void open();
    void read(const QByteArray &writeData);
    void write(const QByteArray &writeData);
    void close();
    QList<QSerialPortInfo> availablePorts();

private slots:
    void handleBytesWritten(qint64 bytes);
    void handleReadyRead();
    void handleWriteTimeout();
    void handleReadTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
    QByteArray  m_writeData;
    QByteArray  m_readData;
    QTextStream m_standardOutput;
    qint64 m_bytesWritten = 0;
    QTimer m_readTimer;
    QTimer m_writeTimer;
};
