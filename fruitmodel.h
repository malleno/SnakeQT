#ifndef FRUITMODEL_H
#define FRUITMODEL_H

#include <QObject>
#include <QGraphicsPixmapItem>

class FruitModel : public QObject
{
    Q_OBJECT
public:
    FruitModel();
signals:
    void AddFruitToGameScene(QGraphicsPixmapItem*);
public slots:
    void SpawnFruit();
    void FruitEated(QGraphicsItem*);
private:
    void ChangePosOfFruit();
    QPointF GenerateFruitPosition();
    QGraphicsPixmapItem* CreateFruit();
};

#endif // FRUITMODEL_H
