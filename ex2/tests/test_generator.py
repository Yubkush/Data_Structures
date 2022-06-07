import random

LOWER_COMPANY = -5
HIGHER_COMPANY = 15
LOWER_ID = -10
HIGHER_ID = 500
LOWER_FACTOR = -1.000
HIGHER_FACTOR = 5.000
LOWER_SALARY = -10
HIGHER_SALARY = 100
LOWER_GRADE = -10
HIGHER_GRADE = 100
LOWER_M = -10
HIGHER_M = 100
LOWER_LOWERSALARY = -10
HIGHER_LOWERSALARY = 100
LOWER_HIGHERSALARY = -10
HIGHER_HIGHERSALARY = 1000


def AddEmployee(filename):
    id = random.randint(LOWER_ID, HIGHER_ID)
    company = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    grade = random.randint(LOWER_GRADE, HIGHER_GRADE)
    with open(filename, "a") as inputfile:
        inputfile.write(f"AddEmployee {id} {company} {grade}\n")


def RemoveEmployee(filename):
    id = random.randint(LOWER_ID, HIGHER_ID)
    with open(filename, "a") as inputfile:
        inputfile.write(f"RemoveEmployee {id}\n")


def AcquireCompany(filename):
    acquirer = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    target = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    factor = round(random.uniform(LOWER_FACTOR,HIGHER_FACTOR), 3)
    with open(filename, "a") as inputfile:
        inputfile.write(f"AcquireCompany {acquirer} {target} {factor}\n")


def EmployeeSalaryIncrease(filename):
    id = random.randint(LOWER_ID, HIGHER_ID)
    salary = random.randint(LOWER_SALARY, HIGHER_SALARY)
    with open(filename, "a") as inputfile:
        inputfile.write(f"EmployeeSalaryIncrease {id} {salary}\n")


def PromoteEmployee(filename):
    id = random.randint(LOWER_ID, HIGHER_ID)
    grade = random.randint(LOWER_GRADE, HIGHER_GRADE)
    with open(filename, "a") as inputfile:
        inputfile.write(f"PromoteEmployee {id} {grade}\n")


def SumOfBumpGradeBetweenTopWorkersByGroup(filename):
    company = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    m = random.randint(LOWER_M, HIGHER_M)
    with open(filename, "a") as inputfile:
        inputfile.write(f"SumOfBumpGradeBetweenTopWorkersByGroup  {company} {m}\n")


def AverageBumpGradeBetweenSalaryByGroup(filename):
    company = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    lower_salary = random.randint(LOWER_LOWERSALARY, HIGHER_LOWERSALARY)
    higher_salary = random.randint(LOWER_HIGHERSALARY, HIGHER_HIGHERSALARY)
    with open(filename, "a") as inputfile:
        inputfile.write(f"AverageBumpGradeBetweenSalaryByGroup  {company} {lower_salary} {higher_salary}\n")


def CompanyValue(filename):
    company = random.randint(LOWER_COMPANY, HIGHER_COMPANY)
    with open(filename, "a") as inputfile:
        inputfile.write(f"CompanyValue {company}\n")


def generate_test(test_num):
    filename = f"generated_tests/test_input{test_num}.txt"
    testfile = open(filename, "w+")
    testfile.write("Init 10\n")
    testfile.close()

    functions = [AddEmployee, 
                RemoveEmployee, 
                AcquireCompany, 
                EmployeeSalaryIncrease, 
                PromoteEmployee,
                SumOfBumpGradeBetweenTopWorkersByGroup,
                AverageBumpGradeBetweenSalaryByGroup,
                CompanyValue]
    
    for _ in range(1, 101):
        AddEmployee(filename)
    
    for _ in range(1,3000):
        (random.choice(functions))(filename)
    
    with open(filename, "a") as inputfile:
        inputfile.write("Quit") 


def main():
    for i in range(0,100):
        generate_test(i)

main()