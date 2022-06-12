#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Company;

class Employee
{
    private:
        long int id;
        Company* company;
        long int salary;
        long int grade;
    
    public:
        Employee(const long int employee_id, Company* company, const long int salary, const long int grade);
        long int GetEmployeeId() const;
        Company* GetCompany() const;
        long int GetSalary() const;
        long int GetGrade() const;
        void SetCompany(Company* company);
        void SetSalary(const long int salary); 
        void SetGrade(const long int grade);
};

#endif /* EMPLOYEE_H_ */