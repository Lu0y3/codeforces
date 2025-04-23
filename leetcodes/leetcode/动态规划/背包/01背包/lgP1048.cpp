https://www.luogu.com.cn/problem/P1048


// 01����(ģ��)
// ����һ������t����ʾ����������
// ��m�����ÿ���������ѡ��һ��
// ÿ���������Լ������costs[i]�ͼ�ֵvalues[i]
// �����ڲ�����������������£���ô��ѡ�����ܴﵽ��ֵ���
// �������ļ�ֵ

/*-------------------------------------------------------------------------*/
// �ϸ�λ�������Ķ�̬�滮
	// n����Ʒ���1~n����i����Ʒ�Ļ���cost[i]����ֵval[i]
	// cost��val������ȫ�ֱ������Ѿ������ݶ�����
	public static int compute1() {
		int[][] dp = new int[n + 1][t + 1];
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= t; j++) {
				// ��Ҫi����Ʒ
				dp[i][j] = dp[i - 1][j];
				if (j - cost[i] >= 0) {
					// Ҫi����Ʒ
					dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - cost[i]] + val[i]);
				}
			}
		}
		return dp[n][t];
	}

	// �ռ�ѹ��
	public static int compute2() {
		Arrays.fill(dp, 0, t + 1, 0);
		for (int i = 1; i <= n; i++) {
			for (int j = t; j >= cost[i]; j--) {
				dp[j] = Math.max(dp[j], dp[j - cost[i]] + val[i]);
			}
		}
		return dp[t];
	}
	/*-------------------------------------------------------------------------*/


//#include <iostream>
//#include <vector>
//using namespace std;

class Knapsack {
	vector<int> dp;
	const int capacity;

public:
	explicit Knapsack(int max_cap) : capacity(max_cap), dp(max_cap + 1, 0) {}

	void add(int time, int value) {
		for (int j = capacity; j >= time; --j) {
			if (dp[j - time] + value > dp[j]) {
				dp[j] = dp[j - time] + value;
			}
		}
	}

	int solve() const {
		return dp[capacity];
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T, M;
	cin >> T >> M;

	Knapsack solver(T);

	for (int i = 0; i < M; ++i) {
		int time, val;
		cin >> time >> val; // �ϸ���Ŀ˳��ʱ�䡢��ֵ
		solver.add(time, val);
	}

	cout << solver.solve();
	return 0;
}