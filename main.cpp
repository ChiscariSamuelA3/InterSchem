#include <iostream>
#include <math.h>
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <fstream>
#define infinit INT_MAX
#define epsi 0.0001
#define  MAX 100
#define MAX1 20
#define MAX2 100
#define max_stiva 100
#define pi 3.1415926;

using namespace std;

ifstream fin("memorie.txt");
ifstream f1("maximAB.txt");
ifstream f2("sumaX.txt");

int screenWidth=GetSystemMetrics(SM_CXSCREEN);
int screenHeight=GetSystemMetrics(SM_CYSCREEN);

struct expresie
{
    char text[MAX2];
};

struct punctLegatura
{
    int x, y;
};

struct piesa
{
    char tip;
    expresie e;
    int x, y;
    int latime, inaltime;
    piesa *urm, *urmA, *urmF;
    punctLegatura pLeg[4];
    bool repetitie;
    bool sfarsit;
    piesa *salt;
};

struct legatura
{
    int bloc1, bloc2;
    int punct1, punct2;
};

struct blocDecizie
{
    int intrari;
    int precedent[4];
};

struct evaluator
{
    int top1, top2;
    double operanzi[max_stiva];
    char operatori[max_stiva];
    char OperatiiBinare[200]="+-*/^<>=#";
    char OperatiiUnare[200]="scarel";
    char Operatii[200]="+-*/^<>=#scarel";
};

struct functie
{
    char variabila[50];
    char expCalcul[300];
    char expDecizie[300];
    char expOutput[300];
    char expresie[300];
    char vect[MAX+1][MAX1];
    int lung;
};
struct diagrama
{
    int nrBlocuri;
    bool zonaDeMiscareBloc = true;
    bool selectareBlocDiferit;
    int FUNDAL = 0;
    evaluator eval;
    functie F[50];
    blocDecizie blc[100];
    bool stergeBloc = true;
    int butonSelectat;
    bool butonLegaturi = true;
    int pozBlStart = -1;
    bool pasCurent = true;
    int contorLegaturi;
    int nrLegaturi;
    piesa bloc[50];
    piesa blStopImaginar;
    int XLegFinala1, YLegFinala1;
    int XLegFinala2, YLegFinala2;
    bool mutareBlocuri;
    bool punereBlocuri;
    int butonMeniu;
    legatura leg[100];
    bool citesteText = true;
    int nrBlocuriStart;
    bool nrBlocuriStop;
    bool existaBloc = false;
    int nrExpresii;
    int nrBlocuriInput;
    char citire[50][2];
    int nrBlocuriOutput;
    char afisare[50][10];
    int xCod = 10, yCod = 45;
    piesa *precedentBlocComun, *precedentBlComunUrm;
    bool ramuraElse = false;
    bool butonBack = false;
    bool butonSave = false;
    bool existaButonSave = true;
    int butonIncarcare;
    int initVar[30];

} d;
void resetare()
{
    d.zonaDeMiscareBloc = true;
    d.selectareBlocDiferit= false;
    d.stergeBloc=true;
    d.butonLegaturi = true;
    d.pasCurent = true;
    d.mutareBlocuri = false;
    d.punereBlocuri = false;
    d.XLegFinala1=0;
    d.XLegFinala2=0;
    d.YLegFinala1=0;
    d.YLegFinala2=0;
    d.FUNDAL=0;
    d.initVar[30] = {0};
    d.pozBlStart = -1;
    d.citesteText = true;
    d.nrBlocuriStart = 0;
    d.nrBlocuriStop = false;
    d.existaButonSave = true;
    d.existaBloc = false;
    d.nrExpresii = 0;
    d.contorLegaturi=0;
    d.butonSelectat=0;
    d.butonMeniu = 0;
    d.nrBlocuriOutput = 0;
    d.nrBlocuriInput = 0;
    d.xCod = 10;
    d.yCod = 45;
    d.ramuraElse = false;
    d.butonBack = false;
    d.eval.top1 = d.eval.top2 = 0;
    d.eval.operanzi[max_stiva] = {0};
    strcpy(d.eval.operatori, "");
    for(int i = 0; i < 50; i++)
    {
        d.F[i].lung = 0;
        strcpy(d.F[i].variabila, "");
        strcpy(d.F[i].expCalcul, "");
        strcpy(d.F[i].expDecizie,"");
        strcpy(d.F[i].expOutput, "");
        strcpy(d.F[i].expresie, "");
        for(int j = 0; j < MAX; j++)
            strcpy(d.F[i].vect[j],"");
    }
    for(int i = 0; i <= d.nrBlocuri; i++)
    {
        d.blc[i].intrari = 0;
        d.blc[i].precedent[4] = {0};
        d.bloc[i].pLeg[4].x = {0};
        d.bloc[i].pLeg[4].y = {0};
        d.bloc[i].repetitie = false;
        d.bloc[i].sfarsit = false;
    }
    for(int i = 0; i <= d.nrLegaturi; i++)
    {
        d.leg[i].bloc1 = d.leg[i].bloc2 = 0;
        d.leg[i].punct1 = d.leg[i].punct2 = 0;
    }
    d.nrBlocuri = 0;
    d.nrLegaturi = 0;
    d.nrBlocuriInput = d.nrBlocuriOutput = 0;
    d.butonSave = false;
    d.butonIncarcare = 0;
}
void textFormat()
{
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    settextjustify(1,1);
}
void drawLine(int x1, int y1, int x2, int y2, int cul, int p)
{

    setactivepage(p);
    setvisualpage(1-p);
    setcolor(cul);

    if(y2>y1)
    {
        line(x1,y1,x1,(y1+y2)/2);
        line(x1,(y1+y2)/2,x2,(y1+y2)/2);
        line(x2,(y1+y2)/2,x2,y2);


        line(x2,y2,x2-7,y2-7);
        line(x2,y2,x2+7,y2-7);
    }
    else
    {
        line(x1,y1,x1,y1+25);
        line(x1,y1+25,x2,y1+25);
        line(x2,y1+25,x2,y2);

        line(x2,y2,x2-7,y2+7);
        line(x2,y2,x2+7,y2+7);
    }

    setcolor(cul);
    setvisualpage(p);

}
void refacere(piesa B,int culoare);

void restaureaza(piesa B[], int p)
{
    int i,idNod1,idNod2,p1,p2,x1,y1,x2,y2;

    for (i=1; i <= d.nrBlocuri; i++)
        refacere(B[i], 14);

    for (i=1; i <= d.nrLegaturi; i++)
    {
        idNod1 = d.leg[i].bloc1;
        p1 = d.leg[i].punct1;

        x1 = B[idNod1].pLeg[p1].x;
        y1 = B[idNod1].pLeg[p1].y;

        idNod2=d.leg[i].bloc2;
        p2=d.leg[i].punct2;

        x2=B[idNod2].pLeg[p2].x;
        y2=B[idNod2].pLeg[p2].y;

        drawLine(x1,y1,x2,y2,15-d.FUNDAL, p);
    }
}
void desenareZonaValida(int culoare)
{
    setcolor(culoare);
    setlinestyle(3, 0, 3);
    rectangle(230, 20, screenWidth-50, screenHeight-100);
    setlinestyle(0, 0, 1);
    setcolor(0);
}
void deseneazaLegatura(piesa B[], int &idNod1, int &p1, int &idNod2, int &p2)
{
    bool click=false;
    int i, xMouse,yMouse;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(700,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<= d.nrBlocuri; i++)
                if (abs(B[i].pLeg[0].x - xMouse)<= 5 && abs(B[i].pLeg[0].y- yMouse)<=5)//cerc jos
                {

                    idNod1 = i;
                    p1=0;
                    click=true;
                }
                else if (abs(B[i].pLeg[1].x - xMouse)<=5 && abs(B[i].pLeg[1].y - yMouse)<=5)//cerc sus
                {
                    idNod1=i;
                    p1=1;
                    click=true;
                }
                else if (abs(B[i].pLeg[2].x - xMouse)<=5 && abs(B[i].pLeg[2].y - yMouse)<=5)//stanga pt decizie
                {
                    idNod1=i;
                    p1=2;

                    click=true;
                }
                else if (abs(B[i].pLeg[3].x - xMouse)<=5 && abs(B[i].pLeg[3].y - yMouse)<=5)//dreapta pt decizie
                {
                    idNod1=i;
                    p1=3;
                    click=true;
                }

        }
        restaureaza(B, 0);
        restaureaza(B, 1);

    }
    while (!click);

    click=false;
    int x1,y1,x2,y2,xMouseVechi,yMouseVechi;

    x1=B[idNod1].pLeg[p1].x;
    y1=B[idNod1].pLeg[p1].y;

    xMouse = mousex();
    yMouse = mousey();

    do
    {
        xMouseVechi = xMouse;
        yMouseVechi = yMouse;

        xMouse = mousex();
        yMouse = mousey();

        if (xMouseVechi != xMouse || yMouseVechi != yMouse)
        {
            drawLine(x1, y1, xMouseVechi, yMouseVechi, 15-d.FUNDAL, 0);
            drawLine(x1, y1, xMouse, yMouse, 15-d.FUNDAL, 1);
            delay(200);
            drawLine(x1,y1,xMouseVechi,yMouseVechi,d.FUNDAL,0);
            drawLine(x1,y1,xMouse,yMouse, d.FUNDAL,1);
            restaureaza(B, 0);
            restaureaza(B, 1);
        }
        else
        {
            drawLine(x1,y1,xMouse,yMouse, 15-d.FUNDAL,0);
            drawLine(x1,y1,xMouse,yMouse, 15-d.FUNDAL,1);
            delay(200);
            drawLine(x1,y1,xMouse,yMouse,d.FUNDAL,0);
            drawLine(x1,y1,xMouse,yMouse, d.FUNDAL,1);
            restaureaza(B, 0);
            restaureaza(B, 1);
        }

        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            Beep(500,100);
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();

            for (i=1; i<= d.nrBlocuri; i++)
                if (abs(B[i].pLeg[0].x  - xMouse)<= 5 && abs(B[i].pLeg[0].y - yMouse)<=5)
                {
                    if(B[i].tip == 'd')
                    {
                        B[i].repetitie = true;
                    }
                    idNod2=i;
                    p2=0;
                    click=true;
                }
                else if(abs(B[i].pLeg[1].x - xMouse)<=5 && abs(B[i].pLeg[1].y - yMouse)<=5)
                {
                    idNod2=i;
                    p2=1;
                    click=true;
                    d.blc[idNod2].intrari++;
                    int indice = d.blc[idNod2].intrari;
                    d.blc[idNod2].precedent[indice] = idNod1;
                }
                else if (abs(B[i].pLeg[2].x - xMouse)<=5 && abs(B[i].pLeg[2].y - yMouse)<=5)
                {
                    idNod2=i;
                    p2=2;
                    click=true;
                }
                else if (abs(B[i].pLeg[3].x - xMouse)<=5 && abs(B[i].pLeg[3].y - yMouse)<=5)
                {
                    idNod2=i;
                    p2=3;
                    click=true;
                }
        }
    }
    while (!click);

    if(d.contorLegaturi + 1 == d.nrLegaturi)
    {
        d.XLegFinala1 = x1;
        d.YLegFinala1 = y1;
        d.XLegFinala2 = xMouse;
        d.YLegFinala2 = yMouse;
        drawLine(x1,y1,xMouse,yMouse, 15-d.FUNDAL,0);
        drawLine(x1,y1,xMouse,yMouse, 15-d.FUNDAL,1);
    }
    restaureaza(B, 0);
    restaureaza(B, 1);

}
void citireText(int x, int y, char s[])
{
    setcolor(14);
    char tasta;
    tasta = 0;
    do
    {
        tasta = getch();
        if(tasta == 8 && strlen(s) >= 1)
        {
            setcolor(0);
            outtextxy(x, y, s);
            s[strlen(s) - 1] = 0;
            setcolor(14);
            outtextxy(x, y, s);
        }
        if(tasta >= 32)
        {
            char t[2];
            t[0] = tasta;
            t[1] = NULL;
            strcat(s, t);
            outtextxy(x, y, s);
        }
    }
    while(tasta != 13);
}

