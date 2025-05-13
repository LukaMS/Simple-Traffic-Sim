#include "Light/Light.h"

Light::Light(STATE startingState, double posX, double posY)
    : state_{startingState}
    , x{posX}
    , y{posY}
{}

Light::STATE Light::getState(){
    return state_;
}

void Light::changeState() {
    switch (state_) {
        case RED2:
            state_ = GREEN;
            break;
        case RED1:
            state_ = RED2;
            break;
        case GREEN:
            state_ = YELLOW;
            break;
        case YELLOW:
            state_ = RED1;
            break;
    }
}