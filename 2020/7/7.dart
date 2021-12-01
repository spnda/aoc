import 'dart:convert';
import 'dart:io';

int countOfColours = 0;
int amountOfBagsInGoldBag = 0;
Map<String, Bag> bags = Map<String, Bag>();

class Pair<K, V> {
  final K count;
  final V bag;

  Pair(this.count, this.bag);

  K get getCount => count;
  V get getBag => bag;

  @override
  String toString() {
    return "$count: $bag";
  }
}

class Bag {
  final String key;
  final List<Pair<int, String>> children;

  Bag(this.children, this.key);

  factory Bag.parse(String str) {
    int i = str.indexOf("contain");
    String sub = str.substring(i + "contain".length);
    List<String> children = sub.split(", ");
    return Bag(children.map((f) {
      f = f.trimLeft();
      String count = f.substring(0, f.indexOf(" ") + 1);
      if (count.trim() != "no") {
        return Pair(count.trim() == "no" ? 0 : int.parse(count), removeBagLabel(f.substring(f.indexOf(" "))).trim());
      }
    }).where((f) => f != null).cast<Pair<int, String>>().toList(), removeBagLabel(str.substring(0, i)).trim());
  }

  @override
  String toString() {
    return "$key: $children";
  }
}

String removeBagLabel(String str) {
  return str.replaceFirst("bags", "").replaceFirst("bag", "").replaceFirst(".", "");
}

void main() async {
  final file = await File('bags.txt')
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .toList();
  
  for (String str in file) {
    Bag bag = Bag.parse(str);
    bags.putIfAbsent(bag.key, () => bag);
  }

  for (MapEntry<String, Bag> entry in bags.entries) {
    check(entry);
    // check2(entry);
  }
  print(countOfColours);
  print(amountOfBagsInGoldBag);
}

void check(MapEntry<String, Bag> entry) {
  for (Pair<int, String> child in entry.value.children) {
    print(child.bag);
    if (child.bag.contains("shiny gold")) {
      countOfColours++;
      break;
    }
    else {
      try {
        MapEntry<String, Bag> i = bags.entries.firstWhere((e) => e.value.key.contains(child.bag));
        check(i);
      } on StateError {}
    }
  }
}

void check2(MapEntry<String, Bag> entry) {
  int count = 0;
  for (Pair<int, String> child in entry.value.children) {
    count += child.count;
    try {
      MapEntry<String, Bag> i = bags.entries.firstWhere((e) => e.value.key.contains(child.bag));
      check2(i);
    } on StateError {}
  }
  amountOfBagsInGoldBag += count;
}
