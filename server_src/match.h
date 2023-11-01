#include <box2d/box2d.h>
#include "../common_src/queue.h"

class Match {
    b2World world;
    
    public:
        Match();
        ~Match();
        void start();
};

