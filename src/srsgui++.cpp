#include "srsgui/srsgui++.h"
#include <stdio.h>
#include <QApplication>
#include <unistd.h>

pthread_t threadxx;
static int sdrgui_initiatedxx=0;

void *qt_threadxx(void *arg)
{
  int argc = 1;
  char* argv[] = { const_cast<char *>("libLTE Visualizer"), NULL };
  QApplication app(argc, argv);
  app.exec();
  pthread_exit(NULL);
}

int sdrgui_init() {
  if(!sdrgui_initiatedxx)
  {
    /** FIXME: Set attributes to detachable */
    if (pthread_create(&threadxx, NULL, qt_threadxx, NULL))
    {
      perror("phtread_create");
      return -1;
    }
    usleep(100000);
    sdrgui_initiatedxx=1;
	}
	return 0;
}

void sdrgui_exit() {
  if(sdrgui_initiatedxx)
  {
    usleep(100000);
    pthread_cancel(threadxx);
	}
  sdrgui_initiatedxx=0;
}
