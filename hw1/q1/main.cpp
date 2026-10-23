#include <iostream>
#include <vector>
using namespace std;
#define ll long long
struct Sq { ll x, y, l; };

void hal (int n, vector<Sq> v,int pow) {
    if (n <= 0){
        if (n == 0) {
            cout << "YES" << endl;
            for (int i = 0; i < v.size(); i++) {
                cout << v[i].y <<" "<< v[i].x <<" "<< v[i].l << endl;
            }
        }
        else {
            cout << "NO" << endl;
        }
        return;
    }
    else {
        if (v.size() == 0) {
            Sq sq;
            sq.x = 1;
            sq.y = 1;
            sq.l = 1;
            v.push_back(sq);
        }
        else {
            for (int i = 0; i < v.size(); i++) {
                v[i].y += pow;
            }
            int size = v.size();
            for (int i = 0; i < size; i++) {
                v.push_back(v[i]);
            }
            for (int i = 0; i < v.size() / 2; i++) {
                v[i].x += pow;
            }
            for (int i = 0; i < v.size() / 2; i++) {
                v[i].y -= pow;
            }
            Sq sq;
            sq.x = 1;
            sq.y = 1;
            sq.l = pow;
            v.insert(v.begin(),sq );
        }
        n = n - pow;
        pow = pow * 2;
        hal(n,v,pow);
    }

}


int main() {
    int n;
    cin >> n;
    vector<Sq> v;
    hal(n, v , 1);

    return 0;
}
