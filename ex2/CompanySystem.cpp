#include "CompanySystem.h"

CompanySystem::CompanySystem(int k):companies(k), num_interns(0), 
                                sum_interns_grades(0), all_employees(), employees_with_salary()
{
    
}

CompanySystem::~CompanySystem()
{
    //delete employees
    all_employees.destroyHashData();
}

void CompanySystem::addEmployee(int employee_id, int company_id, int grade)
{
    try{
        Employee* to_find = all_employees.find(employee_id);
        throw EmployeeAlreadyInSystem();
    }
    catch(const HashTable::ElementNotInTable& e){}
    catch(const EmployeeAlreadyInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
    try{
        Company* company = companies.getCompany(companies.Find(company_id));
        Employee* employee_to_add = new Employee(employee_id, nullptr, 0, grade);
        company->AddEmployee(employee_to_add);
        all_employees.insert(employee_to_add);
        num_interns++;
        sum_interns_grades += grade;
    }
    catch(const std::bad_alloc& e){throw e;}
}

void CompanySystem::removeEmployee(int employee_id)
{
    try{
        Employee* employee_to_remove = all_employees.find(employee_id);
        employee_to_remove->GetCompany()->removeEmployee(employee_to_remove);
        if(employee_to_remove->GetSalary() == 0){
            num_interns--;
            sum_interns_grades -= employee_to_remove->GetGrade();
        }
        all_employees.remove(employee_id);
        delete employee_to_remove;
    }
    catch(const Company::EmployeeNotInCompany& e){throw EmployeeNotInSystem();}
    catch(const Company::EmployeesUnderZero& e){throw EmployeeNotInSystem();}
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

void CompanySystem::employeeSalaryIncrease(int employee_id, int salary_increase)
{
    try{
        Employee* employee = all_employees.find(employee_id);
        if(employee->GetSalary() == 0){
            num_interns--;
            sum_interns_grades -= employee->GetGrade();
        }
        employee->SetSalary(employee->GetSalary() + salary_increase);
        employee->GetCompany()->getEmployeeTree().insert(employee);
        employee->GetCompany()->increaseSumOfInternsGrades(-employee->GetGrade());
        employee->GetCompany()->increaseNumOfInterns(-1);
    }
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

void CompanySystem::promoteEmployee(int employee_id, int bump_grade)
{
    try{
        Employee* employee = all_employees.find(employee_id);
        if(employee->GetSalary() == 0){
            sum_interns_grades += bump_grade;
        }
        employee->GetCompany()->increaseSumOfInternsGrades(bump_grade);
    }
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

// void CompanySystem::acquireCompany(int acquirer_id, int target_id, double factor)

// void CompanySystem::companyValue(int company_id, void* standing)

// void CompanySystem::sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m, void* sumBumpGrade)

// void CompanySystem::averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary, void* average_bump_grade)