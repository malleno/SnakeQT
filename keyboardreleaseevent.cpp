#include "keyboardreleaseevent.h"
#include "snakemodel.h"
KeyboardReleaseEvent::KeyboardReleaseEvent()
{

}

void KeyboardReleaseEvent::EventSnakeMove(QKeyEvent *event) {
    emit KeyPressed(event);
}
