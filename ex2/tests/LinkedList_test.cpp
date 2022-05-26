#include "../Employee.h"
#include "../LinkedList.h"
#include "gtest/gtest.h"

#include <vector>

using std::vector;

TEST(InsertElements, InsertToEmptyList) {
    LinkedList employees_list;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 3; i++)
    {
        employees_vector.push_back(new Employee(i,nullptr,i,i));
    }
    EXPECT_EQ(employees_list.getHead(), nullptr);
    for (int i = 0; i < 3; i++)
    {
        employees_list.insert(employees_vector[i]);
        EXPECT_NE(employees_list.getHead(), nullptr);
        EXPECT_EQ(employees_list.getHead()->getData()->GetEmployeeId(), i);
    }
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}

TEST(RemoveElements, RemoveElementsFromList) {
    LinkedList employees_list;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 3; i++)
    {
        employees_vector.push_back(new Employee(i,nullptr,i,i));
    }
    EXPECT_THROW(employees_list.remove(employees_vector[1]->GetEmployeeId()), LinkedList::ElementNotInList);
    for (int i = 0; i < 3; i++)
    {
        employees_list.insert(employees_vector[i]);
    }
    EXPECT_NO_THROW(employees_list.remove(employees_vector[0]->GetEmployeeId()));
    EXPECT_THROW(employees_list.remove(employees_vector[0]->GetEmployeeId()), LinkedList::ElementNotInList);
    for (int i = 0; i < 3; i++)
    {
        employees_list.insert(employees_vector[i]);
    }
    EXPECT_NO_THROW(employees_list.remove(employees_vector[2]->GetEmployeeId()));
    EXPECT_NO_THROW(employees_list.remove(employees_vector[2]->GetEmployeeId()));
    EXPECT_THROW(employees_list.remove(employees_vector[2]->GetEmployeeId()), LinkedList::ElementNotInList);
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}

TEST(FindElements, FindInEmptyList) {
    LinkedList employees_list;
    EXPECT_THROW(employees_list.find(0), LinkedList::ElementNotInList);
    EXPECT_THROW(employees_list.find(1), LinkedList::ElementNotInList);
    EXPECT_THROW(employees_list.find(2), LinkedList::ElementNotInList);
}

TEST(FindElements, FindInList) {
    LinkedList employees_list;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 3; i++)
    {
        employees_vector.push_back(new Employee(i,nullptr,i,i));
    }
    for (int i = 0; i < 3; i++)
    {
        employees_list.insert(employees_vector[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        Employee* e = employees_list.find(employees_vector[i]->GetEmployeeId());
        EXPECT_EQ(i, e->GetEmployeeId());
    }
    EXPECT_THROW(employees_list.find(6), LinkedList::ElementNotInList);
    EXPECT_THROW(employees_list.find(10), LinkedList::ElementNotInList);
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}