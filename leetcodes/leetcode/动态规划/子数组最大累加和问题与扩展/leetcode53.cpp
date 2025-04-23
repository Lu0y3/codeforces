https://leetcode.cn/problems/maximum-subarray

//����������

// ���´���Ϊ���������ʵ��
    // ���������ҵ�ӵ������ۼӺ͵�������
    // ����������������Ϣ:
    // 1) ����ۼӺ�������Ŀ�ͷleft
    // 2) ����ۼӺ�������Ľ�βright
    // 3) ����ۼӺ���������ۼӺ�sum
    // �����ֹһ��������ӵ������ۼӺͣ���ô�ҵ���һ��������


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


    /*----------------����-----------------*/
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


