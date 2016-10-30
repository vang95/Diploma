#include "Components/UdpClient/updclient.h"

using namespace setting_global;

UdpClient::UdpClient(QWidget *parent)
    : QWidget(parent)
{
    UdpClient::initializeDefaultValues();
    UdpClient::initializeSocket();
    UdpClient::createConnections();

    m_testLog = new QTextEdit("=== Start read data ===");
    m_testLog->show();
}

UdpClient::UdpClient(quint16 port_client, const QString &ip_address_server, quint16 port_server, QWidget *perent)
    : QWidget(perent), m_port_this(port_client), m_port_server(port_server), m_ip_address_server(ip_address_server)
{
    UdpClient::initializeSocket();
    UdpClient::createConnections();
}

void UdpClient::initializeDefaultValues()
{
    using namespace default_setting_udpclient;
    m_port_this = DEFAULT_PORT_CLIENT;
    m_port_server = DEFAULT_PORT_SERVER;
    m_indexPacket = 0;
}

void UdpClient::initializeSocket()
{
    m_socket = new QUdpSocket;
    m_socket->bind(m_port_this);
}

void UdpClient::reInitializeSocket()
{
    delete m_socket;
    m_socket = new QUdpSocket;
    m_socket->bind(m_port_this);
    connect(m_socket, SIGNAL(readyRead()), SLOT(slotReadData()));
}

void UdpClient::createConnections()
{
    connect(m_socket, SIGNAL(readyRead()), SLOT(slotReadData()));
    connect(this, SIGNAL(signalUpdateSocket()), SLOT(slotUpdateSocket()));
}

void UdpClient::setPortClient(quint16 port)
{
    m_port_this = port;
    UdpClient::reInitializeSocket();
}

void UdpClient::setPortServer(quint16 port)
{
    m_port_server = port;
}

void UdpClient::setIpAddressServer(const QString &ip_address)
{
    m_ip_address_server = ip_address;
}

QString UdpClient::getIpAddressServer() const
{
    return m_ip_address_server;
}

quint16 UdpClient::getPortClient() const
{
    return m_port_this;
}

quint16 UdpClient::getPortServer() const
{
    return m_port_server;
}

const tArray & UdpClient::getData() const
{
    return m_data;
}

void UdpClient::makeData(QDataStream &inStream)
{
    PacketArray packet;
    inStream >> packet;

    if(packet.index_packet() != m_indexPacket)
        return;

    const PacketArray::tData & data = packet.get_data();
    for(std::size_t i = 0; i < m_data.size_column(); ++i){
        m_data[packet.index_packet()][i] = data[i];
    }

    if(m_indexPacket + 1 == m_data.size_row()){
        m_indexPacket = 0;
        emit signalHaveingData(m_data);
    }
    else
        ++m_indexPacket;
}

void UdpClient::slotReadData()
{
    QHostAddress host_server(m_ip_address_server);
    QByteArray daData;
    QDataStream inStream(&daData, QIODevice::ReadOnly);
    inStream.setVersion(QDataStream::Qt_4_5);

    do
    {
        daData.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(daData.data(), daData.size(), &host_server, &m_port_server);
    }
    while(m_socket->hasPendingDatagrams());
    makeData(inStream);
    m_testLog->append("Read data: element front = " + QString::number(m_indexPacket));
}

void UdpClient::slotUpdateSocket()
{
    reInitializeSocket();
}

void UdpClient::slotUpdateIpAddressServer(const QString &ipAddress)
{
    setIpAddressServer(ipAddress);
}

void UdpClient::slotUpdatePortServer(int port)
{
    m_port_server = port;
}

void UdpClient::slotUpdatePortClient(int port)
{
    m_port_this = port;
    reInitializeSocket();
}
