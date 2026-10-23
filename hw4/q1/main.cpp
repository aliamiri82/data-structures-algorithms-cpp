#include <iostream>

using namespace std;

typedef long long ll;

struct Node {
    ll val;
    ll sum;
    int height;
    int size;
    Node *left, *right;

    Node(ll v) : val(v), sum(v), height(1), size(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* n) { return n ? n->height : 0; }
int getSize(Node* n) { return n ? n->size : 0; }
ll getSum(Node* n) { return n ? n->sum : 0; }

void update(Node* n) {
    if (n) {
        n->height = 1 + (getHeight(n->left) > getHeight(n->right) ? getHeight(n->left) : getHeight(n->right));
        n->size = 1 + getSize(n->left) + getSize(n->right);
        n->sum = n->val + getSum(n->left) + getSum(n->right);
    }
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

int getBalance(Node* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

Node* insert(Node* node, ll val) {
    if (!node) return new Node(val);
    if (val < node->val) node->left = insert(node->left, val);
    else node->right = insert(node->right, val);

    update(node);
    int balance = getBalance(node);

    if (balance > 1 && val < node->left->val) return rotateRight(node);
    if (balance < -1 && val >= node->right->val) return rotateLeft(node);
    if (balance > 1 && val >= node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && val < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left) current = current->left;
    return current;
}

Node* remove(Node* root, ll val) {
    if (!root) return root;
    if (val < root->val) root->left = remove(root->left, val);
    else if (val > root->val) root->right = remove(root->right, val);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = remove(root->right, temp->val);
        }
    }
    update(root);
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

void findKthAndSum(Node* root, int k, ll &kthVal, ll &prefixSum) {
    int leftSize = getSize(root->left);
    if (k <= leftSize) {
        findKthAndSum(root->left, k, kthVal, prefixSum);
    } else if (k == leftSize + 1) {
        kthVal = root->val;
        prefixSum += getSum(root->left) + root->val;
    } else {
        prefixSum += getSum(root->left) + root->val;
        findKthAndSum(root->right, k - leftSize - 1, kthVal, prefixSum);
    }
}

int main() {

    int n, k;
    cin >> n >> k;
    ll* arr = new ll[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    Node* root = nullptr;
    int m = (k + 1) / 2;

    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        if (i >= k) {
            root = remove(root, arr[i - k]);
        }

        if (i >= k - 1) {
            ll median = 0, sumLow = 0;
            findKthAndSum(root, m, median, sumLow);

            ll sumHigh = getSum(root) - sumLow;
            ll cost = ( (ll)m * median - sumLow ) + ( sumHigh - (ll)(k - m) * median );
            cout << cost << (i == n - 1 ? "" : " ");
        }
    }
    cout << endl;

    delete[] arr;
    return 0;
}