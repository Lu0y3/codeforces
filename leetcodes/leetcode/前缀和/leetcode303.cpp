https://leetcode.cn/problems/range-sum-query-immutable
//区域和简述-数组不变
class NumArray {
    vector<int> sums;
public:
    //先计算主数组的前缀和
    /*
     0  1 2  3 4  5  6
    [-2,0,3,-5,2,-1] 主数组
    [0,-2,-2,1,-4,-2,-3] 前缀和: i当前数的前缀  最后一个-3是主数组累和

    查询索引 l...r 的区域和
    举例 区域[2..4]的累计和 == [0,4] - [0,2] == 索引5的前缀和 - 索引2的前缀和
    -> sums[r+1] - sums[l]
    */

    NumArray(vector<int>& nums) {
        sums = new vector<int>(nums.size());
        sums[0] = nums[0];
        for (int i = 1; i <= nums.size(); ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return sums[right + 1] - sums[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */