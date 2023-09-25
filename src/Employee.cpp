#include "Employee.hpp"

Employee::Employee(std::string name, std::string lastName, int number) noexcept : m_Name{std::move(name)}, m_LastName{std::move(lastName)}, m_Number{number}{}

const std::string &Employee::GetName() const {return m_Name;}

const int &Employee::GetNumber() const  {return m_Number;}

const std::string &Employee::GetLastName() const {return m_LastName;}

void Employee::ShowPersonLastNameFirst() const
{
    std::cout << m_LastName << ' ' << m_Name << ": " << m_Number << std::endl;
}

void Employee::ShowPersonNameFirst() const
{
    std::cout << m_Name << ' ' << m_LastName << ": " << m_Number << std::endl;
}

void Employee::ShowPersonNumberFirst() const
{
    std::cout << m_Number << ": " << m_LastName << ' ' << m_Name << std::endl;
}

