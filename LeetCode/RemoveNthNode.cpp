// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* removeNthFromEnd(ListNode* head, int n) {
    int nodeCnt = 0;
    ListNode *tail = head, *prevRemove = head;

    if(nullptr == head)
        return nullptr;

    if(nullptr == head->next) {
        delete head;
        return nullptr;
    }

    while(tail->next != nullptr) {
        tail = tail->next;
        nodeCnt += 1;

        if(nodeCnt > n) {
            prevRemove = prevRemove->next;
        }
    }
    nodeCnt += 1;

    if(n == nodeCnt) {
        head = head->next;
        return head;
    }

    prevRemove->next = prevRemove->next->next;

    return head;
}
