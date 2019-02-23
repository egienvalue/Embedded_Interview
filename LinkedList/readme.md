
## 2. Add Two Numbers

### Description

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```

### Solution1 O(max(M,N))

```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ptr1=l1;
        ListNode* ptr2=l2;
        ListNode dummy(0);
        ListNode* head = &dummy;
        // 初始化carry 为0
        int carry = 0;
        while(ptr1 != nullptr || ptr2 != nullptr){

            //如果为nullptr 则认为要加的数为0
            int int_1 = ptr1 == nullptr ? 0 : ptr1->val;
            int int_2 = ptr2 == nullptr ? 0 : ptr2->val;
            // cout << int_1 << "  " << int_2 << endl;
            int result = (int_1 + int_2 + carry)%10;
            carry = (int_1 + int_2 + carry) / 10;
            head->next = new ListNode(result);
            head = head->next;
            // 访问next成员变量的时候需要check 是否为空
            ptr1 = ptr1!=nullptr ? ptr1->next : ptr1;
            ptr2 = ptr2!=nullptr ? ptr2->next : ptr2;
        }
        if(carry > 0){
            head->next = new ListNode(carry);
        }
        return dummy.next;
    }
};
```