#include "unistd.h"
#include "stdbool.h"

struct Confer {
  bool Foo;
  int Bar;
};

static struct Confer basic, user, *Conf;

void init_conf(int argc) {
  basic.Foo = false;
  basic.Bar = 42;

  Conf = &user;
  Conf->Foo = argc == 2;
  Conf->Bar = argc;
}

void switch_conf() {
  if (Conf == &basic) {
    Conf = &user;
  } else {
    Conf = &basic;
  }
}

int main( int argc, char *argv[]) {

  init_conf(argc);

  if (Conf->Foo) {
    sleep(5);
  } else {
    sleep(2);
  }

  if (Conf->Bar > 3) {
    sleep(5);
  } else {
    sleep(2);
  }

  switch_conf();

  if (Conf->Bar == 42) {
    sleep(5);
  }

  return 0;
}
