import 'dart:convert';
import 'dart:io';
import 'dart:async';

/// Advent of code 1
void main() async {
  final expenses = await loadExpenses();

  /// Find the two entries that sum to `2020` and then multiply those numbers together.
  for (int i = 0; i < expenses.length; i++) {
    for (int j = 0; j < expenses.length; j++) {
      final int x = expenses[i], y = expenses[j];
      if (x + y == 2020) {
        print("x: $x");
        print("y: $y");
        print("x * y: ${x * y}");
        // Exit the loops by making i and j to big for the loop.
        j = i = expenses.length;
      }
    }
  }

  /// Find the three entries that sum to `2020` and then multiply those numbers together.
  for (int i = 0; i < expenses.length; i++) {
    for (int j = 0; j < expenses.length; j++) {
      for (int k = 0; k < expenses.length; k++) {
        final int x = expenses[i], y = expenses[j], z = expenses[k];
        if (x + y + z == 2020) {
          print("x: $x");
          print("y: $y");
          print("z: $z");
          print("x * y * z: ${x * y * z}");
          // Exit the loops by making i and j to big for the loop.
          k = j = i = expenses.length;
        }
      }
    }
  }
}

Future<List<int>> loadExpenses() {
  final completer = Completer<List<int>>();
  final expenses = <int>[];
  File("expenses.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((e) => expenses.add(int.parse(e)))
    .then((value) => completer.complete(expenses));
  return completer.future;
}
