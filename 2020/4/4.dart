import 'dart:convert';
import 'dart:io';

List<Passport> passports = <Passport>[];
List<String> eyeColors = const ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth'];
String cur = "";
int valid = 0, valid2 = 0;
RegExp clrRegex = RegExp(r"^#(?:[0-9a-fA-F]{3}){1,2}$");

void main() async {
  await File("passports.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((l) {
      if (l == "") {
        passports.add(Passport(cur));
        cur = "";
        if (passports.last.isValid()) valid++;
        if (passports.last.isValid2()) valid2++;
      } else cur += (cur == "" ? "" : " ") + l;
    }).then((v) {
      passports.add(Passport(cur));
      if (passports.last.isValid()) valid++;
      if (passports.last.isValid2()) valid2++;
      print("$valid $valid2");
    });
}

class Passport {
  String? byr, iyr, eyr, hgt, hcl, ecl, pid, cid;
  
  Passport(String str) {
    final parts = str.split(" ");
    for (int i = 0; i < parts.length; i++) {
      final props = parts[i].split(":");
      switch (props[0]) {
        case "byr": byr = props[1]; break;
        case "iyr": iyr = props[1]; break;
        case "eyr": eyr = props[1]; break;
        case "hgt": hgt = props[1]; break;
        case "hcl": hcl = props[1]; break;
        case "ecl": ecl = props[1]; break;
        case "pid": pid = props[1]; break;
        case "cid": cid = props[1]; break;
        default: break;
      }
    }
  }

  bool isValid() {
    return byr != null && iyr != null && eyr != null && hgt != null && hcl != null && ecl != null && pid != null;
  }

  bool isValid2() {
    if (!isValid()) return false;
    if (int.parse(byr!) < 1920 || int.parse(byr!) > 2002) return false;
    if (int.parse(iyr!) < 2010 || int.parse(iyr!) > 2020) return false;
    if (int.parse(eyr!) < 2020 || int.parse(eyr!) > 2030) return false;
    if (hgt!.contains("cm")) { // Height
      int h = int.parse(hgt!.split("cm").first);
      if (h < 150 || h > 193) return false;
    } else if (hgt!.contains("in")) {
      int h = int.parse(hgt!.split("in").first);
      if (h < 59 || h > 76) return false;
    } else return false;
    if (!clrRegex.hasMatch(hcl!)) return false;
    if (!eyeColors.contains(ecl)) return false;
    if (pid!.length != 9) return false;
    return true;
  }
}
