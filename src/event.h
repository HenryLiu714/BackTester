#ifndef EVENT_H
#define EVENT_H 

#include <string>
#include <vector>

#include "datetime.h"

class Event {
    public:
        std::string type;
        Datetime datetime;

        // Constructor
        Event();
        Event(std::string type, std::string datetime);
};

#endif
