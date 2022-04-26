#include "EmploymentSystem.h"


EmploymentSystem::EmploymentSystem() : id_cond(), salary_cond(), company_cond(), highest_earner(nullptr), num_of_employees(0), num_companies_with_employees(0),
employees_id_dict(id_cond), employees_salary_dict(salary_cond), all_companies(company_cond), companies_with_employees(company_cond)
{
    
}

EmploymentSystem::~EmploymentSystem()
{
    employees_id_dict.destroyRecursiveData(employees_id_dict.getRoot());
    all_companies.destroyRecursiveData(all_companies.getRoot());
}

void EmploymentSystem::AddCompany(int CompanyID, int Value)
{
    Company* company;
    try{
        company = new Company(CompanyID, Value);
        all_companies.insertNode(company);
    }
    catch(const AVLTree<Company*, CompanyCondition>::ElementAlreadyInTree& e){
        delete company;
        throw CompanyAlreadyExists();
    }
    catch(const std::bad_alloc& e){
        throw e;
    }
}

Company* EmploymentSystem::GetCompanyInfo(int CompanyID)
{
    try{
        Company dummy(CompanyID, 0);
        return all_companies.findElement(&dummy, all_companies.getRoot())->getData();
    }
    catch(const AVLTree<Company*, CompanyCondition>::ElementNotInTree& e){throw CompanyNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

Employee* EmploymentSystem::GetEmployeeInfo(int EmployeeID)
{
    try{
        Employee employee_to_find(EmployeeID, nullptr, 0, 0);
        return employees_id_dict.findElement(&employee_to_find, employees_id_dict.getRoot())->getData();
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementNotInTree& e){throw EmployeeNotInSystem();}
    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
{
    Company* company_ptr;
    Employee* employee_to_add;
    try{
        company_ptr = GetCompanyInfo(CompanyID);
        if(GetEmployeeInfo(EmployeeID)->GetCompany()->getId() == CompanyID){
            throw EmployeeAlreadyExists();
        } 
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const EmployeeNotInSystem& e){}
    try{
        // find company to add employee to (1)
        company_ptr = GetCompanyInfo(CompanyID);
        employee_to_add = new Employee(EmployeeID, company_ptr, Salary, Grade);
        //insert employee to employees trees (2)
        employees_id_dict.insertNode(employee_to_add);
        employees_salary_dict.insertNode(employee_to_add);
        //update highest_earner
        highest_earner = employees_salary_dict.findMaxNode(employees_salary_dict.getRoot())->getData();
        num_of_employees++;
        //insert employee to company employees tree
        company_ptr->AddEmployee(employee_to_add);
        //insert company to companies_with_employees tree
        if(company_ptr->getNumOfEmployees() == 1){
            companies_with_employees.insertNode(company_ptr);
        }
        num_companies_with_employees++;
    }
    catch(const CompanyNotInSystem& e){ // 1
        throw e;
    }
    catch(const AVLTree<Employee*, IdCondition>::ElementAlreadyInTree& e){ // 2
        delete employee_to_add;
        throw EmployeeAlreadyExists();
    }
    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::removeCompanyIfEmpty(Company* company){
    if(company->getNumOfEmployees() == 0){
        companies_with_employees.deleteNode(company);
        num_companies_with_employees--;
    }
}

void EmploymentSystem::RemoveEmployee(int EmployeeID)
{
    try{
        //find employee (1)
        Employee* employee_to_remove = GetEmployeeInfo(EmployeeID);
        //remove employee from company (2)
        Company* company = employee_to_remove -> GetCompany();
        employee_to_remove->GetCompany()->removeEmployee(employee_to_remove);
        //remove company from companies_with_employees if it becomes empty
        removeCompanyIfEmpty(company);
        //remove employee from employees trees
        employees_id_dict.deleteNode(employee_to_remove);
        employees_salary_dict.deleteNode(employee_to_remove);
        //updadte num_of_employees and highest_earner
        highest_earner = employees_salary_dict.findMaxNode(employees_salary_dict.getRoot())->getData();
        num_of_employees--;
        delete employee_to_remove;
    }
    catch(const EmployeeNotInSystem& e){ // 1
        throw e;
    }
    catch(const Company::EmployeeNotInCompany& e){ // 2
        throw e;
    }
    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::RemoveCompany(int CompanyID)
{
    try{
        Company* company_to_remove = GetCompanyInfo(CompanyID);
        if(company_to_remove->getNumOfEmployees() > 0){
            throw CompanyContainsEmployees();
        }
        all_companies.deleteNode(company_to_remove);
        delete company_to_remove;
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
{
    try{
        Company* company = GetCompanyInfo(CompanyID);
        company->setValue(company->getValue() + ValueIncrease);
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    try{
        Employee* employee = GetEmployeeInfo(EmployeeID);
        if(BumpGrade > 0){
            employee->SetGrade(employee->GetGrade() + 1);
        }
        //update employee placement in trees
        Company* company = employee->GetCompany();
        company->removeEmployee(employee);
        employees_salary_dict.deleteNode(employee);
        //update salary
        employee->SetSalary(employee->GetSalary() + SalaryIncrease);
        company->AddEmployee(employee);
        employees_salary_dict.insertNode(employee);
        //update highest_earner
        highest_earner = employees_salary_dict.findMaxNode(employees_salary_dict.getRoot())->getData();
    }
    catch(const EmployeeNotInSystem& e){throw e;}
    //exceptions that can happen when deleting
    catch(const Company::EmployeeNotInCompany& e){throw EmployeeNotInSystem();}
    catch(const AVLTree<Employee*, SalaryCondition>::ElementNotInTree& e){throw EmployeeNotInSystem();}

    catch(const std::bad_alloc& e){throw e;}
}

void EmploymentSystem::HireEmployee(int EmployeeID, int NewCompanyID)
{
    try{
        //find employee and new_company
        Employee* employee = GetEmployeeInfo(EmployeeID);
        Company* new_company = GetCompanyInfo(NewCompanyID);
        //remove employee from old_company and remove old_company from companies_with_employees if needed
        Company* old_company = employee->GetCompany();
        if(old_company->getId() == new_company->getId()){
            throw Company::EmployeeAlreadyInCompany();
        }
        old_company->removeEmployee(employee);
        removeCompanyIfEmpty(old_company);
        //add employee to new_company and insert new_company to companies_with_employees if needed
        new_company->AddEmployee(employee);
        if(new_company->getNumOfEmployees() == 1){
            companies_with_employees.insertNode(new_company);
            num_companies_with_employees++;
        }
        employee->SetCompany(new_company);
    }
    catch(const EmployeeNotInSystem& e){throw e;}
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const Company::EmployeeAlreadyInCompany& e){throw e;}
}

Employee* EmploymentSystem::GetHighestEarner(int CompanyID)
{
    if(highest_earner == nullptr){
        throw NoEmployeesInSystem();
    }
    if(CompanyID < 0){
        return highest_earner;
    }
    try{
       Company* company = GetCompanyInfo(CompanyID);
       if(company->getNumOfEmployees() == 0){
           throw NoEmployeesInCompany();
       }
       return company->getHighestEarner();
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}

static void changeEmployer(AVLTree<Employee*, IdCondition>::Node* root, Company* company)
{
    if (root == nullptr) {return;}
    changeEmployer(root->left, company);
    root->getData()->SetCompany(company);
    changeEmployer(root->right, company);
}

void EmploymentSystem::AcquireCompany(int AcquirerID, int TargetID, double Factor)
{
    try{
       Company* acquirer = GetCompanyInfo(AcquirerID);
       Company* target = GetCompanyInfo(TargetID);
       int target_value = target->getValue();
       int target_num_of_employees = target->getNumOfEmployees();
       //check if acquir can hapen
       if(acquirer->getValue() < (10 * target->getValue())){
           throw AcquireFailed();
       }
       changeEmployer(target->getEmployeeIdDict().getRoot(), acquirer);
       //remove target from company trees and add acquirer if it didnt have employees
       all_companies.deleteNode(target);
       if(target->getNumOfEmployees() != 0){
           companies_with_employees.deleteNode(target);
           num_companies_with_employees--;
           if(acquirer->getNumOfEmployees() == 0){
                companies_with_employees.insertNode(acquirer);
                num_companies_with_employees++;
           }
       }
       //merge target employees trees into acquirer employees trees
       acquirer->getEmployeeIdDict().absorbTree(target->getEmployeeIdDict());
       acquirer->getEmployeeSalaryDict().absorbTree(target->getEmployeeSalaryDict());
       //update acquirer new value and num_of_employees
       acquirer->setValue((int)((target_value + acquirer->getValue()) * Factor));
       acquirer->setNumOfEmployees(acquirer->getNumOfEmployees() + target_num_of_employees);
        //update acquirer highest_earner
       acquirer->setHighestEarner(acquirer->getEmployeeSalaryDict().findMaxNode(acquirer->getEmployeeSalaryDict().getRoot())->getData());
       delete target;
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}

static int reverseInorderSalary(AVLTree<Employee*, SalaryCondition>::Node* root, int **Employees, int index = 0)
{
    if (root != nullptr){
        index = reverseInorderSalary(root->right, Employees, index);
        (*Employees)[index] = root->getData()->GetEmployeeId();
        index++;
        index = reverseInorderSalary(root->left, Employees, index);
    }
    return index;
}

void EmploymentSystem::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees)
{
    if(CompanyID < 0 && num_of_employees == 0){
        throw NoEmployeesInSystem();
    }
    try{
        AVLTree<Employee*, SalaryCondition> *tree;
        if(CompanyID > 0){
            Company* company = GetCompanyInfo(CompanyID);
            if(company->getNumOfEmployees() == 0){
                throw NoEmployeesInCompany();
            }
            tree = &(company->getEmployeeSalaryDict());
            *NumOfEmployees = company->getNumOfEmployees();
        }
        else{
            tree = &employees_salary_dict;
            *NumOfEmployees = num_of_employees;
        }
        *Employees = (int*)malloc(sizeof(int) * (*NumOfEmployees));
        if(*Employees == NULL){
            throw std::bad_alloc();
        }
        reverseInorderSalary(tree->getRoot(), Employees);
    }
    catch(const CompanyNotInSystem& e){throw e;}
}

static int inorderHighestEarners(AVLTree<Company*, CompanyCondition>::Node* root, int **Employees, int NumOfCompanies, int index = 0)
{
    if (root != nullptr){
        index = inorderHighestEarners(root->left, Employees, NumOfCompanies, index);
        if(index < NumOfCompanies){
            (*Employees)[index] = root->getData()->getHighestEarner()->GetEmployeeId();
            index++;
        }
        index = inorderHighestEarners(root->right, Employees, NumOfCompanies, index);
    }
    return index;
}

void EmploymentSystem::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees)
{
    if(NumOfCompanies > num_companies_with_employees){
        throw NotEnoughCompanies();
    }
    *Employees = (int*)malloc(sizeof(int) * (NumOfCompanies));
    if(*Employees == NULL){
        throw std::bad_alloc();
    }
    inorderHighestEarners(companies_with_employees.getRoot(), Employees, NumOfCompanies);
}

void EmploymentSystem::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                        int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    try{
        if(num_of_employees <= 0){
            throw NoEmployeesInSystem();
        }
        ExtraPlaceholder dummy;
        ExtraEmployeeConditions salary_grade(MinSalary, MinGrade);
        Employee dummy_min_id(MinEmployeeID, nullptr, 0, 0);
        Employee dummy_max_id(MaxEmployeeId, nullptr, 0, 0);
        if(CompanyID > 0){
            Company* company = GetCompanyInfo(CompanyID);
            if(company->getNumOfEmployees() == 0){
                throw NoEmployeesInCompany();
            }
            AVLTree<Employee*, IdCondition> &tree = company->getEmployeeIdDict();
            *TotalNumOfEmployees = tree.elementsInRange<ExtraPlaceholder>(tree.getRoot(), &dummy_min_id, &dummy_max_id, dummy);
            *NumOfEmployees = tree.elementsInRange<ExtraEmployeeConditions>(tree.getRoot(), &dummy_min_id, &dummy_max_id, salary_grade);
        }
        else{
            AVLTree<Employee*, IdCondition> &tree = employees_id_dict;
            *TotalNumOfEmployees = tree.elementsInRange<ExtraPlaceholder>(tree.getRoot(), &dummy_min_id, &dummy_max_id, dummy);
            *NumOfEmployees = tree.elementsInRange<ExtraEmployeeConditions>(tree.getRoot(), &dummy_min_id, &dummy_max_id, salary_grade);
        }
    }
    catch(const CompanyNotInSystem& e){throw e;}
    catch(const std::bad_alloc& e){throw e;}
}