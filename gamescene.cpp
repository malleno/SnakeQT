#include "gamescene.h"
#include "QTimer"
GameScene::GameScene(QWidget *parent)
    : QWidget(parent)
    , gameScene_(new QGraphicsScene(QRectF(0, 0, 550, 550)))
    , gameLoop_(new QTimer())
{
    SetupGameLoop();
    CreateSnake();
    CreateFruit();
}

QGraphicsScene* GameScene::GetScenePointer(){
    return gameScene_;
}

void GameScene::addSnakePart(SnakeModel::SnakeNode* snakeNode){
   gameScene_->addItem(snakeNode->scene_veiw_);
}

void GameScene::SetupGameLoop(){
    connect(gameLoop_, SIGNAL(timeout()), this, SLOT(nextFrameSlot()));
    gameLoop_-> start(150);
}

void GameScene::CreateSnake(){
    SnakeModel* snake = new SnakeModel();
    connect(snake, SIGNAL(AddPartOfSnakeToGameScene(SnakeModel::SnakeNode*)), this, SLOT(addSnakePart(SnakeModel::SnakeNode*)));
    connect(this, SIGNAL(moveSnake()), snake, SLOT(nextFrameSlot()));
    connect(this, SIGNAL(makeSnake()), snake, SLOT(makeSnake()));
    connect(this, SIGNAL(ChangeDiractionOfSnake(QKeyEvent*)), snake, SLOT(ChangeDiractionOfHead(QKeyEvent*)));
    connect(snake, SIGNAL(CollideWithSnake()), this, SLOT(CollideWithSnake()));
    connect(snake, SIGNAL(CollideWithFruit(QGraphicsItem*)), this, SLOT(CollideWithFruit(QGraphicsItem*)));
    emit makeSnake();
}

void GameScene::nextFrameSlot(){
    emit moveSnake();
}

void GameScene::KeyPressed(QKeyEvent* event){
    emit ChangeDiractionOfSnake(event);
}

void GameScene::CreateFruit(){
    FruitModel* fruitModel = new FruitModel();
    connect(this, SIGNAL(makeFruit()), fruitModel, SLOT(SpawnFruit()));
    connect(this, SIGNAL(FruitEated(QGraphicsItem*)), fruitModel, SLOT(FruitEated(QGraphicsItem*)));
    connect(fruitModel, SIGNAL(AddFruitToGameScene(QGraphicsPixmapItem*)), SLOT(addFruit(QGraphicsPixmapItem*)));
    emit makeFruit();
}
void GameScene::addFruit(QGraphicsPixmapItem* fruitView){
    gameScene_->addItem(fruitView);
    qDebug() << "FruitAdded";
}

void GameScene::CollideWithFruit(QGraphicsItem* fruitView){
    emit FruitEated(fruitView);
}

void GameScene::CollideWithSnake(){
    qDebug()<<"SNAKE";
}

void GameScene::GameSpeedChange(int speedFacror){
    gameLoop_->setInterval(150 - speedFacror * 10);
}

void GameScene::ResetGame(){
    gameScene_->clear();
    emit makeSnake();
    emit makeFruit();
}
