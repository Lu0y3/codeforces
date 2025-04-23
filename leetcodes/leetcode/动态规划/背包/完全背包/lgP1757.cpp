https://www.luogu.com.cn/problem/P1757

// ���鱳��(ģ��)
// ����һ������m��ʾ��������������n������ɹ���ѡ
// ÿ���������Լ������(��������)����ֵ(�������)�����(����)
// ͬһ�������Ʒֻ����ѡ1����������ѡ��Ʒ������ܺͲ��ܳ�����������
// ��ô��ѡ�����ܴﵽ��ֵ��󣬷������ļ�ֵ


/*-------------------------------------------------*/
    // �ϸ�λ�������Ķ�̬�滮
    public static int compute1() {
        int teams = 1;
        for (int i = 2; i <= n; i++) {
            if (arr[i - 1][2] != arr[i][2]) {
                teams++;
            }
        }
        // ��ı��1~teams
        // dp[i][j] : 1~i����ķ�Χ��ÿ�������Ʒ��һ��������������j������£��������
        int[][] dp = new int[teams + 1][m + 1];
        // dp[0][....] = 0
        for (int start = 1, end = 2, i = 1; start <= n; i++) {
            while (end <= n && arr[end][2] == arr[start][2]) {
                end++;
            }
            // start ... end-1 -> i��
            for (int j = 0; j <= m; j++) {
                // arr[start...end-1]�ǵ�ǰ�飬���һ��
                // ���е�ÿһ����Ʒö��һ��
                dp[i][j] = dp[i - 1][j];
                for (int k = start; k < end; k++) {
                    // k�����ڵ�һ����Ʒ���
                    if (j - arr[k][0] >= 0) {
                        dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - arr[k][0]] + arr[k][1]);
                    }
                }
            }
            // startȥ����һ��ĵ�һ����Ʒ
            // ��������ʣ�µ���
            start = end++;
        }
        return dp[teams][m];
    }

    // �ռ�ѹ��
    public static int compute2() {
        // dp[0][...] = 0
        Arrays.fill(dp, 0, m + 1, 0);
        for (int start = 1, end = 2; start <= n;) {
            while (end <= n && arr[end][2] == arr[start][2]) {
                end++;
            }
            // start....end-1
            for (int j = m; j >= 0; j--) {
                for (int k = start; k < end; k++) {
                    if (j - arr[k][0] >= 0) {
                        dp[j] = Math.max(dp[j], arr[k][1] + dp[j - arr[k][0]]);
                    }
                }
            }
            start = end++;
        }
        return dp[m];
    }

/*--------------------------------------------------------------------*/



//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;

class GroupKnapsack {
    struct Item {
        int weight;  // ��Ʒ����
        int value;   // ��Ʒ��ֵ
        int group_id;// �������
        Item(int w, int v, int g) : weight(w), value(v), group_id(g) {}
    };

    vector<Item> items;  // ������Ʒ
    vector<int> dp;      // ��̬�滮����
    int capacity;        // ����������

    void process_groups() {
        // ���������
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.group_id < b.group_id;
            });

        int n = items.size();
        int start = 0;

        // ����������
        while (start < n) {
            int end = start;
            // �ҵ���ǰ��Ľ���λ��
            while (end < n && items[end].group_id == items[start].group_id) {
                end++;
            }

            // ������±�������
            for (int j = capacity; j >= 0; --j) {
                // ������ǰ����������Ʒ
                for (int k = start; k < end; ++k) {
                    if (j >= items[k].weight) {
                        dp[j] = max(dp[j], dp[j - items[k].weight] + items[k].value);
                    }
                }
            }
            start = end; // ������һ��
        }
    }

public:
    GroupKnapsack(int cap) : capacity(cap), dp(cap + 1, 0) {}

    void add_item(int w, int v, int g) {
        items.emplace_back(w, v, g);
    }

    int solve() {
        fill(dp.begin(), dp.end(), 0); // ����dp����
        process_groups();
        return dp[capacity];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n; // m: ������, n: ��Ʒ����
    cin >> m >> n;  // �޸�����˳��

    GroupKnapsack solver(m);

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        solver.add_item(a, b, c);
    }

    cout << solver.solve() << endl;

    return 0;
}




