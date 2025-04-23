https://leetcode.cn/problems/maximum-sum-circular-subarray


// 环形数组的子数组最大累加和
// 给定一个数组nums，长度为n
// nums是一个环形数组，下标0和下标n-1是连在一起的
// 返回环形数组中，子数组最大累加和

// 1> 不隔断不跨过0  正常写
// 2> 隔断的    隔断累加和max = all和 - 不隔断累加和min


/*-------------------取反------------------*/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        
        return Negate_(nums);
    }

    /*----------------动态规划-------------------*/



    /*-------------------取反------------------*/
    int Negate_(vector<int>& nums)
    {
        int n = nums.size(), all = nums[0], maxsum = nums[0], minsum = nums[0];
        for (int i = 1, maxpre = nums[0], minpre = nums[0]; i < n; ++i) {
            all += nums[i];
            maxpre = max(maxpre + nums[i], nums[i]);
            maxsum = max(maxsum, maxpre);
            minpre = min(minpre + nums[i], nums[i]);
            minsum = min(minsum, minpre);
        }
        // maxsum   \ all - minsum
        if (maxsum < 0) { //[...]中都是负数
            return maxsum;
        }
        else {
            return max(maxsum, all - minsum);
        }
    }


    /*----------------单调队列-------------------*/




};

