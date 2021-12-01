import 'dart:async';
import 'dart:convert';
import 'dart:io';

void main() async {
  List<int> fuel = await loadFuelRequirements();
  int totalFuelRequirement = 0;

  // Part One
  for (int i = 0; i < fuel.length; i++) {
    totalFuelRequirement += getFuelRequirementForMass(fuel[i]);
  }
  print(totalFuelRequirement);

  // Part Two
  totalFuelRequirement = 0;
  for (int i = 0; i < fuel.length; i++) {
    int j = getFuelRequirementForMass(fuel[i]), 
        k = j;
    while (true) {
      k = getFuelRequirementForMass(k);
      if (k <= 0) break;
      j += k;
    }
    totalFuelRequirement += j;
  }
  print(totalFuelRequirement);
}

int getFuelRequirementForMass(int mass) {
  return (mass / 3).floor() - 2;
}

Future<List<int>> loadFuelRequirements() {
  final completer = Completer<List<int>>();
  final fuel = <int>[];
  File("fuelrequirements.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((e) => fuel.add(int.parse(e)))
    .then((value) => completer.complete(fuel));
  return completer.future;
}
