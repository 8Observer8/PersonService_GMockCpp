#pragma once

#include "Person.h"
#include "IPersonValidator.h"
#include "IDataContext.h"

class PersonService
{
public:
    PersonService(IPersonValidator *validator, IDataContext *dataContext);

    void Save(const Person &person);

private:
    IPersonValidator *_validator;
    IDataContext *_dataContext;
};

