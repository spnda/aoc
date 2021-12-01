import 'dart:io';

void main() async {
  await File('adapters.txt')
    .openRead();
}
