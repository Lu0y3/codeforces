https://leetcode.cn/problems/maximum-depth-of-binary-tree

//二叉树的深度

//下面俩个递归方向的不同主要是 +1的方式
// 自底向上是 先全部递归展开 然后从底层+1 向上 大数在上
// 自顶向下是 边递归展开 边向下 +1  大数在下

//自底向上 ： 

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;

        int l_d = maxDepth(root->left);
        int r_d = maxDepth(root->right);

        return max(l_d, r_d) + 1;
    }
};


//自顶向下

class Solution {
public:
    int maxDepth(TreeNode* root) {
        int ans = 0;

        auto dfs = [&](this auto&& dfs, TreeNode* node, int depth) -> void {
            if (node == nullptr) {
                return;
            }
            depth++;
            ans = max(ans, depth);
            dfs(node->left, depth);
            dfs(node->right, depth);
            };

        dfs(root, 0);
        return ans;
    }
};