#include <iostream>
#include <cmath>

using namespace std;

// ثابت‌ها
const int MAX_S = 1000005; // فرض بر اینکه سریال تا این حدود باشد
const long long MOD = 1000000007;

// ساختار گره برای Heap دستی
struct Node {
    double logVal;
    int p_idx;
    int k;
};

// پیاده‌سازی Min-Heap
Node heap[2000005];
int heapSize = 0;

void push(double v, int p, int k) {
    int i = ++heapSize;
    while (i > 1 && heap[i / 2].logVal > v) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i].logVal = v;
    heap[i].p_idx = p;
    heap[i].k = k;
}

Node pop() {
    Node res = heap[1];
    Node last = heap[heapSize--];
    int i = 1, child;
    while (i * 2 <= heapSize) {
        child = i * 2;
        if (child + 1 <= heapSize && heap[child + 1].logVal < heap[child].logVal)
            child++;
        if (last.logVal > heap[child].logVal) {
            heap[i] = heap[child];
            i = child;
        } else break;
    }
    heap[i] = last;
    return res;
}

// غربال برای تولید اعداد اول
int primes[MAX_S];
bool is_prime[2000000];
void sieve(int n) {
    for (int i = 2; i < 2000000; i++) is_prime[i] = true;
    int count = 0;
    for (int p = 2; p < 2000000; p++) {
        if (is_prime[p]) {
            primes[count++] = p;
            if (count >= n) break;
            for (int i = 2 * p; i < 2000000; i += p)
                is_prime[i] = false;
        }
    }
}

// تابع توان سریع برای محاسبه باقی‌مانده
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// محاسبه p^(2^k) به روش مرحله‌ای برای جلوگیری از سرریز توان
long long get_multiplier(int p_idx, int k) {
    long long p = primes[p_idx];
    long long res = p;
    // ما نیاز به p^(2^k) داریم
    for (int i = 0; i < k; i++) {
        res = (res * res) % MOD;
    }
    return res;
}

int main() {
    long long S;
    if (!(cin >> S)) return 0;

    if (S == 0) {
        cout << 1 << endl;
        return 0;
    }

    // آماده‌سازی اولیه
    sieve(S + 1);
    long long ans = 1;

    // در ابتدا اولین توان عدد اول 2 را در هیپ می‌گذاریم
    push(log((double)primes[0]), 0, 0);

    for (int i = 0; i < S; i++) {
        Node top = pop();

        // به روز رسانی جواب: ضرب در p^(2^k)
        ans = (ans * get_multiplier(top.p_idx, top.k)) % MOD;

        // اضافه کردن انتخاب بعدی برای همین عدد اول (توان بعدی)
        push(top.logVal * 2.0, top.p_idx, top.k + 1);

        // اگر این اولین بار بود که از این عدد اول استفاده کردیم، عدد اول بعدی را مجاز کن
        if (top.k == 0) {
            push(log((double)primes[top.p_idx + 1]), top.p_idx + 1, 0);
        }
    }

    cout << ans << endl;

    return 0;
}