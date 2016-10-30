#ifndef UPDCLIENT_H
#define UPDCLIENT_H

#include <QtWidgets>
#include <QtNetwork>

#include "Components/Data/array.h"
#include "Components/Main/header.h"
#include "Components/UdpClient/packetarray.h"

namespace default_setting_udpclient
{
    const int DEFAULT_PORT_CLIENT = 2525;       // Стандартный порт клиента
    const int DEFAULT_PORT_SERVER = 2424;       // Стандартный порт сервера
}

using namespace setting_global;

class UdpClient : public QWidget
{
    Q_OBJECT
public:
    using tData = tArray;
public:
    UdpClient(QWidget * parent = 0);
    UdpClient(quint16 port_client, const QString & ip_address_server,
              quint16 port_server, QWidget * perent = 0);

    void initializeDefaultValues();                     // Инициализация компонентов стандартными значениями
    void initializeSocket();                            // Инициализация сокета
    void reInitializeSocket();                          // Переинициализация сокета
    void createConnections();                           // Создание связий между сигналами и слотами

    void setPortClient(quint16 port);                   // Установка порта клиента
    void setPortServer(quint16 port);                   // Установка порта сервера
    void setIpAddressServer(const QString & ip_address);// Установка ip-address сервера

    QString getIpAddressServer() const;                 // Получения ip сервера
    quint16 getPortClient() const;                      // ПОлучение порта клиента
    quint16 getPortServer() const;                      // ПОлучение прта сервера

    void makeData(QDataStream & inStream);              // Создание массива данных из полученных пакетов: данные загружаются по 300 точек, что соответствует одной строки двумерного массива
    const tData & getData() const;                      // Получение уже загруженных данных
signals:
    void signalHaveingData(tData array);// Сигнал, характеризующие, что информация польность загружена и ее мжно обрабатывать
    void signalUpdateSocket();              // Сигнал, характеризующий переинициализацию сокита ( после изменения настроек))
public slots:
    void slotUpdateSocket();                // Слот, характеризующий обновление сокита клиента
    void slotUpdatePortClient(int port);    // Слот обновления порта клиента
    void slotUpdatePortServer(int port);    // Слот обновления порта сервера
    void slotUpdateIpAddressServer(const QString & ipAddress);  // Слот обновления ip сервера
private slots:
    void slotReadData();                // Слот, характеризующие получение данных ерез сокет
private:
    std::size_t     m_indexPacket;          // Индекс текущего пакета
    tData           m_data;                 // Данные

    quint16         m_port_this;            // Порт клиента
    quint16         m_port_server;          // Порт сервера
    QString         m_ip_address_server;    // IP сервера
    QUdpSocket *    m_socket;               // Сокет
    QTextEdit *     m_testLog;              // Лог ===== ВРЕМЕННО для тестирования =====
};

#endif // UPDCLIENT_H
