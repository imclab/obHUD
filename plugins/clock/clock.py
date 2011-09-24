#!/usr/bin/env python2
"""
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
"""

import pyosd, time

class PyOSDClock:
    """ Displays a clock on the screen """
    lines = 1;
    default_font = "-*-fixed-medium-*-*-*-15-*-*-*-*-*-*-*"
    def __init__(self, 
                 pos    = pyosd.POS_BOT, 
                 align  = pyosd.ALIGN_RIGHT, 
                 sleep  = 1, 
                 style  = "%a %d %b %Y %I:%M:%S %p",
                 colour = "red",
                 outline_colour = "black",
                 font   = default_font, 
                 shadow = 0):
        
        self.osd = pyosd.osd(colour = colour, timeout = 0, 
                             pos = pos, lines = self.lines, 
                             font = font, shadow = shadow,
                             align = align)
        self.osd.set_outline_offset(1);
        self.osd.set_outline_colour(outline_colour);

    def run(self):
        while(True):
            self.tick()
            time.sleep(1)

    def tick(self):
        now = time.asctime(time.localtime())
        self.osd.display(now)

    def test(self):
        self.osd.set_timeout(2)
        now = time.asctime(time.localtime())
        self.osd.display(now)
        self.osd.wait_until_no_display()

        
clock = PyOSDClock()

clock.run()
