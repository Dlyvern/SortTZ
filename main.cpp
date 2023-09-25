#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class Employee
{
private:
    std::string m_Name;
    std::string m_LastName;
    int m_Number;
public:
    explicit Employee(std::string name, std::string lastName, int number) noexcept: m_Name{std::move(name)}, m_LastName{std::move(lastName)}, m_Number{number}{}

    [[nodiscard]] const std::string &GetName() const {return m_Name;}

    [[nodiscard]] const int& GetNumber() const {return m_Number;}

    [[nodiscard]] const std::string &GetLastName() const {return m_LastName;}

    void ShowPersonLastNameFirst() const
    {
        std::cout << m_LastName << ' ' << m_Name << ": " << m_Number << std::endl;
    }

    void ShowPersonNameFirst() const
    {
        std::cout << m_Name << ' ' << m_LastName << ": " << m_Number << std::endl;
    }

    void ShowPersonNumberFirst() const
    {
        std::cout << m_Number << ": " << m_LastName << ' ' << m_Name << std::endl;
    }
};

std::string ReadFile(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    std::string buffer;

    if(!file)
        throw std::runtime_error("could not open file");

    file.seekg(0, std::ios::end);
    buffer.resize(file.tellg());
    file.seekg(0);
    file.read(buffer.data(), buffer.size());

    return buffer;
}

std::vector<std::shared_ptr<Employee>> Parser(const std::string& stringToParse, char delimiter)
{
    std::size_t start_position{0};

    std::size_t end_position = stringToParse.find('\n');

    std::vector<std::shared_ptr<Employee>>employees;

    while (end_position != std::string::npos)
    {
        std::string employee_string = stringToParse.substr(start_position, end_position - start_position);

        size_t delimiter_position = employee_string.find(delimiter);

        size_t start_position_name = employee_string.find(' ');

        std::string last_name = employee_string.substr(0, start_position_name);

        std::string name = employee_string.substr(start_position_name, delimiter_position - start_position_name);

        int number = std::stoi(employee_string.substr(delimiter_position + 1));

        employees.emplace_back(std::make_shared<Employee>(std::move(name), std::move(last_name), number));

        start_position = end_position + 1;

        end_position = stringToParse.find('\n', start_position);
    }

    return employees;
}

void UserInterface(std::vector<std::shared_ptr<Employee>>& employees)
{
    std::cout << std::endl << std::endl << "By what parameter to sort employees?" << std::endl << std::endl;
    std::cout << "By Name - 1" << std::endl;
    std::cout << "By Last name - 2" << std::endl;
    std::cout << "By phone number - 3" << std::endl;
    std::cout << "Not to sort - default" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << "Select option: ";

    int input = getchar();

    //Dry is crying rn

    if(input == 49)
    {
        std::stable_sort(employees.begin(), employees.end(),
                  [](const std::shared_ptr<Employee> &employee1, const std::shared_ptr<Employee> &employee2) {
                      return employee1->GetName() < employee2->GetName();
                  });

        for (const auto &employee: employees)
            employee->ShowPersonNameFirst();
    }


    else if(input == 50)
    {
        std::stable_sort(employees.begin(), employees.end(),
                  [](const std::shared_ptr<Employee> &employee1, const std::shared_ptr<Employee> &employee2) {
                      return employee1->GetLastName() < employee2->GetLastName();
                  });

        for (const auto &employee: employees)
            employee->ShowPersonLastNameFirst();
    }
    else if(input == 51)
    {
        std::stable_sort(employees.begin(), employees.end(),
                  [](const std::shared_ptr<Employee> &employee1, const std::shared_ptr<Employee> &employee2) {
                      return employee1->GetNumber() < employee2->GetNumber();
                  });

        for (const auto &employee: employees)
            employee->ShowPersonNumberFirst();
    }
}

int main()
{
    std::vector<std::shared_ptr<Employee>> employees;

    try
    {
        std::string employees_in_string = ReadFile("../Employees.txt");
        employees = Parser(employees_in_string, ':');
    }

    catch (const std::exception &exception)
    {
        std::cerr << "Exception was thrown" << std::endl;
        std::cerr << "What: " << exception.what() << std::endl;
    }

    catch (...)
    {
        std::cerr << "Undefined exception was thrown" << std::endl;
    }

    UserInterface(employees);

    return 0;
}
