#include "snakemodel.h"

bool ItemNotInGameScene(QGraphicsItem* item)
{
    bool result = false;
    QPointF pos = item->pos();
    float rightBorderPixel = 525.0;
    if(pos.x() < 0 || pos.y() < 0 || pos.x() > rightBorderPixel || pos.y() > rightBorderPixel){
        result = true;
    }
    return result;
}



SnakeModel::SnakeModel(QObject *parent):
   QObject(parent),
   body_(),
   diratction_(RIGHT)
{
}



SnakeModel::SnakeNode* SnakeModel::createPartOfSnake()
{
    QPixmap imageOfSnake = QPixmap(":/images/snakePart.png");
    imageOfSnake = imageOfSnake.scaled(QSize(25,25));
    SnakeNode* node = new SnakeNode();
    if(body_.isEmpty()){
        node->nextNodeDiraction_ = diratction_;
    }else{
        node->nextNodeDiraction_ = getTail()->nextNodeDiraction_;
    }
    node->scene_veiw_ = new QGraphicsPixmapItem(imageOfSnake);
    return node;
}



SnakeModel::SnakeNode* SnakeModel::getHead()
{
    return body_.front();
}



SnakeModel::SnakeNode* SnakeModel::getTail()
{
    return body_.back();
}



void SnakeModel::addPartOfSnake()
{
    SnakeNode* node = createPartOfSnake();
    if(!body_.isEmpty()){
        SnakeNode* wasNodeTail = getTail();
        node->scene_veiw_->setPos(wasNodeTail->scene_veiw_->pos());
    }
    body_.push_back(node);
    reverseMovePartOfSnake(node);;
    emit addPartOfSnakeToGameScene(node);
}



void SnakeModel::movePartOfSnake(SnakeNode* part)
{
    if(part->nextNodeDiraction_ == LEFT){
        movePartOfSnakeLeft(part);
    }else if(part->nextNodeDiraction_ == UP){
        movePartOfSnakeUp(part);
    }else if(part->nextNodeDiraction_ == RIGHT){
        movePartOfSnakeRight(part);
    }else if(part->nextNodeDiraction_ == DOWN){
        movePartOfSnakeDown(part);
    }
}



void SnakeModel::reverseMovePartOfSnake(SnakeNode* part)
{
    if(part->nextNodeDiraction_ == RIGHT){
        movePartOfSnakeLeft(part);
    }else if(part->nextNodeDiraction_ == DOWN){
        movePartOfSnakeUp(part);
    }else if(part->nextNodeDiraction_ == LEFT){
        movePartOfSnakeRight(part);
    }else if(part->nextNodeDiraction_ == UP){
        movePartOfSnakeDown(part);
    }
}



void SnakeModel::movePartOfSnakeLeft(SnakeNode* snakeNode)
{
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(-25,0));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(525., sceneViewOfNode->pos().y()));
    }
}



void SnakeModel::movePartOfSnakeUp(SnakeNode* snakeNode)
{
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(0,-25));
    if(ItemNotInGameScene(sceneViewOfNode)){
       sceneViewOfNode->setPos(QPointF(sceneViewOfNode->pos().x(), 525.));
    }
}



void SnakeModel::movePartOfSnakeRight(SnakeNode* snakeNode)
{
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(25,0));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(0, sceneViewOfNode->pos().y()));
    }
}



void SnakeModel::movePartOfSnakeDown(SnakeNode* snakeNode)
{
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(0, 25));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(sceneViewOfNode->pos().x(), 0.));
    }
}



void SnakeModel::nextFrameSlot()
{
    updateNextNodeDiractions();
    for(auto partOfSnake : body_){
        movePartOfSnake(partOfSnake);
    }
    collideChek();
}



void SnakeModel::collideChek()
{
    auto ListOfCollidingItems = getHead()->scene_veiw_->collidingItems();
    if(!ListOfCollidingItems.isEmpty()){
        collide(ListOfCollidingItems);
    }
}



void SnakeModel::collide(QList<QGraphicsItem *> listOfCollidingItems)
{
    auto collidingItem = listOfCollidingItems.back();
    for(auto node : body_){
        if(node->scene_veiw_ == collidingItem){
            emit collideWithSnake();
            return;
        }
    }
    addPartOfSnake();
    emit collideWithFruit(collidingItem);
}



void SnakeModel::makeSnake()
{
    body_.clear();
    addPartOfSnake();
    getTail()->scene_veiw_->setPos(200,200);
    addPartOfSnake();
    addPartOfSnake();
}



void SnakeModel::changeDiractionOfHead(QKeyEvent* event)
{
    if (event->key() == Qt::Key_A) diratction_ = LEFT;
    if (event->key() == Qt::Key_W) diratction_ = UP;
    if (event->key() == Qt::Key_D) diratction_ = RIGHT;
    if (event->key() == Qt::Key_S) diratction_ = DOWN;
}



void SnakeModel::updateNextNodeDiractions()
{
    auto nodeIter = --body_.end();
    auto nextNodeIter = --(--body_.end());
    while (nodeIter != body_.begin()){
        nodeIter.operator*()->nextNodeDiraction_ = nextNodeIter.operator*()->nextNodeDiraction_;
        --nodeIter;
        --nextNodeIter;
    }
    if(reverseDiraction( getHead()->nextNodeDiraction_) != diratction_){
         getHead()->nextNodeDiraction_ = diratction_;
    }
}



SnakeModel::Diraction SnakeModel::reverseDiraction(Diraction diraction)
{
    Diraction result = UP;
    if(diraction == UP){
        result = DOWN;
    }else if(diraction == RIGHT){
        result = LEFT;
    }else if (diraction == DOWN){
        result = UP;
    } else if (diraction == LEFT){
        result = RIGHT;
    }
    return result;
}
