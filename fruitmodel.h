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
    void addFruitToGameScene(QGraphicsPixmapItem*);

public slots:
    void spawnFruit();
    void fruitEated(QGraphicsItem*);

private:
    void changePosOfFruit();
    QPointF generateFruitPosition();
    QGraphicsPixmapItem* createFruit();
};

#endif // FRUITMODEL_H
