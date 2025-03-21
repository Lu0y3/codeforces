https://leetcode.cn/problems/as-far-from-land-as-possible
//地图分析

// 从1  扫雷 扫满  取最大


class Solution {
    // 方向数组：上右下左
    const int directions[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;// BFS队列（多源起点）
        vector<vector<bool>> visited(n, vector<bool>(n, false));// 访问标记

        // 多源BFS初始化：所有陆地入队作为BFS起点
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1) {
                    q.push({ i, j });
                    visited[i][j] = true;
                }

        // 全陆地或全海洋的特殊情况
        if (q.empty() || q.size() == n * n) return -1;

        int max_dist = -1;// 记录最大扩散层级（即最远距离）
        // BFS层级扩散（每层对应一步距离）
        while (!q.empty()) {
            int level_size = q.size(); // 当前层节点数
            max_dist++;// 每完成一层扩散，距离+1 

            // 处理当前层所有节点
            for (int k = 0; k < level_size; ++k) {
                auto [x, y] = q.front(); q.pop();

                // 四方向扩散检查
                for (const auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];  // 计算新坐标x y

                    // 边界检查：确保不越界且未访问过
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                        !visited[nx][ny] && grid[nx][ny] == 0) {
                        visited[nx][ny] = true;// 入队即标记（防重复）
                        q.push({ nx, ny });// 新海洋坐标入队
                    }
                }
            }
        }
        return max_dist;
    }
};
//陆地距 最远海洋格 的最近距离
// 一个pass[][] 记录是否已来过


//大致看过官方题解，是从 0 海洋  取找最近的 1 陆地

