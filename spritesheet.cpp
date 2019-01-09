#include "spritesheet.h"
#include <QGraphicsScene>


SpriteSheet::SpriteSheet(int spriteW, int spriteH, QString pixpath,
                         int spriteCount, int spriteSelected,
                         int x, int y, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      pixmapPath_(std::move(pixpath)),
      pixmap_(QPixmap(pixmapPath_)),
      spriteW_(spriteW),
      spriteH_(spriteH), spriteCount_(spriteCount),
      spriteIndex_(spriteSelected),
      x_(x),
      y_(y),
      rows_(pixmap_.height() / spriteH_),
      columns_(pixmap_.width() / spriteW_),
      loop_(false),
      remove_(false)
{
    connect(&timer_, &QTimer::timeout, this, &SpriteSheet::nextSprite);
    connect(this, &SpriteSheet::animationEnd, &timer_, &QTimer::stop);
}

SpriteSheet::SpriteSheet(int spriteW, int spriteH, QPixmap pixmap,
                         int spriteCount, int spriteSelected,
                         int x, int y, QGraphicsItem *parent)
    : QGraphicsObject(parent),
      pixmap_(pixmap),
      spriteW_(spriteW),
      spriteH_(spriteH), spriteCount_(spriteCount),
      spriteIndex_(spriteSelected),
      x_(x),
      y_(y),
      rows_(pixmap_.height() / spriteH_),
      columns_(pixmap_.width() / spriteW_),
      loop_(false),
      remove_(false)
{
    connect(&timer_, &QTimer::timeout, this, &SpriteSheet::nextSprite);
    connect(this, &SpriteSheet::animationEnd, &timer_, &QTimer::stop);
}

void SpriteSheet::setSpriteIndex(int i)
{
    if(i >= 0 && i < spriteCount_)
        spriteIndex_ = i;
    else
        spriteIndex_ = 0;
}

void SpriteSheet::animate(int framerate, bool loop, int spriteIndex, bool removeFromScene)
{
    spriteIndex_ = spriteIndex;
    loop_ = loop;
    remove_ = removeFromScene;
    timer_.start(framerate);
    emit animationStart();
}

QRectF SpriteSheet::boundingRect() const
{
    return {static_cast<qreal>(x_), static_cast<qreal>(y_), static_cast<qreal>(spriteW_), static_cast<qreal>(spriteH_)};
}

void SpriteSheet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // calculate the x, y based on the selected index and the total ammount of sprites available
    int row = 0;
    int col = 0;
    for(int i = 0 ; i < (spriteIndex_) ; i++)
    {
        col++;
        if(col > columns_)
        {
            col = 0;
            row++;
            if(row > rows_)
            {
                row = 0;
            }
        }
    }
    int x = col * spriteW_;
    int y = row * spriteH_;
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By setting the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(x_, y_, pixmap_, x, y, spriteW_, spriteH_);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void SpriteSheet::nextSprite()
{
    spriteIndex_++;
    if(spriteIndex_ >= spriteCount_)
    {   // reset the selected sprite index if greater than the number of available sprites
        spriteIndex_ = -1;
        if(!loop_)
        {
            stop();
        }
        if(remove_)
        {
            setParentItem(nullptr);
            scene()->removeItem(this);
            delete this;
        }
    }
    this->update(x_, y_, spriteW_, spriteH_);
}

void SpriteSheet::stop()
{
    timer_.stop();
    emit animationEnd();
}
