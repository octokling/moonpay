#pragma once

class IJudge {
public:
    virtual void reset();

    virtual void update();

    virtual bool judge();
};
