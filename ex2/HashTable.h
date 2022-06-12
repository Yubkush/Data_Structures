#ifndef HASH_TABLE
#define HASH_TABLE

#include "Employee.h"
#include "LinkedList.h"
#include <exception>
#define SHRINK_EXPANSE_RATE 2
#define INITIAL_SIZE 10
#define SIZE_AFTER_CLEAR 4

class HashTable
{
    private:
        LinkedList* values;
        long int occupancy;
        long int table_size;

        void copyHash(long int new_size, long int prev_size, LinkedList* new_table, LinkedList* prev_table)
        {
            for (long int i = 0; i < prev_size; i++)
            {
                Node* head = prev_table[i].getHead();
                while (head != nullptr)
                {
                    long int new_index = (head->getData()->GetEmployeeId()) % new_size;
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
            long int new_size = 0;
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
        ~HashTable();
        void destroyHashData();
        void clearHash();

        class ElementNotInTable: public std::exception{};

        long int getOccupancy();
        void setOccupancy(const long int&);
        long int getTableSize();
        LinkedList* getValues();
        Employee* find(const long int& employee_id);
        void insert(Employee* employee);
        void remove(const long int& employee_id);
};

#endif /* HASH_TABLE */