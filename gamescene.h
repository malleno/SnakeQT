#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <snakemodel.h>
#include <QWidget>
#include <fruitmodel.h>

class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);
    QGraphicsScene* getScenePointer();

signals:
    void moveSnake();
    void makeSnake();
    void makeFruit();
    void changeDiractionOfSnake(QKeyEvent*);
    void fruitEated(QGraphicsItem*);

public slots:
    void addFruit(QGraphicsPixmapItem*);
    void addSnakePart(SnakeModel::SnakeNode*);
    void keyPressed(QKeyEvent*);
    void nextFrameSlot();
    void collideWithSnake();
    void collideWithFruit(QGraphicsItem*);
    void gameSpeedChange(int);
    void resetGame();
private:
    void setupGameLoop();
    void createSnake();
    void createFruit();
private:
    QGraphicsScene* gameScene_;
    QTimer*         gameLoop_;
};

#endif // GAMESCENE_H
