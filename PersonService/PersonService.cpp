#include "PersonService.h"

PersonService::PersonService(IPersonValidator *validator, IDataContext *dataContext)
{
    _validator = validator;
    _dataContext = dataContext;
}

void PersonService::Save(const Person &person)
{
    if (_validator->IsValid(person))
    {
        _dataContext->SavePerson(person);
    }
    else
    {
        throw std::runtime_error("Person is not valid");
    }
}
