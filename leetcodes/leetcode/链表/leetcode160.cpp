https://leetcode.cn/problems/intersection-of-two-linked-lists

// 相交链表

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        // unordered_map  记录
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        // 获取两个链的长度，记录 然后长的先走差值
        // 可优化 直接使用headA headB 代替a,b
        int deff{};
        ListNode* a = headA, * b = headB;
        while (a->next) {
            a = a->next;
            ++deff;
        }

        while (b->next) {
            b = b->next;
            --deff;
        }
        // 上面两个while是记录链表长的差值

        //判断走到链尾时是否有相交
        if (a != b)
            return nullptr;

        if (deff >= 0) {
            //a先走 b后走  此处是deff>= 说明a链的长度>=b链
            a = headA;
            b = headB;
        }
        else {
            a = headB;
            b = headA;
        }
        //出来之后a的表示长的  b表示短的

        //deff取绝对值
        deff = deff >= 0 ? deff : ~deff + 1;

        //让长的a先走差的deff
        while (deff-- != 0)
            a = a->next;

        //a、b两个结点距离链尾同长，，此时同时出发 如果结点相等则停止返回 无相交结点则返回end nullptr
        while (a != b) {
            a = a->next;
            b = b->next;
        }

        return a;
    }
};