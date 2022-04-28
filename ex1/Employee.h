#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Company;

class Employee
{
    private:
        int id;
        Company* company;
        int salary;
        int grade;
        Company* company;
    
    public:
        Employee(const int employee_id, Company* company, const int salary, const int grade);
        int GetEmployeeId() const;
        Company* GetCompany() const;
        int GetSalary() const;
        int GetGrade() const;
        void SetCompany(Company* company);
        void SetSalary(const int salary); 
        void SetGrade(const int grade);
};

#endif /* EMPLOYEE_H_ */