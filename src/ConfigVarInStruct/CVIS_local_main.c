#include "unistd.h"
#include "stdbool.h"

struct Confer {
  bool Foo;
  int Bar;
};

int main( int argc, char *argv[]) {

  struct Confer Conf;
  Conf.Foo = argc == 2;
  Conf.Bar = argc;

  if (Conf.Foo) {
    sleep(5);
  } else {
    sleep(2);
  }

  if (Conf.Bar > 3) {
    sleep(5);
  } else {
    sleep(2);
  }

  return 0;
}
