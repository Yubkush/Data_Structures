#include "HashTable.h"

HashTable::HashTable() : values(new LinkedList[INITIAL_SIZE]), occupancy(0), table_size(INITIAL_SIZE)
{

}

HashTable::~HashTable()
{
    delete[] values;
}

void HashTable::destroyHashData()
{
    for (int i = 0; i < table_size; i++)
    {
        Node* head = values[i].getHead();
        while(head != nullptr)
        {
            delete head->getData();
            head = head->getNext();
        }
    }
}

void HashTable::clearHash()
{
    //empty values
    for (int i = 0; i < table_size; i++)
    {
        while(values[i].getHead() != nullptr)
        {
            values[i].remove(values[i].getHead()->getData()->GetEmployeeId());
        }
    }
    LinkedList* new_values = new LinkedList[SIZE_AFTER_CLEAR];
    LinkedList* temp = values;
    values = new_values;
    table_size = SIZE_AFTER_CLEAR;
    occupancy = 0;
    delete[] temp;
}

int HashTable::getOccupancy(){
    return occupancy;
}
int HashTable::getTableSize(){
    return table_size;
}
LinkedList* HashTable::getValues(){
    return values;
}

void HashTable::setOccupancy(const int& occupancy){
    this->occupancy = occupancy;
}

Employee* HashTable::find(const int& employee_id)
{
    Employee* temp;
    try{
        temp = values[employee_id % table_size].find(employee_id);
    }
    catch(LinkedList::ElementNotInList& e){
        throw ElementNotInTable();
    }
    return temp;
}

void HashTable::insert(Employee* employee)
{
    if(table_size == occupancy){
        resizeTable(true);
    }
    values[employee->GetEmployeeId() % table_size].insert(employee);
    occupancy++;
}

void HashTable::remove(const int& employee_id)
{
    if(occupancy <= (table_size / (SHRINK_EXPANSE_RATE * SHRINK_EXPANSE_RATE)) && (table_size > 5)){
        resizeTable(false);
    }
    try{
        values[employee_id % table_size].remove(employee_id);
        occupancy--;
    }
    catch(LinkedList::ElementNotInList& e){
        throw ElementNotInTable();
    }
}