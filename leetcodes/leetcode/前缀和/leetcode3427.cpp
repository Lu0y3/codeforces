https://leetcode.cn/problems/sum-of-variable-length-subarrays
//�䳤���������
class Solution {
public:

    int subarraySum(vector<int>& nums) {
        //��������ǰ׺�ͣ� ��ô�������飿
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + nums[i - 1];
        }

        int ans{};
        for (int i = 0; i < n; ++i) {
            int start = max(0, i - nums[i]);
            ans += s[i + 1] - s[start];
        }
        return ans;
    }
};