#ifndef WIDGETVISUALRADIATION_H
#define WIDGETVISUALRADIATION_H

#include <QtWidgets>
#include "Components/Visual/basicvisualradiation.h"

// Класс, для взаимодействия пользователя и класса визуализации поверхности
class WidgetVisualRadiation : public QWidget
{
    Q_OBJECT
public:
    WidgetVisualRadiation(QWidget * perent = 0);
    void initializeComponents();                // Инициализация всех компонентов
    void createConnections();                   // Создание связей сигналов и слотов
signals:
    void signalSetModePoints();                 // Сигнал установки режима визуализации по средствам точек
    void signalSetModeTriangles();              // Сигнал установки режима визуализации по средствам ландшафта
private slots:
    void slotSetModePoints();                   // Слот установки режима визуализации по средствам точек
    void slotSetModeTriangles();                // Слот установки режима визуализации по средствам ландшафта
private:
    QHBoxLayout *   m_mainLayout;               // Главный лайаут
    QVBoxLayout *   m_settingLayout;            // Лайаут настроек изображения

    QComboBox *     m_listColorBackground;      // Лист с выбором фонового цвета
    QPushButton *   m_buttonSetModePoints;      // Кнопка выбора просмотра изображения в точечном режиме
    QPushButton *   m_buttonSetModeTriangles;   // Кнопка выбора просмотра изображения в режиме создания поверхности по средствам ландшафта

};

#endif // WIDGETVISUALRADIATION_H
