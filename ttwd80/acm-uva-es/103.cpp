#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

bool fits_into(int s, int b, int n, int **source) {
  for (int i = 0; i < n; i++) {
    if (source[s][i] >= source[b][i]) {
      return false;
    }
  }
  return true;
}

void process(int k, int n, int **source) {
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

  //display content
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
