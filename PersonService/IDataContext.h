#pragma once

#include "Person.h"

class IDataContext
{
public:
    virtual ~IDataContext() {};
    virtual void SavePerson(const Person &person) = 0;
};