#include "gamescene.h"
#include "QTimer"

GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    gameScene_(new QGraphicsScene(QRectF(0, 0, 550, 550))),
    gameLoop_(new QTimer())
{
    setupGameLoop();
    createSnake();
    createFruit();
}



QGraphicsScene* GameScene::getScenePointer()
{
    return gameScene_;
}



void GameScene::addSnakePart(SnakeModel::SnakeNode* snakeNode)
{
   gameScene_->addItem(snakeNode->scene_veiw_);
}



void GameScene::setupGameLoop()
{
    connect(gameLoop_, SIGNAL(timeout()), this, SLOT(nextFrameSlot()));
    gameLoop_-> start(150);
}



void GameScene::createSnake()
{
    SnakeModel* snake = new SnakeModel();
    connect(snake, SIGNAL(AddPartOfSnakeToGameScene(SnakeModel::SnakeNode*)), this, SLOT(addSnakePart(SnakeModel::SnakeNode*)));
    connect(this, SIGNAL(moveSnake()), snake, SLOT(nextFrameSlot()));
    connect(this, SIGNAL(makeSnake()), snake, SLOT(makeSnake()));
    connect(this, SIGNAL(changeDiractionOfSnake(QKeyEvent*)), snake, SLOT(ChangeDiractionOfHead(QKeyEvent*)));
    connect(snake, SIGNAL(collideWithSnake()), this, SLOT(collideWithSnake()));
    connect(snake, SIGNAL(collideWithFruit(QGraphicsItem*)), this, SLOT(collideWithFruit(QGraphicsItem*)));
    emit makeSnake();
}



void GameScene::nextFrameSlot()
{
    emit moveSnake();
}



void GameScene::keyPressed(QKeyEvent* event)
{
    emit changeDiractionOfSnake(event);
}



void GameScene::createFruit()
{
    FruitModel* fruitModel = new FruitModel();
    connect(this, SIGNAL(makeFruit()), fruitModel, SLOT(SpawnFruit()));
    connect(this, SIGNAL(fruitEated(QGraphicsItem*)), fruitModel, SLOT(fruitEated(QGraphicsItem*)));
    connect(fruitModel, SIGNAL(AddFruitToGameScene(QGraphicsPixmapItem*)), SLOT(addFruit(QGraphicsPixmapItem*)));
    emit makeFruit();
}



void GameScene::addFruit(QGraphicsPixmapItem* fruitView)
{
    gameScene_->addItem(fruitView);
}



void GameScene::collideWithFruit(QGraphicsItem* fruitView)
{
    emit fruitEated(fruitView);
}



void GameScene::collideWithSnake()
{
    qDebug()<<"SNAKE";
}



void GameScene::gameSpeedChange(int speedFacror)
{
    gameLoop_->setInterval(150 - speedFacror * 10);
}



void GameScene::resetGame()
{
    gameScene_->clear();
    emit makeSnake();
    emit makeFruit();
}
