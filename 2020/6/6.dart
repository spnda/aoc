import 'dart:convert';
import 'dart:io';

String cur = "";
Map<int, String> cur2 = Map<int, String>();
int total = 0;
int total2 = 0;

void main() async {
  await File('answers.txt')
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((l) {
      if (l == "") { check(); check2(); }
      else {
        cur += (cur == "" ? "" : " ") + l;
        cur2.putIfAbsent(cur2.length, () => l);
      }
    }).then((v) { check(); check2(); }); // Check the last item aswell. It get's discarded due to line endings not having a last "" line.
  print(total);
  print(total2);
}

void check() {
  cur = cur.replaceAll(" ", "");
  Map<String, int> map = Map<String, int>();
  int n = 0; // Count of new 
  for (int i = 0; i < cur.length; i++) map.putIfAbsent(cur[i], () { n++; return 1; }); // Everytime we add something new, it's a new question, add to the count.
  cur = ""; // Reset current string
  total += n;
}

void check2() {
  int n = 0; // Count of questions everyone answered yes to.
  Map<String, int> map = Map<String, int>();
  for (MapEntry<int, String> person in cur2.entries) {
    for (int i = 0; i < person.value.length; i++) {
      if (map.containsKey(person.value[i])) {
        var val = map[person.value[i]]!; // If the question is already registered, add to the count of it.
        map[person.value[i]] = ++val;
      }
      else map.putIfAbsent(person.value[i], () => 1); // If it doesn't exist yet, add it.
    }
  }
  for (MapEntry<String, int> entry in map.entries) {
    if (entry.value == cur2.length) n++; // If the character exists as often as there are people who are in this group.
  }
  cur2.clear(); // Reset the map of people for the next group
  total2 += n;
}
