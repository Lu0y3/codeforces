https://leetcode.cn/problems/largest-bst-subtree/
//SVIP

// ���BST����
// ����һ�����������ҵ��������Ķ�����������BST�������������ظ������Ĵ�С
// ���У����ָ���������ڵ�������
// ������������BST���е����нڵ㶼�߱��������ԣ�
// ��������ֵС���丸�������ڵ��ֵ
// ��������ֵ�����丸�������ڵ��ֵ
// ע�⣺����������������к��


//����dp��·
// 1> ���������õ�����Ҫ��������Щ��Ϣ
// 2> ����������Ϣ��ȫ������ɵݹ鷵��
// 3> ͨ���ݹ�����������ȫ����Ϣ
// 4> ����������ȫ����Ϣ�õ�������ȫ����Ϣ������
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
	//����
	if (x == null) {
		return new Info(LONG_MIN, LONG_MAX, true, 0);
	}

	Info infol = f(x.left);
	Info infor = f(x.right);
	// �� 4��Ϣ
	// �� 4��Ϣ
	// x ���ϳ�4��Ϣ����
	long max = max(x.val, max(infol.max_val, infor.max_val));
	long min = min(x.val, min(infol.min_val, infor.min_val));

	bool IsBST = infol.IsBST && infor.IsBST && infol.max_val < x.val && x.val < infor.min_val;

	int maxBSTSize;
	if (IsBST) {
		//��xΪͷ����������BST
		maxBSTSize = infol.maxBstSize + infor.maxBstSize + 1;
	}
	else {
		//��xΪͷ�������岻��BST ������x
		maxBSTSize = max(infol.maxBstSize, infor.maxBstSize);
	}
	// 2>
	return new Info(max, min, IsBST, maxBSTSize);
}

