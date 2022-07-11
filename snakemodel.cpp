#include "snakemodel.h"

bool ItemNotInGameScene(QGraphicsItem* item){
    bool result = false;
    QPointF pos = item->pos();
    float borderPix = 525.;
    if(pos.x() < 0 || pos.y() < 0 || pos.x() > borderPix || pos.y() > borderPix){
        result = true;
    }
    return result;
}

SnakeModel::SnakeModel(QObject *parent) : QObject(parent)
  ,body_()
  , diratction_(RIGHT)
{

}

SnakeModel::SnakeNode* SnakeModel::CreatePartOfSnake(){
    QPixmap imageOfSnake = QPixmap(":/images/redSqare.jpeg");
    imageOfSnake = imageOfSnake.scaled(QSize(25,25));
    SnakeNode* node = new SnakeNode();
    if(body_.isEmpty()){
        node->nextNodeDiraction_ = diratction_;
    }else{
        node->nextNodeDiraction_ = GetTail()->nextNodeDiraction_;
    }
    node->scene_veiw_ = new QGraphicsPixmapItem(imageOfSnake);
    return node;
}

SnakeModel::SnakeNode* SnakeModel::GetHead(){
    return body_.front();
}

SnakeModel::SnakeNode* SnakeModel::GetTail(){
    return body_.back();
}

void SnakeModel::AddPartOfSnake(){
    SnakeNode* node = CreatePartOfSnake();
    if(!body_.isEmpty()){
        SnakeNode* wasNodeTail = GetTail();
        node->scene_veiw_->setPos(wasNodeTail->scene_veiw_->pos());
    }
    body_.push_back(node);
    ReverseMovePartOfSnake(node);;
    emit AddPartOfSnakeToGameScene(node);
}


void SnakeModel::MovePartOfSnake(SnakeNode* part){
    if(part->nextNodeDiraction_ == LEFT){
        MovePartOfSnakeLeft(part);
    }else if(part->nextNodeDiraction_ == UP){
        MovePartOfSnakeUp(part);
    }else if(part->nextNodeDiraction_ == RIGHT){
        MovePartOfSnakeRight(part);
    }else if(part->nextNodeDiraction_ == DOWN){
        MovePartOfSnakeDown(part);
    }
}

void SnakeModel::ReverseMovePartOfSnake(SnakeNode* part){
    if(part->nextNodeDiraction_ == RIGHT){
        MovePartOfSnakeLeft(part);
    }else if(part->nextNodeDiraction_ == DOWN){
        MovePartOfSnakeUp(part);
    }else if(part->nextNodeDiraction_ == LEFT){
        MovePartOfSnakeRight(part);
    }else if(part->nextNodeDiraction_ == UP){
        MovePartOfSnakeDown(part);
    }
}

void SnakeModel::MovePartOfSnakeLeft(SnakeNode* snakeNode){
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(-25,0));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(525., sceneViewOfNode->pos().y()));
    }
}

void SnakeModel::MovePartOfSnakeUp(SnakeNode* snakeNode){
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(0,-25));
    if(ItemNotInGameScene(sceneViewOfNode)){
       sceneViewOfNode->setPos(QPointF(sceneViewOfNode->pos().x(), 525.));
    }
}

void SnakeModel::MovePartOfSnakeRight(SnakeNode* snakeNode){
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(25,0));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(0, sceneViewOfNode->pos().y()));
    }
}

void SnakeModel::MovePartOfSnakeDown(SnakeNode* snakeNode){
    QGraphicsItem* sceneViewOfNode = snakeNode->scene_veiw_;
    sceneViewOfNode->setPos(sceneViewOfNode->pos() + QPointF(0, 25));
    if(ItemNotInGameScene(sceneViewOfNode)){
        sceneViewOfNode->setPos(QPointF(sceneViewOfNode->pos().x(), 0.));
    }
}

void SnakeModel::nextFrameSlot(){
    UpdateNextNodeDiractions();
    for(auto partOfSnake : body_){
        MovePartOfSnake(partOfSnake);
    }
    CollideChek();
}

void SnakeModel::CollideChek(){
    auto ListOfCollidingItems = GetHead()->scene_veiw_->collidingItems();
    if(!ListOfCollidingItems.isEmpty()){
        Collide(ListOfCollidingItems);
    }
}

void SnakeModel::Collide(QList<QGraphicsItem *> listOfCollidingItems){
    auto collidingItem = listOfCollidingItems.back();
    for(auto node : body_){
        if(node->scene_veiw_ == collidingItem){
            emit CollideWithSnake();
            return;
        }
    }
    AddPartOfSnake();
    emit CollideWithFruit(collidingItem);
}
void SnakeModel::makeSnake(){
    body_.clear();
    AddPartOfSnake();
    GetTail()->scene_veiw_->setPos(200,200);
    AddPartOfSnake();
    AddPartOfSnake();
}

void SnakeModel::ChangeDiractionOfHead(QKeyEvent* event){
    if (event->key() == Qt::Key_A) diratction_ = LEFT;
    if (event->key() == Qt::Key_W) diratction_ = UP;
    if (event->key() == Qt::Key_D) diratction_ = RIGHT;
    if (event->key() == Qt::Key_S) diratction_ = DOWN;
}

void SnakeModel::UpdateNextNodeDiractions(){
    auto nodeIter = --body_.end();
    auto nextNodeIter = --(--body_.end());
    while (nodeIter != body_.begin()){
        nodeIter.operator*()->nextNodeDiraction_ = nextNodeIter.operator*()->nextNodeDiraction_;
        --nodeIter;
        --nextNodeIter;
    }
    if(ReverseDiraction( GetHead()->nextNodeDiraction_) != diratction_){
         GetHead()->nextNodeDiraction_ = diratction_;
    }
}

SnakeModel::Diraction SnakeModel::ReverseDiraction(Diraction diraction){
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
