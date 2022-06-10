#ifndef COMPANY_SYSTEM
#define COMPANY_SYSTEM

#include "Company.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "UnionFind.h"
#include <new>

class CompanySystem{

    private:
        int num_companies;
        int num_interns;
        int sum_interns_grades;
        UnionFind companies;
        HashTable all_employees;
        RankTree employees_with_salary;

    public:
        class EmployeeAlreadyInSystem: public std::exception{};
        class EmployeeNotInSystem: public std::exception{};
        class SameCompany: public std::exception{};
        class NotEnoughEmployees: public std::exception{};
        class NoEmployeesInRange: public std::exception{};

        CompanySystem(int k);
        ~CompanySystem();
        int getNumCompanies(){return num_companies;}
    
        //employee functions
        void addEmployee(int employee_id, int company_id, int grade);
        void removeEmployee(int employee_id);
        void employeeSalaryIncrease(int employee_id, int salary_increase);
        void promoteEmployee(int employee_id, int bump_grade);
        //company functions
        void acquireCompany(int acquirer_id, int target_id, double factor);
        long double companyValue(int company_id);
        //DS functions
        long int sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m);
        long double averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary);
};

#endif /* UF_COMPANIES */