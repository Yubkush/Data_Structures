#include "../Tree.h"
#include "../Employee.h"


int main(){
    try{
        BinSearchTree<Employee*, int> tree();
    }
    catch(const std::bad_alloc){
        
    }

    Employee emp1(1234, 1, 100, 1);
    Employee emp2(1212, 1, 100, 1);
    Employee emp3(1333, 1, 100, 1);

    return 0;
}