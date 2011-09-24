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

import pyosd, time, subprocess, string, virtkey
import keylogger as kl
import wordbank

class PyOSDWordComplete:
    """ Displays a clock on the screen """
    wb = wordbank.WordBank()
    lines = 10;
    caps = False;
    selected = 0;
    default_font = "-*-fixed-medium-*-*-*-15-*-*-*-*-*-*-*"
    word = ""
    previous_key = ""
    result = []
    end_chars = ["~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+", 
                 "`", 
                 #"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", 
                 "-", "=",
                 "[", "]", "\\", "{", "}", "|", ";", "'", ":", "\"", ",", ".", "/",
                 "<", ">", "?", " "]

    def __init__(self, 
                 pos    = pyosd.POS_TOP, 
                 align  = pyosd.ALIGN_LEFT, 
                 sleep  = 1, 
                 style  = "%a %d %b %Y %I:%M:%S %p",
                 colour = "white",
                 outline_colour = "black",
                 font   = default_font, 
                 shadow = 0):
        
        self.osd = pyosd.osd(colour = colour, timeout = 0, 
                             pos = pos, lines = self.lines, 
                             font = font, shadow = shadow,
                             align = align)
        self.osd.set_outline_offset(1)
        self.osd.set_vertical_offset(200)
        self.osd.set_outline_colour(outline_colour)

    def run(self):
        loop = True
        while(loop):
            loop = self.tick()
            time.sleep(.05)

    def tick(self):
        now = time.asctime(time.localtime())
        changed, modifiers, keys = kl.fetch_keys()
        if(self.previous_key == "<caps lock>") :
            if(keys == "<esc>") :
                return False            
            elif(not keys and modifiers["left shift"] ) :
                self.caps = False
                self.selected+=1
                if(self.selected > (self.lines - 1) or self.selected > len(self.result)) :
                    self.selected = 0
                self.previous_key = ""
        if keys : 
            if(len(keys) == 1 and keys not in self.end_chars) :
                self.word += str(keys)
            elif(keys == "<backspace>"):
                self.word = self.word[0:-1]
            elif(self.result and keys == "<caps lock>" and self.previous_key == "<caps lock>") :
                v = virtkey.virtkey()
                for i in range(len(self.word), len(self.result[self.selected])) :
                    v.press_unicode(ord(self.result[self.selected][i]))
                    v.release_unicode(ord(self.result[self.selected][i]))
                v.press_unicode(ord(" "))
                v.release_unicode(ord(" "))
                self.selected = 0
                self.word = ""
                self.result = []
            elif(keys == "<caps lock>") :
                self.caps = True
                self.previous_key = keys
            else:
                self.word = ""

            if(keys != "<caps lock>") :
                self.caps = False

            self.previous_key = keys

            if(self.word):
                #raw_result = subprocess.Popen(['look', self.word], stdout=subprocess.PIPE).communicate()[0]
                #self.result = string.split(raw_result)
                self.result = self.wb.getWords(self.word)
            else:
                self.result = []

        if(self.caps) :
            self.osd.set_colour("green")
        else :
            self.osd.set_colour("white")

        for i in range(10):
            if(len(self.result) > i):
                if(i == self.selected):
                    self.osd.display("[ " + self.result[i] + " ]", line = i)
                else :
                    self.osd.display("  " + self.result[i], line = i)
            else :
                self.osd.display("", line = i)
                
        return True

if __name__ == "__main__":
    subprocess.call(["xmodmap","-e", "clear Lock"])
    cpl = PyOSDWordComplete()
    cpl.run()
    subprocess.call(["xmodmap", "-e", "add Lock = Caps_Lock"])
