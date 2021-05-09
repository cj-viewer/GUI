#include"acllib.h"
#include<stdio.h>
#include<stdlib.h>
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
    SetCaretBlinkTime(200);
}
void paint(){
    int x = 0,y = 0;
    beginPaint();
    clearDevice();
    setTextSize(str->Wordsize);
    setCaretSize(1,str->Wordsize);
    setCaretPos(car->x*(str->Wordsize/2),car->y);
    paintText(0,0,str->word);
    showCaret();
    endPaint();
}
void keyboardEvent(int key,int event){
    if(key == 46&&event == KEY_DOWN&&car->x>=1){
        char*new = (char*)malloc(sizeof(char)*str->len);
        for(int i = car->x+1;i<str->nowlen;i++)new[i-1] = (str->word)[i];
        for(int i = 0;i<car->x;i++)new[i] = (str->word)[i];
        free(str->word);
        str->word = new;
        str->nowlen--;
        car->x--;
        goto out;
    }
    if(event == KEY_DOWN&&key!=VK_SHIFT&&key!=VK_DELETE){
        if(str->nowlen == str->len)str->len+=20;
        char*new = (char*)malloc(sizeof(char)*str->len);
        for(int i = car->x;i<str->nowlen;i++)new[i+1] = (str->word)[i];
        for(int i = 0;i<car->x;i++)new[i] = (str->word)[i];
        if(key>=65&&key<=90)new[car->x++] = key+32;
        else if(key == VK_SPACE)new[car->x++] = ' ';
        free(str->word);
        str->word = new;
        str->nowlen++;
    }
    out:
    paint();
}
int Setup(){
    initWindow("editor",100,100,600,200);
    initialize();
    registerKeyboardEvent(keyboardEvent);
}