import 'dart:io';

void main() {
  final program = loadProgram();

  program[1] = 12;
  program[2] = 2;

  for (int i = 0; i < program.length; i) {
    switch (program[i]) {
      case 1: // opcode 1: add
        program[program[i + 3]] = program[program[i + 1]] + program[program[i + 2]];
        i += 4;
        break;
      case 2: // opcode 2: multiply
        program[program[i + 3]] = program[program[i + 1]] * program[program[i + 2]];
        i += 4;
        break;
      case 99: // opcode 99: end
        printList(program); // Print the program when we're done.
        return;
      default: 
        break;
        //throw Exception("Unexpected opcode.");
    }
  }
}

List<int> loadProgram() {
  return parseList(File("program.txt").readAsStringSync());
}

List<int> parseList(String list) {
  return list.split(",").map((f) => int.parse(f)).toList();
}

void printList(List list) {
  for (int i = 0; i < list.length; i++) {
    stdout.write(list[i]);
    if (i < list.length - 1) stdout.write(",");
  }
}
