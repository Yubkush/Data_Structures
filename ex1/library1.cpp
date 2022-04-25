#include "library1.h"
#include "EmploymentSystem.h"

void* Init()
{
    EmploymentSystem *DS = new EmploymentSystem();
    return (void*)DS;
}

StatusType AddCompany(void *DS, int CompanyID, int Value)
{
    try{
        if (DS == NULL || CompanyID <= 0 || Value <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> AddCompany(CompanyID, Value);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyAlreadyExists& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    try{
        if (DS == NULL || EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> AddEmployee(EmployeeID, CompanyID, Salary, Grade);
        return SUCCESS;
    }
    catch(const EmploymentSystem::EmployeeAlreadyExists& e){return FAILURE;}
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    try{
        if (DS == NULL || EmployeeID <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> RemoveEmployee(EmployeeID);
        return SUCCESS;
    }
    catch(const EmploymentSystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType RemoveCompany(void *DS, int CompanyID)
{
    try{
        if (DS == NULL || CompanyID <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> RemoveCompany(CompanyID);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::CompanyContainsEmployees& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    try{
        if (DS == NULL || CompanyID <= 0 || Value == NULL || NumEmployees == NULL) return INVALID_INPUT;
        Company* company = ((EmploymentSystem *) DS)-> GetCompanyInfo(CompanyID);
        *Value = company->getValue();
        *NumEmployees = company->getNumOfEmployees();
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    try{
        if (DS == NULL || EmployeeID <= 0 || EmployerID == NULL || Salary == NULL || Grade == NULL) return INVALID_INPUT;
        Employee* employee = ((EmploymentSystem *) DS)-> GetEmployeeInfo(EmployeeID);
        *EmployerID = employee->GetCompany()->getId();
        *Salary = employee->GetSalary();
        *Grade = employee->GetGrade();
        return SUCCESS;
    }
    catch(const EmploymentSystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    try{
        if (DS == NULL || CompanyID <= 0 || ValueIncrease <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> IncreaseCompanyValue(CompanyID, ValueIncrease);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    try{
        if (DS == NULL || EmployeeID <= 0 || SalaryIncrease <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
        return SUCCESS;
    }
    catch(const EmploymentSystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    try{
        if (DS == NULL || EmployeeID <= 0 || NewCompanyID <= 0) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> HireEmployee(EmployeeID, NewCompanyID);
        return SUCCESS;
    }
    catch(const EmploymentSystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const Company::EmployeeAlreadyInCompany& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    try{
        if (DS == NULL || AcquirerID <= 0 || TargetID <= 0 || AcquirerID == TargetID || Factor < 1.00) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> AcquireCompany(AcquirerID, TargetID, Factor);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::AcquireFailed& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    try{
        if (DS == NULL || CompanyID == 0 || EmployeeID == NULL) return INVALID_INPUT;
        Employee* employee = ((EmploymentSystem *) DS)-> GetHighestEarner(CompanyID);
        *EmployeeID = employee->GetEmployeeId();
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInCompany& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    try{
        if (DS == NULL || CompanyID == 0 || Employees == NULL || NumOfEmployees == NULL ) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInCompany& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    try{
        if (DS == NULL || Employees == NULL || NumOfCompanies < 1 ) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
        return SUCCESS;
    }
    catch(const EmploymentSystem::NotEnoughCompanies& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId, int MinSalary,
                                    int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    try{
        if (DS == NULL || TotalNumOfEmployees == NULL || NumOfEmployees == NULL || CompanyID == 0 ||
            MinEmployeeID < 0 || MaxEmployeeId < 0 || MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeId) return INVALID_INPUT;
        ((EmploymentSystem *) DS)-> GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId, MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees);
        return SUCCESS;
    }
    catch(const EmploymentSystem::CompanyNotInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInSystem& e){return FAILURE;}
    catch(const EmploymentSystem::NoEmployeesInCompany& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

void Quit(void** DS)
{
    void **temp = DS;
    *DS = NULL;
    delete static_cast<EmploymentSystem*>(*temp);
}