#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Find the serial port name
    QString serialPortName;
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) {
        if (/*!portInfo.isNull()*/1){
            serialPortName = portInfo.portName();
            qDebug()<<"null olmayan var " << serialPortName;
        }
        else
            qDebug() << "No available serial port.";
      //return 1;

    }

//    for (auto &x : QSerialPortInfo::availablePorts())
//    {
//        qDebug () << x.portName();
//    }
    // Set up the serial port

    QSerialPort serial, s2;
    serial.setPortName("/dev/ttys001");
    serial.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    s2.setPortName("/dev/ttys002");
    s2.setBaudRate(QSerialPort::Baud115200); // Adjust the baud rate as per your requirements
    s2.setDataBits(QSerialPort::Data8);
    s2.setParity(QSerialPort::NoParity);
    s2.setStopBits(QSerialPort::OneStop);
    s2.setFlowControl(QSerialPort::NoFlowControl);



    // Open the serial port
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();

        return 1;
    }
    if (!s2.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open serial port:" << serial.errorString();
        return 1;
    }

    qDebug() << "Serial port opened.Port name is " << ""<<" Sending and receiving data...";

    // Send data to the serial port
    QString sendData = " dogru yapar ";
    QByteArray sendDataArray = sendData.toUtf8();
    qint64 bytesWritten = serial.write(sendDataArray);

    if (bytesWritten == -1) {
        qDebug() << "Failed to write data:" << serial.errorString();
    } else {
        qDebug() << "Data sent successfully Bytes written: " << bytesWritten;

    }




    // Read data from the serial port
    while (serial.waitForReadyRead(100)) { // Wait for data to be available for 100 milliseconds
        QByteArray data = s2.readAll();
        qDebug() << "Received data:" << data;
    }


serial.close(); // Close the serial port when done
  s2.close();
    return a.exec();



}











