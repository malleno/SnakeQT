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
    QGraphicsScene* GetScenePointer();
    void CreateSnake();
    void CreateFruit();

private:
    QGraphicsScene* gameScene_;
    QTimer* gameLoop_;

    void SetupGameLoop();
signals:
    void moveSnake();
    void makeSnake();
    void makeFruit();
    void ChangeDiractionOfSnake(QKeyEvent*);
    void FruitEated(QGraphicsItem*);
public slots:
    void addFruit(QGraphicsPixmapItem*);
    void addSnakePart(SnakeModel::SnakeNode*);
    void KeyPressed(QKeyEvent*);
    void nextFrameSlot();
    void CollideWithSnake();
    void CollideWithFruit(QGraphicsItem*);
    void GameSpeedChange(int);
    void ResetGame();
};

#endif // GAMESCENE_H
