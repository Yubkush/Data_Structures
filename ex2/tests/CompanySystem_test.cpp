#include "../CompanySystem.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>

class CompanySystemTest : public ::testing::Test{
    public:
        CompanySystem ds;
    
    protected:
        CompanySystemTest(): ds(10){}
        ~CompanySystemTest() = default;
};

TEST_F(CompanySystemTest, AddEmployeeTest)
{
    std::ofstream myfile ("test_in0.txt");
    EXPECT_NO_THROW(ds.addEmployee(1,1,1));
    myfile << "AddEmployee 1 1 1\n";
    EXPECT_NO_THROW(ds.addEmployee(2,2,2));
    myfile << "AddEmployee 2 2 2\n";
    EXPECT_NO_THROW(ds.addEmployee(3,3,3));
    myfile << "AddEmployee 3 3 3\n";
    EXPECT_NO_THROW(ds.addEmployee(4,4,4));
    myfile << "AddEmployee 4 4 4\n";
    EXPECT_NO_THROW(ds.addEmployee(5,5,5));
    myfile << "AddEmployee 5 5 5\n";
    EXPECT_NO_THROW(ds.addEmployee(6,6,6));
    myfile << "AddEmployee 6 6 6\n";
    EXPECT_NO_THROW(ds.addEmployee(7,7,7));
    myfile << "AddEmployee 7 7 7\n";
    EXPECT_NO_THROW(ds.addEmployee(8,8,8));
    myfile << "AddEmployee 8 8 8\n";
    EXPECT_NO_THROW(ds.addEmployee(9,9,9));
    myfile << "AddEmployee 9 9 9\n";
    EXPECT_NO_THROW(ds.addEmployee(10,10,10));
    myfile << "AddEmployee 10 10 10\n";
    EXPECT_THROW(ds.addEmployee(1,1,1), CompanySystem::EmployeeAlreadyInSystem);
    myfile << "AddEmployee 1 1 1\n";
    EXPECT_THROW(ds.addEmployee(2,4,10), CompanySystem::EmployeeAlreadyInSystem);
    myfile << "AddEmployee 2 4 10\n";
}

TEST_F(CompanySystemTest, SalaryIncreaseTest)
{
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,i,i));
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));
    }
    EXPECT_THROW(ds.employeeSalaryIncrease(20, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(11, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(34, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(100, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(91923, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(1000000, 14), CompanySystem::EmployeeNotInSystem);
}

TEST_F(CompanySystemTest, SalaryIncreaseSameCompanyTest)
{
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,1,i));
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));
    }
    EXPECT_THROW(ds.employeeSalaryIncrease(20, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(11, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(34, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(100, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(91923, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.employeeSalaryIncrease(1000000, 14), CompanySystem::EmployeeNotInSystem);
}

TEST_F(CompanySystemTest, PromoteEmployeeTest)
{
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,i,i));
        EXPECT_NO_THROW(ds.promoteEmployee(i, i));
    }
    EXPECT_THROW(ds.promoteEmployee(20, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(11, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(34, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(100, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(91923, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(1000000, 14), CompanySystem::EmployeeNotInSystem);

    for (int i = 1; i < 6; i++)
    {
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));
        EXPECT_NO_THROW(ds.promoteEmployee(i, i));
    }
}

TEST_F(CompanySystemTest, PromoteEmployeeSameCompanyTest)
{
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,1,i));
        EXPECT_NO_THROW(ds.promoteEmployee(i, i));
    }
    EXPECT_THROW(ds.promoteEmployee(20, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(11, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(34, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(100, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(91923, 14), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.promoteEmployee(1000000, 14), CompanySystem::EmployeeNotInSystem);

    for (int i = 1; i < 6; i++)
    {
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));
        EXPECT_NO_THROW(ds.promoteEmployee(i, i));
    }
}

TEST_F(CompanySystemTest, RemoveEmployeeTest)
{
    EXPECT_THROW(ds.removeEmployee(5), CompanySystem::EmployeeNotInSystem);
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,i,i));
    }
    for (int i = 1; i < 11; i+=2)
    {
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));   
    }
    EXPECT_NO_THROW(ds.removeEmployee(1));
    EXPECT_THROW(ds.removeEmployee(1), CompanySystem::EmployeeNotInSystem);
    EXPECT_NO_THROW(ds.removeEmployee(5));
    EXPECT_THROW(ds.removeEmployee(5), CompanySystem::EmployeeNotInSystem);
    EXPECT_NO_THROW(ds.removeEmployee(10));
    EXPECT_THROW(ds.removeEmployee(10), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(21), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(566), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(65465), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(1111), CompanySystem::EmployeeNotInSystem);
}

