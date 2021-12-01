import 'dart:convert';
import 'dart:io';

void main() async {
  List<int> seatIDs = <int>[];
  await File('passes.txt')
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((element) {
      final parts = element.split("");
      int upper = 127, lower = 0;
      for (int i = 0; i < 7; i++)
        switch (parts[i]) {
          case "F": upper = lower + ((upper - lower) ~/ 2); break;
          case "B": lower = lower + ((upper - lower) ~/ 2 + 1); break;
        }
      assert(lower != upper);
      int right = 7, left = 0;
      for (int i = 7; i < 10; i++)
        switch (parts[i]) {
          case "L": right = left + ((right - left) ~/ 2); break;
          case "R": left = left + ((right - left) ~/ 2 + 1); break;
        }
      seatIDs.add(upper * 8 + right); // Seat ID
    });
  seatIDs.sort();
  print(seatIDs.last); // Part One
  int previousID = seatIDs.first - 1, yourID = -1;
  for (int i = 0; i < seatIDs.length; i++) {
    if (previousID + 1 != seatIDs[i]) { yourID = previousID + 1; break; }
    previousID = seatIDs[i];
  }
  print(yourID); // Part Two
}
