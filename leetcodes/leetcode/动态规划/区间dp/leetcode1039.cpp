https://leetcode.cn/problems/minimum-score-triangulation-of-polygon

// ����������ʷֵ���͵÷�
// ����һ��͹�� n ���Σ���ÿ�����㶼��һ������ֵ
// ����һ����������values������values[i]�ǵ�i�������ֵ(˳ʱ��˳��)
// ���轫����� �ʷ� Ϊ n - 2 ��������
// ����ÿ�������Σ��������ε�ֵ�Ƕ����ǵĳ˻�
// �����ʷֵķ����ǽ��������ʷֺ����� n - 2 �������ε�ֵ֮��
// ���� ����ν��������ʷֺ���Եõ�����ͷ�

//���ڷ�Χ�ϻ��ֵ�Ŀ�����չ��
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        //return Memor_(values);
        return f2(values);
    }

    int Memor_(const vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return f1(values, 0, n - 1, dp);
    }

    int f1(const vector<int>& values, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans = INT_MAX;

        if (l == r || l == r - 1) ans = 0;
        else {
            for (int m = l + 1; m < r; ++m) {  //���ڷ�Χ�ϻ��ֵ�
                ans = min(ans, f1(values, l, m, dp) + f1(values, m, r, dp) + values[l] * values[m] * values[r]);
            }
        }
        dp[l][r] = ans;
        return ans;
    }



    int f2(const vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int l = n - 3; l >= 0; l--) {
            for (int r = l + 2; r < n; r++) {
                dp[l][r] = INT_MAX;
                for (int m = l + 1; m < r; m++) {
                    dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + values[l] * values[m] * values[r]);
                }
            }
        }
        return dp[0][n - 1];
    }

};