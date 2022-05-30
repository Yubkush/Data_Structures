#include "UFCompanies.h"

UFCompanies::UFCompanies(int k):num_companies(k), company_nodes(new UFNode*[k+1]), groups(new Group[k+1]), num_interns(0), 
                                sum_interns_grades(0), all_employees(), employees_with_salary()
{
    for (int i = 1; i < k+1; i++)
    {
        Company *company = new Company(i,i);
        groups[i].group_num = i;
        groups[i].num_elements = 1;
        groups[i].total_value = company->getValue();
        UFNode *node = new UFNode(company,&groups[i]);
        groups[i].root = node;
        company_nodes[i] = node;
    }
}

UFCompanies::~UFCompanies()
{
    //delete employees
    all_employees.destroyHashData();
    //deletes companies
    for (int i = 1; i < num_companies+1; i++)
    {
        delete company_nodes[i];
    }
    delete[] groups;
    delete[] company_nodes;
}

//Assume that we get 2 groups
//b acquire a
void UFCompanies::Union(int group_a, int group_b, double factor)
{
    UFNode* group_a_root = groups[group_a].root;
    UFNode* group_b_root = groups[group_b].root;
    groups[group_b].num_elements += groups[group_a].num_elements;
    if(groups[group_a].num_elements < groups[group_b].num_elements){
        group_a_root->setParent(group_b_root);
        //update total_value
        groups[group_b].total_value += factor*(groups[group_a].total_value)*(groups[group_a].num_elements);
        //update fixers
        group_b_root->setFixer(group_b_root->getFixer() + (groups[group_a].total_value * factor));
        group_a_root->setFixer(group_a_root->getFixer() - group_b_root->getFixer());
    }
    else{
        group_b_root->setParent(group_a_root);
        group_a_root->setGroup(group_b_root->getGroup());
        //update total_value
        groups[group_b].total_value += factor*(groups[group_a].total_value)*(groups[group_a].num_elements);
        //update fixers
        group_b_root->setFixer(group_b_root->getFixer() + groups[group_a].total_value - group_a_root->getFixer());
    }
}

int UFCompanies::Find(int company_id)
{
    //Node of interest
    UFNode* temp = company_nodes[company_id];
    //For fixing fixers during second phase of find
    int sum_fixers = 0, prev_fixer = 0;
    while(temp->getParent() != nullptr)
    {
        sum_fixers += temp->getFixer();
        temp = temp->getParent();
    }
    UFNode *root = temp, *next;
    //dont need root fixer in sum
    sum_fixers -= root->getFixer();
    int group_to_return = root->getGroup()->group_num;
    //temp returns to Node of interest
    temp = company_nodes[company_id];
    int to_subtract = 0;
    while (temp->getParent() != root && temp->getParent() != nullptr)
    {
        //changing fixers on our way up, and connecting all the nodes in the way to the root
        next = temp->getParent();
        prev_fixer = temp->getFixer();
        temp->setFixer(sum_fixers - to_subtract);
        to_subtract += prev_fixer;
        temp->setParent(root);
        temp = next;
    }
    return group_to_return;
}

// void UFCompanies::addEmployee(int employee_id, int company_id, int grade)

// void UFCompanies::removeEmployee(int employee_id)

// void UFCompanies::employeeSalaryIncrease(int employee_id, int salaryIncrease)

// void UFCompanies::promoteEmployee(int employee_id, int bump_grade)

// void UFCompanies::acquireCompany(int acquirer_id, int target_id, double factor)

// void UFCompanies::companyValue(int company_id, void* standing)

// void UFCompanies::sumOfBumpGradeBetweenTopWorkersByGroup(int company_id, int m, void* sumBumpGrade)

// void UFCompanies::averageBumpGradeBetweenSalaryByGroup(int company_id, int lower_salary, int higher_salary, void* average_bump_grade)

