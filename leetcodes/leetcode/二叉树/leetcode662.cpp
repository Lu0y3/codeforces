https://leetcode.cn/problems/maximum-width-of-binary-tree

//二叉树的最大宽度

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    //想法是 层序遍历 每一层 将队列中属于该层的结点的标记(添加一个记录的)做差 取最大值
    //数组维护， 索引做差  空结点照样扩展数组 这里使用queue去实现了，，也可以用数组 附官解
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        //避雷: 2^3000 ?  666 用 ull
        queue<pair<TreeNode*, unsigned long long>> que; //储存节点和其索引位置

        que.push({ root,1 });
        int max_width = 1;

        while (!que.empty()) {
            int l_s = que.size();

            unsigned long long l_i = que.front().second; //最左idx

            for (int i = 0; i < l_s; ++i) {
                auto [tmn, idx] = que.front(); // tmn 结点 idx 索引
                que.pop();

                //更新max_width : 最右-最左  在每层结点遍历完
                if (l_s - 1 == i)
                    max_width = max(max_width, int(idx - l_i + 1)); //当进入此if时 idx就是最右的  l最左就是刚开始进入这一层的idx

                //左孩子
                if (tmn->left)
                    que.push({ tmn->left,idx * 2 - l_i }); // 这里减去 l_i上一层最左的idx 是为了获取相对位置;同时上面取max的(idx - l_i + 1)也是两个相对位置的相减 类似"同余"的"同减"？ 如果实在不理解可以画图证明，本人也是画图证明理解的。

                //右孩子
                if (tmn->right)
                    que.push({ tmn->right,idx * 2 + 1 - l_i });

            }
        }
        return max_width;

    }
};

//官解 BFS
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        unsigned long long res = 1;
        vector<pair<TreeNode*, unsigned long long>> arr;
        arr.emplace_back(root, 1L);
        while (!arr.empty()) {
            vector<pair<TreeNode*, unsigned long long>> tmp;
            for (auto& [node, index] : arr) {
                if (node->left) {
                    tmp.emplace_back(node->left, index * 2);
                }
                if (node->right) {
                    tmp.emplace_back(node->right, index * 2 + 1);
                }
            }
            res = max(res, arr.back().second - arr[0].second + 1);
            arr = move(tmp);
        }
        return res;
    }
};