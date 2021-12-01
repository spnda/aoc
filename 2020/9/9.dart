import 'dart:convert';
import 'dart:io';

void main() async {
  List<int> all = <int>[];
  List<int> last = <int>[];
  int? invalidInt = null;
  await File('input.txt')
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((i) {
      int newInt = int.parse(i);
      all.add(newInt);
      if (last.length < 25) last.add(newInt);
      else {
        int x = 0, y = 0;
        bool valid = false;
        for (int i = 0; i < last.length; i++) {
          for (int j = 0; j < last.length; j++) {
            if (last[i] + last[j] == newInt) {
              x = last[i];
              y = last[j];
              valid = true;
              break;
            }
          }
          if (valid) break;
        }
        if (!valid) {
          invalidInt = newInt; print(newInt);
        };
        last.removeAt(0);
        last.add(newInt);
      }
    });
  Map<int, List<int>> map = Map<int, List<int>>();
  List<int>? solution;
  for (int i = 0; i < all.length; i++) {
    map.putIfAbsent(i, () => <int>[all[i]]);
    for (int j = i; j > 0; j--) {
      if (!map.containsKey(i - j)) print(i - j);
      int s = sum(map[i - j]!);
      if (s == invalidInt) {
        solution = map[i - j]; 
        break;
      } else if (invalidInt != null && s < invalidInt!) {
        map[i - j]?.add(all[i]);
      }
    }

    if (solution != null)
      break;
  }
  if (solution != null)
    print(smallest(solution) + largest(solution));
}

int sum(List<int> list) {
  int ret = 0;
  for (int i in list) ret += i;
  return ret;
}

int smallest(List<int> list) {
  int smallest = 0;
  for (int i in list) { if (smallest > i) smallest = i; }
  return smallest;
}

int largest(List<int> list) {
  int largest = 0;
  for (int i in list) { if (largest < i) largest = i; }
  return largest;
}
