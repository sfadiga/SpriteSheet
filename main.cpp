#include "testview.h"
#include <QApplication>

#include <QPixmapCache>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene(QRectF(0, 0, 640, 480));
    TestView* view = new TestView(scene);
    view->show();
    return a.exec();
}
