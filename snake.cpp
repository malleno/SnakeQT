#include "snake.h"
#include "ui_snake.h"
#include <qdebug.h>


Snake::Snake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Snake)
    , gamescene_(new GameScene())
{
    ui->setupUi(this);
    ui->Field->setScene(gamescene_->GetScenePointer());
    ui->Field->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    ui->Field->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    connect(this, SIGNAL(keyPressed(QKeyEvent*)), gamescene_, SLOT(KeyPressed(QKeyEvent*)));
    connect(ui->gameSpeedSlider, SIGNAL(sliderMoved(int)), gamescene_, SLOT(GameSpeedChange(int)));
    connect(ui->resetPushButton, SIGNAL(clicked()), gamescene_, SLOT(ResetGame()));
}

GameScene* Snake::GetGameScene(){
    return gamescene_;
}
void Snake::keyPressEvent(QKeyEvent* event){
        emit keyPressed(event);
}

Snake::~Snake()
{
    delete ui;
}


