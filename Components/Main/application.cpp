#include "Components/Main/application.h"

Application::Application(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Визуализация лазерного излучения");
    initializeComponents();
    createConnections();
}

void Application::initializeComponents()
{
    m_udpClient = new UdpClient;
    m_basicVisualRadiation = new BasicVisualRadiation;
    m_widgetVisualRadiation = new WidgetVisualRadiation;

    // начало... Временная инициализация
    m_udpClient->setIpAddressServer("192.168.0.4");
    // конец...

    m_mainLayout = new QVBoxLayout;
    m_visualLayout = new QHBoxLayout;

    m_visualLayout->addWidget(m_basicVisualRadiation);
    m_visualLayout->addWidget(m_widgetVisualRadiation);
    m_mainLayout->addLayout(m_visualLayout);

    this->setLayout(m_mainLayout);
}

void Application::createConnections()
{
    connect(m_widgetVisualRadiation, SIGNAL(signalSetModePoints()), m_basicVisualRadiation, SLOT(slotSetModePoints()));
    connect(m_widgetVisualRadiation, SIGNAL(signalSetModeTriangles()), m_basicVisualRadiation, SLOT(slotSetModeTriangles()));
}
