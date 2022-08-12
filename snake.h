#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include "gamescene.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Snake; }
QT_END_NAMESPACE

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();
    GameScene* getGameScene();
    void keyPressEvent(QKeyEvent*);

signals:
    void keyPressed(QKeyEvent*);

private:
    Ui::Snake* ui;
    GameScene* gamescene_;
};
#endif // SNAKE_H
