#ifndef HASH_TABLE
#define HASH_TABLE

#include "Employee.h"
#include "LinkedList.h"
#include <exception>
#define SHRINK_EXPANSE_RATE 2
#define INITIAL_SIZE 10

class HashTable
{
    private:
        LinkedList* values;
        int occupancy;
        int table_size;

        void copyHash(int new_size, int prev_size, LinkedList* new_table, LinkedList* prev_table)
        {
            for (int i = 0; i < prev_size; i++)
            {
                Node* head = prev_table[i].getHead();
                while (head != nullptr)
                {
                    int new_index = (head->getData()->GetEmployeeId()) % new_size;
                    new_table[new_index].insert(head->getData());
                    head = head->getNext();
                }
            }
        }
        
        /**
         * @brief resize table with SHRINK_EXPANSE_RATE
         * 
         * @param expand if expand=True expanse table otherwise shrink table
         */
        void resizeTable(bool expand){
            int new_size = 0;
            if(expand){
                new_size = table_size * SHRINK_EXPANSE_RATE;
            }
            else{
                new_size = table_size / SHRINK_EXPANSE_RATE;   
            }
            LinkedList* new_values = new LinkedList[new_size];
            copyHash(new_size, table_size, new_values, values);
            LinkedList* temp = values;
            values = new_values;
            table_size = new_size;
            delete[] temp;
        }

    public:
        HashTable();
        ~HashTable() = default;

        class ElementNotInTable: public std::exception{};

        int getOccupancy();
        void setOccupancy(const int&);
        int getTableSize();
        LinkedList* getValues();
        Employee* find(const int& employee_id);
        void insert(Employee* employee);
        void remove(const int& employee_id);
};

#endif /* HASH_TABLE */