/*************************************************************
CONSOLA.H
LIBRERÍA PARA AUMENTAR LA EXTENSIÓN 
DE CONIO.H Y OTRAS EN VISUAL C++
(Da soporte a funciones como gotoxy, clrscr, etc.)

Antonio A.
Ayuda en C, C++ y Visual C++
http://ayudacpp.tripod.com.mx/
ayudacpp@tutopia.com
México, D.F.

Última actualización: 2-Enero-2003

ESTA LIBRERIA SE PUEDE DISTRIBUIR LIBREMENTE SIEMPRE Y CUANDO
SE ENTREGUE SIN MODIFICACIONES CON TODOS LOS ARCHIVOS ADJUNTOS
SOBRETODO SIN MODIFICAR LA FUENTE DONDE SE OBTUVO.
**************************************************************/

LIBRARY TO INCREASE THE EXTENSION 
OF CONIO.H AND OTHERS IN VISUAL C++ 
(It gives support to functions like gotoxy, clrscr, 
delay, textcolor, etc.)  
 



The library conio.h and others de Visual C++ for *Console programs (unlike its predecessors or those of Borland for example) already do not include some functions that are still enough useful (coverall at scholastic level) like: gotoxy, clrscr, textcolor, textbackground, delay, etc. At least they do not exist thus directly and with those names. An option is to manually do them using the Windows API for Console functions, or to thus use them directly. To consult the information on the library Wincon.h of Visual C++ for more details. 

The library Consola.h that appears here covers this apparent deficiency of Conio.h and others providing some functions that it had before (in Win16) to add certain compatibility with other applications. That is to say, if you have programs that use these functions, now already them will be able to compile in Visual C++ using this library!. 

So far the functions that contain are the following ones: 


*CONSOLE: applications that execute in a window style DOS. Any application C/C++ that uses like entry point the function main(), is said are of type console (consola in spanish).  




ORIGINAL OF CONIO.H  
clrscr  
void clrscr(void); 
Clean the screen in text mode and places the cursor in the upper left corner (in position 1,1). 
 
clreol  
void clreol(void); 
Clean from the current cursor position to the end of line, without moving the cursor. 
 
delline  
void delline(void); 
It eliminates all current line of the cursor position, moving everything what is under him a line upwards. The cursor does not move. 
 
insline  
void insline(void); 
It inserts new line in the current cursor position, moving everything a line downwards. The cursor does not move. The last line is lost. 
 
gotoxy  
void gotoxy(int x,int y); 
It moves the cursor position given by x,y (coordinated horizontally an vertical respectively). 
By default the screen is of 80 columns by 25 lines, where the upper left corner is the position: (x=1, y=1), and the lower right corner, the coordinate: (80,25).  

wherex 
wherey  
int wherex(void); 
int wherey(void); 
They respectively return x-coordinated and the and y-coordinated of current cursor position. 
If the text screen has the size by default of 80 columns by 25 lines, wherex() returns a number between 1 and 80, and wherey() between 1 and 25.  


textcolor  
void textcolor(int nuevocolor); 
It changes the color of the text. 
All the characters that are after a call this function will appear with this color in screen. The text that was before shown to call to this function will conserve its original color. 
The colors available as much for "textcolor" and "textbackground" are such that for its predecessors (from 0 to 15): 0 BLACK (negro)
1 BLUE (azul marino)
2 GREEN (verde perico)
3 CYAN (verde claro)
4 RED (rojo)
5 MAGENTA (morado o violeta)
6 BROWN (café)
7 LIGHTGRAY (gris claro)  8 DARKGRAY (gris obscuro) 
9 LIGHTBLUE (azul marino claro)
10 LIGHTGREEN (verde claro)
11 LIGHTCYAN (azul claro)
12 LIGHTRED (rojo claro)
13 LIGHTMAGENTA (rosa mexicano)
14 YELLOW (amarillo)
15 WHITE (blanco)  
*the difference is that here the background color takes the 16 colors and not only the 8 first as happened with its predecessors.  

