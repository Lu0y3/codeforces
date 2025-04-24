https://leetcode.cn/problems/predict-the-winner

// Ԥ��Ӯ��
// ����һ���������� nums ����� 1 ����� 2 ����������������һ����Ϸ
// ��� 1 ����� 2 ���������Լ��Ļغϣ���� 1 ����
// ��ʼʱ��������ҵĳ�ʼ��ֵ���� 0
// ÿһ�غϣ���Ҵ����������һ��ȡһ������
// ȡ�������ֽ�����������Ƴ������鳤�ȼ�1
// ���ѡ�е����ֽ���ӵ����ĵ÷���
// ��������û��ʣ�����ֿ�ȡʱ��Ϸ����
// ������ 1 �ܳ�ΪӮ�ң����� true
// ���������ҵ÷���ȣ�ͬ����Ϊ��� 1 ����Ϸ��Ӯ�ң�Ҳ���� true
// ����Լ���ÿ����ҵ��淨����ʹ���ķ������



// ����dp ��������
class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {

        // return Recur_(nums);
        // return Memor_(nums);
        return Dynamic_(nums);
    }

    /*---------------�ݹ�----------------*/
    bool Recur_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        int play1 = f1(nums, 0, n - 1);
        return play1 >= sums - play1;
    }
    //�������1 �ĵ÷�
    int f1(const vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        if (l == r - 1) return nums[l] >= nums[r] ? nums[l] : nums[r];
        //���1 ����� �� ���2 �� max �� l+1 �� r �� ; ���1ֻ����֮��� min
        int p1 = nums[l] + min(f1(nums, l + 2, r), f1(nums, l + 1, r - 1));
        //���1 ���ұ� �� ���2 �� max �� l �� r-1 �� ; ���1ֻ����֮��� min
        int p2 = nums[r] + min(f1(nums, l, r - 2), f1(nums, l + 1, r - 1));

        return max(p1, p2);
    }

    /*---------------���仯----------------*/
    bool Memor_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int play1 = f2(nums, 0, n - 1, dp);
        return play1 >= sums - play1;
    }
    //�������1 �ĵ÷�
    int f2(const vector<int>& nums, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans{};
        if (l == r)  ans = nums[l];
        else if (l == r - 1) ans = nums[l] >= nums[r] ? nums[l] : nums[r];
        else {
            int p1 = nums[l] + min(f2(nums, l + 2, r, dp), f2(nums, l + 1, r - 1, dp));
            int p2 = nums[r] + min(f2(nums, l, r - 2, dp), f2(nums, l + 1, r - 1, dp));
            ans = max(p1, p2);
        }
        dp[l][r] = ans;
        return ans;
    }

    /*----------------��̬�滮-----------------*/
    //: �ϸ�λ������
    bool Dynamic_(const vector<int>& nums) {
        int n = nums.size();
        int sums{};
        for (const auto& sum : nums) {
            sums += sum;
        }
        vector<vector<int>> dp(n, vector<int>(n));

        for (int i = 0; i < n - 1; ++i) {
            dp[i][i] = nums[i];
            dp[i][i + 1] = max(nums[i], nums[i + 1]);
        }

        dp[n - 1][n - 1] = nums[n - 1];

        //���������for ��Ϊ�������������
        for (int l = n - 3; l >= 0; --l) {
            for (int r = l + 2; r < n; ++r) {
                dp[l][r] = max(
                    nums[l] + min(dp[l + 2][r], dp[l + 1][r - 1]),
                    nums[r] + min(dp[l][r - 2], dp[l + 1][r - 1])
                );
            }
        }
        int play1 = dp[0][n - 1];
        return play1 >= sums - play1;

    }

};