void terminal(piesa &B, char mesaj[], int culoare, int dly)
{
    if(!strcmp("START", mesaj))
        B.tip = 's';
    else B.tip = 't';

    delay(dly);

    char text[50];
    sprintf(text, "%s", mesaj);

    strcpy(B.e.text, text);

    B.inaltime = 30;
    B.latime = 40;


    setcolor(culoare);
    setfillstyle(SOLID_FILL, 4);
    textFormat();
    if(culoare != 0)
        setbkcolor(4);
    else setbkcolor(0);

    ellipse(B.x, B.y, 0, 360, B.latime, B.inaltime);
    outtextxy(B.x, B.y, text);

    if(B.tip == 's')
    {
        circle(B.x, B.y + B.inaltime, 5);
        B.pLeg[0].x = B.x;
        B.pLeg[0].y = B.y + B.inaltime;
    }
    else
    {
        circle(B.x, B.y - B.inaltime, 5);
        B.pLeg[1].x = B.x;
        B.pLeg[1].y = B.y - B.inaltime;
    }

    setbkcolor(0);
}

void calculBloc(piesa &B, int culoare, int dly, char text[])
{

    B.tip = 'c';

    textFormat();
    setcolor(culoare);

    delay(dly);

    if(d.citesteText == true)
    {

        strcpy(text, "_");
        outtextxy(B.x, B.y, text);

        setcolor(culoare);
        strcpy(text, "");

        citireText(B.x, B.y, text);
        B.inaltime = 45;
        B.latime = 25 + textwidth(text);
        d.citesteText = false;
    }
    else
    {
        B.inaltime = 45;
        B.latime = 25 + textwidth(text);
        outtextxy(B.x, B.y, text);
    }
    d.initVar[B.e.text[0] - 'A']++;

    strcpy(B.e.text, text);

    rectangle(B.x-B.latime/2,B.y-B.inaltime/2,B.x+B.latime/2,B.y+B.inaltime/2);
    circle(B.x,B.y-B.inaltime/2,5);//intrare
    B.pLeg[1].x = B.x;
    B.pLeg[1].y = B.y-B.inaltime/2;

    circle(B.x,B.y+B.inaltime/2,5);//iesire
    B.pLeg[0].x= B.x;
    B.pLeg[0].y = B.y+B.inaltime/2;

}
void decizie(piesa &B, int culoare, int dly, char text[])
{

    B.tip = 'd';

    textFormat();

    setcolor(culoare);

    delay(dly);

    if(d.citesteText == true)
    {

        strcpy(text, "_");
        outtextxy(B.x, B.y + 25, text);

        setcolor(culoare);
        strcpy(text, "");

        citireText(B.x, B.y + 25, text);
        B.inaltime = 40;
        B.latime =  20 + 2*textwidth(text);
        d.citesteText = false;
    }
    else
    {
        B.inaltime = 40;
        B.latime =  20 + 2*textwidth(text);
        outtextxy(B.x, B.y + 25, text);
    }

    strcpy(B.e.text, text);

    line(B.x-B.latime/2, B.y+B.inaltime/2, B.x, B.y-B.inaltime + 10);
    line(B.x+B.latime/2, B.y+B.inaltime/2, B.x,B.y-B.inaltime + 10);
    line(B.x-B.latime/2, B.y+B.inaltime/2, B.x, B.y + 2*B.inaltime - 10);
    line( B.x, B.y + 2*B.inaltime - 10, B.x+B.latime/2, B.y+B.inaltime/2);

    circle(B.x,  B.y + 2*B.inaltime - 10, 5);
    B.pLeg[0].x = B.x;
    B.pLeg[0].y = B.y + 2*B.inaltime - 10;

    circle(B.x,  B.y-B.inaltime + 10, 5);
    B.pLeg[1].x = B.x;
    B.pLeg[1].y = B.y-B.inaltime + 10;

    circle(B.x-B.latime/2, B.y+B.inaltime/2, 5);//cerc stanga
    outtextxy(B.x-B.latime/2, B.y+B.inaltime/2 - 10, "A");
    B.pLeg[2].x = B.x-B.latime/2;
    B.pLeg[2].y =  B.y+B.inaltime/2;

    circle(B.x+B.latime/2, B.y+B.inaltime/2, 5);//cerc dreapta
    outtextxy(B.x+B.latime/2, B.y+B.inaltime/2 - 10, "F");
    B.pLeg[3].x = B.x+B.latime/2;
    B.pLeg[3].y = B.y+B.inaltime/2;

}
void trapez(piesa &B, int culoare, int dly, char text[])
{
    B.tip = 'o';

    textFormat();

    setcolor(culoare);

    delay(dly);

    if(d.citesteText == true)
    {

        strcpy(text, "_");
        outtextxy(B.x, B.y, text);

        setcolor(culoare);
        strcpy(text, "");

        citireText(B.x, B.y, text);
        B.inaltime = 35;
        B.latime = 80 + 3 * textwidth(text);
        d.citesteText = false;
    }
    else
    {
        B.inaltime = 35;
        B.latime = 80 + 3 * textwidth(text);
        outtextxy(B.x, B.y, text);
    }

    strcpy(B.e.text, text);

    line(B.x-B.latime/2, B.y+B.inaltime/2, B.x+B.latime/2, B.y+B.inaltime/2);
    line(B.x+B.latime/2, B.y+B.inaltime/2, B.x+B.latime/4, B.y-B.inaltime + 10);
    line(B.x-B.latime/4, B.y-B.inaltime + 10,B.x+B.latime/4,B.y-B.inaltime + 10);
    line(B.x-B.latime/2, B.y+B.inaltime/2, B.x-B.latime/4, B.y-B.inaltime + 10);

    circle(B.x, B.y+B.inaltime/2, 5);
    B.pLeg[0].x = B.x;
    B.pLeg[0].y =  B.y+B.inaltime/2;

    circle(B.x, B.y-B.inaltime + 10, 5);
    B.pLeg[1].x = B.x;
    B.pLeg[1].y =  B.y - B.inaltime + 10;
}

void trapez_rasturnat(piesa &B, int culoare, int dly, char text[])
{
    B.tip = 'i';

    textFormat();

    setcolor(culoare);

    delay(dly);

    if(d.citesteText == true)
    {

        strcpy(text, "_");
        outtextxy(B.x, B.y, text);

        setcolor(culoare);
        strcpy(text, "");

        citireText(B.x, B.y, text);
        strcpy(d.citire[++d.nrBlocuriInput], text);
        B.inaltime = 35;
        B.latime = 80 + 3 * textwidth(text);
        d.citesteText = false;
    }
    else
    {
        B.inaltime = 35;
        B.latime = 80 + 3 * textwidth(text);
        outtextxy(B.x, B.y, text);
    }

    strcpy(B.e.text, text);



    line(B.x-B.latime/4, B.y+B.inaltime/2, B.x-B.latime/2, B.y-B.inaltime);
    line(B.x+B.latime/4, B.y+B.inaltime/2, B.x+B.latime/2,B.y-B.inaltime);
    line(B.x-B.latime/4, B.y+B.inaltime/2, B.x+B.latime/4, B.y+B.inaltime/2);
    line(B.x-B.latime/2, B.y-B.inaltime,B.x+B.latime/2,B.y-B.inaltime);

    circle(B.x, B.y+B.inaltime/2, 5);
    B.pLeg[0].x = B.x;
    B.pLeg[0].y = B.y+B.inaltime/2;
    circle(B.x, B.y-B.inaltime, 5);
    B.pLeg[1].x = B.x;
    B.pLeg[1].y = B.y-B.inaltime;
}

