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

void print_row(int r, int n, int **source) {

  string sep = "";
  cout << "[";
  for (int i = 0; i < n; i++) {
    cout << sep << source[r][i];
    sep = ", ";
  }
  cout << "]";
}

void append_to(map<int, vi*> &count_map, int count, int i) {
  //cout << "adding " << i << " to " << count << endl;
  if (0 == count_map[count]) {
    vi *vip = new vi();
    vip->push_back(i);
    count_map[count] = vip;
  } else {
    count_map[count]->push_back(i);
    //cout << "length of map[" << count << "] is now " << count_map[count]->size() << endl;
  }
}
int process_row(int i, map<int, vi*> &count_map, int max_count, int k, int n, int **source) {
  //cout << "max count => " << max_count << endl;
  for (int c = max_count; c >= 1; c--) {
    vi *vip = count_map[c];
    for (vi::iterator it = vip->begin(); vip->end() != it; ++it) {
      if (fits_into(*it, i, n, source)) {
        //cout << (*it) << " fits into " << i << endl;
        return c + 1;
      } else {
        //cout << (*it) << " does not fit into " << i << endl;
      }
    }
  }
  return 1;
}
void process(int k, int n, int **source) {
  map<int, vi*> count_map;
  int max_count = 0;
  for (int i = 0; i < k; i++) {
    int count = process_row(i, count_map, max_count, k, n, source);
    append_to(count_map, count, i);
    max_count = max(max_count, count);
    //cout << endl;
  }
  //cout << "max count = " << max_count << endl;
  //cout << count_map[max_count]->size() << endl;
}

void display_content(int k, int n, int **source) {
  for (int r = 0; r < k; r++) {
    for (int i = 0; i < n; i++) {
      cout << source[r][i] << " ";
    }
    cout << endl;
  }
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
  //display_content(k, n, source);


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
