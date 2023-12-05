#include <box2d/box2d.h>

#include "entity.h"


class ProvisionBoxCallback: public b2QueryCallback {
    friend class BoxManager;
    int count = 0;

    bool ReportFixture(b2Fixture* fixture) override;

public:
    ~ProvisionBoxCallback();
};
