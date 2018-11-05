#include "testview.h"

#include <QGraphicsScene>
#include <QPixmapCache>

#include "spritesheet.h"

TestView::TestView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView (scene, parent)
{
    rowonly_ = new SpriteSheet(20, 20, ":/sprites/sprite_sheet.png", 15, 0, -10, -10);
    scene->addItem(rowonly_);
    rowonly_->setPos(100, 100);
    rowonly_->animate(25, true);

    smoke_ = new SpriteSheet(130, 125, ":/sprites/smoke_exp.png", 37);
    scene->addItem(smoke_);
    smoke_->setPos(200, 200);
    smoke_->animate(50, true);

    blood_ = new SpriteSheet(480, 480, ":/sprites/blood_exp.png", 9, -10, -20);
    scene->addItem(blood_);
    blood_->setPos(250, 50);
    blood_->animate(150);

    fire_ = new SpriteSheet(130, 125, ":/sprites/fire_exp.png", 37);
    scene->addItem(fire_);
    fire_->setPos(50, 200);
    fire_->animate(25, true, 0, true);

}

TestView::~TestView()
{
    scene()->clear();
    delete blood_;
    delete smoke_;
    delete rowonly_;
    delete fire_;
}
