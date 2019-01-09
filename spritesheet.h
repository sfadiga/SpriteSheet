#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QSharedPointer>

//!
//! \brief The SpriteSheet class - a class that draw sprites from a sheet (table) of sprites (rows / columns)
//! the class can be used in QGraphicsView/Scene to animate sprites in sequence or display sprites
//! selected by index.
//! The idea behind this class was 'stoled' from here:
//! https://evileg.com/en/post/92/
//!
class SpriteSheet : public QGraphicsObject
{
    Q_OBJECT
public:
    //!
    //! \brief SpriteSheet - the only available constructor for the class.
    //! \param spriteW - the width of a individual sprite on the sheet
    //! \param spriteH - the height of a individual sprite on the sheet
    //! \param pixmap - the path to the pixmap
    //! \param spriteCount - the total number of sprites available in the sheet
    //! \param spriteIndex - the starting sprite zero as default (from 0..spriteCount - 1)
    //! \param offsetW - the offset width of the sprite (related to the bounding rect)
    //! \param offsetH - the offset height of the sprite (related to the bounding rect)
    //! \param parent - a parent item of the scene, if any
    //!
    SpriteSheet(int spriteW, int spriteH, QString pixpath,
                int spriteCount, int spriteIndex = 0, int x = 0, int y = 0,
                QGraphicsItem *parent = nullptr);

    //!
    //! \brief SpriteSheet - almost same constructor as above, but uses an actual reference to a pixmap obj
    //! \param spriteW
    //! \param spriteH
    //! \param pixpath
    //! \param spriteCount
    //! \param spriteIndex
    //! \param offsetW
    //! \param offsetH
    //! \param parent
    //!
    SpriteSheet(int spriteW, int spriteH, QPixmap pixmap,
                int spriteCount, int spriteIndex = 0, int x = 0, int y = 0,
                QGraphicsItem *parent = nullptr);

    ~SpriteSheet() override = default;
    SpriteSheet() = delete;

    //!
    //! \brief setSpriteIndex - change the current sprite displayed by sprite sheet
    //! \param i - the desired index, if out of bounds will default to 0
    //!
    void setSpriteIndex(int i);

    //!
    //! \brief animate - start the animation of the sprites on the sprite sheet
    //! \param framerate - frame rate in miliseconds (25 ms as default)
    //! \param loop - if the animation should play indefinitely (true)
    //! \param spriteIndex - the starting index of the animation, default is 0
    //! \param removeFromScene - after animation ends remove automatically from scene if true
    //!
    void animate(int framerate = 25, bool loop = false, int spriteIndex = 0, bool removeFromScene = false);

    //!
    //! \brief isAnimating - indicates if a animation is in progress (to users that must avoid using signals/slots)
    //! \return
    //!
    //bool isAnimating();

signals:
    //!
    //! \brief animationStart - this signal is emited once the animation starts
    //!
    void animationStart();

    //!
    //! \brief animationEnd - this signal is emited once when the animation reach its end (if not in loop mode)
    //!
    void animationEnd();


public slots:

    //!
    //! \brief nextSprite - step trought the sprite sheet, it is a slot so it can be used on animations
    //! if you the nextSprite method is called from an update at a game loop (i.e) it can be animated outside of this class
    //! timer.
    //!
    void nextSprite();

    //!
    //! \brief stop - stops the animation
    //!
    void stop();

public:
    //!
    //! \brief paint - overrides the paint from parent
    //! \param painter
    //! \param option
    //! \param widget
    //!
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //!
    //! \brief boundingRect - overrides from parent,
    //! this method defines the boundaries of the item on screen,
    //! it usually will be the size of the individual sprite
    //! \return
    //!
    QRectF boundingRect() const override;

private:

    QString pixmapPath_;

    //!
    //! \brief pixmap_ - the qpixmap will load the image as the sprite sheet
    //!
    //QSharedPointer<QPixmap> pixmap_;
    QPixmap pixmap_;

    //!
    //! \brief spriteW_ - the width of the sprite inside the sprite sheet
    //!
    int spriteW_;

    //!
    //! \brief spriteH_ - the height of the sprite inside the sprite sheet
    //!
    int spriteH_;

    //!
    //! \brief spriteCount_
    //!
    int spriteCount_;

    //!
    //! \brief spriteIndex_ - the index of the current sprite in display (or animation)
    //! the index is zerobased and starts on top left corner running from left to right column
    //! first and then through rows
    //!
    int spriteIndex_;

    //!
    //! \brief x_ - a offset in x of the designated square of the sprite
    //!
    int x_;

    //!
    //! \brief y_ - a offset in y of the designated square of the sprite
    //!
    int y_;

    //!
    //! \brief rows_ - number of rows in the sprite sheet
    //!
    int rows_;

    //!
    //! \brief columns_ - number of columns in the sprite sheet
    //!
    int columns_;

    //!
    //! \brief timer_ - for turning images into QPixmap
    //!
    QTimer timer_;

    //!
    //! \brief loop_ -
    //!
    bool loop_;

    //!
    //! \brief remove_
    //!
    bool remove_;

};


#endif // SPRITE_H
