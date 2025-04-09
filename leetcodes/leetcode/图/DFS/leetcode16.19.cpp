https://leetcode.cn/problems/pond-sizes-lcci

//水域大小

class Solution {
public:
    vector<int> pondSizes(vector<vector<int>>& land) {
        // 相较于 200 695 这里需要八个方向
        int m = land.size(), n = land[0].size();

        auto dfs = [&](this auto&& dfs, int i, int j)->int {
            if (i < 0 || i >= m || j < 0 || j >= n || land[i][j] != 0) return 0;

            land[i][j] = -1;
            int count = 1;
            //访问八个方向
            for (int x = i - 1; x <= i + 1;x++) {
                for (int y = j - 1; y <= j + 1;y++) {
                    count += dfs(x, y);
                }
            }
            return count;

            };


        vector<int> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (land[i][j] == 0) { //发现水域
                    //dfs();
                    //将水域大小存 入数组中 然后排序
                    ans.push_back(dfs(i, j));
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
