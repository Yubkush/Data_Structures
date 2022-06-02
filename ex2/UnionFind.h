#ifndef UNION_FIND
#define UNION_FIND

#include "Company.h"

struct Group;

class UFNode{
    private:
        Company* company;
        Group* group;
        //added value for companies which purchased other companies according to the requirements of the exercise
        double fixer;
        UFNode* parent;
    public:
        UFNode(Company* company, Group* group):company(company), group(group), fixer(0), parent(nullptr){};
        ~UFNode(){delete company;}
        Company* getCompany(){return company;}
        Group* getGroup(){return group;}
        double getFixer(){return fixer;}
        UFNode* getParent(){return parent;}
        void setGroup(Group* group){this->group = group;}
        void setFixer(double fixer){this->fixer = fixer;}
        void setParent(UFNode* parent){this->parent = parent;}
};

typedef struct Group
{
    int group_num;
    int num_elements;
    double total_value;
    UFNode* root;
}Group;

class UnionFind{
    private:
        int num_companies;
        UFNode** company_nodes;
        Group* groups;
    public:
        UnionFind(int k);
        ~UnionFind();

        /**
         * @brief group b acquire a
         * 
         * @param group_a group_a id
         * @param group_b group_b id
         * @param factor all companies in group b add factor*(group_a.value)
         */
        void Union(int group_a, int group_b, double factor);
        //returns company name
        int Find(int company_id);
        double getCompanyValue(int company_id);
        //O(1)
        Company* getCompany(int company_id);
};

#endif /* UNION_FIND */