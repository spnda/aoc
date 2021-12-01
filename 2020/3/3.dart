import 'dart:convert';
import 'dart:io';

void main() async {
  List<List<String>> map = <List<String>>[];
  await File("map.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((e) => map.add(e.split("")))
    .then((v) {
      print(check(map, 1, 1) * check(map, 3, 1) * check(map, 5, 1) * check(map, 7, 1) * check(map, 1, 2));
    });
}

int check(List<List<String>> map, int slopeX, int slopeY) {
  int x = 0, y = 0, trees = 0;
  while (y <= map.length) {
    if (map[y][x] == "#") trees++;
    x += slopeX; y += slopeY;
    if (y >= map.length) break;
    else if (x >= map[y].length) x = slopeX - (map[y].length - 1 - (x - slopeX)) - 1;
  }
  return trees;
}
