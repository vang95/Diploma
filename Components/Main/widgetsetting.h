#ifndef WIDGETSETTING_H
#define WIDGETSETTING_H
// Виджет настроект приложения

#include <QtWidgets>

class WidgetSetting : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSetting(QWidget *parent = 0);
    void initializeComponents();
//public slots:
//    void slotShowSetting();
private:
    QPushButton *   m_buttonShowSetting;    // Кнопка для показа изображения
};

#endif // SETTINGWIDGET_H
