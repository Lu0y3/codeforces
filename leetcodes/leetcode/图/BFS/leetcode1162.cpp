https://leetcode.cn/problems/as-far-from-land-as-possible
//��ͼ����

// ��1  ɨ�� ɨ��  ȡ���


class Solution {
    // �������飺��������
    const int directions[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;// BFS���У���Դ��㣩
        vector<vector<bool>> visited(n, vector<bool>(n, false));// ���ʱ��

        // ��ԴBFS��ʼ��������½�������ΪBFS���
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1) {
                    q.push({ i, j });
                    visited[i][j] = true;
                }

        // ȫ½�ػ�ȫ������������
        if (q.empty() || q.size() == n * n) return -1;

        int max_dist = -1;// ��¼�����ɢ�㼶������Զ���룩
        // BFS�㼶��ɢ��ÿ���Ӧһ�����룩
        while (!q.empty()) {
            int level_size = q.size(); // ��ǰ��ڵ���
            max_dist++;// ÿ���һ����ɢ������+1 

            // ����ǰ�����нڵ�
            for (int k = 0; k < level_size; ++k) {
                auto [x, y] = q.front(); q.pop();

                // �ķ�����ɢ���
                for (const auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];  // ����������x y

                    // �߽��飺ȷ����Խ����δ���ʹ�
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                        !visited[nx][ny] && grid[nx][ny] == 0) {
                        visited[nx][ny] = true;// ��Ӽ���ǣ����ظ���
                        q.push({ nx, ny });// �º����������
                    }
                }
            }
        }
        return max_dist;
    }
};
//½�ؾ� ��Զ����� ���������
// һ��pass[][] ��¼�Ƿ�������


//���¿����ٷ���⣬�Ǵ� 0 ����  ȡ������� 1 ½��

