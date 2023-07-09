#include<fstream.h>
#include<conio.h>
#include<graphics.h>
#include<string.h>

 int gd=DETECT, gm;

 struct neighbour
  {
    int r, l, u, d;
    neighbour()
     {
       r=l=u=d=0;
     }
  };

 struct data
  {
    char a[5], sym[5], name[15], mp[10], bp[10], dy[10], mass[8];
    data()
     {
       strcpy(a, "NULL");
       strcpy(sym, "NULL");
       strcpy(name, "NULL");
       strcpy(mp, "NULL");
       strcpy(bp, "NULL");
       strcpy(dy, "NULL");
       strcpy(mass, "NULL");
     }
  };

 class Element
  {
    int id, x, y, size, l, bk;
    data d;
    neighbour n;
   public:
    Element()
     {
       bk=0;
       x=y=-25;
       l=0;
       size=25;
     }

    char* getsym()     { return d.sym; }
    int getid()     { return id; }
    char *getano()  {  return d.a;  }
    char *getname()  {  return d.name;  }
    neighbour getnbr()     { return n; }

    void show(int);
    void show_data();

  }t[118], *cur=&t[0], *prev=&t[0];

 void Element::show_data()
  {
    int x1=470, y1=144;
    outtextxy(x1+67, y1-30, "Info");
    line(x1+64, y1-20, x1+100, y1-20);
    outtextxy(x1, y1, "Name:");
    outtextxy(x1+45, y1, d.name);
    outtextxy(x1, y1+20, "Atomic no:");
    outtextxy(x1+83, y1+20, d.a);
    outtextxy(x1, y1+40, "Mass:");
    outtextxy(x1+45, y1+40, d.mass);
    outtextxy(x1, y1+60, "MP(K):");
    outtextxy(x1+50, y1+60, d.mp);
    outtextxy(x1, y1+80, "BP(K):");
    outtextxy(x1+50, y1+80, d.bp);
    outtextxy(x1, y1+100, "Density(Kg):");
    outtextxy(x1+100, y1+100, d.dy);
  }

 void Element::show(int i=0)
  {
    int og=getcolor();
    rectangle( x-size/2, y-size/2, x+size/2, y+size/2);

    if(i==2)
     {
       setfillstyle(SOLID_FILL, bk);
       floodfill(x-size/2+1, y-size/2+1, WHITE);
       outtextxy(x-4*l, y-2, d.sym);
       return;
     }
    if(i==1)
      setcolor(BLUE);
    if(strcmpi(d.sym,"NULL")!=0)
      outtextxy(x-4*l, y-2, d.sym);

    setcolor(og);
  }

 void remove_sel()
  {
    setfillstyle(SOLID_FILL,getbkcolor());
    floodfill(565, 55, YELLOW);
    setcolor(WHITE);
    cur->show();
  }

 void remove_data()
  {
    setfillstyle(SOLID_FILL, getbkcolor());
    floodfill(561, 111, CYAN);
    setcolor(WHITE);
  }

 void display_sel()
  {
    int x=560, y=20, l=0;
    char c[5];
    strcpy(c, cur->getsym());
    l=strlen(c);
    settextstyle(0, 0, 2);
    outtextxy(x-7*l+25, y-7+25, c);
    settextstyle(0,0,0);
    int ogc=getcolor();
    setcolor(RED);
    cur->show(1);
    setcolor(ogc);
  }

 void gettable()
  {
    ifstream fin("Eledat.txt",ios::binary);

    Element e;
    for(int i=0; fin.read((char*)&e, sizeof(Element)); i++)
     {
       t[i]=e;
       t[i].show(2);
     }
    fin.close();
  }

 void frontpage()
  {
    ellipse( 40, 40, 270 , 360, 40, 40);
    ellipse( getmaxx()-40, 40, 180 , 270, 40, 40);
    ellipse( getmaxx()-40, getmaxy()-40, 90 , 180, 40, 40);
    ellipse( 40, getmaxy()-40, 0 , 90, 40, 40);

    line( 80, 40, getmaxx()-80, 40);
    line( 80, getmaxy()-40, getmaxx()-80, getmaxy()-40);
    line( 40, 80, 40, getmaxy()-80);
    line( getmaxx()-40, 80, getmaxx()-40, getmaxy()-80);

    ellipse( 40-5, 40-5, 270 , 360, 40, 40);
    ellipse( getmaxx()-40+5, 40-5, 180 , 270, 40, 40);
    ellipse( getmaxx()-40+5, getmaxy()-40+5, 90 , 180, 40, 40);
    ellipse( 40-5, getmaxy()-40+5, 0 , 90, 40, 40);

    line( 80-5, 40-5, getmaxx()-80+5, 40-5);
    line( 80-5, getmaxy()-40+5, getmaxx()-80+5, getmaxy()-40+5);
    line( 40-5, 80-5, 40-5, getmaxy()-80+5);
    line( getmaxx()-40+5, 80-5, getmaxx()-40+5, getmaxy()-80+5);

    setfillstyle( SOLID_FILL, LIGHTGRAY);
    floodfill( 80-5+2, 40-5+2, WHITE);

    settextstyle(7,0,6);
    setcolor(LIGHTRED);
    outtextxy(getmaxx()/2-190, getmaxy()/2-150, "Periodic Table");
    setcolor(WHITE);

    settextstyle(3,0,2);
    outtextxy( 280, getmaxy()-220, "Made by-");
    outtextxy( 380, getmaxy()-190, "Anshul Dhakar");
    outtextxy( 380, getmaxy()-160, "Prakhar Murary");
    outtextxy( 380, getmaxy()-130, "Apoorv Gupta");
    outtextxy( 380, getmaxy()-100, "Anushk Dua");

    settextstyle(0,0,0);
    setcolor(WHITE);
  }

 void main()
  {
    clrscr();
    initgraph(&gd, &gm, "\\turboc3\\bgi");

    frontpage();
    getch();
    setfillstyle(SOLID_FILL, getbkcolor());
    floodfill(0,0,YELLOW);

    gettable();

    outtextxy(480, 43, "SELECTED:");

    int oc=getcolor();
    settextstyle(7,0,2);
    setcolor(LIGHTCYAN);
    outtextxy(95, 5, "THE PERIODIC");
    outtextxy(150, 35,"TABLE");
    setcolor(LIGHTRED);
    line(92, 32, 250, 32);
    line(147, 62, 220, 62);
    setcolor(oc);
    settextstyle(0,0,0);

    outtextxy(10, 3, "1");
    outtextxy(35, 28, "2");
    outtextxy(60, 78, "3");
    outtextxy(85, 78, "4");
    outtextxy(110, 78, "5");
    outtextxy(135, 78, "6");
    outtextxy(160, 78, "7");
    outtextxy(185, 78, "8");
    outtextxy(210, 78, "9");
    outtextxy(232, 78, "10");
    outtextxy(257, 78, "11");
    outtextxy(282, 78, "12");
    outtextxy(307, 28, "13");
    outtextxy(332, 28, "14");
    outtextxy(357, 28, "15");
    outtextxy(382, 28, "16");
    outtextxy(407, 28, "17");
    outtextxy(432, 3, "18");

    int x1=460, y1=104;
    setcolor(CYAN);
    rectangle(x1, y1, getmaxx(), y1+160);
    setcolor(WHITE);

    outtextxy(0, 223, "Lanthanides:");
    outtextxy(15, 248, "Actinides:");

    outtextxy(0, getmaxy()-130, "Use W,A,S,D keys to choose an element");
    outtextxy(0, getmaxy()-110, "Press enter on a Element to get information");
    outtextxy(0, getmaxy()-90, "Press f to select search box. Enter the name, atomic no or symbol to search");
    outtextxy(0, getmaxy()-70, "Type \"esc\" to unselect the search box.");
    outtextxy(0, getmaxy()-50, "Press esc to end program");

    int x2=70, y2=190;
    outtextxy( 0, getmaxy()-180, "Search :");
    setcolor(LIGHTGRAY);
    rectangle( x2, getmaxy()-y2 , x2+120, getmaxy()-y2+30);
    setcolor(WHITE);
    outtextxy( x2+10, getmaxy()-y2+10, "SEARCH BOX");

    int x=560, y=20;
    int ogc=getcolor();

    setcolor(YELLOW);
    rectangle( x, y, x+50, y+50);
    cur->show();
    setcolor(ogc);
    display_sel();
    cur->show_data();

    int loop;
    char opt;
    neighbour nb;
    while(loop)
     {
       if(kbhit())
	{
	  opt=getch();
	  nb=cur->getnbr();
	  switch(opt)
	   {
	     case 13: if(prev->getid()==cur->getid())
			break;
		      remove_data();        //enter
		      cur->show_data();
		      prev=cur;
		      break;

	     case 27: loop=0;          //esc
		      break;

	     case 97: if(nb.l==-1)       //a
			break;
		      remove_sel();
		      prev=cur;
		      cur=&t[nb.l];
		      display_sel();
		      break;

	     case 100: if(nb.r==-1)       //d
			 break;
		       remove_sel();
		       prev=cur;
		       cur=&t[nb.r];
		       display_sel();
		       break;

	     case 119: if(nb.u==-1)       //w
			 break;
		       remove_sel();
		       prev=cur;
		       cur=&t[nb.u];
		       display_sel();
		       break;

	     case 115: if(nb.d==-1)       //s
			 break;
		       remove_sel();
		       prev=cur;
		       cur=&t[nb.d];
		       display_sel();
		       break;

	     case 102: int i, l=1;             //f
		       char inp[15], ch, opt[3];
		       cur->show();

		       repeat:
		       strcpy( inp, "NULL");
		       ch='a';
		       strcpy( opt, "N");

		       setcolor(RED);
		       rectangle( x2, getmaxy()-y2 , x2+120, getmaxy()-y2+30);
		       setcolor(WHITE);
		       setfillstyle( 1, getbkcolor());
		       floodfill( x2+2, getmaxy()-y2+2, RED);

		       for(i=0; ch!=13&&i<13; i++)
			{
			  ch=getch();
			  if(ch==13)      //enter
			   {
			     inp[i]='\0';
			     continue;
			   }
			  //*
			  if(ch==8&&i>0&&inp[0]!='\0')       //backspace
			   {
			     inp[--i]='\0';
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     outtextxy( x2+10, getmaxy()-y2+10, inp);
			     //outtextxy( getmaxx()/2, getmaxy()-y2+10, "H");
			     i--;
			     continue;
			   }
			  //*
			  inp[i]=opt[0]=ch;
			  opt[1]=inp[i+1]='\0';
			  outtextxy( x2+10+i*8, getmaxy()-y2+10, opt);
			}

		       if(inp[0]>=48&&inp[0]<=57)      //ifdigit
			{
			  if( strlen(inp)>=4 )
			   {
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     outtextxy( x2+10, getmaxy()-y2+10, "Renter");
			     getch();
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     goto repeat;
			   }

			  for(i=0; i<118&&l; i++)
			   {
			     if( strcmpi( t[i].getano(), inp)==0)
			      {
				if(i==cur->getid())
				 {
				   l=0;
				   break;
				 }
				cur=&t[i];
				remove_sel();
				if(prev->getid()==cur->getid())
				  break;
				remove_data();
				cur->show_data();
				prev=cur;
				l=0;
			      }
			   }
			  if(l)
			   {
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     outtextxy( x2+10, getmaxy()-y2+10, "Renter");
			     getch();
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     goto repeat;
			   }
			}
		       else   //means string as input
			{
			  if( strcmpi( inp, "esc")==0 )
			   {
			     display_sel();
			     setcolor(LIGHTGRAY);
			     rectangle( x2, getmaxy()-y2 , x2+120, getmaxy()-y2+30);
			     setcolor(WHITE);
			     break;
			   }

			  if(strlen(inp)<=2)
			   {
			     for(i=0; i<118&&l; i++)
			      {
				if( strcmpi( t[i].getsym(), inp)==0 )
				 {
				   if(i==cur->getid())
				    {
				      l=0;
				      break;
				    }
				   cur=&t[i];
				   remove_sel();
				   if(prev->getid()==cur->getid())
				     break;
				   remove_data();
				   cur->show_data();
				   prev=cur;
				   l=0;
				 }
			      }
			   }

			  for(i=0; i<118&&l; i++)
			   {
			     if(strlen( t[i].getname())==strlen(inp) )
			      {
			       if( strcmpi( t[i].getname(), inp )==0 )
				{
				  if(i==cur->getid())
				   {
				     l=0;
				     break;
				   }
				  cur=&t[i];
				  remove_sel();
				  if(prev->getid()==cur->getid())
				    break;
				  remove_data();
				  cur->show_data();
				  prev=cur;
				  l=0;
				}
			      }
			   }
			  if(l)
			   {
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     outtextxy( x2+10, getmaxy()-y2+10, "Renter");
			     getch();
			     setfillstyle( 1, getbkcolor());
			     floodfill( x2+2, getmaxy()-y2+2, RED);
			     goto repeat;
			   }
			}

		       display_sel();
		       setcolor(LIGHTGRAY);
		       rectangle( x2, getmaxy()-y2 , x2+120, getmaxy()-y2+30);
		       setcolor(WHITE);
		       break;
	   }
	}
     }

    outtextxy(0,getmaxy()-30, "Press any key to Exit");
    getch();
  }
