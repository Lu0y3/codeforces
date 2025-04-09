https://leetcode.cn/problems/reverse-nodes-in-k-group

//K个一组反转链表

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
     // 翻转流程：首先记录此时e节点的next用于将链表连接上，
     //然后用next = cur->next; 和cur = next; 去更新正在操作的cur结点
     // cur->next = pre; 和 pre = cur; 用于操作箭头的反转和 pre的更替
     void fanz(ListNode* s, ListNode* e) {
         e = e->next;
         ListNode* pre = nullptr, * cur = s, * next = nullptr;
         while (cur != e) {
             next = cur->next;
             cur->next = pre; //指空
             pre = cur;
             cur = next;
         }
         s->next = e;
     }
     //返回尾部结点  分组  边界
     ListNode* grepkre(ListNode* s, int k) {
         while (--k != 0 && s) {
             s = s->next;
         }
         return s;
     }

     ListNode* reverseKGroup(ListNode* head, int k) {
         //  a->b->c->d->e->f->g->h->i->j->k->nullptr
         //  先进行第一个k的考虑
         ListNode* s = head;
         ListNode* e = grepkre(s, k);
         if (e == nullptr) return head;

         head = e;

         fanz(s, e);
         //反转之后上一组的头 当作尾  是下一组头的前一个结点 
         ListNode* lteam_e = s;

         // 考虑后续的结点
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