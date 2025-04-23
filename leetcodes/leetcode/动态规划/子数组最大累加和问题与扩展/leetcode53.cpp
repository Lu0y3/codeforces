https://leetcode.cn/problems/maximum-subarray

//最大子数组和

// 如下代码为附加问题的实现
    // 子数组中找到拥有最大累加和的子数组
    // 并返回如下三个信息:
    // 1) 最大累加和子数组的开头left
    // 2) 最大累加和子数组的结尾right
    // 3) 最大累加和子数组的累加和sum
    // 如果不止一个子数组拥有最大累加和，那么找到哪一个都可以


class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        return Dynamc_2(nums);
    }

    int Dynamc_(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];

        int ans = nums[0];

        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    int Dynamc_2(vector<int>& nums) {
        int n = nums.size();
        int ans = nums[0];
        for (int i = 1, pre = nums[0]; i < n; ++i) {
            pre = max(nums[i], pre + nums[i]);
            ans = max(ans, pre);
        }
        return ans;
    }


    /*----------------附加-----------------*/
    auto Dynamc_3(vector<int>& nums) {
        int n = nums.size();
        int left{}, right{};
        int sum = INT_MIN;

        for (int l{}, r{}, pre = nums[0]; i < n; ++i) {

            if (pre >= 0) {
                pre += nums[i];
            }
            else {
                pre = nums[i];
                l = r;
            }

            if (pre > sum) {
                sum = pre;
                left = l;
                right = r;
            }

        }
        return {sum, left, right};
    }


};