void miscareBlocCuMouse(piesa &B, char text[], bool &zonaValida)
{
    int mX = mousex();
    int mY = mousey();

    if(mX >= 20 && mX <= 170 && mY >= 20 && mY <= 710)
    {
        zonaValida = false;
        return;
    }


    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);

        if(B.tip == 'c')// dreptunghiul
        {

            int xA = B.x-B.latime/2, yA = B.y-B.inaltime/2;
            int xB = B.x+B.latime/2, yB = B.y+B.inaltime/2;

            if(mX >= xA && mX <= xB && mY >= yA && mY <= yB)
            {
                clearmouseclick(WM_LBUTTONUP);
                while(!ismouseclick(WM_LBUTTONUP))
                {

                    if(ismouseclick(WM_MOUSEMOVE))
                    {
                        clearmouseclick(WM_MOUSEMOVE);

                        if(mousex() >= 230 && mousex() <= screenWidth-50 && mousey() >= 20 && mousey() <= screenHeight-100)
                        {
                            calculBloc(B, 0, 0, text);
                            B.x = mousex();
                            B.y = mousey();
                            calculBloc(B, 14, 0, text);
                        }
                    }
                }
            }
            else d.selectareBlocDiferit = true;
        }
        else if(B.tip == 'd')// decizie - triunghi
        {
            int x1 = B.x-B.latime/2;
            int x2 = B.x+B.latime/2;
            int y1 = B.y-B.inaltime + 10;
            int y2 = B.y+B.inaltime/2;

            if(mX >= x1 && mX <= x2 && mY >= y1 && mY <= y2)
            {
                clearmouseclick(WM_LBUTTONUP);
                while(!ismouseclick(WM_LBUTTONUP))
                {
                    if(ismouseclick(WM_MOUSEMOVE))
                    {
                        clearmouseclick(WM_MOUSEMOVE);

                        if(mousex() >= 230 && mousex() <= screenWidth-50 && mousey() >= 20 && mousey() <= screenHeight-100)
                        {
                            decizie(B, 0, 0, text);
                            B.x = mousex();
                            B.y = mousey();
                            decizie(B, 14, 0, text);
                        }
                    }
                }
            }
            else d.selectareBlocDiferit = true;
        }
        else if(B.tip == 's' || B.tip == 't')
        {

            int x1 = B.x - B.latime / 2;
            int x2 = B.x + B.latime / 2;
            int y1 = B.y - B.inaltime / 2;
            int y2 = B.y + B.latime / 2;
            if(mX >= x1 && mX <= x2 && mY >= y1 && mY <= y2)
            {
                clearmouseclick(WM_LBUTTONUP);
                while(!ismouseclick(WM_LBUTTONUP))
                {
                    if(ismouseclick(WM_MOUSEMOVE))
                    {
                        clearmouseclick(WM_MOUSEMOVE);

                        if(mousex() >= 230 && mousex() <= screenWidth-50 && mousey() >= 20 && mousey() <= screenHeight-100)
                        {

                            terminal(B, text, 0, 0);
                            B.x = mousex();
                            B.y = mousey();
                            terminal(B, text, 14, 0);
                        }
                    }
                }
            }
            else d.selectareBlocDiferit = true;
        }
        else if(B.tip == 'o') //trapez
        {

            int x1= B.x-B.latime/2;
            int y1=B.y+B.inaltime/2;
            int  x2=B.x+B.latime/2;
            int x3=B.x-B.latime/4;
            int x4=B.x+B.latime/4;
            int y2=B.y-B.inaltime + 10;

            if(mX >= x1 && mY<=y1 && mX<=x2 && mX>=x3 && mX<=x4 && mY>=y2)
            {
                clearmouseclick(WM_LBUTTONUP);
                while(!ismouseclick(WM_LBUTTONUP))
                {
                    if(ismouseclick(WM_MOUSEMOVE))
                    {
                        clearmouseclick(WM_MOUSEMOVE);

                        if(mousex() >= 230 && mousex() <= screenWidth-50 && mousey() >= 20 && mousey() <= screenHeight-100)
                        {
                            trapez(B, 0, 0, text);
                            B.x = mousex();
                            B.y = mousey();
                            trapez(B, 14, 0, text);
                        }
                    }
                }
            }
            else d.selectareBlocDiferit = true;
        }
        else if(B.tip == 'i')
        {
            int x1=B.x-B.latime/4;
            int x2=B.x+B.latime/4;
            int y1=B.y+B.inaltime/2;
            int y2=B.y-B.inaltime;

            if(mX>=x1 && mX<=x2 && mY<=y1 && mY>=y2)
            {
                clearmouseclick(WM_LBUTTONUP);
                while(!ismouseclick(WM_LBUTTONUP))
                {
                    if(ismouseclick(WM_MOUSEMOVE))
                    {
                        clearmouseclick(WM_MOUSEMOVE);

                        if(mousex() >= 230 && mousex() <= screenWidth-50 && mousey() >= 20 && mousey() <= screenHeight-100)
                        {
                            trapez_rasturnat(B, 0, 0, text);
                            B.x = mousex();
                            B.y = mousey();
                            trapez_rasturnat(B, 14, 0, text);
                        }
                    }
                }
            }
            else d.selectareBlocDiferit = true;
        }
    }
}

void punereBloc(piesa &B, int culoare, int c)
{
    char text[200];

    strcpy(text, "");

    int mX = mousex();
    int mY = mousey();

    B.x = mX;
    B.y = mY;

    if(c == 'c')
    {
        d.citesteText = true;
        calculBloc(B, culoare, 0, text);

    }
    else if(c == 'd')
    {
        d.citesteText = true;
        decizie(B, culoare, 0, text);
    }
    else if(c == 's')
    {
        d.nrBlocuriStart++;
        d.citesteText = true;
        strcpy(text, "START");
        terminal(B, text, culoare, 0);
    }
    else if(c == 't')
    {
        d.nrBlocuriStop = true;
        d.citesteText = true;
        strcpy(text, "STOP");
        terminal(B, text, culoare, 0);
    }
    else if(c=='o')
    {
        d.citesteText=true;
        trapez(B,culoare,0,text);
    }
    else if(c=='i')
    {
        d.citesteText=true;

        trapez_rasturnat(B,culoare,0,text);
    }
}

void refacere(piesa B, int culoare)
{

    d.citesteText = false;

    if(B.tip == 'c')
    {
        calculBloc(B, culoare, 0, B.e.text);
    }
    else if(B.tip == 'd')
    {
        decizie(B,  culoare, 0, B.e.text);
    }
    else if(B.tip == 's')
    {
        terminal(B, "START",  culoare, 0);
    }
    else if(B.tip == 't')
    {
        terminal(B, "STOP",  culoare, 0);
    }
    else if(B.tip =='o')
    {
        trapez(B, culoare,0, B.e.text);
    }
    else if(B.tip =='i')
    {
        trapez_rasturnat(B, culoare,0, B.e.text);
    }
}

void blocksCheck()
{
    d.punereBlocuri = false;
    d.mutareBlocuri = false;


    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);

        int x = mousex();
        int y = mousey();

        if(x >= 20 && x <= 170 && y >= 480 && y <= 530)
        {
            d.pasCurent = false;
            d.butonSelectat = -1;
            if(d.butonLegaturi)
            {
                desenareZonaValida(0);
                readimagefile("legaturiON.jpg", 20, 480, 170, 530);
            }
            else
            {
                readimagefile("codON.jpg", 20, 480, 170, 530);
                delay(400);
                readimagefile("black.jpg", 20, 20, 170, 800);
            }

            return;
        }

        if(d.stergeBloc)
        {
            if(x >= 20 && x <= 170 && y >= 660 && y <= 710)//sterge ultimul bloc introdus
            {
                readimagefile("stergeON.jpg", 20, 660, 170, 710);

                readimagefile("startOFF.jpg", 20, 20, 170, 70);
                readimagefile("stopOFF.jpg", 20, 90, 170, 140);
                readimagefile("inputOFF.jpg", 20, 160, 170, 210);
                readimagefile("outputOFF.jpg", 20, 230, 170, 280);
                readimagefile("decizieOFF.jpg", 20, 300, 170, 350);
                readimagefile("calculOFF.jpg", 20, 370, 170, 420);
                d.butonSelectat = 10;
                return;
            }
            else
            {
                readimagefile("stergeOFF.jpg", 20, 660, 170, 710);
            }
        }
        if(!d.butonLegaturi)
        {

            if(x>=50 && x<=130 && y>=660 && y <= 710)
            {
                readimagefile("saveON.jpg", 50, 660, 130, 710);
                delay(500);
                readimagefile("saveOFF.jpg", 50, 660, 130, 710);
                delay(0);
                d.butonSave = true;
            }
        }
        if(x >= 20 && x <= 170 && y >= 20 && y <= 420)
        {
            d.existaBloc = true;
            if(x >= 20 && x <= 170 && y >= 20 && y <= 70)
            {
                readimagefile("startON.jpg", 20, 20, 170, 70);
                d.butonSelectat = 1;
            }
            else
            {
                readimagefile("startOFF.jpg", 20, 20, 170, 70);
            }

            if(x >= 20 && x <= 170 && y >= 90 && y <= 140)
            {
                readimagefile("stopON.jpg", 20, 90, 170, 140);
                d.butonSelectat = 2;
            }
            else
            {
                readimagefile("stopOFF.jpg", 20, 90, 170, 140);
            }

            if(x >= 20 && x <= 170 && y >= 160 && y <= 210)
            {
                readimagefile("inputON.jpg", 20, 160, 170, 210);
                d.butonSelectat = 3;
            }
            else
            {
                readimagefile("inputOFF.jpg", 20, 160, 170, 210);
            }

            if(x >= 20 && x <= 170 && y >= 230 && y <= 280)
            {
                readimagefile("outputON.jpg", 20, 230, 170, 280);
                d.butonSelectat = 4;
            }
            else
            {
                readimagefile("outputOFF.jpg", 20, 230, 170, 280);
            }

            if(x >= 20 && x <= 170 && y >= 300 && y <= 350)
            {
                readimagefile("decizieON.jpg", 20, 300, 170, 350);
                d.butonSelectat = 5;
            }
            else
            {
                readimagefile("decizieOFF.jpg", 20, 300, 170, 350);
            }

            if(x >= 20 && x <= 170 && y >= 370 && y <= 420)
            {
                readimagefile("calculON.jpg", 20, 370, 170, 420);
                d.butonSelectat = 6;
            }
            else
            {
                readimagefile("calculOFF.jpg", 20, 370, 170, 420);
            }
        }
        else if(d.existaBloc == true)
        {
            d.punereBlocuri = true;
            d.mutareBlocuri = true;
            d.existaBloc = false;
        }
    }
}

