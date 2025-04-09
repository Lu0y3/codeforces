https://leetcode.cn/problems/reverse-linked-list-ii?envType=study-plan-v2&envId=top-interview-150

//反转链表II

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 class Solution {
 public:
     ListNode* reverseBetween(ListNode* head, int left, int right) {
         ListNode tp(0, head); //创建一个对象 0

         ListNode* pr = &tp; //这是一个指针

         //先找到left的前一个
         for (int i = 0; i < left - 1; ++i) {
             pr = pr->next;
         }
         //反转
         ListNode* pre = nullptr;
         ListNode* cur = pr->next;
         // 全部掉头
         for (int i = 0; i < right - left + 1; ++i) {
             ListNode* nt = cur->next;
             cur->next = pre;
             pre = cur;
             cur = nt;
         }
         //接转头尾部
         pr->next->next = cur;
         pr->next = pre;

         return tp.next;
     }
 };