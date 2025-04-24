https://leetcode.cn/problems/diameter-of-binary-tree

// 二叉树的直径
// 给你一棵二叉树的根节点，返回该树的直径
// 二叉树的 直径 是指树中任意两个节点之间最长路径的长度
// 这条路径可能经过也可能不经过根节点 root
// 两节点之间路径的 长度 由它们之间边数表示


struct Info {
	int diamater;
	int height;
	//不经过x头 ： max（左max直径， 右max直径）
	//经过x头 : x到右最深 + x到右最深 (左树的高度差+右数的高度差)
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
    struct Info {
        int diameter;
        int height;

        Info(int a, int b) : diameter(a), height(b) {}
    };

public:
    int diameterOfBinaryTree(TreeNode* root) { return max_diaOfTree(root); }
    // 不经过x头 ： max（左max直径， 右max直径）
    // 经过x头 : x到右最深 + x到右最深 (左树的高度差+右数的高度差)
    //
    int max_diaOfTree(TreeNode* root) { return f(root).diameter; }

    Info f(TreeNode* root) {
        // 空
        if (root == nullptr)
            return Info(0, 0);

        Info infol = f(root->left);
        Info infor = f(root->right);

        int height_ = max(infol.height, infor.height) + 1;
        // 不经过x头
        int diameter_ = max(infol.diameter, infor.diameter);
        // 经过x头
        diameter_ = max(diameter_, infol.height + infor.height);

        return Info(diameter_, height_);
    }
};