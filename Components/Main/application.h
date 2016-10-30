#ifndef APPLICATION_H
#define APPLICATION_H

#include <QtWidgets>
#include "widgetvisualradiation.h"
#include "Components/UdpClient/updclient.h"
#include "Components/Main/header.h"

namespace setting_application
{
    const int DEFAULT_SIZE_WIDTH_WINDOW = 1024;    // Стандартная ширина окна
    const int DEFAULT_SIZE_HEIHT_WINDOW = 768;     // Стандартная высота окна
}

class Application : public QWidget
{
    Q_OBJECT
public:
    Application(QWidget *parent = 0);
    void initializeComponents();        // Инициализация компонентов
    void createConnections();           // Создание связий по средствам сигналов и слотов между виджетами
private:
    UdpClient *               m_udpClient;                  // Класс приема данных о поверхности
    BasicVisualRadiation *    m_basicVisualRadiation;       // Класс визуализации поверхности
    WidgetVisualRadiation *   m_widgetVisualRadiation;      // Класс манипуляций над поверхностью
private:
    QVBoxLayout *   m_mainLayout;   // Главный Layout приложения
    QHBoxLayout *   m_visualLayout; // Лайаут прорисовки поверхности
};

#endif // APPLICATION_H
