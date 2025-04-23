https://leetcode.cn/problems/house-robber-ii/


//打家劫舍II
// 
// 环形数组中不能选相邻元素的最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 可以随意选择数字，但是不能选择相邻的数字
// 返回能得到的最大累加和


class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        //1> [0]不要  1...n-1 上不是"环形的" 不相邻的
        //2> [0]要    2...n-2 上不是"环形的" 不相邻的
        return max(Cycle_F(nums, 1, n - 1), nums[0] + Cycle_F(nums, 2, n - 2));

    }
    //在[0]要不要下 不是环形的 不相邻的 情况
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



