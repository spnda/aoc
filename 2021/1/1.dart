import 'dart:convert';
import 'dart:io';

void main() async {
  final s = File("sea_depth.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter());

  var j = 0, k = 0, last = 0;
  final l = <int>[];
  await for (final ln in s) {
    l.add(int.parse(ln));
    // Part one
    if (l.length > 1 && l[l.length - 2] < l[l.length - 1])
      ++j;

    // Part two
    if (l.length <= 3) continue;
    if (l.length == 3)
      last = l.sublist(0, 3).fold(0, (p, n) => p + n);
    final sum = l.sublist(l.length - 3).fold(0, (p, n) => n + (p as int));
    if (sum > last)
      ++k;
    last = sum;
  }
  
  print(j); print(k);
}
