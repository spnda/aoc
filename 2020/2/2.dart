import 'dart:convert';
import 'dart:io';

void main() async {
  int validPasswords = 0, validPasswordsPartTwo = 0;
  await File("passwords.txt")
    .openRead()
    .map(utf8.decode)
    .transform(LineSplitter())
    .forEach((e) {
      Password pw = Password(e);
      int count = pw.findCountOf(pw.char);
      if (count >= pw.minOrPosition && count <= pw.maxOrExclude) validPasswords++;

      if ((pw.pw[pw.minOrPosition - 1] == pw.char && pw.pw[pw.maxOrExclude - 1] != pw.char)
       || (pw.pw[pw.minOrPosition - 1] != pw.char && pw.pw[pw.maxOrExclude - 1] == pw.char)) validPasswordsPartTwo++;
    });
  print("$validPasswords\n$validPasswordsPartTwo");
}

class Password {
  late int minOrPosition, maxOrExclude;
  late String char, pw;

  Password(String str) {
    final parts = str.split(" "),
          minMax = parts[0].split("-");
    minOrPosition = int.parse(minMax[0]); maxOrExclude = int.parse(minMax[1]);
    char = parts[1].replaceFirst(":", ""); pw = parts[2];
  }

  int findCountOf(String str) {
    int ret = 0;
    for (int i = 0; i < pw.length; i++) if (pw[i] == str) ret++;
    return ret;
  }
}
