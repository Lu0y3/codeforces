https://leetcode.cn/problems/house-robber-ii/


//��ҽ���II
// 
// ���������в���ѡ����Ԫ�ص�����ۼӺ�
// ����һ������nums������Ϊn
// nums��һ���������飬�±�0���±�n-1������һ���
// ��������ѡ�����֣����ǲ���ѡ�����ڵ�����
// �����ܵõ�������ۼӺ�


class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        //1> [0]��Ҫ  1...n-1 �ϲ���"���ε�" �����ڵ�
        //2> [0]Ҫ    2...n-2 �ϲ���"���ε�" �����ڵ�
        return max(Cycle_F(nums, 1, n - 1), nums[0] + Cycle_F(nums, 2, n - 2));

    }
    //��[0]Ҫ��Ҫ�� ���ǻ��ε� �����ڵ� ���
    int Cycle_F(const vector<int>& nums, int l, int r) {
        if (l > r) {
            return 0;
        }

        if (l == r) return nums[l];
        if (l + 1 == r) return max(nums[l], nums[r]);

        int prepre = nums[l];
        int pre = max(nums[l], nums[l + 1]);
        for (int i = l + 2, cur{}; i <= r; ++i) {
            cur = max(cur, max(pre, prepre + nums[i]));
            prepre = pre;
            pre = cur;
        }

        return pre;
    }

};



