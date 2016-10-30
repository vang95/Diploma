#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H
// Виджет настроект приложения

#include <QtWidgets>

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = 0);
    void initializeComponents();
//public slots:
//    void slotShowSetting();
private:
    QPushButton *   m_buttonShowSetting;    // Кнопка для показа изображения


};

#endif // SETTINGWIDGET_H
