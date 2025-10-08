//
// Created by Petr Pavlík on 05.10.2025.
//

#include "Location.h"

Location Location::operator+(const Location &location) const
{
    return {x + location.GetX(), y + location.GetY(), z + location.GetZ()};
}
