#ifndef LINKED_LIST
#define LINKED_LIST

#include <exception>
#include "Employee.h"

class Node
{
    private:
        Employee* data;
        Node* next;
    public:
        Node(Employee* data) : data(data), next(nullptr) {};
        Node(Employee* data, Node* next) : data(data), next(next) {};
        ~Node() = default;
        void setNext(Node* next){
            this->next = next;
        }
        void setData(Employee* data){
            this->data = data;
        }
        Node* getNext(){
            return this->next;
        }
        Employee* getData(){
            return this->data;
        }
};

class LinkedList
{
    private:
        Node* head;
    public:
        class ElementNotInList: public std::exception{};

        LinkedList() : head(nullptr){};
        ~LinkedList() {
            Node* temp = head;
            while(head != nullptr){
                temp = head;
                head = head->getNext();
                delete temp;
            }
        }

        Node* getHead(){
            return head;
        }
        
        void insert(Employee* data){
            Node* tmp = new Node(data, this->head);
            this->head = tmp;
        }

        void remove(const long int id){
            Node* temp = head;
            if(head == nullptr){
                throw ElementNotInList();
            }
            if(head->getData()->GetEmployeeId() == id){
                head = head->getNext();
                delete temp;
            }
            else{
                while(temp->getNext() != nullptr && temp->getNext()->getData()->GetEmployeeId() != id)
                {
                    temp = temp->getNext();
                }
                if(temp->getNext() != nullptr && temp->getNext()->getData()->GetEmployeeId() == id){
                    Node* to_delete = temp->getNext();
                    temp->setNext(to_delete->getNext());
                    delete to_delete;
                    to_delete = nullptr;
                }
                else{
                    throw ElementNotInList();
                }
            }
        }

        Employee* find(const long int id){
            Node* temp = head;
            while(temp != nullptr && temp->getData()->GetEmployeeId() != id)
            {
                temp = temp->getNext();
            }
            if(temp == nullptr){
                throw ElementNotInList();
            }
            return temp->getData();
        }
};

#endif /* LINKED_LIST */