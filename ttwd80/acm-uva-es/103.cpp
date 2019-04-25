#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

typedef vector<int> vi;

bool fits_into(int s, int b, int n, int **source) {
  for (int i = 0; i < n; i++) {
    if (source[s][i] >= source[b][i]) {
      return false;
    }
  }
  return true;
}

int process_row(int value, int n, int **source, map<int, vi *> &count_map,
                int max_count) {
  for (int i = max_count; i >= 1; i--) {
    vi *vip = count_map[i];
    for (vi::iterator it = vip->begin(); it != vip->end(); ++it) {
      cout << "testing with all elements with length = " << i << endl;
      if (fits_into(*it, value, n, source)) {
        cout << *it << " is smaller than " << value << endl;
        return i + 1;
      } else {
        cout << *it << " is NOT smaller than " << value << endl;
      }
    }
  }
  return 1;
}

void display_count_map(map<int, vi *> &count_map, int max_count) {
  cout << "count map" << endl;
  for (int i = 1; i <= max_count; i++) {
    vi *vip = count_map[i];
    cout << i << ": ";
    string sep = "";
    for (vi::iterator it = vip->begin(); it != vip->end(); ++it) {
      cout << sep << *it;
      sep = ", ";
    }
    cout << endl;
  }
}

void process(int k, int n, int **source) {
  int *sequence = new int[k];
  map<int, vi *> count_map;
  for (int i = 0; i < k; i++) {
    sequence[i] = -1;
    count_map[i + 1] = new vi();
  }

  int max_count = 0;
  for (int i = 0; i < k; i++) {
    int count = process_row(i, n, source, count_map, max_count);
    count_map[count]->push_back(i);
    max_count = max(max_count, count);
  }

  display_count_map(count_map, max_count);

  for (int i = 0; i < k; i++) {
    delete count_map[i + 1];
  }
  delete[] sequence;
}

bool compare(int *a, int *b) { return a[0] < b[0]; }
void process(int k, int n) {
  int **source = new int *[k];
  for (int i = 0; i < k; i++) {
    source[i] = new int[n];
  }
  for (int r = 0; r < k; r++) {
    for (int c = 0; c < n; c++) {
      cin >> source[r][c];
    }
    sort(source[r], source[r] + n);
  }
  sort(source, source + k, compare);

  // display content
  for (int r = 0; r < k; r++) {
    for (int i = 0; i < n; i++) {
      cout << source[r][i] << " ";
    }
    cout << endl;
  }

  process(k, n, source);

  for (int i = 0; i < k; i++) {
    delete[] source[i];
  }
  delete[] source;
}
int main(int argc, char const *argv[]) {
  int k;
  int n;
  while (cin >> k >> n) {
    process(k, n);
  }
  return 0;
}
