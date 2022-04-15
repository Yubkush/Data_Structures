#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee
{
    private:
        int id;
        int company_id;
        int salary;
        int grade;
    
    public:
        Employee(const int employee_id, const int company_id, const int salary, const int grade);
        int GetEmployeeId() const;
        int GetCompanyId() const;
        int GetSalary() const;
        int GetGrade() const;
        void SetCompanyId(const int company_id);
        void SetSalary(const int salary); 
        void SetGrade(const int grade);
        bool operator<(const Employee& employee) const;
};

#endif /* EMPLOYEE_H_ */