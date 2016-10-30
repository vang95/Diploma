#ifndef BASICVISUALRADIATION_H
#define BASICVISUALRADIATION_H

#pragma comment(lib, "opengl32.lib")

#include <QtWidgets>
#include <QGLWidget>
#include <QMouseEvent>
#include <QQueue>
#include <QMap>

#include "Components/Data/bufferdata.h"
#include "Components/Main/header.h"

class BasicVisualRadiation;
namespace setting_visual_radiation
{
    enum class ModeView{mode_points, mode_triangles};       // Режимы визаулизации изображения: по средствам точек, по средствам ландшафта
    const int       DEFAULT_SIZE_WIDHT_WINDOW = 800;        // Размер ширины окна виджета
    const int       DEFAULT_SIZE_HEIGHT_WINDOW = 600;       // Размер высоты окна виджета
    const int       MINIMUM_SIZE_WIDHT_WINDOW = 800;        // Минимальный размер окна виджета в ширину
    const int       MINIMUM_SIZE_HEIGHT_WINDOW = 600;       // Минимальный размер окна виджета в высоту
    const QColor    DEFAULT_COLOR_BACKGROUND = Qt::black;   // Стандартный цвет фона
    const QColor    DEFAULT_COLOR_SURFACE = Qt::red;        // Стандартный цвет поверхности
    const int       DEFAULT_SIZE_POINST = 2;                // Стандартный размер точек
    const ModeView  DEFAULT_MODE_VIEW = ModeView::mode_points;// Стандартный режим вывода изображения
}

using namespace setting_global;

class BasicVisualRadiation : public QGLWidget
{
    Q_OBJECT
public:
    using tMapColor = QMap<QString, QColor>;
    using tBuffer = QQueue<tArray>;
    BasicVisualRadiation(QWidget * perent = 0);
protected:
    void initializeComponents();        // Инициализация всех сопутствующих компонентов
    virtual void initializeGL();        // Инициализация OpenGl
                                        // Установка размеров окна виджета
    virtual void resizeGL(int widht = setting_visual_radiation::DEFAULT_SIZE_WIDHT_WINDOW,
                          int heigth = setting_visual_radiation::DEFAULT_SIZE_HEIGHT_WINDOW);
    virtual void paintGL();                         // Визуализация всего виджета
    virtual void mousePressEvent(QMouseEvent * pe); // Реагирование виджета при нажатии мышки
    virtual void mouseMoveEvent(QMouseEvent * pe);  // Реагирования виджета при движении мышки
public slots:
    void slotUpdateSurface(tArray array);   // Слот обновление поверхности
    void slotSetModePoints();               // Слот установки режима визуализации по средствам точек
    void slotSetModeTriangles();            // Слот установки режима визуализации по средствам ландшафта
    void slotSetColorBackground(const QColor & colorBackground);    // Слот установки цвета фона
private:
    GLuint createSurface();             // Создание всей поверхности
    void createAxises();                // Создание осей x, y, z
    void createModePoints(const tArray & dataSurface);      // Формирование поверхности по средствам точек
    void createModeTriangles(const tArray & dataSurface);   // Формирование поверхности по средствам ландшафта(через треугольники)
private:
    GLuint          m_nSurface;         // Положение поверхности в прастранстве
    GLfloat         m_xRotate;          // Положение поверхности по оси x
    GLfloat         m_yRotate;          // Положение поверхности по оси y
    QPoint          m_Position;         // Позиция поверхности

    tMapColor       m_mapColors;        // Список возможных цветов
    QColor          m_colorBackground;  // Цвет фона
    QColor          m_colorSurface;     // Цвет поверхности

    GLuint          m_sizePoint;        // Размер точек
    setting_visual_radiation::ModeView  m_modeView; // Режим прорисовки поверхности(через точки или ландшафта)

    GLfloat         m_ratio_x;          // Коофициент значений по оси x
    GLfloat         m_ratio_y;          // Коофициент значений по оси y
    GLfloat         m_ratio_z;          // Коофициент значений по оси z
    tBuffer         m_bufferDataSurface;// Буффер данных о поверхности.
};

#endif // BASICVISUALRADIATION_H