textbackground  
void textbackground(int nuevocolor); 
It changes the color of background of the text. 
This function changes only the color of background of the characters. In order to change the background to all the screen it is necessary to call this function followed of "clrscr()" to erase the screen and appears with the new color. For this intention not to use system("CLS") to erase the screen beacuse does not take into account the new value from background color.  

_setcursortype  
void _setcursortype(int type); 
It changes the appearance of the text cursor (not of mouse). 
It places the type of cursor to one of the following ones: 
_NORMALCURSOR (like underline character of) 
_NOCURSOR (it hides the cursor) 
_SOLIDCURSOR (solid cursor) 
 

ORIGINAL OF DOS.H  
delay  
void delay(int miliseg); 
Suspends execution for interval. 
With a call to delay, the current program is suspended from execution for the time specificied by the argument in milliseconds.  

sleep  
void sleep(int seg); 
Suspends execution for interval. 
With a call to sleep, the current program is suspended from execution for the time specificied by the argument in seconds.  


OTHERS USEFUL  
gettextcolor 
gettextbackground 
int gettextcolor(void); 
int gettextbackground(void); 
They return the color of the text and background respectively used (from 0 to 15).  

getcols 
getrows  
int getcols(); 
int getrows(); 
They respectively return wide and the high of the window in characters.  
setsizedefault  void setsizedefault(void); 
It recovers the window size to its value predetermined of 80x25 characters 
(80 columns by 25 rows).  

setsize8043 
setsize8050 
setsizexy  
void setsize8043(void);
void setsize8050(void);
void setsizexy(int x, int y); 
They change the window size in characters, to 80x43, 80x50 o user defined respectively. 
*If the size used is different from 80x25, 80x43 or 80x50, the window will not possibly be able to be changed to complete screen.  

settitle 
gettitle  
int settitle(const char *cadena);
int gettitle(char *cadena, int tam); 
Functions to handle the messages of the bar of title of the window. 
The function settitle places the title to the window taking like argument a chain of characters. Zero return if fails the function 
The function gettitle obtains the title of the windows and stores it in a chain that is passed like first argument. It is necessary to also send the number to him of characters that can store this chain. the returned value is the size of the chain copied to the first argument. 
*Another option is to use them directly as they then come do not require greater definition: 
BOOL SetConsoleTitle(LPCTSTR lpConsoleTitle); 
DWORD GetConsoleTitle(LPTSTR lpConsoleTitle,DWORD nSize);  




HOW TO CREATE OUR OWN FUNCTIONS  


The library CONSOLE.LIB that appears here already is made these functions to facilitate their use, employing the Windows API for Console functions. Although it is recommendable study the functions of this API so that you have an idea of how they became, coverall if you want create yours own ones or to add more functions. 

Next two examples of how the functions gotoxy y clrscr were defined, so that a clearer idea is had one more of how they became: 



//DEFINITION OF "gotoxy(x,y)"

#include <wincon.h>
//...

void gotoxy(int x,int y)
{
 COORD pos;
 pos.X=x-1;
 pos.Y=y-1;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

 


Here the SetConsoleCursorPosition function (from the Windows API -Win32- for Console) is the one in charge to position the cursor in the text screen. It requiere that two arguments go to him: first it a "HANDLE" that is not another thing that a unique value used by Windows to identify an object, that int this case is for identifying the standard output of the application. This is obtained calling to the GetStdHandle(STD_OUTPUT_HANDLE) function. 

The second argument is a structure that keeps the position x,y that is required. It is diminished in one both coordinates because one is going away to take like reference a (1,1) the top left corner from the window for compatibility with the predecesoras functions from conio.h, since the functions of the API take it like reference a (0,0). And ready already it is the function. 

Another example, but now for the function "clrscr" would be something a little more laborious, as it is seen next: 



//DEFINITION OF "clrscr()"

#include <wincon.h>
//...

void clrscr(void)
{
 HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
 COORD coordScreen={0,0};//position that will occupy cursor
 DWORD cCharsWritten;
 CONSOLE_SCREEN_BUFFER_INFO csbi;//to obtain information from buffer
 DWORD dwConSize;//number of character cells from buffer

 //to obtain the total number of character cells from the current buffer
 GetConsoleScreenBufferInfo(hConsole, &csbi);
 dwConSize = csbi.dwSize.X * csbi.dwSize.Y;//rows by columns

 //To fill the whole screen with the character ' '
 FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,
	coordScreen,&cCharsWritten);
  
 //To obtain the present attribute of text
 GetConsoleScreenBufferInfo(hConsole, &csbi);
  
 //Now, to place te attribute of buffer corresponding
 FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,
	coordScreen,&cCharsWritten);
  
 //To put the cursor in the position (0,0) - top left corner-
 SetConsoleCursorPosition(hConsole,coordScreen);

 return;
}

 

