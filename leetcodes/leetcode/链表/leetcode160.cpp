https://leetcode.cn/problems/intersection-of-two-linked-lists

// �ཻ����

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
        // unordered_map  ��¼
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        // ��ȡ�������ĳ��ȣ���¼ Ȼ�󳤵����߲�ֵ
        // ���Ż� ֱ��ʹ��headA headB ����a,b
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
        // ��������while�Ǽ�¼�����Ĳ�ֵ

        //�ж��ߵ���βʱ�Ƿ����ཻ
        if (a != b)
            return nullptr;

        if (deff >= 0) {
            //a���� b����  �˴���deff>= ˵��a���ĳ���>=b��
            a = headA;
            b = headB;
        }
        else {
            a = headB;
            b = headA;
        }
        //����֮��a�ı�ʾ����  b��ʾ�̵�

        //deffȡ����ֵ
        deff = deff >= 0 ? deff : ~deff + 1;

        //�ó���a���߲��deff
        while (deff-- != 0)
            a = a->next;

        //a��b������������βͬ��������ʱͬʱ���� �����������ֹͣ���� ���ཻ����򷵻�end nullptr
        while (a != b) {
            a = a->next;
            b = b->next;
        }

        return a;
    }
};