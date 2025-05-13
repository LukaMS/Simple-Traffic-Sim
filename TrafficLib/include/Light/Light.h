#ifndef LIGHT_H
#define LIGHT_H

class Light {
    public:
        enum STATE {
            RED1,
            RED2,
            YELLOW,
            GREEN
        };

        Light(STATE startingState, double x, double y);

        double getX(){return x;};
        double getY(){return y;};

        STATE getState();
        void changeState();
    private:
        STATE state_;
        double x, y;
};

#endif