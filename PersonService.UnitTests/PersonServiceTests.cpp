#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

#include "IDataContext.h"
#include "IPersonValidator.h"
#include "Person.h"
#include "PersonService.h"

class MockDataContext : public IDataContext
{
public:
    MOCK_METHOD1(SavePerson, void(const Person &person));
};

class MockPersonValidator : public IPersonValidator
{
public:
    MOCK_METHOD1(IsValid, bool(const Person &person));
};

TEST(PersonService, IsValid_ValidPerson_CallSavePerson)
{
    MockDataContext dataContext;
    MockPersonValidator validator;
    PersonService service = PersonService(&validator, &dataContext);
    Person validPerson;

    EXPECT_CALL(validator, IsValid(_))
        .WillOnce(Return(true));

    EXPECT_CALL(dataContext, SavePerson(_)).Times(1);

    service.Save(validPerson);
}

TEST(PersonService, IsValid_NotValidPerson_ThrowException)
{
    MockDataContext dataContext;
    MockPersonValidator validator;
    PersonService service = PersonService(&validator, &dataContext);
    Person validPerson;

    EXPECT_CALL(validator, IsValid(_))
        .WillOnce(Return(false));
    EXPECT_CALL(dataContext, SavePerson(_)).Times(0);

    //EXPECT_THROW({
    //    service.Save(validPerson);
    //}, std::runtime_error);

    try
    {
        service.Save(validPerson);
        FAIL() << "Exptected std::runtime_error";
    }
    catch (std::runtime_error const & err)
    {
        EXPECT_EQ(err.what(), std::string("Person is not valid"));
    }
    catch (...)
    {
        FAIL() << "Exptected std::runtime_error";
    }
}

