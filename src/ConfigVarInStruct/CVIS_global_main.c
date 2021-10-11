#include "unistd.h"
#include "stdbool.h"

struct Confer {
  bool Foo;
  int Bar;
};

static struct Confer Conf;

int main( int argc, char *argv[]) {

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
