#include "UnionFind.h"

UnionFind::UnionFind(int k):num_companies(k), company_nodes(new UFNode*[k+1]), groups(new Group[k+1])
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

UnionFind::~UnionFind()
{
    for (int i = 1; i < num_companies+1; i++)
    {
        delete company_nodes[i]->getCompany();
        delete company_nodes[i];
    }
    delete[] groups;
    delete[] company_nodes;
}

//Assume that we get 2 groups
//b acquire a
void UnionFind::Union(int group_a, int group_b, double factor)
{
    UFNode* group_a_root = groups[group_a].root;
    UFNode* group_b_root = groups[group_b].root;
    if(groups[group_a].num_elements < groups[group_b].num_elements){
        group_a_root->setParent(group_b_root);
        //update total_value
        groups[group_b].total_value += factor*(groups[group_a].total_value);
        //update fixers
        group_b_root->setFixer(group_b_root->getFixer() + (groups[group_a].total_value * factor));
        group_a_root->setFixer(group_a_root->getFixer() - group_b_root->getFixer());
    }
    else{
        group_b_root->setParent(group_a_root);
        group_a_root->setGroup(group_b_root->getGroup());
        groups[group_b].root = group_a_root;
        //update total_value
        groups[group_b].total_value += factor*(groups[group_a].total_value);
        //update fixers
        group_b_root->setFixer(group_b_root->getFixer() + ((factor)*groups[group_a].total_value) - group_a_root->getFixer());
    }
    groups[group_b].num_elements += groups[group_a].num_elements;
}

int UnionFind::Find(int company_id)
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

double UnionFind::getCompanyValue(int company_id)
{
    UFNode* start = company_nodes[company_id];
    double sum_fixers = start->getCompany()->getValue();
    while(start != nullptr)
    {
        sum_fixers += start->getFixer();
        start = start->getParent();
    }
    return sum_fixers;
}

Company* UnionFind::getCompany(int company_id)
{
    return company_nodes[company_id]->getCompany();
}