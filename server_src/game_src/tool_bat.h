#include "tool.h"

class Bat : public Tool {
    int damage;

    public:
        Bat();
        void use(b2Body* worm, int direction, float angle, int time , int power , float x , float y, std::unordered_set<std::shared_ptr<Projectile>>& projectiles) override;
        ~Bat();
};