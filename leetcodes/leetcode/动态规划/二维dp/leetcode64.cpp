https://leetcode.cn/problems/minimum-path-sum

//��С·����

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        //return _Recur(grid, n-1, m-1);
        //return _Memor(grid, n-1, m-1);
        //return _Dymac(grid, n-1, m-1);
        return _Dymac2(grid, n - 1, m - 1);

        //��Ҫע��������������n-1 �� m-1 Ϊ����Ժÿ��㣬����Ҫ��������

    }

    // ������ (i,j) -> min{(i ,j-1),(i-1 ,j)}...  (0,0)->(0,0) ... (3,3)->(3,2)\(2,3)

    /*--------------------------------��̬�滮---------------------------------*/
    /*
        �ϸ�λ������
    */
    int _Dymac(const vector<vector<int>>& grid, int n, int m) {
        //���Ȱ����Ϻ�����Ķ������������ֻ����һ����
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        dp[0][0] = grid[0][0];
        //����
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        //����
        for (int j = 1; j <= m; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        //������ ����
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[n][m];
    }

    /*
        �ϸ�λ������ + �ռ�ѹ��(����������������һ��)
    */
    int _Dymac2(const vector<vector<int>>& grid, int n, int m) {
        //���Ȱ����Ϻ�����Ķ������������ֻ����һ����
        vector<int> dp(m + 1, -1);
        dp[0] = grid[0][0];
        //��ʼ����һ�� (0��n)
        for (int j = 1; j <= m; j++) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        //������ 
        for (int i = 1; i <= n; i++) {
            dp[0] += grid[i][0];
            for (int j = 1; j <= m; j++) {
                dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
            }
        }

        return dp[m];
    }



    /*--------------------------------���仯����---------------------------------*/
    int _Memor(const vector<vector<int>>& grid, int n, int m) {
        // array<array<int,m>,n> dp;  �����ڳ���constexpr
        // dp.fill(-1);
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return _Memory(grid, n, m, dp);
    }

    int _Memory(const vector<vector<int>>& grid, int n, int m, vector<vector<int>>& dp) {
        if (dp[n][m] != -1) return dp[n][m];

        if (n == 0 && m == 0) return dp[0][0] = grid[0][0];

        int left = INT_MAX;
        int up = INT_MAX;
        if (n - 1 >= 0) {
            left = _Memory(grid, n - 1, m, dp); //��
        }
        if (m - 1 >= 0) {
            up = _Memory(grid, n, m - 1, dp); //��
        }
        dp[n][m] = grid[n][m] + min(left, up);


        return  dp[n][m];
    }


    /*--------------------------------�����ݹ�---------------------------------*/
    /*
    ��Ȼ�����Ǵ����ϵ����µ���Сֵ�� ��һ�뷨�Ǵ����Ͽ�ʼ����Сֵ�ߣ������Ǵ���ģ������ǰ�·���ĵݹ�չ���ͻᷢ��������Ҫ����·������С�����ǿ�ʼ��С�������С�� ��������������������ǵ�ǰ[n,m]�����µ� λ��·���� ��ÿ��λ�ö������������� ��ʼ��grid[0][0]���������������߽�
    */
    int _Recur(const vector<vector<int>>& grid, int n, int m) {
        if (n == 0 && m == 0) return grid[0][0];

        int left = INT_MAX;
        int up = INT_MAX;
        if (n - 1 >= 0) {
            left = _Recur(grid, n - 1, m); //��
        }
        if (m - 1 >= 0) {
            up = _Recur(grid, n, m - 1); //��
        }

        return grid[n][m] + min(left, up); // �����min��Ȼ���ҵĽ�Сֵ����������Ҫ�ݹ�����������·��(����)��  ���ȫ��չ����·��һ����  grid[n][m] + min { grid[n-1][m]\grid[n][m-1] + min{ ..{grid[0][0]}.. }  }  ����ѡ�š�
    }

};