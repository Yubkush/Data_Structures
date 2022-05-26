#include "../HashTable.h"
#include "../Employee.h"
#include <vector>
#include "gtest/gtest.h"

using std::vector;

TEST(ExceptionsTest, ExceptionsValidity)
{
    HashTable table;
    EXPECT_THROW(table.find(0), HashTable::ElementNotInTable);
    EXPECT_THROW(table.remove(0), HashTable::ElementNotInTable);
}

TEST(InsertTest, InsertElementsAndExpand)
{
    HashTable table;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 15; i++)
    {
        employees_vector.push_back(new Employee(i*7,nullptr,i,i));
        table.insert(employees_vector[i]);
    }
    EXPECT_EQ(15, table.getOccupancy());
    EXPECT_EQ(20, table.getTableSize());
    for (int i = 15; i < 60; i++)
    {
        employees_vector.push_back(new Employee(i*7,nullptr,i,i));
        table.insert(employees_vector[i]);
    }
    EXPECT_EQ(60, table.getOccupancy());
    EXPECT_EQ(80, table.getTableSize());
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}

TEST(findTest, findTest1)
{
    HashTable table;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 15; i++)
    {
        employees_vector.push_back(new Employee(i*7,nullptr,i,i));
        table.insert(employees_vector[i]);
    }
    for(auto e : employees_vector){
        Employee* found = table.find(e->GetEmployeeId());
        EXPECT_EQ(found->GetEmployeeId(), e->GetEmployeeId());
    }
    for(int i = 5; i < 35; i*=2){
        EXPECT_THROW(table.find(i), HashTable::ElementNotInTable);
    }
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}

TEST(removeTest, removeAll)
{
    HashTable table;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 15; i++)
    {
        employees_vector.push_back(new Employee(i*7,nullptr,i,i));
        table.insert(employees_vector[i]);
    }
    int occupancy = table.getOccupancy();
    //remove all employees
    for(auto e : employees_vector){
        table.remove(e->GetEmployeeId());
        occupancy--;
        EXPECT_EQ(table.getOccupancy(), occupancy);
    }
    EXPECT_EQ(table.getTableSize(), 5);
    for(auto e : employees_vector){
        EXPECT_THROW(table.find(e->GetEmployeeId()), HashTable::ElementNotInTable);
    }
    //insert 5 employees, size still 5
    for (int i = 3; i < 8; i++)
    {
        table.insert(employees_vector[i]);
    }
    EXPECT_EQ(table.getTableSize(), 5);
    EXPECT_EQ(table.getOccupancy(), 5);
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}

TEST(CombinedTest, Demo)
{
    HashTable table;
    vector<Employee*> employees_vector;
    for (int i = 0; i < 15; i++)
    {
        employees_vector.push_back(new Employee(i*7,nullptr,i,i));
        table.insert(employees_vector[i]);
    }
    EXPECT_EQ(table.getOccupancy(), 15);
    EXPECT_EQ(table.getTableSize(), 20);
    employees_vector.push_back(new Employee(92541,nullptr,92541,92541));
    table.insert(employees_vector[15]);
    employees_vector.push_back(new Employee(45212,nullptr,45212,45212));
    table.insert(employees_vector[16]);
    employees_vector.push_back(new Employee(843,nullptr,843,843));
    table.insert(employees_vector[17]);
    employees_vector.push_back(new Employee(9564,nullptr,9564,9564));
    table.insert(employees_vector[18]);
    employees_vector.push_back(new Employee(189,nullptr,189,189));
    table.insert(employees_vector[19]);
    employees_vector.push_back(new Employee(89898,nullptr,89898,89898));
    table.insert(employees_vector[20]);
    EXPECT_EQ(table.getOccupancy(), 21);
    EXPECT_EQ(table.getTableSize(), 40);
    for (int i = 0; i < 12; i++)
    {
        table.remove(i*7);
    }
    EXPECT_EQ(table.getOccupancy(), 9);
    EXPECT_EQ(table.getTableSize(), 20);
    EXPECT_THROW(table.find(666666), HashTable::ElementNotInTable);
    EXPECT_THROW(table.find(7), HashTable::ElementNotInTable);
    EXPECT_THROW(table.find(0), HashTable::ElementNotInTable);
    Employee* temp;
    EXPECT_NO_THROW(temp = table.find(92541)); 
    EXPECT_EQ(temp->GetGrade(), 92541);
    EXPECT_NO_THROW(temp = table.find(98));
    EXPECT_EQ(temp->GetGrade(), 14);
    EXPECT_NO_THROW(temp = table.find(89898));
    EXPECT_EQ(temp->GetGrade(), 89898);
    EXPECT_NO_THROW(temp = table.find(9564));
    EXPECT_EQ(temp->GetGrade(), 9564);
    for(auto e : employees_vector){
        delete e;
    }
    employees_vector.clear();
}