// Zadacha_4.cpp : 
//Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
using namespace std;
struct  List
{
    char data;
    int pos;
    List* next;
    List* prev;
};

void addtohead(List*& head, List*& tail, char data)
{
    List* newNode = new List();
    newNode->data = data;
    newNode->pos = 1;
    if (head == nullptr && tail == nullptr)
    {
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
    }
    head = newNode;
    tail->next = head;
    head->prev = tail;
    //в списке ровно 2 узла, не делаем цикл, т.к. он не сработает
    if (head != tail && head->next == tail) {
        tail->pos = 2;
    }
    else
    {
        List* cur = head->next;
        while (cur != head) {
            cur->pos++;
            cur = cur->next;
        }
    }
}
void show(List* head, List* tail)
{
    if (head == nullptr) cout << "Список пуст" << endl;
    else
    {
        List* cur = head;
        while (cur != tail)
        {
            cout << cur->data << " -> " << cur->pos << " ";
            cur = cur->next;
        }
        cout << tail->data << " -> " << tail->pos << " ";
        cout << endl;
    }
}
void delnode(List*& head, List*& tail, int pos) {
    List* temp;
    //Удаляем голову
    if (pos == head->pos) {
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            temp = head;
            head = head->next;
            head->prev = tail;
            delete temp;
        }
    }
    //Удаляем хвост
    else 
        if (pos == tail->pos)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = head;
            delete temp;
        }
    //удаляем узел между головой и хвостом
        else
        {
            List* cur = head;
            while (cur->pos != pos) {
                cur = cur->next;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
        }
}
void deletelist(List*& head, List*& tail) {
    List* temp;
    while (head != tail) {
        temp = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete temp;
    }
    delete tail;
    head = tail = nullptr;
}
void del(List*& head, List*& tail, int k) {
    //удаляем весь список
    if (k == 1) deletelist(head, tail);
    //удаляем избранные позиции
    else {
        List* cur = head;
        while (cur != tail) {
            if (cur->pos % k == 0) {
                int pos = cur->pos;
                cur = cur->prev;
                delnode(head, tail, pos);
            }
            cur = cur->next;
        }
        if (tail->pos % k == 0) 
        {
            delnode(head, tail, tail->pos);
        }
        head->pos = 1;
        cur = head->next;
        while (cur != tail) 
        {
            cur->pos = cur->prev->pos + 1;
            cur = cur->next;
        }
        tail->pos = tail->prev->pos + 1;
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    int count;
    int i = 0;

    List* head = nullptr; List* tail = nullptr;
    cout << "Введите число узлов" << endl;
    cin >> count;
    for (int i = 0; i < count; i++) {
        char data;
        cin >> data;
        addtohead(head, tail, data);
    }
    show(head, tail);
    int k;
    cout << "Введите какие позиции удалить" << endl;
    cin >> k;
    del(head, tail, k);
    show(head, tail);
}

