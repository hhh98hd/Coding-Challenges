// https://leetcode.com/problems/linked-list-cycle-ii/

#include <iostream>
#include <unordered_map>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* detectCycle(ListNode* head) {
    if (nullptr == head || nullptr == head->next)
        return nullptr;

    ListNode* slowPtr = head;
    ListNode* fastPtr = head;

    while (fastPtr && fastPtr->next) {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;

        if(slowPtr == fastPtr) {
            ListNode* cycleEntry = head;

            while(cycleEntry != slowPtr) {
                cycleEntry = cycleEntry->next;
                slowPtr = slowPtr->next;
            }

            return cycleEntry;
        }
    }

    return nullptr;
}

int main() {
    ListNode* node1 = new ListNode(3);
    ListNode* node2 = new ListNode(2);
    ListNode* node3 = new ListNode(0);
    ListNode* node4 = new ListNode(-4);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node1;

    std::unordered_map<ListNode*, int> nodeMap = {
        {node1, 0},
        {node2, 1},
        {node3, 2},
        {node4, 3},
    };

    ListNode* cycleDetected =  detectCycle(node1);

    if(nullptr == cycleDetected) {
        std::cout << "No cycle detected in this linked list";
    } else {
        std::cout << "Cycle detected at index " << nodeMap[cycleDetected] << std::endl;
    }
}