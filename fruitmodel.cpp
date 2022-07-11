#include "fruitmodel.h"

FruitModel::FruitModel()
{

}

void FruitModel::SpawnFruit(){
    auto fruit = CreateFruit();
    emit AddFruitToGameScene(fruit);
}

QPointF FruitModel::GenerateFruitPosition(){
    srand(time(0));
    int xPixPos = rand()%22*25;
    int yPixPos = rand()%22*25;
    return QPointF(xPixPos, yPixPos);
}

QGraphicsPixmapItem* FruitModel::CreateFruit(){
    QPixmap imageOfFruit = QPixmap(":/images/fruit.png");
    imageOfFruit = imageOfFruit.scaled(QSize(25,25));
    QGraphicsPixmapItem* fruitView = new QGraphicsPixmapItem(imageOfFruit);
    fruitView->setPos(GenerateFruitPosition());
    return fruitView;
}

void FruitModel::FruitEated(QGraphicsItem* fruieView){
    while(!fruieView->collidingItems().isEmpty()) //FREZZING WHEN SNAKE IS BIG
    fruieView->setPos(GenerateFruitPosition());
}
