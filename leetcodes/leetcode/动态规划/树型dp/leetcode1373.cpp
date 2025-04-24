https://leetcode.cn/problems/maximum-sum-bst-in-binary-tree/

// 二叉搜索子树的最大键值和
// 给你一棵以 root 为根的二叉树
// 请你返回 任意 二叉搜索子树的最大键值和
// 二叉搜索树的定义如下：
// 任意节点的左子树中的键值都 小于 此节点的键值
// 任意节点的右子树中的键值都 大于 此节点的键值
// 任意节点的左子树和右子树都是二叉搜索树


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
    struct Info {
        long max_val;
        long min_val;
        long sum;
        bool IsBST;
        long maxBSTsum;

        Info(long a, long b, long e, bool c, long d) :
            max_val(a), min_val(b), sum(e), IsBST(c), maxBSTsum(d) {
        }
    };

public:
    int maxSumBST(TreeNode* root) {
        auto res = f(root);
        return res.maxBSTsum > 0 ? res.maxBSTsum : 0;
    }

    Info f(TreeNode* root) {
        //空树
        if (root == nullptr) return Info(INT_MIN, INT_MAX, 0, true, 0);

        Info infol = f(root->left);
        Info infor = f(root->right);

        long max_ = max((long)root->val, max(infol.max_val, infor.max_val));
        long min_ = min((long)root->val, min(infol.min_val, infor.min_val));

        bool isBST_ = infol.IsBST && infor.IsBST &&
            infol.max_val < root->val && infor.min_val > root->val;

        //考虑带负数的结点 添加测试用例 [-3,-5,-1,-6,-4,null,6]  
        long sum_ = infol.sum + infor.sum + root->val;
        long maxBSTsum_ = max(infol.maxBSTsum, infor.maxBSTsum);

        if (isBST_) {
            maxBSTsum_ = max(sum_, maxBSTsum_);
        }

        return Info(max_, min_, sum_, isBST_, maxBSTsum_);
    }

};