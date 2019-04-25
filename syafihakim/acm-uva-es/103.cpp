#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int, vi > piv;

bool comp(piv a, piv b) {
    return (a.second < b.second);
}

bool inside(vi a, vi b) {
    for(unsigned int i = 0; i < a.size(); i++) {
        if(a[i] >= b[i])
            return false;
    }
    return true;
}

int main() {

    int k, n;

    while(cin >> k >> n) {
        vector< piv > boxes(k, piv (n, {1,{0}}));

        for(int i = 0; i < k; i++) {
            vi tempV(n, 0);
            for(int j = 0; j < n; j++) {
                int tmp;
                cin >> tmp;
                tempV[j] = tmp;
            }
            sort(tempV.begin(), tempV.end(), greater<int>());
            boxes[i] = {i+1, tempV};
        }
        sort(boxes.begin(), boxes.end(), comp);

        map<int, int> parentBox;
        map<int, int> count;

        for(int i = 0; i < k; i++) {
            parentBox[boxes[i].first] = -1;
            count[boxes[i].first] = 1;
        }

        for(int i = 1; i < k; i++) {
            for(int j = 0; j < i; j++) {
                if(inside((boxes[j]).second, (boxes[i]).second)) {
                    if(count[boxes[j].first] >= count[boxes[i].first]-1) {
                        parentBox[boxes[i].first] = boxes[j].first;
                        count[boxes[i].first] = 1 + count[boxes[j].first];
                    }
                }
            }
        }

        cout << count[boxes[k-1].first] << endl;

        vector<int> res;

        int _box = boxes[k-1].first;

        while(_box != -1) {
            res.push_back(_box);
            _box = parentBox[_box];
        }

        reverse(res.begin(), res.end());

        for(int j = 0; j < res.size(); j++) {
            if(j > 0)
                cout << " ";
            cout << res[j];
        }
        cout << endl;
    }

    return 0;
}
