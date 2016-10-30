#include "Components/Visual/basicvisualradiation.h"

using namespace setting_global;

BasicVisualRadiation::BasicVisualRadiation(QWidget * perent)
    : QGLWidget(perent)
{
    initializeComponents();
}

void BasicVisualRadiation::initializeComponents()
{
    m_colorBackground = setting_visual_radiation::DEFAULT_COLOR_BACKGROUND;
    m_colorSurface = setting_visual_radiation::DEFAULT_COLOR_SURFACE;
    m_modeView = setting_visual_radiation::DEFAULT_MODE_VIEW;
    m_sizePoint = setting_visual_radiation::DEFAULT_SIZE_POINST;

    // Временная инициализация кофициентов точек вручную, потом я буду их высчитывать
    m_ratio_y = GLfloat(SIZE_Y) / GLfloat(1.0);
    m_ratio_x = m_ratio_y / GLfloat(SIZE_X);
    m_ratio_z = m_ratio_y / GLfloat(SIZE_Z);

    this->setMinimumWidth(setting_visual_radiation::MINIMUM_SIZE_WIDHT_WINDOW);
    this->setMinimumHeight(setting_visual_radiation::MINIMUM_SIZE_HEIGHT_WINDOW);
}

void BasicVisualRadiation::initializeGL()
{
    qglClearColor(m_colorBackground);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_FLAT);
    m_nSurface = createSurface();
}

void BasicVisualRadiation::resizeGL(int widht, int height)
{
    GLint   x = 0;
    GLint   y = -10;
    glViewport(x, y, GLint(widht), GLint(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
}

void BasicVisualRadiation::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_TRIANGLES);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, 0.0);

    glRotatef(m_xRotate, 1.0, 0.0, 0.0);
    glRotatef(m_yRotate, 0.0, 1.0, 0.0);

    glCallList(m_nSurface);
}

void BasicVisualRadiation::mousePressEvent(QMouseEvent * pe)
{
    m_Position = pe->pos();
}

void BasicVisualRadiation::mouseMoveEvent(QMouseEvent * pe)
{
    m_xRotate += 180 * (GLfloat)(pe->y() - m_Position.y()) / height();
    m_yRotate += 180 * (GLfloat)(pe->x() - m_Position.x()) / width();
    updateGL();
    m_Position = pe->pos();
}

void BasicVisualRadiation::createAxises()
{
    // Сделать цвета осей управляемыми
    QColor  colorAxisCenter(Qt::white); // Цвет центра
    QColor  colorAxisX(Qt::white);      // Цвет оси x
    QColor  colorAxisY(Qt::yellow);     // Цвет оси y
    QColor  colorAxisZ(Qt::blue);       // Цвет оси z
    GLuint  sizePointCenter = 4;        // Размер точки центра
    GLuint  sizePointAxis = 2;          // Размер точек осей
    GLfloat sizeStepPointsAxis = GLfloat(0.05);  // шаг между точками оси
    GLfloat MAX_SIZE_AXIS = 2.0;        // Максимальная длинна оси

    // Формирования цента
    qglColor(colorAxisCenter);
    glPointSize(sizePointCenter);
    glBegin(GL_POINTS);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    // Формирование оси x
    qglColor(colorAxisX);
    glPointSize(sizePointAxis);
    glBegin(GL_POINTS);
    for(GLfloat x = 0.0; x < MAX_SIZE_AXIS; x += sizeStepPointsAxis)
        glVertex3f(x, 0.0, 0.0);
    glEnd();

    // Формирование оси y
    qglColor(colorAxisY);
    glPointSize(sizePointAxis);
    glBegin(GL_POINTS);
    for(GLfloat y = 0.0; y < MAX_SIZE_AXIS; y += sizeStepPointsAxis)
        glVertex3f(0.0, y, 0.0);
    glEnd();

    // Формирование оси z
    qglColor(colorAxisZ);
    glPointSize(sizePointAxis);
    glBegin(GL_POINTS);
    for(GLfloat z = 0.0; z < MAX_SIZE_AXIS; z += sizeStepPointsAxis)
        glVertex3f(0, 0, z);
    glEnd();
}

void BasicVisualRadiation::createModePoints(const tArray & dataSurface)
{
    qglColor(m_colorSurface);
    glBegin(GL_POINTS);
        for(GLfloat X = 0.0; X < dataSurface.size_row(); ++X)
        {
            for(GLfloat Z = 0.0; Z < dataSurface.size_column(); ++Z){
                GLfloat xReault = X * m_ratio_x;
                GLfloat zResult = Z * m_ratio_z;
                GLfloat yResult = dataSurface[int(Z)][int(X)] * m_ratio_y;
                glVertex3f(xReault, yResult, zResult);
            }
        }
    glEnd();
}

void BasicVisualRadiation::createModeTriangles(const tArray & dataSurface)
{
    qglColor(m_colorSurface);
    for(GLfloat Z = 0.0; Z < dataSurface.size_column(); ++Z)
    {
        GLfloat zTemp = Z;
        glBegin(GL_TRIANGLE_STRIP);
            for(GLfloat X = 0.0; X < dataSurface.size_row(); ++X)
            {
                GLfloat xReault = X * m_ratio_x;
                GLfloat zResult = zTemp * m_ratio_z;
                GLfloat yResult = dataSurface[int(zTemp)][int(X)] * m_ratio_y;

                glVertex3f(xReault, yResult, zResult);
                ++zTemp;
                xReault = X * m_ratio_x;
                zResult = zTemp * m_ratio_z;
                yResult = dataSurface[int(zTemp)][int(X)] * m_ratio_y;
                glVertex3f(xReault, yResult, zResult);
                --zTemp;
            }
        glEnd();
    }
}

GLuint BasicVisualRadiation::createSurface()
{
    using namespace setting_visual_radiation;
    GLuint n = glGenLists(1);
    glNewList(n, GL_COMPILE);
        createAxises();             // Создание осей x, y, z
        if(!m_bufferDataSurface.isEmpty()){
            if(m_modeView == ModeView::mode_points)
                createModePoints(m_bufferDataSurface.front());
            else if(m_modeView == ModeView::mode_triangles)
                createModeTriangles(m_bufferDataSurface.front());
            m_bufferDataSurface.pop_front();
        }
    glEndList();
    return n;
}

void BasicVisualRadiation::slotSetModePoints()
{
    m_modeView = setting_visual_radiation::ModeView::mode_points;
}

void BasicVisualRadiation::slotSetModeTriangles()
{
    m_modeView = setting_visual_radiation::ModeView::mode_triangles;
}

void BasicVisualRadiation::slotUpdateSurface(tArray array)
{
    m_bufferDataSurface.push_back(array);
    m_nSurface = createSurface();
    glCallList(m_nSurface);
    updateGL();
}

void BasicVisualRadiation::slotSetColorBackground(const QColor &colorBackground)
{
    m_colorBackground = colorBackground;
}
