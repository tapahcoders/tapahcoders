#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
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
                int max_count, int *sequence) {
  for (int i = max_count; i >= 1; i--) {
    vi *vip = count_map[i];
    for (vi::iterator it = vip->begin(); it != vip->end(); ++it) {
      //cout << "testing with all elements with length = " << i << endl;
      if (fits_into(*it, value, n, source)) {
        sequence[value] = *it;
        //cout << *it << " is smaller than " << value << endl;
        return i + 1;
      } else {
        //cout << *it << " is NOT smaller than " << value << endl;
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

void display_array(int *sequence, int k) {
  cout << "[";
  string sep = "";
  for (int i = 0; i < k; i++) {
    cout << sep << sequence[i];
    sep = ", ";
  }
  cout << "]" << endl;
}

int process(int k, int n, int **source, int *sequence, int &track) {
  map<int, vi *> count_map;
  for (int i = 0; i < k; i++) {
    count_map[i + 1] = new vi();
  }

  int max_count = 0;
  for (int i = 0; i < k; i++) {
    int count = process_row(i, n, source, count_map, max_count, sequence);
    count_map[count]->push_back(i);
    max_count = max(max_count, count);
  }

  //display_count_map(count_map, max_count);
  //display_array(sequence, k);
  track = count_map[max_count]->at(0);

  for (int i = 0; i < k; i++) {
    delete count_map[i + 1];
  }
  return max_count;
}

bool compare(int *a, int *b) { return a[0] < b[0]; }
void process(int k, int n) {
  int **source = new int *[k];
  map<int, int *> position_box_map;
  map<int *, int> box_position_map;
  int *sequence = new int[k];

  for (int i = 0; i < k; i++) {
    sequence[i] = -1;
  }

  for (int i = 0; i < k; i++) {
    source[i] = new int[n];
    box_position_map[source[i]] = i;

  }
  for (int r = 0; r < k; r++) {
    for (int c = 0; c < n; c++) {
      cin >> source[r][c];
    }
    sort(source[r], source[r] + n);
  }
  sort(source, source + k, compare);

  for (int i = 0; i < k; i++) {
    position_box_map[i] = source[i];
  }

  // display content
  //for (int r = 0; r < k; r++) {
    //for (int i = 0; i < n; i++) {
      //cout << source[r][i] << " ";
    //}
    //cout << endl;
  //}

  int track = -1;
  int max_count = process(k, n, source, sequence, track);
  stack<int> stack;
  while (track != -1) {
    //cout << "track = " << track << endl;
    int pos = box_position_map[position_box_map[track]];
    //cout << "pos " << pos << endl;
    stack.push(pos + 1);
    //cout << track << ": ";
    //display_array(source[track], n);
    track = sequence[track];
  }
  cout << max_count << endl;
  string sep = "";
  while(!stack.empty()) {
    cout << sep << stack.top();
    stack.pop();
    sep = " ";
  }
  cout << endl;

  for (int i = 0; i < k; i++) {
    delete[] source[i];
  }
  delete[] source;
  delete[] sequence;
}
int main(int argc, char const *argv[]) {
  int k;
  int n;
  while (cin >> k >> n) {
    process(k, n);
  }
  return 0;
}
