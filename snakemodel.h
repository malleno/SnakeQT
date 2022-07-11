#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QWidget>

class SnakeModel: public QObject
{
    Q_OBJECT
    enum Diraction {LEFT, UP, RIGHT, DOWN};


public:
    struct SnakeNode : public QObject{
        Diraction nextNodeDiraction_;
        QGraphicsPixmapItem* scene_veiw_;
    };
    SnakeModel(QObject* parent = nullptr);
    SnakeNode* GetHead();
    SnakeNode* GetTail();
public slots:
    void nextFrameSlot();
    void makeSnake();
    void ChangeDiractionOfHead(QKeyEvent*);

signals:
    void AddPartOfSnakeToGameScene(SnakeModel::SnakeNode*);
    void CollideWithFruit(QGraphicsItem*);
    void CollideWithSnake();
private:
    QList<SnakeNode*> body_;
    Diraction diratction_;

    void AddPartOfSnake();
    SnakeNode* CreatePartOfSnake();
    void MovePartOfSnake(SnakeNode*);
    void ReverseMovePartOfSnake(SnakeNode*);
    void MovePartOfSnakeLeft(SnakeNode*);
    void MovePartOfSnakeUp(SnakeNode*);
    void MovePartOfSnakeRight(SnakeNode*);
    void MovePartOfSnakeDown(SnakeNode*);
    void UpdateNextNodeDiractions();
    Diraction ReverseDiraction(Diraction);
    void CollideChek();
    void Collide(QList<QGraphicsItem *>);

};

#endif // SNAKEMODEL_H