int Prioritate(char c)
{
    if(c=='(' || c==')')
        return 0;
    if(c=='+' || c=='-')
        return 1;
    if(c=='*' || c=='/')
        return 2;
    if(c=='^')
        return 3;
    if(c=='=' || c=='#' || c=='<' || c=='>')
        return 4;
    if(c=='c' || c=='s' || c=='l' || c=='e' || c=='t' || c=='a' || c=='r')
        return 5;
}

bool DifInf(float x)
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x>epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}

float Exponential(float x)
{
    if (DifInf(x)) return exp(x);
    else return infinit;
}

float Inmultit(float x, float y)
{
    if (fabs(x < epsi) || fabs(y) < epsi) return 0;
    else if (DifInf(x) && DifInf(y)) return x*y;
    else return infinit;
}

float Putere(float x, float y)
{
    if (x==0) return 0;
    else if (y==0) return 1;
    else if (x==infinit || y==infinit) return infinit;
    else return pow(x,y);
}

float Egal(float x, float y)
{
    return x==y;
}

float Diferit(float x, float y)
{
    return x!=y;
}

float MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x+y;
    else return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))  return x-y;
    else return infinit;
}

float Impartit(float x, float y)
{
    if (fabs(y)>epsi) return x/y;
    else return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}

float Modul(float x)
{
    if (DifInf(x)) return fabs(x);
    else return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x>epsi)) return sqrt(x);
    else return infinit;
}

bool EsteNumar(char sir[MAX1])
{
    return (atof(sir)!=0.0 &&
            strchr("0123456789",sir[0]));
}

double ValoareFunctie(functie E, double x)
{
    int i;
    double valo, x_1, x_2;
    for (i = 1; i <= max_stiva; i++)
    {
        d.eval.operanzi[i] = 0;
        d.eval.operatori[i] = '@';
    }
    d.eval.top1=0;
    d.eval.top2=1;
    d.eval.operatori[d.eval.top2]='(';
    i = 0;
    while (i <= E.lung && d.eval.top2 > 0)
    {
        i++;
        if (EsteNumar(E.vect[i]))
        {
            d.eval.top1++;
            valo = atof(E.vect[i]);
            d.eval.operanzi[d.eval.top1] = valo;
        }
        else
            switch (E.vect[i][0])
            {
            /* constanta pi=3.1415926 se da sub forma literei q */
            case 'q':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=pi;
                break;
            case 'X': /* variabila x */
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case 'Y':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case 'Z':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case 'A':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case 'B':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case 'C':
                d.eval.top1++;
                d.eval.operanzi[d.eval.top1]=x;
                break;
            case '(': /* inceput de bloc */
                d.eval.top2++;
                d.eval.operatori[d.eval.top2]='(';
                break;
            default:
                /* operatii binare si unare */
                while ((d.eval.top2>0) && !(strchr("()",d.eval.operatori[d.eval.top2])) &&
                        Prioritate(d.eval.operatori[d.eval.top2])>=Prioritate(E.vect[i][0]))
                {
                    if (d.eval.top1>1) x_1=d.eval.operanzi[d.eval.top1-1];
                    x_2=d.eval.operanzi[d.eval.top1];
                    /* functii scrise in OPERATII */
                    switch (d.eval.operatori[d.eval.top2])
                    {
                    case '=':
                        valo=Egal(x_1,x_2);
                        break;
                    case '#':
                        valo=Diferit(x_1,x_2);
                        break;
                    case '<':
                        valo=MaiMic(x_1,x_2);
                        break;
                    case '>':
                        valo=MaiMare(x_1,x_2);
                        break;
                    case '+':
                        valo=Plus(x_1,x_2);
                        break;
                    case '-':
                        valo=Minus(x_1,x_2);
                        break;
                    case '*':
                        valo=Inmultit(x_1,x_2);
                        break;
                    case '/':
                        valo=Impartit(x_1,x_2);
                        break;
                    case '^':
                        valo=Putere(x_1,x_2);
                        break;
                    case 's':
                        valo=Sinus(x_2);
                        break;
                    case 'c':
                        valo=Cosinus(x_2);
                        break;
                    case 'l':
                        valo=Logaritm(x_2);
                        break;
                    case 'e':
                        valo=Exponential(x_2);
                        break;
                    case 'a':
                        valo=Modul(x_2);
                        break;
                    case 'r':
                        valo=Radical(x_2);
                        break;
                    } //operator[top2]
                    if (strchr(d.eval.OperatiiBinare,d.eval.operatori[d.eval.top2]))
                        d.eval.top1--;
                    if (strchr(d.eval.Operatii,d.eval.operatori[d.eval.top2]))
                        d.eval.operanzi[d.eval.top1]=valo;
                    d.eval.top2--;
                }
                if (d.eval.top2>0)
                    if ((d.eval.operatori[d.eval.top2]!='(') || (strcmp(E.vect[i],")")))
                    {
                        d.eval.top2++;
                        d.eval.operatori[d.eval.top2] = E.vect[i][0];
                    }
                    else d.eval.top2--;
            }
    }
    if (d.eval.top2==0) return d.eval.operanzi[1];
    else return infinit;
}

void tab(int k, char spatii[])
{
    while(k--)
    {
        strcat(spatii,"   ");
    }
}

