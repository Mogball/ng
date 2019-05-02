#pragma once

namespace ng {

    struct Location {
        float w = 1;
        float h = 1;
        float r = 1;
        float x = 0;
        float y = 0;
        float angle = 0;
        float vx = 0;
        float vy = 0;
        float omega = 0;
    };

    struct Properties {
        float density = 1;
        float friction = 3;
        float restitution = 0.1;
    };

}
