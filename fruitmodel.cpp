#include "fruitmodel.h"

FruitModel::FruitModel()
{
}



void FruitModel::spawnFruit()
{
    auto fruit = createFruit();
    emit addFruitToGameScene(fruit);
}



QPointF FruitModel::generateFruitPosition()
{
    srand(time(0));
    int xPixPos = rand()%22*25;
    int yPixPos = rand()%22*25;
    return QPointF(xPixPos, yPixPos);
}



QGraphicsPixmapItem* FruitModel::createFruit()
{
    QPixmap imageOfFruit = QPixmap(":/images/fruit.png");
    imageOfFruit = imageOfFruit.scaled(QSize(25,25));
    QGraphicsPixmapItem* fruitView = new QGraphicsPixmapItem(imageOfFruit);
    fruitView->setPos(generateFruitPosition());
    return fruitView;
}



void FruitModel::fruitEated(QGraphicsItem* fruieView)
{
    while(!fruieView->collidingItems().isEmpty()) //FREZZING WHEN SNAKE IS BIG
    fruieView->setPos(generateFruitPosition());
}