void codCalcul(piesa *B, int c)
{
    settextjustify(0, 1);
    ++d.nrExpresii;

    int k = 0;
    while(B -> e.text[k] != '<' && B -> e.text[k] != NULL)
        k++;
    if(B -> e.text[k] == NULL || B -> e.text[k + 1] != '-')
    {
        cout << "   Diagrama incorecta! - Variabila din blocul CALCUL nu contine o atribuire ";
        getch();
        closegraph();
        return ;
    }
    int v;
    printf("    double ");

    for(v = 0; v < k; v++)
    {
        d.F[d.nrExpresii].variabila[v] = B-> e.text[v];
        cout << d.F[d.nrExpresii].variabila[v];
    }
    d.F[d.nrExpresii].variabila[v] = '\0';

    cout << " = ";

    k++;
    char expr[100];
    strcpy(expr, B-> e.text + k + 1);

    cout << expr << ";" << endl;

    char sir[100];
    char codIdentat[200];

    sprintf(sir,"%s=%s;", d.F[d.nrExpresii].variabila, expr);
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, sir);
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod += textheight(sir) + 5;

    strcpy(d.F[d.nrExpresii].expCalcul, expr);

    strcpy(d.F[d.nrExpresii].expresie, expr);
    strcat(d.F[d.nrExpresii].expresie,")");

    d.F[d.nrExpresii].lung = strlen(d.F[d.nrExpresii].expresie);
    int auxLung = d.F[d.nrExpresii].lung;

    strcpy(d.F[d.nrExpresii].vect[0],"(");

    for(int i = d.F[d.nrExpresii].lung - 1; i >= 0; i--)
    {
        strcpy(d.F[d.nrExpresii].vect[i + 1], d.F[d.nrExpresii].expresie + i);
        strcpy(d.F[d.nrExpresii].expresie + i, d.F[d.nrExpresii].expresie + i + 1);
    }

    d.F[d.nrExpresii].lung = auxLung;

}
void codInput(piesa *B, int c)
{
    settextjustify(0, 1);

    char var[100];
    strcpy(var, B -> e.text);

    if(strlen(var) > 1)
    {
        cout << "   Diagrama incorecta! - Variabila din blocul INPUT nu are lungimea 1 ";
        getch();
        closegraph();
        return ;
    }
    if(!strchr("ABCXYZ",var[0]))
    {
        cout << "   Diagrama incorecta! - Variabila din blocul INPUT nu este A, B, C, X, Y sau Z";
        getch();
        closegraph();
        return ;
    }

    printf("    double %s;\n    cin >> %s;\n", var, var);

    char sir[100];
    char codIdentat[200];

    sprintf(sir, "cin>>%s;", var);
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, sir);
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");
}
void codOutput(piesa *B, int c)
{
    settextjustify(0, 1);

    char var[100];

    strcpy(var, B -> e.text);
    bool gasit = false;
    char ch = 0;
    bool expDeEvaluat = true;
    for(int l = 0 ; var[l]; l++)
    {
        if(strchr(".,;:][{}#~&%$£ ", var[l]))
        {
            cout << "   Diagrama incorecta! - Variabila din blocul OUTPUT contine simbolul " << var[l] << endl;
            getch();
            closegraph();
            return ;
        }
        else if(strchr("XYZABC", var[l]))
        {
            if(!ch)
            {
                gasit = true;
                ch = var[l];
            }
            else if(var[l] != ch)
                expDeEvaluat = false;
        }
    }
    if(expDeEvaluat)
    {
        ++d.nrExpresii;

        strcpy(d.F[d.nrExpresii].expOutput, var);
        strcpy(d.F[d.nrExpresii].variabila, var);

        strcpy(d.F[d.nrExpresii].expresie, var);
        strcat(d.F[d.nrExpresii].expresie,")");

        d.F[d.nrExpresii].lung = strlen(d.F[d.nrExpresii].expresie);
        int auxLung = d.F[d.nrExpresii].lung;

        strcpy(d.F[d.nrExpresii].vect[0],"(");

        for(int i = d.F[d.nrExpresii].lung - 1; i >= 0; i--)
        {
            strcpy(d.F[d.nrExpresii].vect[i + 1], d.F[d.nrExpresii].expresie + i);
            strcpy(d.F[d.nrExpresii].expresie + i, d.F[d.nrExpresii].expresie + i + 1);
        }

        d.F[d.nrExpresii].lung = auxLung;
    }

    strcpy(d.afisare[++d.nrBlocuriOutput], var);

    printf("    cout << %s;\n", var);

    char sir[100];
    char codIdentat[200];
    sprintf(sir, "cout<<%s;", var);
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, sir);
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

}
void declarareVariabile()
{
    int copieXcod = d.xCod;
    bool existaX= false, existaY= false, existaZ = false;
    bool existaA= false, existaB= false, existaC = false;
    int sep = textwidth("X");
    if(d.nrBlocuriInput)
    {
        outtextxy(d.xCod, d.yCod, "   double ");
        copieXcod += textwidth("    double ");
        for(int i = 1 ; i <= d.nrBlocuriInput; i++)
        {
            if(!existaX && d.citire[i][0] == 'X')
            {
                existaX = true;
                outtextxy(copieXcod, d.yCod, "X");
                d.initVar['X' - 'A'] = 0;
                copieXcod += sep;
                if((existaA && existaB && existaC && existaY && existaZ) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
            else if(!existaY && d.citire[i][0] == 'Y')
            {
                existaY = true;
                outtextxy(copieXcod, d.yCod, "Y");
                d.initVar['Y' - 'A'] = 0;
                copieXcod += sep;
                if((existaA && existaB && existaC && existaX && existaZ) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
            else if(!existaZ && d.citire[i][0] == 'Z')
            {
                existaZ = true;
                outtextxy(copieXcod, d.yCod, "Z");
                d.initVar['Z' - 'A'] = 0;
                copieXcod += sep;
                if((existaA && existaB && existaC && existaY && existaX) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
            else if(!existaA && d.citire[i][0] == 'A')
            {
                existaA = true;
                outtextxy(copieXcod, d.yCod, "A");
                d.initVar['A' - 'A'] = 0;
                copieXcod += sep;
                if((existaX && existaB && existaC && existaY && existaZ) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
            else if(!existaB && d.citire[i][0] == 'B')
            {
                existaB = true;
                outtextxy(copieXcod, d.yCod, "B");
                d.initVar['B' - 'A'] = 0;
                copieXcod += sep;
                if((existaA && existaX && existaC && existaY && existaZ) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
            else if(!existaC && d.citire[i][0] == 'C')
            {
                existaC = true;
                outtextxy(copieXcod, d.yCod, "C");
                d.initVar['C' - 'A'] = 0;
                copieXcod += sep;
                if((existaA && existaB && existaX && existaY && existaZ) || (i + 1 > d.nrBlocuriInput))
                {
                    outtextxy(copieXcod, d.yCod, ";");
                    break;
                }
                else
                {
                    outtextxy(copieXcod, d.yCod, ",");
                }
                copieXcod += sep;
            }
        }
        d.yCod+=textheight("a");
    }
    int x = d.xCod;
    bool exista = false;
    for(int i = 0; i <= 30; i++)
        if(d.initVar[i])
        {
            outtextxy(x, d.yCod, "   double ");
            x += textwidth("    double ");
            exista = true;
            break;
        }



    for(int i = 0; i <= 30; i++)
        if(d.initVar[i])
        {
            char sir[10];
            char c = char(i + 'A');
            sprintf(sir, "%c, ", c);
            outtextxy(x, d.yCod, sir);
            x += sep;
        }
    if(exista)
    {
        x -= 1;
        outtextxy(x, d.yCod, ";");

        d.yCod+=textheight("a");
    }


}
void codStart(int c)
{
    line(0, 20, 230, 20);

    settextjustify(0, 1);
    printf("\n\n #include <bits/stdc++.h>\n using namespace std; \n\n int main() \n { \n");
    outtextxy(d.xCod, d.yCod, "#include <bits/stdc++.h>");
    d.yCod+=textheight("a");
    outtextxy(d.xCod, d.yCod, "using namespace std;");
    d.yCod+=textheight("a");
    outtextxy(d.xCod, d.yCod, "int main()");
    d.yCod+=textheight("a");
    outtextxy(d.xCod, d.yCod, "{");
    d.yCod+=textheight("a");
    declarareVariabile();

}
void codStop(int c)
{
    printf("    return 0;\n }\n");
    settextjustify(0, 1);

    char codIdentat[100];
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "return 0;");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");
}
void codDecizie(piesa *B, int c)
{
    settextjustify(0, 1);
    ++d.nrExpresii;
    if(strchr(B -> e.text, '<-'))
    {
        cout << "   Diagrama incorecta! - Expresia din blocul DECIZIE contine o atribuire.";
        getch();
        closegraph();
        return ;
    }
    cout << "    if(";

    char sir[100];
    int cnt = 0;
    for(int i = 0; B -> e.text[i]; i++)
    {
        cout << B -> e.text[i];
        sir[cnt++] = B -> e.text[i];

        if(B -> e.text[i] == '=')
        {
            if(!(B -> e.text[i-1] == '<' || B -> e.text[i-1] == '>'))
            {
                cout << B -> e.text[i];
                sir[cnt++] = B -> e.text[i];
            }

        }
    }
    cout << ")\n    {\n";

    sir[cnt] = NULL;

    char arr[120];
    char codIdentat[200];

    sprintf(arr, "if(%s)", sir);
    strcpy(d.F[d.nrExpresii].expDecizie, sir);
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, arr);
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "{");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

    char expr[100];
    strcpy(expr, B -> e.text);

    strcpy(d.F[d.nrExpresii].expresie, expr);
    strcat(d.F[d.nrExpresii].expresie,")");

    d.F[d.nrExpresii].lung = strlen(d.F[d.nrExpresii].expresie);
    int auxLung = d.F[d.nrExpresii].lung;

    strcpy(d.F[d.nrExpresii].vect[0],"("); //!!!


    for(int i = d.F[d.nrExpresii].lung - 1; i >= 0; i--)
    {
        strcpy(d.F[d.nrExpresii].vect[i + 1], d.F[d.nrExpresii].expresie + i);
        strcpy(d.F[d.nrExpresii].expresie + i, d.F[d.nrExpresii].expresie + i + 1);
    }

    d.F[d.nrExpresii].lung = auxLung;
}
void codElse(int c)
{
    settextjustify(0, 1);
    char codIdentat[100];
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "else");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "{");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

}
void codInchidereAcolada(int c)
{
    settextjustify(0, 1);
    char codIdentat[100];
    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "}");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");
}
void codificareSimpla(piesa *B, int identare)
{
    if(B -> tip == 'c')
        codCalcul(B, identare);
    else if(B -> tip == 'i')
        codInput(B, identare);
    else if(B -> tip == 'o')
        codOutput(B, identare);
}

void codWhile(piesa *B, int c)
{
    settextjustify(0, 1);
    ++d.nrExpresii;
    if(strchr(B -> e.text, '<-'))
    {
        cout << "   Diagrama incorecta! - Expresia din blocul DECIZIE contine o atribuire.";
        getch();
        closegraph();
        return ;
    }

    cout << "    while(";

    char sir[100];
    int cnt = 0;
    for(int i = 0; B -> e.text[i]; i++)
    {
        cout << B -> e.text[i];
        sir[cnt++] = B -> e.text[i];

        if(B -> e.text[i] == '=')
        {
            if(!(B -> e.text[i-1] == '<' || B -> e.text[i-1] == '>'))
            {
                cout << B -> e.text[i];
                sir[cnt++] = B -> e.text[i];
            }
        }

    }
    cout << ")\n    {\n";

    sir[cnt] = NULL;

    char arr[120];
    char codIdentat[200];
    sprintf(arr, "while(%s)", sir);
    strcpy(d.F[d.nrExpresii].expDecizie, sir);

    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, arr);
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");

    strcpy(codIdentat, "");
    tab(c, codIdentat);
    strcat(codIdentat, "{");
    outtextxy(d.xCod, d.yCod, codIdentat);
    d.yCod+=textheight("a");


    char expr[100];
    strcpy(expr, B -> e.text);


    strcpy(d.F[d.nrExpresii].expresie, expr);
    strcat(d.F[d.nrExpresii].expresie,")");

    d.F[d.nrExpresii].lung = strlen(d.F[d.nrExpresii].expresie);
    int auxLung = d.F[d.nrExpresii].lung;

    strcpy(d.F[d.nrExpresii].vect[0],"("); //!!!


    for(int i = d.F[d.nrExpresii].lung - 1; i >= 0; i--)
    {
        strcpy(d.F[d.nrExpresii].vect[i + 1], d.F[d.nrExpresii].expresie + i);
        strcpy(d.F[d.nrExpresii].expresie + i, d.F[d.nrExpresii].expresie + i + 1);
    }
    d.F[d.nrExpresii].lung = auxLung;
}

void codificare(piesa *B, int identare)
{
    if(B != NULL)
    {
        if(B -> sfarsit == false)
        {
            if(B -> tip != 't')
            {
                if(B -> tip != 'd')
                {
                    if(B -> tip == 's')
                    {
                        codStart(1);

                        codificare(B -> urm, identare);

                        codInchidereAcolada(identare - 1);
                    }
                    else
                    {
                        codificareSimpla(B, identare);
                        if(d.ramuraElse == true)
                        {
                            d.precedentBlocComun = B;
                            if(B -> salt)
                            {
                                d.ramuraElse = false;
                            }
                            else codificare(B -> urm, identare);
                        }
                        else
                        {
                            codificare(B -> urm, identare);
                        }
                    }
                }
                else
                {
                    if(B -> repetitie == false)
                    {
                        codDecizie(B, identare);

                        codificare(B -> urmA, identare + 1);

                        codInchidereAcolada(identare);

                        codElse(identare);

                        d.ramuraElse = true;
                        codificare(B -> urmF, identare + 1);

                        codInchidereAcolada(identare);

                        d.precedentBlComunUrm = d.precedentBlocComun -> salt;
                        codificare(d.precedentBlComunUrm, identare);
                        d.precedentBlocComun = d.precedentBlComunUrm;

                    }
                    else
                    {
                        codWhile(B, identare);

                        codificare(B -> urmA, identare + 1);

                        codInchidereAcolada(identare);

                        codificare(B -> urmF, identare);
                    }
                }
            }
            else
            {
                codStop(identare);
            }
        }
    }
}
void evaluareExpresiiGasite()
{

    settextjustify(0, 1);
    for(int i = 1; i <= d.nrBlocuriInput; i++)
    {
        float x;
        char sir[200];

        sprintf(sir, "Citeste %s:  ", d.citire[i]);
        outtextxy(d.xCod, d.yCod, sir);

        int dim = textwidth(sir);
        d.xCod+=dim;

        strcpy(sir, "_");
        outtextxy(d.xCod, d.yCod, sir);
        strcpy(sir, "");

        citireText(d.xCod, d.yCod, sir);
        x = atof(sir);

        d.xCod-=dim;
        d.yCod+=textheight("a");

        for(int j = 1; j <= d.nrExpresii; j++)
        {
            if(strchr(d.F[j].expCalcul, d.citire[i][0]))
            {

                float rez = ValoareFunctie(d.F[j], x);
                for(int k = 1; k <= d.nrBlocuriOutput; k++)
                    if(!strcmp(d.F[j].variabila, d.afisare[k]))
                    {
                        char sir[200];
                        sprintf(sir, "%s = %.2f", d.F[j].variabila, rez);
                        outtextxy(d.xCod,  d.yCod, sir);
                        d.yCod+=textheight("a");
                    }
            }
            if(strchr(d.F[j].expOutput, d.citire[i][0]))
            {
                float rez = ValoareFunctie(d.F[j], x);
                char sir[200];
                sprintf(sir, "%s = %.2f", d.F[j].variabila, rez);
                outtextxy(d.xCod, d.yCod, sir);
                d.yCod+=textheight("a");
            }
            if(strchr(d.F[j].expDecizie, d.citire[i][0]))
            {
                outtextxy(d.xCod,  d.yCod, d.F[j].expDecizie);
                float rez = ValoareFunctie(d.F[j], x);
                d.xCod += textwidth(d.F[j].expDecizie);
                if(rez == 1)
                {
                    outtextxy(d.xCod, d.yCod, " : ADEVARAT");
                }
                else outtextxy(d.xCod, d.yCod, " : FALS");
                d.xCod -= textwidth(d.F[j].expDecizie);
                d.yCod+=textheight("a");
            }
        }

    }
}

void menuCheck()
{
    int x = mousex();
    int y = mousey();
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        if(x >= screenWidth/2-textwidth("Construieste")&& x <= screenWidth/2+textwidth("Construieste") && y >= 100 && y <= 200)
            d.butonMeniu = 1;
        else if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 300 && y <= 400)
            d.butonMeniu = 2;
        else if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 500 && y <= 600)
            d.butonMeniu = 3;
        else if(x >= 100 && x <=100+textwidth("Construieste")  && y >= 100 && y <= 200)
            d.butonMeniu = 4;
    }

    if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste")&& y >= 100 && y <= 200)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("Construieste")+15, 135, "Construieste Diagrama");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("Construieste")+15, 135, "Construieste Diagrama");
    }

    if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 300 && y <= 400)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("Construieste")+135, 335, "Instructiuni");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("Construieste")+135, 335, "Instructiuni");
    }

    if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 500 && y <= 600)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("Construieste")+60, 535, "Incarca Diagrama");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("Construieste")+60, 535, "Incarca Diagrama");
    }

    if(x >= 100 && x <=100+textwidth("Construieste")  && y >= 100 && y <= 200)
    {
        setcolor(3);
        outtextxy(160, 133, "Iesire");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(160, 133, "Iesire");
    }
}
void backCheck()
{
    int x = mousex();
    int y = mousey();
    if(x>=screenWidth-200 && x<=screenWidth-100 && y>=screenHeight-95 && screenHeight-40)
    {
        readimagefile("back2.jpg",screenWidth-200,screenHeight-95,screenWidth-100,screenHeight-40);
    }
    else  readimagefile("back1.jpg",screenWidth-200,screenHeight-95,screenWidth-100,screenHeight-40);

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        if(x>=screenWidth-200 && x<=screenWidth-100 && y>=screenHeight-95 && screenHeight-40)
        {

            d.butonBack = true;

            return;
        }
    }
}
void instructiuni()
{
    readimagefile("Instructiuni.jpg",0,0,screenWidth-10,screenHeight-10);
}
void initializareMeniu()
{
    readimagefile("INTERSCHEMBG.jpg", 0, 0, screenWidth, screenHeight);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    setbkcolor(12);

    setcolor(0);
    rectangle(screenWidth/2-textwidth("Construieste"), 100, screenWidth/2+textwidth("Construieste"), 200);
    rectangle(screenWidth/2-textwidth("Construieste"), 300, screenWidth/2+textwidth("Construieste"), 400);
    rectangle(screenWidth/2-textwidth("Construieste"), 500, screenWidth/2+textwidth("Construieste"), 600);
    rectangle(100, 100, 100+textwidth("Construieste"), 200);

}
void butoaneOprite()
{
    readimagefile("saveOFF.jpg", 50, 660, 130, 710);
    readimagefile("startOFF.jpg", 20, 20, 170, 70);
    readimagefile("stopOFF.jpg", 20, 90, 170, 140);
    readimagefile("inputOFF.jpg", 20, 160, 170, 210);
    readimagefile("outputOFF.jpg", 20, 230, 170, 280);
    readimagefile("decizieOFF.jpg", 20, 300, 170, 350);
    readimagefile("calculOFF.jpg", 20, 370, 170, 420);
}

