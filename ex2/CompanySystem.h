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
        long int num_interns;
        long int sum_interns_grades;
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
        void addEmployee(long int employee_id, int company_id, long int grade);
        void removeEmployee(long int employee_id);
        void employeeSalaryIncrease(long int employee_id, long int salary_increase);
        void promoteEmployee(long int employee_id, long int bump_grade);
        //company functions
        void acquireCompany(int acquirer_id, int target_id, long double factor);
        long double companyValue(int company_id);
        //DS functions
        long int sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, long int m);
        long double averageBumpGradeBetweenSalaryByGroup(int company_id, long int lower_salary, long int higher_salary);
};

#endif /* UF_COMPANIES */