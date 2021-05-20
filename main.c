#include"acllib.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
typedef struct{
    char*word;
    int len;
    int nowlen;
    short Wordsize;
}string;
typedef string*String;
typedef struct{
    int x;
    int y;
    int show;
}caret;
typedef caret*Caret;
String str;
Caret car;
int p = 1,k = 1;
int start = 0,end = 0;
char pa[2];
void initialize(){
    str = (String)malloc(sizeof(string));
    car = (Caret)malloc(sizeof(caret));
    str->len = 20;
    str->nowlen = 1;
    str->Wordsize = 20;
    str->word = (char*)malloc(sizeof(char)*str->len);
    (str->word)[0] = '\0';
    car->x = car->y = 0;
    car->show = 0;
    setTextFont("Consolas");
    SetCaretBlinkTime(500);
    showCaret();
}
void paint(){
    int x = 0,y = 0;
    beginPaint();
    clearDevice();
    setTextSize(str->Wordsize);
    setCaretSize(1,str->Wordsize);
    if(car->x%50 == 0&&car->x!=0)setCaretPos(50*12,0);
    else setCaretPos(car->x%50*12,0);    
    if(car->x%50 == 0&&car->x!=0)start = (car->x/50-1)*50;
    else start = car->x/50*50;
    if((car->x/50+1)*50>=str->nowlen)end = str->nowlen;
    else end = (car->x/50+1)*50;
    for(int i = start;i<end;i++){
        pa[0] = (str->word)[i];
        if(p == -1&&i == car->x-1)setTextBkColor(YELLOW);
        else setTextBkColor(DEFAULT);
        paintText((i%50)*12,0,pa);
    }
    //if(p == -1)rectangle((car->x-1)*12,0,(car->x)*12,str->Wordsize);
    endPaint();
    if(p == -1)hideCaret();
    else showCaret();
}
void keyboardEvent(int key,int event){
    paint();
    if((key == VK_DELETE||key == VK_BACK)&&event == KEY_DOWN){
        if(car->x>=1){
            char*new = (char*)malloc(sizeof(char)*str->len);
            for(int i = car->x;i<str->nowlen;i++)new[i-1] = (str->word)[i];
            for(int i = 0;i<car->x-1;i++)new[i] = (str->word)[i];
            free(str->word);
            str->word = new;
            str->nowlen--;
            car->x--;
            return;
        }
    }else if((key == VK_RIGHT||key == VK_LEFT)&&event == KEY_DOWN){
            if(key == VK_RIGHT&&car->x<str->nowlen-1)car->x++;
            if(key == VK_LEFT&&(p == 1&&car->x>0||p == -1&&car->x>1))car->x--;
    }else if(key == VK_SHIFT&&event == KEY_DOWN){
        k*=-1;
    }else if(key == VK_INSERT&&event == KEY_DOWN){
        p*=-1;
        // if(p == -1)hideCaret();
        // else showCaret();
    }else if(key == 13&&event == KEY_DOWN){
        printf("%s",str->word);
        exit(0);
    }else if(event == KEY_DOWN){
        if(str->nowlen == str->len)str->len+=20;
        char*new = (char*)malloc(sizeof(char)*str->len);
        if(p == -1){
            if(key>=48&&key<=57){
                switch(key){
                case 48 : (str->word)[car->x-1] = k == 1?'0':')';break;
                case 49 : (str->word)[car->x-1] = k == 1?'1':'!';break;
                case 50 : (str->word)[car->x-1] = k == 1?'2':'@';break;
                case 51 : (str->word)[car->x-1] = k == 1?'3':'#';break;
                case 52 : (str->word)[car->x-1] = k == 1?'4':'$';break;
                case 53 : (str->word)[car->x-1] = k == 1?'5':'%';break;
                case 54 : (str->word)[car->x-1] = k == 1?'6':'^';break;
                case 55 : (str->word)[car->x-1] = k == 1?'7':'&';break;
                case 56 : (str->word)[car->x-1] = k == 1?'8':'*';break;
                case 57 : (str->word)[car->x-1] = k == 1?'9':'(';break;
            }
          }else{
              switch(key){
                case 188:(str->word)[car->x-1] = k == 1?',':'<';break;
                case 186:(str->word)[car->x-1] = k == 1?';':':';break;
                case 187:(str->word)[car->x-1] = k == 1?'=':'+';break;
                case 189:(str->word)[car->x-1] = k == 1?'-':'_';break;
                case 190:(str->word)[car->x-1] = k == 1?'.':'>';break;
                case 191:(str->word)[car->x-1] = k == 1?'/':'?';break;
                case 192:(str->word)[car->x-1] = k == 1?'`':'~';break;
                case 219:(str->word)[car->x-1] = k == 1?'[':'{';break;
                case 220:(str->word)[car->x-1] = k == 1?'\\':'|';break;
                case 221:(str->word)[car->x-1] = k == 1?']':'}';break;
                case 222:(str->word)[car->x-1] = k == 1?'\'':'"';break;
                default :if(k == -1)(str->word)[car->x-1] = toascii(key);
                         else (str->word)[car->x-1] = tolower(toascii(key));
                         break;
              }
          }
        }else{
            for(int i = car->x;i<str->nowlen;i++)new[i+1] = (str->word)[i];
            for(int i = 0;i<car->x;i++)new[i] = (str->word)[i];
            if(key>=65&&key<=90&&k == 1)if(k == 1)key = tolower(toascii(key));
            if((key>=48&&key<=57)&&k == -1)
            switch(key){
                case 48 : new[car->x++] = ')';goto out;
                case 49 : new[car->x++] = '!';goto out;
                case 50 : new[car->x++] = '@';goto out;
                case 51 : new[car->x++] = '#';goto out;
                case 52 : new[car->x++] = '$';goto out;
                case 53 : new[car->x++] = '%';goto out;
                case 54 : new[car->x++] = '^';goto out;
                case 55 : new[car->x++] = '&';goto out;
                case 56 : new[car->x++] = '*';goto out;
                case 57 : new[car->x++] = '(';goto out;
            }
            switch(key){
                case 188 :new[car->x++] = k == 1?',':'<';break;
                case 186 :new[car->x++] = k == 1?';':':';break;
                case 187 :new[car->x++] = k == 1?'=':'+';break;
                case 189 :new[car->x++] = k == 1?'-':'_';break;
                case 190 :new[car->x++] = k == 1?'.':'>';break;
                case 191 :new[car->x++] = k == 1?'/':'?';break;
                case 192 :new[car->x++] = k == 1?'`':'~';break;
                case 219 :new[car->x++] = k == 1?'[':'{';break;
                case 220 :new[car->x++] = k == 1?'\\':'|';break;
                case 221 :new[car->x++] = k == 1?']':'}';break;
                case 222 :new[car->x++] = k == 1?'\'':'"';break;
                default :new[car->x++] = toascii(key);break;
            }
            out:
            free(str->word);
            str->word = new;
            str->nowlen++;
        }
    }
}
int Setup(){
    initWindow("editor",100,100,600,200);
    initConsole();
    initialize();
    registerKeyboardEvent(keyboardEvent);
    //registerKeyboardEvent(paint);
    //startTimer(0,15);
}