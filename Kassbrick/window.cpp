#include "window.h"


void init_colors(void)
{
  start_color();
  init_pair(WBLACK,   COLOR_WHITE, COLOR_BLACK);
  init_pair(WCYAN,    COLOR_WHITE, COLOR_CYAN);
  init_pair(WBLUE,    COLOR_WHITE, COLOR_BLUE);
  init_pair(WYELLOW,  COLOR_WHITE, COLOR_YELLOW);  
  init_pair(WGREEN,   COLOR_WHITE, COLOR_GREEN); 
  init_pair(WMAGENTA, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(WRED,     COLOR_WHITE, COLOR_RED);  
  init_pair(BWHITE,   COLOR_BLACK, COLOR_WHITE);
  init_pair(BCYAN,    COLOR_BLACK, COLOR_CYAN);
  init_pair(BBLUE,    COLOR_BLACK, COLOR_BLUE);
  init_pair(BYELLOW,  COLOR_BLACK, COLOR_YELLOW);  
  init_pair(BGREEN,   COLOR_BLACK, COLOR_GREEN); 
  init_pair(BMAGENTA, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(BRED,     COLOR_BLACK, COLOR_RED);  
}



Color inttoCol(int n) 
{
  Color C;
  switch (n)
  {
      case 1:
    C=WBLACK;
    return C;
    break;
      case 2:
    C=WCYAN;
    return C;
    break;
      case 3:
    C=WBLUE;
    return C;
    break;
      case 4:
    C=WYELLOW;
    return C;
    break;
      case 5:
    C=WGREEN;
    return C;
    break;
      case 6:
    C=WMAGENTA;
    return C;
    break;
      case 7:
    C=WRED;
    return C;
    break;
      case 8:
    C=BWHITE;
    return C;
    break;
      case 9:
    C=BCYAN;
    return C;
    break;
      case 10:
    C=BBLUE;
    return C;
    break;
      case 11:
    C=BYELLOW;
    return C;
    break;
      case 12:
    C=BGREEN;
    return C;
    break;
      case 13:
    C=BMAGENTA;
    return C;
    break;
      case 14:
    C=BRED;
    return C;
    break;
  }
}



void startProgramX() {
  initscr();             // initialize curses
  cbreak();              // pass key presses to program, but not signals
  noecho();              // don't echo key presses to screen
  keypad(stdscr, TRUE);  // allow arrow keys
  timeout(5);            // no blocking on getch()
  curs_set(0);           // set the cursor to invisible
  init_colors();
}

void stopProgramX() {
  refresh();
  getch();    
  endwin();
}



void Window::update() const{
  wrefresh(win);
  wrefresh(frame);
  refresh();
}


Window::Window(int h,int w, int x, int y, char c)
  : height(h), width(w), startx(x), starty(y), bord(c)
{
  colorwin=WBLACK;
  colorframe=WBLACK;
  frame=newwin(h+2,w+2,y,x);
  win=subwin(frame,h,w,y+1,x+1);
  wbkgd(frame,COLOR_PAIR(colorwin));
  wbkgd(win,COLOR_PAIR(colorframe));
  wborder(frame, c,c,c,c,c,c,c,c);
  wattron(win,COLOR_PAIR(colorwin));
  wattron(frame,COLOR_PAIR(colorframe));
  update();
}

Window::Window(Window& w1) : height(w1.getHauteur()), width(w1.getLargeur()), startx(w1.getX()), starty(w1.getY()), bord(w1.getBord())
{
  int h = w1.getHauteur();
  int w = w1.getLargeur();
  int x = w1.getX();
  int y = w1.getY();
  int c = w1.getBord();
  colorwin=WBLACK;
  colorframe=WBLACK;
  frame=newwin(h+2,w+2,y,x);
  win=subwin(frame,h,w,y+1,x+1);
  wbkgd(frame,COLOR_PAIR(colorwin));
  wbkgd(win,COLOR_PAIR(colorframe));
  wborder(frame, c,c,c,c,c,c,c,c);
  wattron(win,COLOR_PAIR(colorwin));
  wattron(frame,COLOR_PAIR(colorframe));
  update();

}

Window::~Window(){
  wborder(frame, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  wattroff(win,COLOR_PAIR(colorwin));
  wattroff(win,COLOR_PAIR(colorframe));
  werase(win);
  update();
  delwin(win); 
}

void Window::print(int x, int y, std::string s, Color c) const {
  wattron(win,COLOR_PAIR(c));
  mvwprintw(win,y,x,s.c_str());
  wattroff(win,COLOR_PAIR(c));
  update();  
}
void Window::print(int x, int y, char s, Color c) const{
  wattron(win,COLOR_PAIR(c));
  mvwaddch(win,y,x,s);
  wattroff(win,COLOR_PAIR(c));
  update();
}
void Window::print(int x, int y, std::string s) const{
  mvwprintw(win,y,x,s.c_str());
  update();  
}
void Window::print(int x, int y, char s) const{
  mvwaddch(win,y,x,s);
  update();  
}


// void Window::print(int x, int y, std::string s, Couleur c) const {
//   wattron(win,COLOR_PAIR(c));
//   mvwprintw(win,y,x,s.c_str());
//   wattroff(win,COLOR_PAIR(c));
//   update();  
// }

int Window::getX() const { return startx;} 
int Window::getY() const { return starty;} 
int Window::getHauteur() const { return height;} 
int Window::getLargeur() const { return width;}  
char Window::getBord() const { return bord; }
Color Window::getCouleurBordure() const{ return colorframe;}
Color Window::getCouleurFenetre() const{ return colorwin;}
void Window::setCouleurBordure(Color c){
  colorframe=c;
  wattron(frame,COLOR_PAIR(colorframe));
  wborder(frame, bord,bord,bord,bord,bord,bord,bord,bord);
  update();
}
void Window::setCouleurFenetre(Color c){
  colorwin=c;
  wattron(win,COLOR_PAIR(colorwin));
  wbkgd(win,COLOR_PAIR(colorwin));
  update();  
}

void Window::clear() const{  werase(win); update(); }