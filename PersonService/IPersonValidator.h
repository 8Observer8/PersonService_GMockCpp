#pragma once

#include "Person.h"

class IPersonValidator
{
public:
    virtual ~IPersonValidator() {};
    virtual bool IsValid(const Person &person) = 0;
};