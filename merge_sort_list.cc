#include <iostream>
#include <vector>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {
    }
};

class Solution {
public:
    ListNode* MergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        if (l1->val <= l2->val) {
            l1->next = MergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = MergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    ListNode* MergeTwoLists2(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        ListNode *res = nullptr;
        if (l1->val <= l2->val) {
            res = l1;
            l1 = l1->next;
        } else {
            res = l2;
            l2 = l2->next;
        }
        ListNode *head = res;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                head->next = l1;
                head = head->next;
                l1 = l1->next;
            } else {
                head->next = l2;
                head = head->next;
                l2  = l2->next;
            }
        }
        head->next = l1 != nullptr ? l1 : l2;

        return res;
    }
};


int main(int argc, char *argv[]) {
    std::vector<int> v1 = {1, 4, 7};
    std::vector<int> v2 = {2, 3, 5, 9, 11};
    ListNode n1(0), n2(0);
    ListNode *cursor = nullptr;
    for (auto iter = v1.begin(); iter != v1.end(); iter++) {
        if (cursor == nullptr) {
            cursor = &n1;
            cursor->val = *iter;
        } else {
            auto tmp = new ListNode(*iter);  
            tmp->val = *iter;
            cursor->next = tmp;
            cursor = tmp;
        }
    }

    cursor = nullptr;
    for (auto iter = v2.begin(); iter != v2.end(); iter++) {
        if (cursor == nullptr) {
            cursor = &n2;
            cursor->val = *iter;
        } else {
            auto tmp = new ListNode(*iter);  
            tmp->val = *iter;
            cursor->next = tmp;
            cursor = tmp;
        }
    }

    Solution s;
    //auto xx = s.MergeTwoLists(&n1, &n2);
    auto xx = s.MergeTwoLists2(&n1, &n2);
    while (xx->next) {
        std::cout << xx->val << " " ;
        xx = xx->next;
    }
    std::cout << std::endl;

    return 0;
}