void initializareDiagrama()
{
    initwindow(screenWidth,screenHeight,"InterSchem");

    setactivepage(0);
    setbkcolor(d.FUNDAL);
    cleardevice();

    setactivepage(1);
    setbkcolor(d.FUNDAL);
    cleardevice();

    setvisualpage(0);
    setactivepage(0);
}

void salvareDiagrama()
{
    ofstream fout("memorie.txt");
    int i,idNod1,idNod2,p1,p2,x1,y1,x2,y2;
    fout << d.nrBlocuri << '\n';
    fout << d.nrLegaturi << '\n';
    fout << d.nrBlocuriInput << '\n';
    for(int i = 1; i <= d.nrBlocuriInput; i++)
        fout << d.citire[i][0]<<" ";

    for(int i = 1; i <= d.nrBlocuri; i++)
    {
        fout << d.bloc[i].tip << '\n';
        fout << d.bloc[i].x << " " << d.bloc[i].y << " " << d.bloc[i].inaltime <<" " << d.bloc[i].latime << '\n';
        fout << d.bloc[i].e.text <<'\n';
        if(d.bloc[i].repetitie)
            fout << 1 << '\n';
        else fout << 0 << '\n';
        fout << d.blc[i].intrari << '\n';
        for(int j = 1; j <= d.blc[i].intrari; j++)
            fout << d.blc[i].precedent[j] << '\n';
    }

    for (i=1; i <= d.nrLegaturi; i++)
    {
        idNod1 = d.leg[i].bloc1;
        p1 = d.leg[i].punct1;
        x1 = d.bloc[idNod1].pLeg[p1].x;
        y1 = d.bloc[idNod1].pLeg[p1].y;

        fout << idNod1 << " " << p1 << " " << x1 << " " << y1<< '\n';

        idNod2=d.leg[i].bloc2;
        p2=d.leg[i].punct2;
        x2=d.bloc[idNod2].pLeg[p2].x;
        y2=d.bloc[idNod2].pLeg[p2].y;

        fout << idNod2 << " " << p2 << " " << x2 << " " << y2 << '\n';
    }
    fout << d.XLegFinala1 <<" " << d.YLegFinala1 << '\n';
    fout << d.XLegFinala2 << " " << d.YLegFinala2 << '\n';
}

