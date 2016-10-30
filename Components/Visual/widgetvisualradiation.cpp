#include "Components/Visual/widgetvisualradiation.h"

WidgetVisualRadiation::WidgetVisualRadiation(QWidget * perent)
    : QWidget(perent)
{
    initializeComponents();
    createConnections();
}

void WidgetVisualRadiation::initializeComponents()
{
    m_mainLayout = new QHBoxLayout;
    m_settingLayout = new QVBoxLayout;

    // Инициализация панели настроек выводящего изображения
    QLabel * labelChooseModeView = new QLabel("Вид поверхности");
    QLabel * labelColorBackground = new QLabel("Цвет фона");

    m_buttonSetModePoints = new QPushButton("Точечный режим");
    m_buttonSetModeTriangles = new QPushButton("Режим ландшафта");
    m_listColorBackground = new QComboBox;

    const int MAX_SIZE_WIDTH_WIDGETS_SETTING = 150;       // Максимальный размер виджетов в ширину в настройках
    m_buttonSetModePoints->setMaximumWidth(MAX_SIZE_WIDTH_WIDGETS_SETTING);
    m_buttonSetModeTriangles->setMaximumWidth(MAX_SIZE_WIDTH_WIDGETS_SETTING);
    m_listColorBackground->setMaximumWidth(MAX_SIZE_WIDTH_WIDGETS_SETTING);

    m_settingLayout->addWidget(labelChooseModeView);
    m_settingLayout->addWidget(m_buttonSetModePoints);
    m_settingLayout->addWidget(m_buttonSetModeTriangles);
    m_settingLayout->addWidget(labelColorBackground);
    m_settingLayout->addWidget(m_listColorBackground);
    m_settingLayout->addStretch(1);

    m_mainLayout->addLayout(m_settingLayout);
    this->setLayout(m_mainLayout);

    if(setting_visual_radiation::DEFAULT_MODE_VIEW == setting_visual_radiation::ModeView::mode_points)
        m_buttonSetModePoints->setDisabled(true);
    else
        m_buttonSetModeTriangles->setDisabled(true);
}

void WidgetVisualRadiation::createConnections()
{
    connect(m_buttonSetModePoints, SIGNAL(clicked(bool)), SLOT(slotSetModePoints()));
    connect(m_buttonSetModeTriangles, SIGNAL(clicked(bool)), SLOT(slotSetModeTriangles()));
}

void WidgetVisualRadiation::slotSetModePoints()
{
    m_buttonSetModePoints->setDisabled(true);
    m_buttonSetModeTriangles->setEnabled(true);
    emit signalSetModePoints();
}

void WidgetVisualRadiation::slotSetModeTriangles()
{
    m_buttonSetModeTriangles->setDisabled(true);
    m_buttonSetModePoints->setEnabled(true);
    emit signalSetModeTriangles();
}
