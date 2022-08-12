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
    SnakeNode* getHead();
    SnakeNode* getTail();

public slots:
    void nextFrameSlot();
    void makeSnake();
    void changeDiractionOfHead(QKeyEvent*);

signals:
    void addPartOfSnakeToGameScene(SnakeModel::SnakeNode*);
    void collideWithFruit(QGraphicsItem*);
    void collideWithSnake();

private:
    void addPartOfSnake();
    SnakeNode* createPartOfSnake();

    void movePartOfSnake(SnakeNode*);
    void reverseMovePartOfSnake(SnakeNode*);
    void movePartOfSnakeLeft(SnakeNode*);
    void movePartOfSnakeUp(SnakeNode*);
    void movePartOfSnakeRight(SnakeNode*);
    void movePartOfSnakeDown(SnakeNode*);

    void updateNextNodeDiractions();
    Diraction reverseDiraction(Diraction);

    void collideChek();
    void collide(QList<QGraphicsItem *>);

private:
    QList<SnakeNode*>  body_;
    Diraction          diratction_;
};

#endif // SNAKEMODEL_H