void incarcareDiagramaSalvata()
{
    fin >> d.nrBlocuri >> d.nrLegaturi;
    fin >> d.nrBlocuriInput;
    for(int i = 1; i <= d.nrBlocuriInput; i++)
        fin >> d.citire[i][0];
    for(int i = 1; i <= d.nrBlocuri; i++)
    {
        fin >> d.bloc[i].tip;
        fin >> d.bloc[i].x >> d.bloc[i].y >> d.bloc[i].inaltime >> d.bloc[i].latime;
        fin >> d.bloc[i].e.text;
        fin >> d.bloc[i].repetitie;
        fin >> d.blc[i].intrari;
        for(int j = 1; j <= d.blc[i].intrari; j++)
            fin >> d.blc[i].precedent[j];
    }
    for(int i = 1; i <= d.nrLegaturi; i++)
    {
        fin >> d.leg[i].bloc1;
        fin >> d.leg[i].punct1;
        fin >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].x;
        fin >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].y;

        fin >> d.leg[i].bloc2;
        fin >> d.leg[i].punct2;
        fin >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].x;
        fin >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].y;
    }

    fin >> d.XLegFinala1 >> d.YLegFinala1;
    fin >> d.XLegFinala2 >> d.YLegFinala2;


    restaureaza(d.bloc, 0);
}
void incarcareMaxim()
{
    f1 >> d.nrBlocuri >> d.nrLegaturi;
    f1 >> d.nrBlocuriInput;
    for(int i = 1; i <= d.nrBlocuriInput; i++)
        f1 >> d.citire[i][0];


    for(int i = 1; i <= d.nrBlocuri; i++)
    {
        f1 >> d.bloc[i].tip;
        f1 >> d.bloc[i].x >> d.bloc[i].y >> d.bloc[i].inaltime >> d.bloc[i].latime;
        f1 >> d.bloc[i].e.text;
        f1 >> d.bloc[i].repetitie;
        f1 >> d.blc[i].intrari;
        for(int j = 1; j <= d.blc[i].intrari; j++)
            f1 >> d.blc[i].precedent[j];
    }
    for(int i = 1; i <= d.nrLegaturi; i++)
    {
        f1 >> d.leg[i].bloc1;
        f1 >> d.leg[i].punct1;
        f1 >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].x;
        f1 >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].y;

        f1 >> d.leg[i].bloc2;
        f1 >> d.leg[i].punct2;
        f1 >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].x;
        f1 >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].y;
    }

    f1 >> d.XLegFinala1 >> d.YLegFinala1;
    f1 >> d.XLegFinala2 >> d.YLegFinala2;

    restaureaza(d.bloc, 0);
}
void incarcareSuma()
{
    f2 >> d.nrBlocuri >> d.nrLegaturi;
    f2 >> d.nrBlocuriInput;
    for(int i = 1; i <= d.nrBlocuriInput; i++)
        f2 >> d.citire[i][0];
    for(int i = 1; i <= d.nrBlocuri; i++)
    {
        f2 >> d.bloc[i].tip;
        f2 >> d.bloc[i].x >> d.bloc[i].y >> d.bloc[i].inaltime >> d.bloc[i].latime;
        f2 >> d.bloc[i].e.text;
        f2 >> d.bloc[i].repetitie;
        f2 >> d.blc[i].intrari;
        for(int j = 1; j <= d.blc[i].intrari; j++)
            f2 >> d.blc[i].precedent[j];
    }
    for(int i = 1; i <= d.nrLegaturi; i++)
    {
        f2 >> d.leg[i].bloc1;
        f2 >> d.leg[i].punct1;
        f2 >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].x;
        f2 >> d.bloc[d.leg[i].bloc1].pLeg[d.leg[i].punct1].y;

        f2 >> d.leg[i].bloc2;
        f2 >> d.leg[i].punct2;
        f2 >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].x;
        f2 >> d.bloc[d.leg[i].bloc2].pLeg[d.leg[i].punct2].y;
    }

    f2 >> d.XLegFinala1 >> d.YLegFinala1;
    f2 >> d.XLegFinala2 >> d.YLegFinala2;

    restaureaza(d.bloc, 0);
}
void blocSelectat(int b, char &caracterBloc)
{
    switch(b)
    {
    case 1:
    {
        caracterBloc = 's';
        break;
    }
    case 2:
    {
        caracterBloc = 't';
        break;
    }
    case 3:
    {
        caracterBloc = 'i';
        break;
    }
    case 4:
    {
        caracterBloc = 'o';
        break;
    }
    case 5:
    {
        caracterBloc = 'd';

        break;
    }
    case 6:
    {
        caracterBloc = 'c';
        break;
    }
    }
}
void meniuIncarcare()
{
    readimagefile("INTERSCHEMBG.jpg", 0, 0, screenWidth, screenHeight);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
    setbkcolor(12);

    setcolor(0);
    rectangle(screenWidth/2-textwidth("Construieste"), 100, screenWidth/2+textwidth("Construieste"), 200);
    rectangle(screenWidth/2-textwidth("Construieste"), 300, screenWidth/2+textwidth("Construieste"), 400);
    rectangle(screenWidth/2-textwidth("Construieste"), 500, screenWidth/2+textwidth("Construieste"), 600);
}
void incarcareCheck()
{
    int x = mousex();
    int y = mousey();

    if(x>=screenWidth-200 && x<=screenWidth-100 && y>=screenHeight-95 && screenHeight-40)
    {
        readimagefile("back2.jpg",screenWidth-200,screenHeight-95,screenWidth-100,screenHeight-40);
    }
    else  readimagefile("back1.jpg",screenWidth-200,screenHeight-95,screenWidth-100,screenHeight-40);

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        if(x >= screenWidth/2-textwidth("Construieste")&& x <= screenWidth/2+textwidth("Construieste") && y >= 100 && y <= 200)
            d.butonIncarcare = 1;
        else if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 300 && y <= 400)
            d.butonIncarcare = 2;
        else if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 500 && y <= 600)
            d.butonIncarcare = 3;
        else if(x>=screenWidth-200 && x<=screenWidth-100 && y>=screenHeight-95 && screenHeight-40)
        {
            d.butonBack = true;
            return;
        }
    }

    if(x >= screenWidth/2-textwidth("Construieste")&& x <= screenWidth/2+textwidth("Construieste") && y >= 100 && y <= 200)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("UltimaS"), 135, "Ultima Salvata");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("UltimaS"), 135, "Ultima Salvata");
    }

    if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 300 && y <= 400)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("MaximAB")+50, 335, "Maxim A si B");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("MaximAB")+50, 335, "Maxim A si B");
    }

    if(x >= screenWidth/2-textwidth("Construieste") && x <= screenWidth/2+textwidth("Construieste") && y >= 500 && y <= 600)
    {
        setcolor(3);
        outtextxy(screenWidth/2-textwidth("Construieste")+100, 535, "Suma 1 la X");
    }
    else
    {
        setcolor(WHITE);
        outtextxy(screenWidth/2-textwidth("Construieste")+100, 535, "Suma 1 la X");
    }
}
int main()
{

start:
    bool aplicareSalt = false;
    closegraph();
    initwindow(screenWidth,screenHeight, "MENU");
    cleardevice();
    initializareMeniu();

    do
    {
        menuCheck();
    }
    while(!d.butonMeniu);

    setbkcolor(0);
    if(d.butonMeniu == 3)
        aplicareSalt = true;

saltIncarcare:

    char caracterBloc;
    d.blStopImaginar.tip = 't';
    d.blStopImaginar.sfarsit = true;

    if(d.butonMeniu == 1)
    {
        d.butonMeniu = 0;
        d.butonBack = false;

        if(!aplicareSalt)
        {
            resetare();
            closegraph();
            initializareDiagrama();
            int idBloc1, idBloc2, punctLegatura1, punctLegatura2;
            int nrLegaturiDecizii = 0;
            butoaneOprite();
            outtextxy(20, 460, "Treci la urmatorul pas?");
            readimagefile("legaturiOFF.jpg", 20, 480, 170, 530);
            readimagefile("stergeOFF.jpg", 20, 660, 170, 710);


            desenareZonaValida(14);

            while(d.pasCurent)
            {
                d.butonSelectat = 0;
                do
                {
                    blocksCheck();
                }
                while(!d.butonSelectat && !d.punereBlocuri);

                if(d.butonSelectat == 10 && d.nrBlocuri)
                {
                    desenareZonaValida(14);

                    refacere(d.bloc[d.nrBlocuri], 0);
                    if(d.bloc[d.nrBlocuri].tip == 'd')
                        nrLegaturiDecizii--;
                    --d.nrBlocuriInput;
                    --d.nrBlocuri;
                    continue;
                }

                if(d.punereBlocuri == true)
                {
                    ++d.nrBlocuri;
                    if(caracterBloc == 'd')
                        nrLegaturiDecizii++;

                    punereBloc(d.bloc[d.nrBlocuri], 14, caracterBloc);


                    bool zonaDeAsezareBloc = true;
                    do
                    {
                        miscareBlocCuMouse(d.bloc[d.nrBlocuri], d.bloc[d.nrBlocuri].e.text, zonaDeAsezareBloc);
                    }
                    while(zonaDeAsezareBloc);
                }
                else
                {
                    blocSelectat(d.butonSelectat, caracterBloc);
                }

                for (int i = 1; i < d.nrBlocuri; i++)
                    refacere(d.bloc[i], 14);
            }
            delay(200);
            readimagefile("black.jpg", 20, 20, 170, 710);
            delay(0);

            d.nrLegaturi += (d.nrBlocuri - 1);
            d.nrLegaturi  += nrLegaturiDecizii;

            cout << "\nLEG: "<< d.nrLegaturi;
            d.contorLegaturi = 0;
            cout << "LEG intre blocuri:\n";

            do
            {
                deseneazaLegatura(d.bloc, idBloc1, punctLegatura1, idBloc2, punctLegatura2);

                ++d.contorLegaturi;
                d.leg[d.contorLegaturi].bloc1 = idBloc1;
                d.leg[d.contorLegaturi].bloc2 = idBloc2;

                d.leg[d.contorLegaturi].punct1 = punctLegatura1;
                d.leg[d.contorLegaturi].punct2 = punctLegatura2;

                if(d.bloc[idBloc1].tip == 't')
                {
                    d.bloc[idBloc1].urm = NULL;
                }
                else if(d.bloc[idBloc1].tip == 's')
                {
                    d.pozBlStart = idBloc1;
                    d.bloc[idBloc1].urm = &d.bloc[idBloc2];
                }
                else if(d.bloc[idBloc1].tip == 'd')
                {
                    if(punctLegatura1 == 2)
                    {
                        d.bloc[idBloc1].urmA = &d.bloc[idBloc2];
                    }
                    else if(punctLegatura1 == 3)
                    {
                        d.bloc[idBloc1].urmF = &d.bloc[idBloc2];
                    }
                }
                else d.bloc[idBloc1].urm = &d.bloc[idBloc2];

                if(d.bloc[idBloc2].repetitie == true)
                {
                    d.bloc[idBloc1].urm = &d.blStopImaginar;
                }

            }
            while (d.contorLegaturi < d.nrLegaturi);
        }
        else
        {
            for(int i = 1; i <= d.nrLegaturi; i++)
            {
                if(d.bloc[d.leg[i].bloc1].tip == 't')
                {
                    d.bloc[d.leg[i].bloc1].urm = NULL;
                }
                else if(d.bloc[d.leg[i].bloc1].tip == 's')
                {
                    d.pozBlStart = d.leg[i].bloc1;
                    d.bloc[d.leg[i].bloc1].urm = &d.bloc[d.leg[i].bloc2];
                }
                else if(d.bloc[d.leg[i].bloc1].tip == 'd')
                {

                    if(d.leg[i].punct1 == 2)
                    {

                        d.bloc[d.leg[i].bloc1].urmA = &d.bloc[d.leg[i].bloc2];
                    }
                    else if(d.leg[i].punct1  == 3)
                    {
                        d.bloc[d.leg[i].bloc1].urmF = &d.bloc[d.leg[i].bloc2];
                    }
                }
                else d.bloc[d.leg[i].bloc1].urm = &d.bloc[d.leg[i].bloc2];

                if(d.bloc[d.leg[i].bloc2].repetitie == 1)
                {
                    if(d.leg[i].punct2 == 0)
                        d.bloc[d.leg[i].bloc1].urm = &d.blStopImaginar;
                }
            }
        }

        for(int i = 1; i <= d.nrBlocuri; i++)
        {
            if(d.blc[i].intrari == 2)
            {
                if(d.bloc[i].tip != 't')
                {
                    d.bloc[d.blc[i].precedent[1]].urm = &d.blStopImaginar;
                    d.bloc[d.blc[i].precedent[2]].urm = &d.blStopImaginar;
                    d.bloc[d.blc[i].precedent[1]].salt = &d.bloc[i];
                    d.bloc[d.blc[i].precedent[2]].salt = &d.bloc[i];
                }
            }
        }
        desenareZonaValida(14);

        for(int i = 1; i <= d.nrBlocuri; i ++)
            if(d.bloc[i].tip != 't')
            {
                if(d.bloc[i].tip == 'd')
                {
                    cout <<d.bloc[i].tip <<" "<< d.bloc[i].urmA -> tip <<" SI ";
                    cout <<d.bloc[i].tip <<" "<< d.bloc[i].urmF -> tip <<"; ";
                }
                else cout <<d.bloc[i].tip <<" "<< d.bloc[i].urm -> tip <<"; ";
            }
        cout << endl;


        butoaneOprite();
        outtextxy(80, 460, "Diagrama in cod: ");
        readimagefile("codOFF.jpg", 20, 480, 170, 530);

        d.butonLegaturi = false;
        d.pasCurent = true;
        d.stergeBloc = false;
        d.butonSave = false;
        d.mutareBlocuri = false;
        while(d.pasCurent)
        {
            d.butonSelectat = 0;

            do
            {
                blocksCheck();
            }
            while(!d.butonSelectat && !d.mutareBlocuri);

            if(d.butonSave == true)
            {

                salvareDiagrama();
                d.butonSave = false;
            }
            if(d.mutareBlocuri == true)
            {
                d.FUNDAL = 15;
                drawLine(d.XLegFinala1,d.YLegFinala1,d.XLegFinala2,d.YLegFinala2, 15-d.FUNDAL,0);
                drawLine(d.XLegFinala1,d.YLegFinala1,d.XLegFinala2,d.YLegFinala2, 15-d.FUNDAL,1);
                restaureaza(d.bloc, 0);
                restaureaza(d.bloc, 1);
                if(aplicareSalt)
                {
                    butoaneOprite();
                    readimagefile("codOFF.jpg", 20, 480, 170, 530);
                }
                d.FUNDAL = 0;

                bool zonaDeMiscareBloc = true;
                while(zonaDeMiscareBloc)
                {
                    for(int i = 1; i <= d.nrBlocuri && zonaDeMiscareBloc; i++)
                    {
                        d.selectareBlocDiferit = false;
                        if(d.bloc[i].tip == caracterBloc)
                        {
                            do
                            {
                                miscareBlocCuMouse(d.bloc[i], d.bloc[i].e.text, zonaDeMiscareBloc);
                            }
                            while(!d.selectareBlocDiferit && zonaDeMiscareBloc);
                        }
                    }
                }
                desenareZonaValida(14);
                restaureaza(d.bloc, 0);
                restaureaza(d.bloc, 1);
            }
            else
            {
                blocSelectat(d.butonSelectat, caracterBloc);
            }
        }

        if(d.pozBlStart == -1)
        {
            printf("Diagrama incorecta - Nu contine bloc START");
            getch();
            closegraph();
            return 0;
        }

        ///codificare

        piesa *bl = &d.bloc[d.pozBlStart];
        setcolor(15);
        codificare(bl, 1);

        ///evaluare
        setcolor(7);
        line(0, d.yCod+5, 230, d.yCod+5);
        d.yCod += 25;
        if(!aplicareSalt)
        {
             evaluareExpresiiGasite();
        }
        else
        {
            if(d.butonIncarcare == 2)
            {
                setcolor(14);
                double A, B;
                char sir[30];
                strcpy(sir, "Citeste A: ");
                int x = d.xCod;
                outtextxy(x, d.yCod, sir);
                x += textwidth(sir);

                outtextxy(x, d.yCod, "_");
                strcpy(sir, "");
                citireText(x, d.yCod, sir);
                d.yCod += textheight("a");
                A = atof(sir);

                strcpy(sir, "Citeste B: ");
                x = d.xCod;
                outtextxy(x, d.yCod, sir);
                x += textwidth(sir);
                outtextxy(x, d.yCod, "_");
                strcpy(sir, "");
                citireText(x, d.yCod, sir);
                d.yCod += textheight("a");
                B  = atof(sir);
                if(A > B)
                {
                    outtextxy(d.xCod, d.yCod, "DA");
                }
                else outtextxy(d.xCod, d.yCod, "NU");
                setcolor(0);
            }
            else if(d.butonIncarcare == 3)
            {
                setcolor(14);
                char sir[30];
                strcpy(sir, "Citeste X: ");
                int x = d.xCod;
                outtextxy(x, d.yCod, sir);
                x += textwidth(sir);
                outtextxy(x, d.yCod, "_");
                strcpy(sir, "");
                citireText(x, d.yCod, sir);
                d.yCod += textheight("a");
                int X = atof(sir);
                int S = 0;
                for(int i = 1; i <= X; i++)
                    S += i;
                strcpy(sir, "");
                sprintf(sir, "Suma este: %d", S);
                outtextxy(d.xCod, d.yCod, sir);




                setcolor(0);
            }
        }

        do
        {
            backCheck();

        }
        while(!d.butonBack);

        if(d.butonBack)
        {
            aplicareSalt = false;
            goto start;
        }


        closegraph();
    }
    else if(d.butonMeniu == 2)
    {
        closegraph();
        initwindow(screenWidth,screenHeight,"InterSchem");
        instructiuni();
        d.butonBack = false;
        do
        {
            backCheck();

        }
        while(!d.butonBack);

        if(d.butonBack)
        {
            d.butonMeniu=0;
            goto start;
        }
        getch();
    }
    else if(d.butonMeniu == 3)
    {
        closegraph();

        initializareDiagrama();
        meniuIncarcare();
        d.butonBack = false;
        d.butonIncarcare = 0;
        do
        {
            incarcareCheck();

        }while(!d.butonIncarcare && !d.butonBack);

        if(d.butonBack)
        {
            aplicareSalt = false;
            d.butonMeniu = 0;
            closegraph();
            goto start;
        }

        if(d.butonIncarcare == 1)
        {
            closegraph();
            initializareDiagrama();

            d.xCod = 10;
            d.yCod = 45;
            aplicareSalt = true;
            d.butonMeniu = 1;

            incarcareDiagramaSalvata();

            goto saltIncarcare;
        }
        else if(d.butonIncarcare == 2)
        {
            closegraph();
            initializareDiagrama();

            d.xCod = 10;
            d.yCod = 45;
            aplicareSalt = true;
            d.butonMeniu = 1;

            incarcareMaxim();

            goto saltIncarcare;
        }
        else if(d.butonIncarcare == 3)
        {
            closegraph();
            initializareDiagrama();

            d.xCod = 10;
            d.yCod = 45;
            aplicareSalt = true;
            d.butonMeniu = 1;

            incarcareSuma();

            goto saltIncarcare;
        }




    }
    else if(d.butonMeniu == 4)
    {
        delay(200);
        resetare();
        closegraph();
    }



    return 0;
}
