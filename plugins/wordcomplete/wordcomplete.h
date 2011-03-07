#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <X11/keysym.h>

Display *display;

int die;
char clear[] = "{CLEAR}";
char bkspce[] = "{BKSPCE}";
char ignore[] = "{IGNORE}";
