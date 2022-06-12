#ifndef COMPANY_H_
#define COMPANY_H_

#include "Employee.h"
#include "RankTree.h"
#include "HashTable.h"
#include <exception>

class Employee;

class Company
{
    private:
        int id;
        int value;
        long int num_of_interns;
        long int sum_of_interns_grades;
        HashTable all_employees;
        RankTree employees_with_salary;

    public:
        class EmployeesUnderZero: public std::exception{};
        class EmployeeAlreadyInCompany: public std::exception{};
        class EmployeeNotInCompany: public std::exception{};
        Company(const int id, const int value);
        ~Company() = default;

        //Getters
        int getId() const;
        int getValue() const;
        long int getNumOfInterns() const;
        long int getSumOfInternsGrades() const;
        RankTree& getEmployeesWithSalaryTree();
        HashTable& getEmployeesHash();
        //setters
        void setValue(int value);
        void increaseNumOfInterns(long int num_of_interns);
        void increaseSumOfInternsGrades(long int sum_of_interns_grades);

        //O(1) without insert to employees tree
        void AddEmployee(Employee* employee);
        void removeEmployee(Employee* employee);
};

#endif /* COMPANY_H_ */