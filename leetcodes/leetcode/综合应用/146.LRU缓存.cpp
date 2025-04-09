https://leetcode.cn/problems/lru-cache

// LRU����

#include <unordered_map>
using namespace std;

struct Node {
    int key, val;       
    Node* prev, * next;  
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int cap;             // ��������
    Node* head, * tail;   // ��ͷβ�ڵ㣨�ڱ��ڵ㣩
    unordered_map<int, Node*> cache;  // ��ϣ��ʵ��O(1)����

    // ��ӽڵ㵽����ͷ�����������λ�ã�
    void addNode(Node* node) {
        node->prev = head;         // �½ڵ�ǰ��ָ��ͷ�ڱ�
        node->next = head->next;   // �½ڵ���ָ��ԭͷ�ڵ�
        head->next->prev = node;   // ԭͷ�ڵ�ǰ��ָ���½ڵ�
        head->next = node;         // ͷ�ڱ����ָ���½ڵ�
    }

    // �Ƴ�ָ���ڵ㣨���ڷ���ʱ��λ�õ�����
    void removeNode(Node* node) {
        node->prev->next = node->next;  // ǰ���ڵ�������ǰ�ڵ�
        node->next->prev = node->prev;  // ��̽ڵ�����ǰ���ڵ�
    }

    // ���ڵ��ƶ�������ͷ�������Ϊ���ʹ�ã�
    void moveToHead(Node* node) {
        removeNode(node);  // �ȴӵ�ǰλ���Ƴ�
        addNode(node);     // �ٲ���ͷ��
    }

public:
    // ���캯����ʼ���ڱ��ڵ�[3](@ref)
    LRUCache(int capacity) : cap(capacity) {
        head = new Node(-1, -1);  // ����ͷ�ڱ�
        tail = new Node(-1, -1);  // ����β�ڱ�
        head->next = tail;        // ��ʼ��������
        tail->prev = head;
    }

    // ��ѯ������ʱ�临�Ӷ�O(1)
    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;            // δ�ҵ�����-1

        Node* node = cache[key];
        moveToHead(node);         // ����Ϊ���ʹ��
        return node->val;
    }

    // ����/���²�����ʱ�临�Ӷ�O(1)
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {  // �Ѵ��ڼ�
            Node* node = cache[key];
            node->val = value;    // ����ֵ
            moveToHead(node);     // ����Ϊ���ʹ��
        }
        else {                  // ������
            Node* newNode = new Node(key, value);
            cache[key] = newNode; // �����ϣ��
            addNode(newNode);      // ��������ͷ��

            if (cache.size() > cap) {  // ���������
                Node* lru = tail->prev; // ��ȡLRU�ڵ�
                removeNode(lru);       // �������Ƴ�
                cache.erase(lru->key); // �ӹ�ϣ��ɾ��
                delete lru;            // �ͷ��ڴ棨ʵ�ʹ��̽���������ָ�룩
            }
        }
    }
};
