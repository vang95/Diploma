#include <QApplication>
#include "Components/Main/application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

//    WidgetVisualRadiation * visualRadiation = new WidgetVisualRadiation;
//    visualRadiation->resize(1024, 768);
//    visualRadiation->show();
    return a.exec();
}
