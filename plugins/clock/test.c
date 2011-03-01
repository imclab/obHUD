#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <xosd.h>

int main (int argc, char *argv[])
{
  xosd *osd;
  osd = xosd_create (2);
  if (osd == NULL)
    {
      perror ("Could not create \"osd\"");
      exit (1);
    }
  xosd_set_pos(osd,XOSD_middle);
  xosd_set_align(osd,XOSD_center);

  xosd_display (osd, 0, XOSD_string, "Hello World!");
  sleep (8);
  xosd_destroy (osd);
  exit (0);
}
