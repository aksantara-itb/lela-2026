#ifndef MAVLINK_DROP_LOGIC_H
#define MAVLINK_DROP_LOGIC_H

#include "common/types.h"

namespace mavlink {

class DropLogic {
public:
    DropLogic();
    ~DropLogic();

    // Initialize drop logic
    void initialize();
    
    // Check if conditions are met for dropping
    bool canDrop() const;
    
    // Execute drop sequence
    bool executeDrop();
    
    // Set drop parameters
    void setDropAltitude(double altitude);
    void setDropVelocity(double velocity);

private:
    double drop_altitude_;
    double drop_velocity_;
    bool drop_executed_;
};

} // namespace mavlink

#endif // MAVLINK_DROP_LOGIC_H
