#ifndef HASH_TABLE
#define HASH_TABLE

#include "Employee.h"
#include "LinkedList.h"
#define SHRINK_EXPANSE_RATE 2
#define INITIAL_SIZE 10

class HashTable
{
    private:
        LinkedList* values;
        int occupancy;
        int table_size;

        void resizeTable();

    public:
        HashTable();
        ~HashTable() = default;

        bool Find(const int& employee_id);
        void Insert(Employee* employee);
        void Remove(const int& employee_id);
};

#endif /* HASH_TABLE */