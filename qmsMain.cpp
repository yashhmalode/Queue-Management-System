#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Node{
    public:
    int data;
    Node* next;

    Node(){
        data = 0;
        next = NULL;
    }
};

class Queue{
    Node* front;
    Node* rear;

    public:
    Queue(){
        front = NULL;
        rear = NULL;
    }

    void enQueue(int x){
        Node* newNode = new Node();
        newNode -> data = x;
        if (rear == NULL){
            front = rear = newNode;
        }
        else{
            rear -> next = newNode;
            rear = newNode;
        }
    }

    int deQueue(){
        if (front == NULL){
            cout << "Empty queue\n";
            return -1;
        }
        
        Node* temp = front;
        int data = temp -> data;
        front = front -> next;

        if (front == NULL) rear = NULL;

        delete temp;
        return data;
    }

    bool isEmpty(){
        if (front == NULL) return true;
        else return false;
    }

    int qSize(){
        Node* temp = front;
        int count = 0;
        while (temp != NULL){
            count++;
            temp = temp -> next;
        }
        return count;
    }

    int qFront(){
        if (front != NULL) return front -> data;
        else return -1;
    }

    void qDisplay(){
        Node* temp = front;
        while (temp != NULL){
            cout << temp -> data << " ";
            temp = temp -> next;
        }
        cout << endl;
    }
};

int arrMin(int arr[], int size){
    int min = 100;
    for(int i = 0; i <= size - 1; i++){
        if (arr[i] < min){
            min = arr[i];
        }
    }
    for(int i = 0; i <= size - 1; i++){
        if(arr[i] == min){
            return i;
            break;
        }
    }
}
//queueInitialize.cpp ends

//from addCustomer.cpp
struct Customer{
    int taskChoice;
    int arrivalTime;
    int tokenNum;
};

int addCustomer(int choice){
    Customer c;

    c.taskChoice = choice;

    string strChoice = to_string(choice);

    //Fetch system time
    time_t now = time(0);           // get current time
    tm *ltm = localtime(&now);      // convert to local time

    int hh = ltm->tm_hour;          // hours (0–23)
    int mm = ltm->tm_min;          // minutes (0–59)
    int ss = ltm->tm_sec;          // seconds (0-59)

    int timeArrival = hh * 60 * 60 + mm * 60 + ss;       // combinely tell seconds passed
    c.arrivalTime = timeArrival;

    string strTime = to_string(timeArrival);

    // Bank IFSC = XXXX0111111, here, 
    //the last six digits indicate the
    // bank branch location

    string branchLoc = "111111";

   

    c.tokenNum = stoi(strChoice + strTime);

    return c.tokenNum;
}


int main(){

    Queue accCreate1;
    Queue accCreate2;
    Queue accCreate3;
    Queue passEntry;
    Queue loanEnq;
    Queue forEx;
    Queue otherQuery;

    Queue* qArr[] = {&accCreate1, &accCreate2, &accCreate3, &passEntry, &loanEnq, &forEx, &otherQuery};
    int opt;

    while (true){
        cout << "########\n";
        cout << "1. Add to queue\n";
        cout << "2. View queues\n";
        cout << "3. Estimate wait time\n";
        cout << "4. Dequeue\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> opt;

        switch(opt) {
            case 1:
            {
                int task;
                cout << "Task choice: \n";
                cout << "1. Account creation\n";
                cout << "2. Passbook entry\n";
                cout << "3. Loan enquiry\n";
                cout << "4. Foreign exchange\n";
                cout << "5. Other queries\n";
                cout << "Enter choice : ";

                cin >> task;

                int token = addCustomer(task);
                cout << "Token number: " << token << endl;

                switch(task) {
                    case 1:
                    {
                        Queue* qArr[] = {&accCreate1, &accCreate2, &accCreate3};
                        int qSizeArr[] = {accCreate1.qSize(), accCreate2.qSize(), accCreate3.qSize()};
                        int arrSize = sizeof(qSizeArr) / sizeof(qSizeArr[0]);

                        int idx = arrMin(qSizeArr, arrSize);
                        qArr[idx]->enQueue(token);
                        cout << "Head to counter " << idx + 1 << endl;
                        break;       
                    }

                    case 2:
                    {
                        passEntry.enQueue(token);
                        cout << "Head to counter " << task + 2 << endl;
                        break;
                    }

                    case 3:
                    {
                        loanEnq.enQueue(token);
                        cout << "Head to counter " << task + 2 << endl;
                        break;
                    }

                    case 4:
                    {
                        forEx.enQueue(token);
                        cout << "Head to counter " << task + 2 << endl;
                        break;
                    }

                    case 5:
                    {
                        otherQuery.enQueue(token);
                        cout << "Head to counter " << task + 2 << endl;
                        break;
                    }
                    
                    default:
                    {
                        cout << "Enter valid task choice\n" << endl;    
                    }
                }
                break;
            }
            
            case 2:
            {
                

                for (int i = 1; i <= (sizeof(qArr) / sizeof(qArr[0])); i++){
                    cout << "Counter " << i << ": ";
                    qArr[i-1]->qDisplay();
                }
                break;
            }

            case 3:
            {
                float avgWait[] = {5, 5, 5, 2, 8, 3.5, 6.5};
                cout << "Estimated waiting times: " << endl;
                for (int i = 1; i <= (sizeof(qArr) / sizeof(qArr[0])); i++){
                    cout << "Counter " << i << ": ";
                    cout << qArr[i-1]->qSize() * avgWait[i-1] << " minutes\n";
                }
                break;
            }
            case 4:
            {
                int counter;
                cout << "Counter to dequeue: ";
                cin >> counter;

                if (counter >= 1 && counter <= (sizeof(qArr) / sizeof(qArr[0]))){
                    if(qArr[counter - 1]->qFront() == - 1){
                        cout << "Empty Queue" << endl;
                    }
                    
                    if(qArr[counter - 1]->qFront() != - 1){
                        cout << "Dequeued " << qArr[counter - 1]->qFront() << endl;
                        qArr[counter - 1]->deQueue();
                    }  
                                     
                }

                else {
                    cout << "Invalid counter number";
                }
                break;
            }
        }
        if (opt == 5){
            break;
        }
    }
}
