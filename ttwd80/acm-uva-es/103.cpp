#include <map>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

/*
 * standard, checks to see if s is smaller than b.
 * s - the index of the smaller element
 * b - the index of the bigger element
 * n - the number of elements in the row
 * source - the 2 dimentional matrix
 */
bool fits_into(int s, int b, int n, int **source) {
  for (int i = 0; i < n; i++) {
    if (source[s][i] >= source[b][i]) {
      return false;
    }
  }
  return true;
}

/*
 * Processes the row.
 * The function looks at the count_map.
 * Starting with the biggest value. let say max_count = 5.
 * that means, the longest sequence we have so far is 5.
 * we want to see if the current row can make it longer with 6.
 * the count_map would return a list of boxes that make up the 5 sequence
 * eg: [29, 39, 109]
 * in this example, 3 boxes have a sequence of 5 -> 29, 39, 109
 * in turn, 29 may be used to form [29, 28, 27, 26, 25]
 * but currently we don't care about it.
 * if the current box is 120, we want to see if box-29 can fit in box-120
 * if it can, then box-120 will be added to the map, under the key 6.
 * 6 because it can contain box-29 and box-29 can contain 5 items.
 * adding to the map is not done here, it is added in the calling function
 * this function simply returns 6, so that the caller can add it to the count_map.
 * This function links box-120 with box-29 by setting sequence[120] = 29.
 * if max_count = 5 and no box with size-5 can fit inside the current box,
 * we decrement it to 4 and try again,
 * if there is a match, we return 5, because try=4, and fit, so it must be 4 + 1.
 * if there is no match, we decrement until we reach try=1
 * if still no match, we return 1, since 1 is the smallest sequence.
 * a box that can't fit any other box has a sequence of 1. [55]
 *
 * value - the index of the current row in from "source"
 * n - the total elements in each row
 * source - the 2 dimentional matrix
 * count_map - the map of how many box (including self) can be contained.
 *           - if count_map[2] returns [10, 20, 30],
 *             boxes 10, 20, 30 can contain 2 boxes (including self)
 *           - eg: 10 stores 9, 9 is too small to store anything [10, 9]
 *                 20 stores 15, 15 is too small to store anything [20, 15]
 *           - if count_map[4] returns [40]
 *             40 may contain 33, 33 may contain 32, 32 may contain 31
 *             and 31 is too small to contain anything [40, 33, 32, 31]
 * max_count - the maximum count in the count_map
 *             if max_count is 5, then the longest sequence is 4 boxes long
 *             eg: [3, 1, 2, 4, 5]
 * sequence - we need this to backtrack.
 *            eg: [-1, -1, 1, 2, 2, 1, 4, 4]
 *            the 0-th box is too small to contain anything
 *            the 1-st box is too small to contain anything
 *            the 2-nd box contains box-1 (totaling 2, including self)
 *            the 3-rd box contains box-2 (totaling 3, including self)
 *            the 4-th box contains box-2 (totaling 3, including self)
 *            the 5-th box contains box-1 (totaling 2, including self)
 *            the 6-th box contains box-4 (totaling 4, including self)
 *            the 7-th box contains box-4 (totaling 4, including self)
 *            the largest number is 4, so the max seqeunce is 4
 *            4 can be found at index 6 or 7 so we can pick either 6 or 7
 *            element-6 has the value 4
 *            add that to our array [6, 4]
 *            element-4 has the value 2
 *            add that to our array [6, 4, 2]
 *            element-2 has the value 1
 *            add that to our array [6, 4, 2, 1]
 *            element-1 has the value -1, we stop
 *            this is our sequence on the sorted matrix
 */
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

/*
 * display function
 */
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

/*
 * display function
 */
void display_array(int *a, int k) {
  cout << "[";
  string sep = "";
  for (int i = 0; i < k; i++) {
    cout << sep << a[i];
    sep = ", ";
  }
  cout << "]" << endl;
}

/*
 * The function creates a count_map. then for each row index, 0-k, adds them to the count_map.
 * count_map with a value of {1 => {0, 1}, 2 => {2, 5}, 3 => {3, 4}, 4 => {6, 7} }
 * would indicate that box-0 and box-1 is the biggest box in a sequence of 1 box.
 * and and box-3 and box-4 is the biggest box in a sequence of 3 boxes.
 * it returns the max_count, in this case, 4.
 * it also modifies the parameter passed by ref, for track.
 * k - the number of rows
 * n - the number of columns
 * source - the 2 dimentional matrix
 * sequence - we need this to backtrack.
 *            eg: [-1, -1, 1, 2, 2, 1, 4, 4]
 *            the 0-th box is too small to contain anything
 *            the 1-st box is too small to contain anything
 *            the 2-nd box contains box-1 (totaling 2, including self)
 *            the 3-rd box contains box-2 (totaling 3, including self)
 *            the 4-th box contains box-2 (totaling 3, including self)
 *            the 5-th box contains box-1 (totaling 2, including self)
 *            the 6-th box contains box-4 (totaling 4, including self)
 *            the 7-th box contains box-4 (totaling 4, including self)
 *            the largest number is 4, so the max seqeunce is 4
 *            4 can be found at index 6 or 7 so we can pick either 6 or 7
 *            element-6 has the value 4
 *            add that to our array [6, 4]
 *            element-4 has the value 2
 *            add that to our array [6, 4, 2]
 *            element-2 has the value 1
 *            add that to our array [6, 4, 2, 1]
 *            element-1 has the value -1, we stop
 *            this is our sequence on the sorted matrix
 * track - this keeps track of where we should begin our backtrack.
 *         this should be a value in count_map[max_count]
 *         since count_map[max_count] is a vector, any value in the vector is valid.
 *         to make it easy, we choose index-0.
 * returns the max_count, we need this to display the longest sequence
 */
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

/*
 * simple function to compare 2 arrays
 */
bool compare(int *a, int *b) { return a[0] < b[0]; }

void read(int k, int n, int **source) {
  for (int r = 0; r < k; r++) {
    for (int c = 0; c < n; c++) {
      cin >> source[r][c];
    }
    sort(source[r], source[r] + n);
  }
  sort(source, source + k, compare);

}

/*
 * as the array is created, stores the original position and the pointer to a map
 * after the array is sorted, store new pointer and new position to a map.
 * this is needed to tranlate the after-sorted position to a before-sorted position
 *
 */
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

  read(k, n, source);

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
