/* Copyright (c) 2011, Kevin Porter
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *    *  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    *  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    *  Neither the name of Ryan Flannery nor the names of his contributors
 *       may not be used to endorse or promote products derived from this
 *       software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#include <xosd.h>


typedef struct
{
   int   daemonize;
   int   xoffset;
   int   yoffset;
   int   sleep;
   char *format;
   char *color;
   char *font;
   int   shadow;
   char *bcolor;
} xosd_clock_settings;


void usage(const char *progname);
void parse_cmdline(int argc, char **argv, xosd_clock_settings *settings);


int main(int argc, char *argv[])
{
   time_t   t;                      /* time object */
   char     timestr[1000];          /* string to hold time output */
   xosd    *osd = NULL;             /* xosd object */
   xosd_clock_settings settings;    /* settings container */

   /* initialize default settings */
   settings.daemonize = 0;
   settings.xoffset   = XOSD_right;
   settings.yoffset   = XOSD_bottom;
   settings.sleep     = 1;
   settings.format    = "%a %d %b %Y %I:%M:%S %p";
   settings.color     = "red";
   settings.font      = "";
   settings.shadow    = 0;
   settings.bcolor    = "black";

   /* create xosd window and apply window settings */
   if ((osd = xosd_create(1)) == NULL)
      errx(1, "could not create xosd: %s", xosd_error);

   xosd_set_pos(osd,settings.yoffset);
   xosd_set_align(osd,settings.xoffset);
   xosd_set_horizontal_offset(osd,20);
   /* set font, color, shadow */
   if (xosd_set_colour(osd, settings.color) < 0)
      errx(1, "could not set color '%s': %s", settings.color, xosd_error);

   if (settings.font != "" && xosd_set_font(osd, settings.font) < 0)
      errx(1, "could not set font '%s': %s", settings.font, xosd_error);

   if (settings.shadow > 0 && xosd_set_shadow_offset(osd, settings.shadow) < 0)
      errx(1, "could not setup shadow: %s", xosd_error);

   if (settings.bcolor != "")
   {  if (xosd_set_outline_offset(osd, 1) < 0)
         errx(1, "could not set border width: %s", xosd_error);
      else
         if (xosd_set_outline_colour(osd, settings.bcolor) < 0)
            errx(1, "could not set border color '%s': %s", settings.bcolor,
               xosd_error);
   }

   /* begin main display loop */
   while (1)
   {
      t = time(NULL);
      strftime(timestr, sizeof(timestr) / sizeof(char), settings.format,
         localtime(&t));

      if (xosd_display(osd, 0, XOSD_string, timestr) < 0)
         errx(1, "could not display osd: %s", xosd_error);

      sleep(settings.sleep);
   }

   return 0;
}
