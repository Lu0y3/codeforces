https://leetcode.cn/problems/largest-bst-subtree/
//SVIP

// 最大BST子树
// 给定一个二叉树，找到其中最大的二叉搜索树（BST）子树，并返回该子树的大小
// 其中，最大指的是子树节点数最多的
// 二叉搜索树（BST）中的所有节点都具备以下属性：
// 左子树的值小于其父（根）节点的值
// 右子树的值大于其父（根）节点的值
// 注意：子树必须包含其所有后代


//树型dp套路
// 1> 分析父树得到答案需要子树的哪些信息
// 2> 把子树的信息的全集定义成递归返回
// 3> 通过递归让子树返回全集信息
// 4> 整合子树的全集信息得到父树的全集信息并返回
//

// 1> 
struct Info {
	long max_val;
	long min_val;
	bool IsBST;
	int maxBSTsize; 

	Info(long a, long b, bool c, int d):
		max_val(a),
		min_val(b),
		IsBST(c),
		maxBSTsize(d){ }
};

Info f(TreeNode* x) {
	//空树
	if (x == null) {
		return new Info(LONG_MIN, LONG_MAX, true, 0);
	}

	Info infol = f(x.left);
	Info infor = f(x.right);
	// 左 4信息
	// 右 4信息
	// x 整合出4信息返回
	long max = max(x.val, max(infol.max_val, infor.max_val));
	long min = min(x.val, min(infol.min_val, infor.min_val));

	bool IsBST = infol.IsBST && infor.IsBST && infol.max_val < x.val && x.val < infor.min_val;

	int maxBSTSize;
	if (IsBST) {
		//以x为头的树整体是BST
		maxBSTSize = infol.maxBstSize + infor.maxBstSize + 1;
	}
	else {
		//以x为头的树整体不是BST 不包含x
		maxBSTSize = max(infol.maxBstSize, infor.maxBstSize);
	}
	// 2>
	return new Info(max, min, IsBST, maxBSTSize);
}

