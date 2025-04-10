// https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem?isFullScreen=true

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node *p, Node *n, int k, int val) : prev(p), next(n), key(k), value(val) {};
   Node(int k, int val) : prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache{
protected: 
    map<int,Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    LRUCache(int capacity) {
        this->cp = capacity;
    };

    void set(int key, int val) {
        if(0 == this->mp.size()) {
            Node* newNode = new Node(key, val);
            this->tail = newNode;
            this->mp[key] = tail;
            this->head = this->tail;

            return;
        }

        if(this->mp.size() < this->cp) {
            Node* newNode = new Node(key, val);
            
            if(1 == mp.size()) {
                this->tail->prev = newNode;
                this->head = newNode;
                this->head->next = tail;
            } else {
                newNode->next = this->head;
                this->head->prev = newNode;
                this->head = newNode;
            }
                
            this->mp[key] = newNode;
        } else {
            auto it = this->mp.find(key);

            if(it == this->mp.end()) {
                // Cache miss
                Node* newNode = new Node(key, val);
                this->mp[key] = newNode;

                // Append a new head
                Node* headNode = this->head;
                this->head = newNode;
                this->head->next = headNode;

                // Trim the last node in the linked list
                Node* tailNode = this->tail;
                this->tail = this->tail->prev;
                this->tail->next = nullptr;

                this->mp.erase(tailNode->key);
                delete tailNode;

            } else {
                // Cache hit
                // This node was accessed the last time so it is already at the the head of the linked list
                if(this->head->key == key) {
                    this->head->value = val;
                    return;
                }

                if(this->tail->key == key) {
                    this->tail->value = val;

                    Node* headNode = this->head;
                    Node* nextHead = this->head->next;
                    Node* prevTail = this->tail->prev;

                    this->head = this->tail;
                    this->head->next = headNode;
                    headNode->prev = this->head;
                    this->tail = prevTail;
                    this->tail->next = nullptr;
                    
                    return;
                }

                Node* node = it->second;
                node->value = val;

                Node* prevNode = node->prev;
                Node* nextNode = node->next;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;

                Node* headNode = this->head;                

                this->head = node;
                this->head->next = headNode;
                headNode->prev = this->head;     
            }
        }
    }

    int get(int key) {
        auto it = this->mp.find(key);
        if(it != this->mp.end())
            return it->second->value;
        else
            return -1;
    }

    friend ostream& operator<<(ostream& os, const LRUCache& cache) {
        Node* cur = cache.head;

        while (cur != nullptr) {
            os << "(" << cur->key << ", " << cur->value << ") ";
            cur = cur->next;
        }

        return os;
    }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
