
#include <JFF.h>
#include <Application.h>

int main(int argc, char *argv[]) {
  JFF_init();

  Application_t app = send(Application, new, argc, argv);

  int ret = send(app, start);

  JFF_release();
  return ret;
}

