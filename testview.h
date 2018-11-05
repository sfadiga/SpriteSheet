#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QGraphicsView>

class SpriteSheet;

//!
//! \brief The TestView class - a view used for the test of the sprite animations
//!
class TestView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit TestView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~TestView();

private:

    SpriteSheet* blood_;

    SpriteSheet* smoke_;

    SpriteSheet* rowonly_;

    SpriteSheet* fire_;
};

#endif // TESTVIEW_H
