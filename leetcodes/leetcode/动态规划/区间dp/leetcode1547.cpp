https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/

// �й��ӵ���С�ɱ�
// ��һ������Ϊn����λ��ľ�������ϴ�0��n���������λ��
// ����һ����������cuts������cuts[i]��ʾ����Ҫ�������п���λ��
// ����԰�˳������иҲ���Ը�����Ҫ�����и��˳��
// ÿ���и�ĳɱ����ǵ�ǰҪ�и�Ĺ��ӵĳ��ȣ��й��ӵ��ܳɱ��������и�ɱ����ܺ�
// �Թ��ӽ����и���һ��ľ���ֳ�������С��ľ��
// ������ľ���ĳ��Ⱥ;����и�ǰľ���ĳ���
// �����й��ӵ���С�ܳɱ�

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        sort(cuts.begin(), cuts.end());
        //return f1(n, cuts);
        return f3(n, cuts);
    }

    /*--------------���仯+�ݹ�---------------*/
    int f1(int n, const vector<int>& cuts) {
        int m = cuts.size();
        vector<int> cuts_(m + 2);
        cuts_[0] = 0;
        cuts_[m + 1] = n;
        for (int i = 1; i <= m; ++i) {
            cuts_[i] = cuts[i - 1];
        }
        vector<vector<int>> dp(m + 2, vector<int>(m + 2, -1));
        return f2(cuts_, 1, m, dp);
    }

    int f2(const vector<int>& cuts_, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1)
            return dp[l][r];
        if (l > r)
            return 0;
        if (l == r)
            return cuts_[r + 1] - cuts_[l - 1];
        int ans = INT_MAX;
        for (int k = l; k <= r; ++k) {
            ans = min(ans, f2(cuts_, l, k - 1, dp) + f2(cuts_, k + 1, r, dp));
        }
        ans += cuts_[r + 1] - cuts_[l - 1];
        dp[l][r] = ans;
        return ans;
    }
    /*--------------��̬�滮---------------*/

    int f3(int n, const vector<int>& cuts) {
        int m = cuts.size();
        vector<int> cuts_(m + 2);
        cuts_[0] = 0;
        for (int i = 1; i <= m; ++i) {
            cuts_[i] = cuts[i - 1];
        }
        cuts_[m + 1] = n;

        vector<vector<int>> dp(m + 2, vector<int>(m + 2, 0));
        //0-m+1�� 1-mά����ά��  0��0��ȫΪ0 
        for (int i = 1; i <= m; ++i) {
            dp[i][i] = cuts_[i + 1] - cuts_[i - 1];
        }
        //����ѶԽ�������  
        //����for�Ǵ� (m-1,m)��ʼ  ��ά�����½ǵ���һ��ͬ�и���
        for (int l = m - 1, tmp; l >= 1; --l) {
            for (int r = l + 1; r <= m; ++r) {

                tmp = INT_MAX;
                for (int k = l; k <= r; ++k) { //���ڷ�Χ ���ֵ�
                    tmp = min(tmp, dp[l][k - 1] + dp[k + 1][r]);
                }
                dp[l][r] = tmp + cuts_[r + 1] - cuts_[l - 1];

            }
        }

        return dp[1][m];

    }


};