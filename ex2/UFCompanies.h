#ifndef UF_COMPANIES
#define UF_COMPANIES

#include "Company.h"
#include "HashTable.h"

struct Group;

class UFNode{
    private:
        Company* company;
        Group* group;
        //added value for companies which purchased other companies according to the requirements of the exercise
        double fixer;
    public:
        UFNode(Company* company, Group* group):company(company), group(group), fixer(0){};
        ~UFNode(){delete company;}
        Company* getCompany(){return company;}
        Group* getGroup(){return group;}
        double getFixer(){return fixer;}
        void setGroup(Group* group){this->group = group;}
        void setFixer(double fixer){this->fixer = fixer;}
};

typedef struct Group
{
    int group_num;
    int num_elements;
    double total_value;
    UFNode* root;
}Group;


class UFCompanies{

    private:
        int num_companies;
        UFNode** company_nodes;
        Group* groups;
        int num_interns;
        int sum_interns_grades;
        HashTable all_employees;
        RankTree employees_with_salary;

    public:
        UFCompanies(int k);
        ~UFCompanies();
        //returns company name
        int Union(int group_a, int group_b);
        int Find(int company_id);
        //employee functions
        void addEmployee(int employee_id, int company_id, int grade);
        void removeEmployee(int employee_id);
        void employeeSalaryIncrease(int employee_id, int salaryIncrease);
        void promoteEmployee(int employee_id, int bump_grade);
        //company functions
        void acquireCompany(int acquirer_id, int target_id, double factor);
        void companyValue(int company_id, void* standing);
        //DS functions
        void sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m, void* sumBumpGrade);
        void averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary, void* average_bump_grade);
};

#endif /* UF_COMPANIES */