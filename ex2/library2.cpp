#include "library2.h"
#include "CompanySystem.h"

void* Init(int k)
{
    if(k <= 0)
        return nullptr;
    CompanySystem *DS = new CompanySystem(k);
    return (void*)DS;
}

StatusType AddEmployee(void *DS, int employeeID, int companyID, int grade)
{
    if(DS == nullptr || companyID<=0 || companyID > (((CompanySystem*)DS)->getNumCompanies()) || employeeID <= 0 || grade < 0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->addEmployee(employeeID, companyID, grade);
        return SUCCESS;
    }
    catch(const CompanySystem::EmployeeAlreadyInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType RemoveEmployee(void *DS, int employeeID)
{
    if(DS == nullptr || employeeID <= 0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->removeEmployee(employeeID);
        return SUCCESS;
    }
    catch(const CompanySystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType AcquireCompany(void *DS, int companyID1, int companyID2, double factor)
{
    if(DS == nullptr || companyID1<=0 || companyID1 > (((CompanySystem*)DS)->getNumCompanies()) || 
        companyID2<=0 || companyID2 > (((CompanySystem*)DS)->getNumCompanies()) || factor <= 0.0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->acquireCompany(companyID1, companyID2, factor);
        return SUCCESS;
    }
    catch(const CompanySystem::SameCompany& e){return INVALID_INPUT;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType EmployeeSalaryIncrease(void *DS, int employeeID, int salaryIncrease)
{
    if(DS == nullptr || employeeID <= 0 || salaryIncrease <= 0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->employeeSalaryIncrease(employeeID, salaryIncrease);
        return SUCCESS;
    }
    catch(const CompanySystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType PromoteEmployee(void *DS, int employeeID, int bumpGrade)
{
    if(DS == nullptr || employeeID <= 0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->promoteEmployee(employeeID, bumpGrade);
        return SUCCESS;
    }
    catch(const CompanySystem::EmployeeNotInSystem& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType SumOfBumpGradeBetweenTopWorkersByGroup(void *DS, int companyID, int m, void ** sumBumpGrade)
{
    if(DS == nullptr || *sumBumpGrade == nullptr || companyID < 0 || companyID > (((CompanySystem*)DS)->getNumCompanies()) || m <= 0){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->sumOfBumpGradeBetweenTopWorkersByGroup(companyID, m, *sumBumpGrade);
        return SUCCESS;
    }
    catch(const CompanySystem::NotEnoughEmployees& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType AverageBumpGradeBetweenSalaryByGroup(void *DS, int companyID, int lowerSalary, int higherSalary, void ** averageBumpGrade)
{
    if(DS == nullptr || *averageBumpGrade == nullptr || companyID < 0 || companyID > (((CompanySystem*)DS)->getNumCompanies()) ||
        lowerSalary < 0 || higherSalary < 0 || lowerSalary > higherSalary){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->averageBumpGradeBetweenSalaryByGroup(companyID, lowerSalary, higherSalary, *averageBumpGrade);
        return SUCCESS;
    }
    catch(const CompanySystem::NoEmployeesInRange& e){return FAILURE;}
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

StatusType CompanyValue(void *DS, int companyID, void ** standing)
{
    if(DS == nullptr || *standing == nullptr || companyID <= 0 || companyID > (((CompanySystem*)DS)->getNumCompanies())){
        return INVALID_INPUT;
    }
    try{
        ((CompanySystem*)DS)->companyValue(companyID, *standing);
        return SUCCESS;
    }
    catch(const std::bad_alloc& e){return ALLOCATION_ERROR;}
}

void Quit(void** DS)
{
    void **temp = DS;
    delete (CompanySystem*)(*temp);
    *DS = NULL;
}