The other functions are defined of way similar to since it were made here for gotoxy and clrscr (in minor or greater degree of difficulty). To consult the information on the library Wincon.h de Visual C++ for more details. 





HOW TO ADD THE LIBRARY TO YOURS PROJECT  

In order to use library CONSOLA.LIB in Visual C++ it is necessary to copy to yours working directory these two archives that are provided: 

Consola.h (head file) 
Consola.lib (precompiled static library) 
That is to say, to copy them to the directory where it is the code of yours program, that by comfort is generally where they are the project archives (.DSW and .DSP). 
         Now it is necessary "to load" these archives to his project, for it a simple form is to go to the menu of Visual C++: 

Project / Add To Project / Files... 

and there to look for these archives in the dialogue box that appears, and to add them. 
NOTE: Once fact this, in the Window of the Project (Workspace Window , FileView eyelash) must appear these archives (coverall the Consola.lib file). If LIB file not appears, Visual C++ (rather the linker) will not know how to connect this library to his program and it will send the error: 

"unresolve external...".
So there is to make sure that library appears listing there. 
         In order to finish including the head to the code where they are going away to use the functions, of this form: 

#include "Consola.h" 

... and ready. The functions of the library in their program can already be used. In the compressed file (ZIP) two examples come in where the functions for more clarity are used. One is using the library "stdio.h" to use it with printf or cprintf (style C). The other is with "iomanip.h" to use it with cout<<... 




IMPORTANT NOTES: 

It is necessary to indicate that the library was done for Visual C++, for other compilers could not be compatible, is question to prove it. 

Remember that it is not enough that only they copy the archives to its folder and put the head (the #include "Consola.h") in the code. They need to say to the compiler (the "linker") who connects this library else it will not know that it exists. The head only fulfills informing that functions are available, the prototypes (among other things), but it does not say anything to him where they are. For it as it indicates lines above, an option is simply to include file LIB to the project making sure that it appears listing in the Workspace Window of his application. Of course there is more options so that it finds and the connection, but this one is simplest. 
For way "DEBUG" configuration to use "ConsolaD.lib" instead of "Consola.lib" (RELEASE) to avoid "warnings" on conflicts between libraries. 


If even so it continues appearing this "warning" of conflicts between libraries, more surely it is than they are using another type of libraries in run time (run-Time library) that is "Multithreaded" and not of "Single-Threaded". This is common if it is being used classes MFC in his program. 
In order to know the type of library, to go to the menu of Visual C++: 
Project / Setttings... 
which will open the dialogue box "Project Settings". Of the list of the left to select the name of its project. Of the options of the right to go to eyelash "C/C++", and to select there from the drop-down list, the option Code Generation. Finally in the part that says "Use run-time library" can observe that type of librerias is using: Single-Threaded or Multithreaded. 

If it is Single-Threaded then the libraries that there are to use are: 


Consola.lib and ConsolaD.lib
If it is Multithreaded it is necessary to use: 

ConsolaM.lib y ConsolaMD.lib
Depending if the present configuration is for RELEASE way or DEBUG way. Where the letter "D" indicates: DEBUG. On the other hand the letter "M" indicates: Multithreaded. 

In summary it is had: 


Election of library  
Configuration  Run Time Library  
Single-Threaded  Multithreaded  
Release  Consola.lib  ConsolaM.lib  
Debug  ConsolaD.lib  ConsolaMD.lib  






