#include "CompanySystem.h"

CompanySystem::CompanySystem(int k):num_companies(k), num_interns(0), sum_interns_grades(0), 
                                    companies(k), all_employees(), employees_with_salary()
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
        all_employees.find(employee_id);
        throw EmployeeAlreadyInSystem();
    }
    catch(const HashTable::ElementNotInTable& e){}
    catch(const EmployeeAlreadyInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
    try{
        Company* company = companies.getCompany(companies.Find(company_id));
        Employee* employee_to_add = new Employee(employee_id, company, 0, grade);
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
        if(employee_to_remove->GetSalary() == 0){
            num_interns--;
            sum_interns_grades -= employee_to_remove->GetGrade();
        }
        else{
            employees_with_salary.remove(employee_to_remove);
        }
        all_employees.remove(employee_id);
        //company of employee is updated all time by acquireCompany
        employee_to_remove->GetCompany()->removeEmployee(employee_to_remove);
        delete employee_to_remove;
    }
    catch(const Company::EmployeeNotInCompany& e){throw EmployeeNotInSystem();}
    catch(const Company::EmployeesUnderZero& e){throw EmployeeNotInSystem();}
    catch(const RankTree::ElementNotInTree& e){throw EmployeeNotInSystem();}
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

void CompanySystem::employeeSalaryIncrease(int employee_id, int salary_increase)
{
    try{
        Employee* employee = all_employees.find(employee_id);
        if(employee->GetSalary() == 0){
            employee->SetSalary(employee->GetSalary() + salary_increase);
            num_interns--;
            sum_interns_grades -= employee->GetGrade();
            employees_with_salary.insert(employee);
            employee->GetCompany()->getEmployeesWithSalaryTree().insert(employee);
            employee->GetCompany()->increaseSumOfInternsGrades(-(employee->GetGrade()));
            employee->GetCompany()->increaseNumOfInterns(-1);
        }
        else{
            //update employee location in trees
            employee->GetCompany()->getEmployeesWithSalaryTree().remove(employee);
            employees_with_salary.remove(employee);
            employee->SetSalary(employee->GetSalary() + salary_increase);
            employee->GetCompany()->getEmployeesWithSalaryTree().insert(employee);
            employees_with_salary.insert(employee);
        }
    }
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

void CompanySystem::promoteEmployee(int employee_id, int bump_grade)
{
    try{
        Employee* employee = all_employees.find(employee_id);
        if(bump_grade > 0){
            if(employee->GetSalary() == 0){
                sum_interns_grades += bump_grade;
                employee->GetCompany()->increaseSumOfInternsGrades(bump_grade);
                employee->SetGrade(employee->GetGrade() + bump_grade);
            }
            else{
                employee->GetCompany()->getEmployeesWithSalaryTree().remove(employee);
                employees_with_salary.remove(employee);
                employee->SetGrade(employee->GetGrade() + bump_grade);
                employee->GetCompany()->getEmployeesWithSalaryTree().insert(employee);
                employees_with_salary.insert(employee);
            }
        }
    }
    catch(const HashTable::ElementNotInTable& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

static void mergeHashTables(Company* acquirer_company, HashTable& acquirer, HashTable& target)
{
    LinkedList* values_target = target.getValues();
    //insert all target employees to acquirer
    for (int i = 0; i < target.getTableSize(); i++)
    {
        Node* head = values_target[i].getHead();
        while(head != nullptr){
            head->getData()->SetCompany(acquirer_company);
            acquirer.insert(head->getData());
            head = head->getNext();
        }
    }
    //clear target
    target.clearHash();
}

void CompanySystem::acquireCompany(int acquirer_id, int target_id, double factor)
{
    try{
        if(companies.Find(acquirer_id) == companies.Find(target_id)){
            throw SameCompany();
        }
        Company* acquirer_company = companies.getCompany(companies.Find(acquirer_id));
        Company* target_company = companies.getCompany(companies.Find(target_id));
        mergeHashTables(acquirer_company, acquirer_company->getEmployeesHash(), target_company->getEmployeesHash());
        //merge ranked trees of employees with salary
        (acquirer_company->getEmployeesWithSalaryTree()).absorbTree(target_company->getEmployeesWithSalaryTree());
        //update num_of_interns and sum_of_interns_grades
        acquirer_company->increaseSumOfInternsGrades(target_company->getSumOfInternsGrades());
        acquirer_company->increaseNumOfInterns(target_company->getNumOfInterns());
        target_company->increaseNumOfInterns(-target_company->getNumOfInterns());
        target_company->increaseSumOfInternsGrades(-target_company->getSumOfInternsGrades());
        companies.Union(companies.Find(target_id), companies.Find(acquirer_id), factor);
    }
    catch(const Company::EmployeesUnderZero& e){throw e;}
    catch(const SameCompany& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}

long double CompanySystem::companyValue(int company_id)
{
    try{
        if(company_id == 2){
            company_id += 1;
            company_id -= 1;
        }
        long double standing = companies.getCompanyValue(company_id);
        return standing;
    }
    catch(const std::bad_alloc& e){throw e;}
}

long int CompanySystem::sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m)
{
    try{
        long int sumBumpGrade = 0;
        if(company_id == 0){
            sumBumpGrade = employees_with_salary.sumOfGradeTopWorkers(m);
        }
        else{
            Company* company = companies.getCompany(companies.Find(company_id));
            sumBumpGrade = (company->getEmployeesWithSalaryTree()).sumOfGradeTopWorkers(m);
        }
        return sumBumpGrade;
    }
    catch(const RankTree::NotEnoughEmployees& e){throw NotEnoughEmployees();}
    catch(const RankTree::RankNotFound& e){throw NotEnoughEmployees();}
    catch(const std::bad_alloc& e){throw e;}
}

long double CompanySystem::averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary)
{
    try{
        long int num_employees_in_range = 0, sum_grades_in_range = 0;
        if(company_id == 0){
            if(employees_with_salary.getRoot() != nullptr){
                employees_with_salary.averageGradesInSalaryRange(lower_salary, higher_salary, &num_employees_in_range, &sum_grades_in_range);
            }
            if(lower_salary == 0){
                num_employees_in_range += this->num_interns;
                sum_grades_in_range += this->sum_interns_grades;
            }
        }
        else{
            Company* company = companies.getCompany(companies.Find(company_id));
            if((company->getEmployeesWithSalaryTree()).getRoot() != nullptr){
                (company->getEmployeesWithSalaryTree()).averageGradesInSalaryRange(lower_salary, higher_salary, &num_employees_in_range, &sum_grades_in_range);
            }
            if(lower_salary == 0){
                num_employees_in_range += company->getNumOfInterns();
                sum_grades_in_range+= company->getSumOfInternsGrades();
            }
        }
        if(num_employees_in_range == 0){
            throw NoEmployeesInRange();
        }
        else{
            return (long double)sum_grades_in_range/num_employees_in_range;
        }
    }
    catch(const NoEmployeesInRange& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}