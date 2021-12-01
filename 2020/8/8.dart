import 'dart:convert';
import 'dart:io';

// Only answer for part 1
void main() async {
  int acc = 0;
  Map<int, bool> ins = Map<int, bool>();
  List<String> program = await File('program.txt')
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .toList();
  
  for (int i = 0; i < program.length; i++) {
    if (ins[i] != null) break; // Been run before
    List<String> instruction = program[i].split(" ");
    print("${i + 1}: ${program[i]}");
    switch (instruction[0]) {
      case "nop": 
        break;
      case "jmp":
        int jmp = int.parse(instruction[1]);
        ins.putIfAbsent(i, () => true);
        if (i + jmp < program.length) i += jmp - 1;
        break;
      case "acc":
        acc += int.parse(instruction[1]);
        break;
      default:
        break;
    }
    ins.putIfAbsent(i, () => true);
  }
  print(acc);
}
