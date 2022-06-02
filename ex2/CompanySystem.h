#ifndef COMPANY_SYSTEM
#define COMPANY_SYSTEM

#include "Company.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "UnionFind.h"


class CompanySystem{

    private:
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
    
        //employee functions
        void addEmployee(int employee_id, int company_id, int grade);
        void removeEmployee(int employee_id);
        void employeeSalaryIncrease(int employee_id, int salary_increase);
        void promoteEmployee(int employee_id, int bump_grade);
        //company functions
        void acquireCompany(int acquirer_id, int target_id, double factor);
        void companyValue(int company_id, void* standing);
        //DS functions
        void sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m, void* sumBumpGrade);
        void averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary, void* average_bump_grade);
};

#endif /* UF_COMPANIES */