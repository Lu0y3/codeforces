https://leetcode.cn/problems/reverse-nodes-in-k-group

//K��һ�鷴ת����

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
     // ��ת���̣����ȼ�¼��ʱe�ڵ��next���ڽ����������ϣ�
     //Ȼ����next = cur->next; ��cur = next; ȥ�������ڲ�����cur���
     // cur->next = pre; �� pre = cur; ���ڲ�����ͷ�ķ�ת�� pre�ĸ���
     void fanz(ListNode* s, ListNode* e) {
         e = e->next;
         ListNode* pre = nullptr, * cur = s, * next = nullptr;
         while (cur != e) {
             next = cur->next;
             cur->next = pre; //ָ��
             pre = cur;
             cur = next;
         }
         s->next = e;
     }
     //����β�����  ����  �߽�
     ListNode* grepkre(ListNode* s, int k) {
         while (--k != 0 && s) {
             s = s->next;
         }
         return s;
     }

     ListNode* reverseKGroup(ListNode* head, int k) {
         //  a->b->c->d->e->f->g->h->i->j->k->nullptr
         //  �Ƚ��е�һ��k�Ŀ���
         ListNode* s = head;
         ListNode* e = grepkre(s, k);
         if (e == nullptr) return head;

         head = e;

         fanz(s, e);
         //��ת֮����һ���ͷ ����β  ����һ��ͷ��ǰһ����� 
         ListNode* lteam_e = s;

         // ���Ǻ����Ľ��
         while (lteam_e->next) {
             s = lteam_e->next;
             e = grepkre(s, k);
             if (e == nullptr) return head;

             fanz(s, e);
             lteam_e->next = e;
             lteam_e = s;
         }
         return head;
     }
 };