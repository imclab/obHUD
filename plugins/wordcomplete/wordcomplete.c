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

#include "wordcomplete.h"

int fooling(unsigned char c) {
  switch(c) {
    case 1: return 0;
    case 2: return 1;
    case 4: return 2;
    case 8: return 3;
    case 16: return 4;
    case 32: return 5;
    case 64: return 6;
    case 128: return 7;
  }
}

void restore(int s) {
  die=1;
}

/*
void handleKey(char* keyname, char* word, char* wp){
  if(keyname == clear){
    wp = word;
    *wp = '\0';
  } else if(keyname == bkspce){
    if(wp != &word[0]){
      wp--;
      *wp = '\0';
    }
  } else if(keyname == ignore){
    //nothing
  } else {
    *wp = *keyname;
    wp++;
    *wp = '\0';
  }
  //printf("%s, %x, %x\n", keyname, word, wp);
  //printf("%s\n", word);
}
*/

int main(int argc, char* argv) {
  unsigned char ok[32];
  unsigned char nk[32];
  int i;
  unsigned int keycode;
  char word[100] = "\0";
  char* wp = word;
  
  //daemonizing it
  /*if (fork() < 0) {
    return -1;
  }
  if (setsid() < 0) {
    return -1;
  }*/

  //Handle nice closing
  die=0;
  signal(SIGTERM, restore);
  signal(SIGQUIT, restore);
  signal(SIGINT, restore);
  display = XOpenDisplay(NULL);
  if(display==NULL) {
    return -1;
  }
  XQueryKeymap(display, ok);
  while(!die) {
    fflush(stdout);
    usleep(5000);
    XQueryKeymap(display, nk);
    for(i=0;i<32;i++) {
      if(nk[i] != ok[i]) {
        if(nk[i] != 0) {
          //pressed key
          keycode=i*8+fooling(nk[i] ^ ok[i]);
          char ks;
          char *keyname;
          keyname="";
          switch(keycode){
            // numpad
          case 79: // 7
          case 80: // 8
          case 81: // 9
          case 83: // 4
          case 84: // 5
          case 85: // 6
          case 87: // 1
          case 88: // 2
          case 89: // 3
          case 90: // 0
            // Numpad keys do not work att
            keyname = clear;
            break;
            // numbers
          case 10: // 1
          case 11: // 2
          case 12: // 3
          case 13: // 4
          case 14: // 5
          case 15: // 6
          case 16: // 7
          case 17: // 8
          case 18: // 9
          case 19: // 0
            // top row
          case 24: // q
          case 25: // w
          case 26: // e
          case 27: // r
          case 28: // t
          case 29: // y
          case 30: // u
          case 31: // i
          case 32: // o
          case 33: // p
            // middle row
          case 38: // a
          case 39: // s
          case 40: // d
          case 41: // f
          case 42: // g
          case 43: // h
          case 44: // j
          case 45: // k
          case 46: // l
            // bottom row
          case 52: // z
          case 53: // x
          case 54: // c
          case 55: // v
          case 56: // b
          case 57: // n
          case 58: // m
            ks = XKeycodeToKeysym(display, keycode, 0);
            keyname = XKeysymToString(ks);
            break;
            
          case 105: // "ctrl down";
          case 133: // "win down";
          case 108: // "alt gr down";
          case 64: // "alt down";
          case 34: // "å";
          case 48: // "ä";
          case 47: // "ö";
          case 23: // "tab";
          case 67: // "F1";
          case 68: // "F2";
          case 69: // "F3";
          case 70: // "F4";
          case 71: // "F5";
          case 72: // "F6";
          case 73: // "F7";
          case 74: // "F8";
          case 75: // "F9";
          case 76: // "F10";
          case 95: // "F11";
          case 96: // "F12";
          case 9:  // "escape";
          case 111: // "up"
          case 113: // "left"
          case 114: // "right"
          case 116: // "down"
          case 65: // "space"
          case 35: // "]"
          case 51: // "\"
          case 59: // ","
          case 60: // "."`
          case 61: // "/"
          case 49: // "~"
          case 20: // "-"
          case 21: // "="
          case 119: // "del" 
          case 36:  // "return";
          case 104: // "return";
            keyname = clear;
            break;
          case 22: // "backspace";
            keyname = bkspce;
            break;
          case 50:
          case 62: // "shift down";
          case 66: // "caps lock";
          case 37: // "control"
          case 135: // "menu"
          case 107: // "PrtSc"
          case 127: // "pause"
          case 118: // "insert"
          case 77: // "Num Lock"
          case 78: // "Scroll Lock"
            keyname = ignore;
            break;
          default:
            printf("\n*Error: keycode %d not recognized*\n",keycode);
          }

          if(strcmp(keyname,"Q")==0) {
            //keyname="[left key]";
            keyname = clear;
          } else if(strcmp(keyname,"S")==0){
            //keyname="[right key]";
            keyname = clear;
          } else if(strcmp(keyname,"R")==0){
            //keyname="[up key]";
            keyname = clear;
          } else if(strcmp(keyname,"T")==0){
            //keyname="[down key]";
            keyname = clear;
          } 

          if(keyname == clear){
            wp = word;
            *wp = '\0';
          } else if(keyname == bkspce){
            if(wp != &word[0]){
              wp--;
              *wp = '\0';
            }
          } else if(keyname == ignore){
            //nothing
          } else {
            *wp = *keyname;
            wp++;
            *wp = '\0';
          }            //printf("%s",keyname);
        } else {
          keycode=i*8+fooling(nk[i] ^ ok[i]);
          /*
            switch(keycode){
            case 50:
            case 62:
            printf("[shift up]");
            break;
            case 37:
            case 105:
            printf("[ctrl up]");
            break;
            case 133:
            printf("[win up]");
            break;
            case 108:
            printf("[alt gr up]");
            break;
            case 64:
            printf("[alt up]");
            break;
            }
          */
        }
        ok[i]=nk[i];
      }
    }
  }
  XCloseDisplay(display);
  return 0;
}