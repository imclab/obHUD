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
  printf("%s\n", word);
}

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
          char ks = XKeycodeToKeysym(display, keycode, 0);
          char *keyname = XKeysymToString(ks);
          if(keycode == 65){  // space
            keyname = clear;
          }
          if(!keyname) {
            keyname="";
            switch(keycode){
            case 37:
            case 105:
              //keyname="ctrl down";
            case 133:
              //keyname="win down";
            case 108:
              //keyname="alt gr down";
            case 64:
              //keyname="alt down";
            case 34:
              //keyname="å";
            case 48:
              //keyname="ä";
            case 47:
              //keyname="ö";
            case 23:
              //keyname="tab";
            case 67:
              //keyname="F1";
            case 68:
              //keyname="F2";
            case 69:
              //keyname="F3";
            case 70:
              //keyname="F4";
            case 71:
              //keyname="F5";
            case 72:
              //keyname="F6";
            case 73:
              //keyname="F7";
            case 74:
              //keyname="F8";
            case 75:
              //keyname="F9";
            case 76:
              //keyname="F10";
            case 95:
              //keyname="F11";
            case 96:
              //keyname="F12";
            case 9:
              //keyname="escape";
            case 32:
              //keyname="space";
              printf("space");
            case 36:
            case 104:
              //keyname="return";
              keyname = clear;
              break;
            case 22:
              //keyname="backspace";
              keyname = bkspce;
              break;
            case 50:
            case 62:
              //keyname="shift down";
            case 66:
              //keyname="caps lock";
              keyname = ignore;
              break;
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
            }
            //printf("%s, %x, %x\n", keyname, word, wp);
            printf("%s\n", word);
            //handleKey(keyname,&word[0],wp);
            /*
            if(strcmp("",keyname)==0) {
              printf("[unknown: %u]",keycode);
            } else {
              printf("[%s]",keyname);
            }
            */
          } else {
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
            //printf("%s",keyname);
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
            printf("%s\n", word);

            //handleKey(keyname,&word[0],wp);
          }
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
