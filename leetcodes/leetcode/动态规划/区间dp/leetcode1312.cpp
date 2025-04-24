https://leetcode.cn/problems/minimum-insertion-steps-to-make-a-string-palindrome/

// ���ַ�����Ϊ���Ĵ������ٲ������
// ����һ���ַ��� s
// ÿһ�β����㶼�������ַ���������λ�ò��������ַ�
// ���㷵����s��Ϊ���Ĵ������ٲ�������

/*����dp: ������չ�� ��������˵� */



class Solution {
public:
    int minInsertions(string s) {
        //return Memory_(s);
        //return Dynamic_(s);
        return Dynamic_space(s);


        // int n = s.length();

        // return Recur_(s,0,n-1); 
    }

    /*------------------�ݹ�--------------------*/
    int Recur_(const string& s, int l, int r) {
        if (l == r) return 0;  //������ֻ��һ���ַ�
        if (l + 1 == r) return s[l] == s[r] ? 0 : 1; //�������������ַ� aa  ab 

        //��������
        if (s[l] == s[r]) //��������
        {
            return Recur_(s, l + 1, r - 1);
        }
        else {
            return min(Recur_(s, l + 1, r), Recur_(s, l, r - 1)) + 1;
        }
    }


    /*------------------���仯--------------------*/
    int Memory_(const string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, -1)); //dp[l][r]: ������l...r���Ƿ��Լ��ݹ�
        return Memor_(s, 0, n - 1, dp);
    }
    int Memor_(const string& s, int l, int r, vector<vector<int>>& dp) {
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        int ans{};

        if (l == r) ans = 0;  //������ֻ��һ���ַ�
        else if (l + 1 == r)  ans = s[l] == s[r] ? 0 : 1; //�������������ַ� aa  ab 

        //��������
        else if (s[l] == s[r]) //��������
        {
            ans = Memor_(s, l + 1, r - 1, dp);
        }
        else {
            ans = min(Memor_(s, l + 1, r, dp), Memor_(s, l, r - 1, dp)) + 1;
        }

        dp[l][r] = ans;
        return ans;
    }

    /*------------------��̬�滮--------------------*/
    // : �ϸ�λ������   ��ά����(l,r) ���� (l+1,r-1)���� �� (l,r-1)\(l+1,r)�� ��
    int Dynamic_(const string& s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0)); // n * n �Ķ�ά�� 
        //�����Ѿ����l == r  ������l+1 == r
        for (int l = 0; l < n - 1; ++l) {
            dp[l][l + 1] = s[l] == s[l + 1] ? 0 : 1;
        }

        //�������� ÿ���������� 
        for (int l = n - 3; l >= 0; --l) {
            for (int r = l + 2; r < n; ++r) {
                if (s[l] == s[r]) {
                    dp[l][r] = dp[l + 1][r - 1];
                }
                else {
                    dp[l][r] = min(dp[l][r - 1], dp[l + 1][r]) + 1;
                }

            }
        }
        return dp[0][n - 1];
    }

    // : �ϸ�λ������ + �ռ�ѹ��  ֻ��Ҫά�� ���� �� �� ���� 
    // ��άdp �ĳ� һάdp   һάdp��ά����ͬ���ֵ
    // ���ݹ��̿��������һ�� ���� ���Ͻ�Ϊ��ǰҪ���ֵ ��ÿ�������ƶ�  
    //���Բο��ӵݹ����ֶ�ά��̬�滮����Ŀ4�����������������Ľ���
    int Dynamic_space(const string& s) {
        int n = s.length();
        if (n < 2) return 0;

        vector<int> dp(n, 0);
        dp[n - 1] = s[n - 1] == s[n - 2] ? 0 : 1;

        for (int l = n - 3, leftDown{}, backUp{}; l >= 0; --l) {

            leftDown = dp[l + 1]; //�����dp[l + 1]
            dp[l + 1] = s[l] == s[l + 1] ? 0 : 1; //������dp[l + 1]

            for (int r = l + 2; r < n; ++r) {
                backUp = dp[r]; //�����dp[r]

                //������dp[r]
                if (s[l] == s[r]) {
                    dp[r] = leftDown;
                }
                else {
                    dp[r] = min(dp[r - 1], dp[r]) + 1;
                }

                leftDown = backUp; //����leftDown

            }
        }
        return dp[n - 1];
    }

};
