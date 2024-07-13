# pragma once

#include <string>

class MoveIf
{
public:
    virtual std::string toString() const = 0;
    virtual ~MoveIf() = default;
};