TEST_F(CompanySystemTest, RemoveEmployeeTestSameCompany)
{
    EXPECT_THROW(ds.removeEmployee(5), CompanySystem::EmployeeNotInSystem);
    for (int i = 1; i < 11; i++)
    {
        EXPECT_NO_THROW(ds.addEmployee(i,1,i));
    }
    for (int i = 1; i < 11; i+=2)
    {
        EXPECT_NO_THROW(ds.employeeSalaryIncrease(i, i));   
    }
    EXPECT_NO_THROW(ds.removeEmployee(1));
    EXPECT_THROW(ds.removeEmployee(1), CompanySystem::EmployeeNotInSystem);
    EXPECT_NO_THROW(ds.removeEmployee(5));
    EXPECT_THROW(ds.removeEmployee(5), CompanySystem::EmployeeNotInSystem);
    EXPECT_NO_THROW(ds.removeEmployee(10));
    EXPECT_THROW(ds.removeEmployee(10), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(21), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(566), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(65465), CompanySystem::EmployeeNotInSystem);
    EXPECT_THROW(ds.removeEmployee(1111), CompanySystem::EmployeeNotInSystem);
}

TEST_F(CompanySystemTest, AcquireCompanyTest)
{
    double standing;
    EXPECT_NO_THROW(ds.acquireCompany(1, 4, 2));
    EXPECT_THROW(ds.acquireCompany(4, 1, 2), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&standing)));
    EXPECT_EQ(standing, 4.0);
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&standing)));
    EXPECT_EQ(standing, 9.0);
    EXPECT_NO_THROW(ds.acquireCompany(6, 7, 1));
    EXPECT_THROW(ds.acquireCompany(7, 6, 2), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.companyValue(7, (void*)(&standing)));
    EXPECT_EQ(standing, 7.0);
    EXPECT_NO_THROW(ds.companyValue(6, (void*)(&standing)));
    EXPECT_EQ(standing, 13.0);
    EXPECT_NO_THROW(ds.acquireCompany(6, 8, 1));
    EXPECT_THROW(ds.acquireCompany(8, 6, 2), CompanySystem::SameCompany);
    EXPECT_THROW(ds.acquireCompany(8, 7, 2), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.companyValue(8, (void*)(&standing)));
    EXPECT_EQ(standing, 8.0);
    EXPECT_NO_THROW(ds.companyValue(7, (void*)(&standing)));
    EXPECT_EQ(standing, 15.0);
    EXPECT_NO_THROW(ds.companyValue(6, (void*)(&standing)));
    EXPECT_EQ(standing, 21.0);
    EXPECT_NO_THROW(ds.acquireCompany(6, 1, 1));
    EXPECT_THROW(ds.acquireCompany(8, 1, 2), CompanySystem::SameCompany);
    EXPECT_THROW(ds.acquireCompany(8, 4, 2), CompanySystem::SameCompany);
    EXPECT_THROW(ds.acquireCompany(7, 1, 2), CompanySystem::SameCompany);
    EXPECT_THROW(ds.acquireCompany(7, 4, 2), CompanySystem::SameCompany);
    EXPECT_THROW(ds.acquireCompany(4, 6, 2), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&standing)));
    EXPECT_EQ(standing, 4.0);
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&standing)));
    EXPECT_EQ(standing, 9.0);
    EXPECT_NO_THROW(ds.companyValue(6, (void*)(&standing)));
    EXPECT_EQ(standing, 30.0);
    EXPECT_NO_THROW(ds.companyValue(7, (void*)(&standing)));
    EXPECT_EQ(standing, 24.0);
    EXPECT_NO_THROW(ds.companyValue(8, (void*)(&standing)));
    EXPECT_EQ(standing, 17.0);
}

TEST_F(CompanySystemTest, Note342Test)
{
    double val;
    EXPECT_NO_THROW(ds.acquireCompany(1, 4, 2));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 9.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 4.0);
    EXPECT_NO_THROW(ds.acquireCompany(4, 3, 1));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 12.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 7.0);
    EXPECT_NO_THROW(ds.companyValue(3, (void*)(&val)));
    EXPECT_EQ(val, 3.0);
    EXPECT_THROW(ds.acquireCompany(1, 3, 1), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.acquireCompany(2, 4, 1));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 12.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 7.0);
    EXPECT_NO_THROW(ds.companyValue(3, (void*)(&val)));
    EXPECT_EQ(val, 3.0);
    EXPECT_NO_THROW(ds.companyValue(2, (void*)(&val)));
    EXPECT_EQ(val, 14.0);
}

TEST_F(CompanySystemTest, Note342extraTest)
{
    double val;
    EXPECT_NO_THROW(ds.acquireCompany(1, 4, 2));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 9.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 4.0);
    EXPECT_NO_THROW(ds.acquireCompany(4, 3, 1));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 12.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 7.0);
    EXPECT_NO_THROW(ds.companyValue(3, (void*)(&val)));
    EXPECT_EQ(val, 3.0);
    EXPECT_THROW(ds.acquireCompany(1, 3, 1), CompanySystem::SameCompany);
    EXPECT_NO_THROW(ds.acquireCompany(4, 2, 1));
    EXPECT_NO_THROW(ds.companyValue(1, (void*)(&val)));
    EXPECT_EQ(val, 14.0);
    EXPECT_NO_THROW(ds.companyValue(4, (void*)(&val)));
    EXPECT_EQ(val, 9.0);
    EXPECT_NO_THROW(ds.companyValue(3, (void*)(&val)));
    EXPECT_EQ(val, 5.0);
    EXPECT_NO_THROW(ds.companyValue(2, (void*)(&val)));
    EXPECT_EQ(val, 2.0);
}