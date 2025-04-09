https://leetcode.cn/problems/reverse-linked-list-ii?envType=study-plan-v2&envId=top-interview-150

//��ת����II

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
         ListNode tp(0, head); //����һ������ 0

         ListNode* pr = &tp; //����һ��ָ��

         //���ҵ�left��ǰһ��
         for (int i = 0; i < left - 1; ++i) {
             pr = pr->next;
         }
         //��ת
         ListNode* pre = nullptr;
         ListNode* cur = pr->next;
         // ȫ����ͷ
         for (int i = 0; i < right - left + 1; ++i) {
             ListNode* nt = cur->next;
             cur->next = pre;
             pre = cur;
             cur = nt;
         }
         //��תͷβ��
         pr->next->next = cur;
         pr->next = pre;

         return tp.next;
     }
 };