#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
#include <iostream>

class Employee
{
private:
    std::string m_Name;
    std::string m_LastName;
    int m_Number;
public:
    explicit Employee(std::string name, std::string lastName, int number) noexcept;

    [[nodiscard]] const std::string &GetName() const;

    [[nodiscard]] const int& GetNumber() const;

    [[nodiscard]] const std::string &GetLastName() const;

    void ShowPersonLastNameFirst() const;

    void ShowPersonNameFirst() const;

    void ShowPersonNumberFirst() const;
};

#endif //EMPLOYEE_HPP
