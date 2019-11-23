//wykona� Konrad Matusiak
#include<stdlib.h>			//dodaj� bibliotek� stdlib.h
#include<string.h>			//dodaj� bibliotek� string.h
#include<stdio.h>			//dodaj� bibliotek� stdio.h
#include<math.h>
/**************************************************************************/
typedef struct leaf{		//deklaruje typ zmiennej do budowy drzewa, zawiera on
struct	leaf *parent;		//wska�nik na poprzednik w�z�a
struct	leaf *Lson;			//wska�nik na lewy nast�pnik w�z�a
struct	leaf *Rson;			//wska�nik na prawy nast�pnik w�z�a
	int val;				//warto�� w�z�a
	int level;				//poziom w�z�a
	int wsp_rownowagi;		//wsp�czynnik r�wnowagi w�z�a

}tree;						//nazywam nowy typ tree



/**************************************************************************/


typedef struct queue{
struct queue *nast;
struct leaf *cell;

}queue;


/**************************************************************************/

//zmienne

queue *head,*wsk_q,*wsk_qlast;

int level;			//zmienna level do struktury leaf
int space;
int i;				//zmienna steruj�ca p�tl� for
int j;				//zmienna steruj�ca p�tl� for
int balans_check;
int menu;			//zmienna steruj�ca switchem
int wart;			//zmienna przechowuj�ca warto�� kt�ra ma zosta� dodana do w�z�a drzewa
int hold;			//zmienna przytrzymuj�ca dzia�anie switcha

int k;				//zmienna przytrzymuj�ca while'a dodaj�cego element do drzewa

int left;			//zmienna pomocnicza przy wyznaczaniu wsp�czynnik�w r�wnowagi
int right;			//zmienna pomocnicza przy wyznaczaniu wsp�czynnik�w r�wnowagi

int e;
int loper;
int key;			//zmienna przechowuje warto�� wez�a kt�rago wska�nik jest poszukiwany
int max;			//zmienna przechowuje wysoko�� drzewa
int wys;
int l;				//zmienna tymczasowo przechwuj�ca ilo�� lewych nast�pnik�w
int lw;				//zmienna przechowuj�ca ilo�� lewych nast�pnik�w
tree *node_A,*node_B,*node_B_synL,*node_B_synR,*prawe,*lewe, *node_C,*node_A_parent,*node_BR;	//deklaruje pomocnicze wska�niki w�z�a u�ywane przy funkcjach rotacji
tree *tmp,*node,*wsk;		//deklaruje wska�niki na elementy drzewa BST tmp,wsk2,node
tree *root,*obecny,*wsk2;				//deklaruje wska�nik na korze� drzewa , wska�niki pomocnicze obecny i wsk2

#define nullptr 0	//dla estetyki ustawiam jako wska�nik zerowy nullptr


/**************************************************************************/

void restore_parents(tree *root,tree *wsk,tree *wsk2)
{



	if(wsk!=root)
{
	wsk->parent=wsk2;
	}
	wsk2=wsk;

	if(wsk->Rson!=nullptr){
		restore_parents(root,wsk->Rson,wsk2);
	}


	if(wsk->Lson!=nullptr){
		restore_parents(root,wsk->Lson,wsk2);
	}





}//koniec deklaracji funkcji




//		tree *root,queue **wsk_qlast,queue **wsk_q


void print_from_top()  // TEST
{
                head=malloc(sizeof(queue));		//przypisuje pami�� g�owie koljeki
                head->cell=root;				//warto�ci� g�owy kolejki staje si� root
                head->nast=nullptr;				//nast�pnikiem jest nullptr

				wsk_q=head;						//ustawiam wska�nik obecnego wez�a i w�z�a ostatniego na g�owe kolejki( czyli root'a)
				wsk_qlast=head;
                

max=wys=inordermax(root,0);						//uzyskuje wysoko�� listy potrzebn� do oblicze�


max=pow(2,max+1);								//wyliczam maksymaln� ilo�� wez�ow w drzewie o danej wysoko�ci
    max=max-2;
    
    loper=0;									//ustawiam sw�j licznik na 0
    
    while(loper<max)
 {


        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej cz�sci listy ( lewy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						//je�li obecnie analizowany weze� nie jest zerem
{
    if(wsk_q->cell->Lson!=nullptr)				//j�sli lewy syn obecnego wez�a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Lson;		//to staje si� on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;				// je�li syn analizowanego w�z�a jest zerem to ostatni element kolejki te� jest zerem
        }
}
else{wsk_qlast->cell=nullptr;					//je�li analizowny w�ze� jest zerem to ostatni element kolejki te� jest zerem
}
        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej cz�sci listy ( prawy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						///je�li obecnie analizowany weze� nie jest zerem
{
    if(wsk_q->cell->Rson!=nullptr)				//j�sli lewy syn obecnego wez�a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Rson;		///to staje si� on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;			// je�li syn analizowanego w�z�a jest zerem to ostatni element kolejki te� jest zerem
        }
}else{
wsk_qlast->cell=nullptr;					//je�li analizowny w�ze� jest zerem to ostatni element kolejki te� jest zerem
}
    wsk_q=wsk_q->nast;						// przesuwam wska�nik analiwowanego w�z�a o 1 

loper=loper+2;								// zwi�kszam licznik o 2
 }		// koniec while

 //i wyswietlanie

 wsk_q=head;								// ustawiam wska�nik pomocniczy na g�ow� kolejki
 for(i=0;i<=wys;i++)						//ilo�� powt�rze� p�tli r�wna si� wysoko�ci mask. drzewa
 {
 	loper=pow(2,i);							//ilo�� w�z�ow na poziom r�wna si� 2 do pot�gi wysoko�ci 
  for(j=0;j<loper;j++)						//jak wy�ej
   {
    space=pow(2,wys-i);						// liczenie ilo�ci spacji ( dla przejrzysto�ci [cho� przy liczbach dwu cyfrowych drzewo nieco si� rozje�d�a])
    space=space-1;							// jak wy�ej

	for(k=0;k<space;k++){printf(" ");	}	//wy�wietl odpowiedni� ilo�� spacji

         if(wsk_q->cell!=nullptr)			//j�sli w�ze� kolejki nie jest r�wny nullptr
         { printf("%d ",wsk_q->cell->val); }//wy�wietl zawarto�� w�z�a

		 else{								//j�sli w�ze� kolejki jest r�wny nullptr wyswietl _
            printf("_ ");					//
             }
         for(k=0;k<space;k++){printf(" ");	}//wy�wietl drug� po�owe spacji

              wsk_q=wsk_q->nast;			//przesu� wska�nik kolejki o 1 weze�
     }
printf("\n");								// po zako�czeniu wypisywania poziomu enter

    }
               
            }

/**************************************************************************/

void root_balance()		//TEST
{
}


/**************************************************************************/

void general_AVL_function()		//TEST
{
}

/**************************************************************************/

//funkcja przypisuj�ca wsp�czynnik r�wnowagi do danego pojedy�czego w�z�a drzewa
void balance_asign(tree *wsk2)
{



if(wsk2->Lson!=nullptr)				//je�l w�ze� ma lewy nast�pnik  to:

{left=inordermax(wsk2->Lson,0)	;	//zapisz wynik funckji inorder max do zmiennej left (czyli najwi�ksza warto�� level w lewym poddrzewie
left=left-(wsk2->level);			//do zmiennej left zapisz warto�� left pomniejszon� o warto�� level obecnego korzenia
}
else{left=0;}						//je�li nie ma lwego nast�pnika to left =0

//level_asign(wsk2->Rson);
if(wsk2->Rson!=nullptr)				//je�l w�ze� ma prawy nast�pnik  to:

{right=inordermax(wsk2->Rson,0);	//zapisz wynik funckji inorder max do zmiennej prawy (czyli najwi�ksza warto�� level w prawym poddrzewie
right=right-(wsk2->level);			//do zmiennej prawy zapisz warto�� prawy pomniejszon� o warto�� level obecnego korzenia
}

else{right=0;}						//je�li nie ma lwego nast�pnika to right =0
wsk2->wsp_rownowagi=left-right;		//do zmiennej wsp�czynnik r�wnowagi wprowad� r�nic� left - right (czyli r�nic� d�ugo�ci poddrzew lewego i prawego)


}//koniec deklaracji funkcji

/**************************************************************************/

//przypisz ka�demu w�z�u warto�� wsp�czynnika r�wnowagi

void balance_asign_all(tree *wsk2)//deklaracji funkcji balance asign all
{


	balance_asign(wsk2);			//uruchom funkcj� przypisuj�c� wsp�czynnik r�wnowagi pojedy�czenia w�z�a

	if(wsk2->Lson!=nullptr)			//je�li isnieje lewy nast�pnik to
	{balance_asign_all(wsk2->Lson);	}		//wywowa� funkcj� inorder dla wska�nika na lewy nast�pnik



	if(wsk2->Rson!=nullptr)						//je�li isnieje prawy nast�pnik to
	{balance_asign_all(wsk2->Rson);	}					//wywowa� funkcj� inorder dla wska�nika na prawy nast�pnik


}		//koniec deklaracji funkcji



/**************************************************************************/
//funkcja r�wnowa��ca drzewo avl, nie dzia�a dla root'a
//wsk2=root;
void balancing(tree *wsk2, tree* root,tree * lewe,tree * prawe)
{

node_A_parent=wsk2->parent;


if((wsk2->wsp_rownowagi==-2)&&((prawe->wsp_rownowagi)==1))//RL
{

right_right(wsk2->Rson,root);

//left_left(wsk2,root);
}
//rozpatrywanie rotacji podwojnej Rl


if((wsk2->wsp_rownowagi==2)&&(lewe->wsp_rownowagi==-1))//LR
{

left_left(wsk2->Lson,root);

//right_right(wsk2,root);
}
//ropatrywanie rotacji podwojnej LR


if((wsk2->wsp_rownowagi<=-2)	)		//jesli wsp�czynnik r�wnowagi jest wi�kszy lub r�wny 2 (prawe poddrzewo jest d�u�sze od lewego o 2
{

	left_left(wsk2,root);			//wywo�aj funkcj� left_left (wykonaj rotacj� w lewo)
}

if(wsk2->wsp_rownowagi>=2)			//jesli wsp�czynnik r�wnowagi jest mniejszy lub r�wny 2 (prawe poddrzewo jest d�u�sze od lewego o 2
{
	right_right(wsk2,root);			//wywo�aj funkcj� right_right (wykonaj rotacj� w prawo)

}



}//koniec deklaracji funkcji

//*************************************************

int check_balance(tree * root, int balans_check)
{
	if(((root->wsp_rownowagi)>=2)||((root->wsp_rownowagi)<=-2))
	{balans_check=0; return balans_check; 	}

	else
{
balans_check=1;

	if(root->Lson!=nullptr)
	{balans_check=check_balance(root->Lson,balans_check);	}

	if(root->Rson!=nullptr)

	{balans_check=check_balance(root->Rson,balans_check);	}
}
	return balans_check;
}


//**************************************************************************

void balancing_all(tree * wsk2,tree * root)//deklaracja funckji balancing all (z wyj�tkiem root'a)
{


if(wsk2->Lson!=nullptr)					//j�li istnieje lewy nast�pnik obecnego wez�a
{balancing_all(wsk2->Lson,root);}		//wywo�aj funckj� balancing _all dla lewego nast�pnika obecnego w�z�a

	if(wsk2->Rson!=nullptr)				//j�li istnieje prawy nast�pnik obecnego wez�a
{balancing_all(wsk2->Rson,root);}		//wywo�aj funckj� balancing _all dla prawego nast�pnika obecnego w�z�a

lewe=wsk2->Lson;
prawe=wsk2->Rson;		//jyyyyyyyyyyyyyyyyyssssssssssssssssssssssss

balancing(wsk2,root,lewe,prawe);					//wywo�aj funckj� r�wnowa�enia pojedynczego w�z�a dla obecnego w�z�a

}			//koniec deklaracji funkcji

/**************************************************************************/

void right_right(tree *wsk2,tree *root)			//deklaracja funkcji rotacji w prawo(nie dla korzenia)
{
	node_A=wsk2;					//ustawiam wska�nik pomocniczy na w�ze� na kt�rym wykonuj� rotacje
node_B=wsk2->Lson;					//ustawiam wska�nik pomocniczy node_B na lewy nast�pnik wska�nika na kr�rym wykoujemy rotacje

if(wsk2->parent->Rson==wsk2)		//jesli wska�nik na kt�rym dokonujemy roatcji jest czyim� prawym nastepnikiem to:
	{
		node_A->parent->Rson=node_B;	//ustawiamy wska�nik na prawy nast�pnik rodzica node_A na node_B

		node_A->Lson=node_B->Rson;		//ustawiamy wska�nik lewego nast�pnika node_A na node_B
	//	node_B_synR->parent=node_A;
		node_B->Rson=node_A;	//ustawiam wska�nik prawego nast�pnika node_B na swojego rodzica czyli node_A
		node_B->parent=node_A->parent;	//rodzicem node_B staje si� rodzic node_A

		node_A->parent=node_B;		//rodzicem node_A staje si� node_B

	}
	else			//jesli wska�nik na kt�rym dokonujemy roatcji jest czyim� lewym nastepnikiem to:
	{
		node_A->parent->Lson=node_B;			//ustawiamy wska�nik na lewy nast�pnik rodzica node_A na node_B

		node_A->Lson=node_B->Rson;				//ustawiamy wska�nik lewego nast�pnika node_A na node_B
//node_B_synL->parent=node_A;
		node_B->Rson=node_B->parent;			//ustawiam wska�nik prawego nast�pnika node_B na swojego rodzica czyli node_A
		node_B->parent=node_A->parent;			//rodzicem node_B staje si� rodzic node_A

		node_A->parent=node_B;					//rodzicem node_A staje si� node_B

	}

root->level=0;level_asign(root);			//na nowo przypisuj� warto�� wysoko�ci wszystkich w�z��w

balance_asign_all(root);		//na nowo przypisuj� wsp�czynniki r�wnowagi

root->level=0;level_asign(root);

}		//koniec deklaracji funkcji

/**************************************************************************/

/**************************************************************************/
void left_left(tree *wsk2,tree *root)		//deklaracja funckji rotacji w lewo(nie dla korzenia)
{

node_A=wsk2;								//ustawiam wska�nik pomocniczy node_A na w�ze� wok� kt�rego b�dziemy robi� rotacj�
node_B=wsk2->Rson;							//ustawiam wska�nik pomocniczy na prawy nast�pnik node_A
node_BR=node_B->Lson;
if(wsk2->parent->Rson==wsk2)				//je�li node_A jest prawym nast�pnikiem to:
{
node_A->parent->Rson=node_B;		//ustawiamy wska�nik na prawy nast�pnik rodzica nde_A na node_B
//node_BR->parent=node_A;			//DZIA�AJ
node_A->Rson=node_B->Lson;			//lewy nastepnik node_B staje si� prawym nast�pnikiem node_A

node_B->Lson=node_A;		//rodzi� node_B staje lewym nast�pnikiem node_B
node_B->parent=node_A->parent;		//rodzicem node_B staje si� rodzic node_A
node_A->parent=node_B;				//rodzicem node_A stajenssi� node_B



}
else						//je�li node_A jest lweym nast�pnikiem to:
{
node_A->parent->Lson=node_B;	//ustawiam wskaxnik lewego nast�pnika rodzica node_A na node_B

node_A->Rson=node_B->Lson;		//lewy nast�pnik node_B staje si� prawym nast�pnikiem node_A
//node_B->Lson->parent=node_A;
node_B->Lson=node_A;		//rodzic node_B staje si� lewym nast�pnikiem node_B
node_B->parent=node_A->parent;		//rodzicem node_A staje si� rodzic node_B
node_A->parent=node_B;				//rodzicem node_A staje si� node_B


}

root->level=0;level_asign(root);		//na nowo przypisuj� poziomy w�z��w
balance_asign_all(root);		// na nowo przypisuj� wsp�czynniki r�wowagi

root->level=0;level_asign(root);

}//konie deklaracji funkcji rotacji

/**************************************************************************/


/**************************************************************************/


//dlugosc poddrzewa

int inordermax(tree *wsk2,int max)
{	//deklaracja funkcji obliczaj�cej wysoko�� poddrzewa o korzeniu w wsk2 z argumentami wsk2 i licznikiem wyskoko�ci drzewa max


	if(wsk2->Lson!=nullptr)						//je�li istnieje lewy nat�pnik
	{max=inordermax(wsk2->Lson,max);	}		//przypisz licznikowi wynik funkcji inordermax



	if(wsk2->Rson!=nullptr)						//je�li istnieje lewy nat�pnik
	{max=inordermax(wsk2->Rson,max);	}		//przypisz licznikowi wynik funkcji inordermax

	if(max<wsk2->level){max=wsk2->level;}		//je�li warto�� poziomu obecnego w�z�a jestwi�ksza od obecnej warto�ci max to ustaw warto�� max na warto�� level

return max;										//zwr�� warto�� zmiennej max


}//koniec deklaracji funkcji

/**************************************************************************/








/**************************************************************************/

//wyszukiwanie klucza w poddrzewie zwraca wskaznik na klucz

struct tree *search(tree *obecny,int key)//deklaracja funckji wyszukuj�cej wska�nik drzewa BST na podstawie podanego klucza

{//	obecny=root;//umiescic przed wywo�aniem funckji


if(key==obecny->val)			//je�li warto�� w�z�a i klucza s� takie same to:
		{

		return obecny;			//zwr�� wska�nik na obecny element

		}
		else{					//w przeciwnym przypadku to:


	if(key>obecny->val)			//sprawd� czy warto�� klucza jest wieksza od warto�ci obecnego  w�z�a je�li tak to:
		{

			if(obecny->Rson!=nullptr)		//je�li istnieje prawy nastepnik
			{
			obecny=search(obecny->Rson,key);//uruchom funkcj� search dla poddrzewa z korzeniem w prawym nast�pniku
			}
			else		//je�li nie ma prawego nast�pnika to:
			{printf("W drzewie nie ma takiego wez�a"); 	}		//wy�wietl komunikat
		}

	if(key<obecny->val)							//sprawd� czy warto�� klucza jest mniejsza od warto�ci obecnego  w�z�a je�li tak to:
		{

			if(obecny->Lson!=nullptr)			//je�li istnieje lewy nastepnik
			{
			obecny=search(obecny->Lson,key);	//uruchom funkcj� search dla poddrzewa z korzeniem w lewym nast�pniku
			}
			else									//je�li nie ma lewego nast�pnika to:
			{printf("W drzewie nie ma takiego wez�a"); 	}	//wy�wietl komunikat
		}
}





	return obecny;			//zwr��  wska�nik na w�ze� z szukanym kluczem
}//koniec deklaracji funkcji

/**************************************************************************/



//wypisuje poprzecznie drzewo

int printopronto(int e,tree *wsk2)					//deklaracja funkcji rysowania drzewa z z argumentami :e-warto�� steruj�ca spacjami,wsk2 wska�nik na rysowane poddrzewa
{
int i;						//zmienna steruj�ca p�tl� for
  if(!wsk2) return;			//jesli nie istnieje poddrzewa  okorzeniu wsk2 wyjd� z funkcji
  printopronto(e+1,wsk2->Rson);		//wywo�aj funkcj� printopronto ze zwi�kszonym ilo�ci� spacji dla drzewa z korzeniem wsk2->Rson
  for(i=0; i<e; ++i){				//wykonaj e spacji
   printf("     ");}				//wy�wietl spacje
  printf("%d (%d)\n ", wsk2->val,wsk2->parent->val );	//wy�wietl warto�� obecnego wez�a i jego wysoko�� w drzewie
  printopronto(e+1,wsk2->Lson);					//wywo�aj funkcj� printopronto ze zwi�kszonym ilo�ci� spacji dla drzewa z korzeniem wsk2->Lson

}//koniec deklaracji funkcji

/**************************************************************************/
//root->level=0;level_asign(root);
void level_asign(tree *wsk2)
{


		if(wsk2->Lson!=nullptr)				//jesli istnieje lewy nast�pnik w�z�a to:
		{wsk2->Lson->level=(wsk2->level)+1;level_asign(wsk2->Lson);}			//ustaw wysoko�� lewego nast�pnika wsk2 na wysoko�� wsk2 zwi�kszon� o 1

			if(wsk2->Rson!=nullptr)			//jesli istnieje prawy nast�pnik w�z�a to:
		{wsk2->Rson->level=(wsk2->level)+1;level_asign(wsk2->Rson);}			//ustaw wysoko�� prawego nast�pnika wsk2 na wysoko�� wsk2 zwi�kszon� o 1


}//koniec deklaracji funkcji


//funckja przypisuje na nowo warto�ci level pocz�wszy od wskazanego wez�a by odczyta� warto�ci poddrzew poczynaj�c od danego w�z�a
//funkcja nie dzia�a dla root'a


//***************************************************************************************************

//***************************************************************************************************


int main()			//pocz�tek funkcji g�ownej
{


	balans_check=0;


	printf("Podaj wartosc korzenia\n");		//wy�wietl komunikat dla u�ytkownika
	scanf("%d",&wart);						//wprowad� warto�� korzenia

	
	root=malloc(sizeof(tree));				//przydziel pami�� rozmiaru w�z�a drzewa dla korzenia
	root->parent=root;					//ustawiam wska�nik na rodzica korzenia na 0
	root->Lson=nullptr;						//ustawiam wska�nik na lewy nast�pnik korzenia na 0
	root->Rson=nullptr;						//ustawiam wska�nik na prawy nast�pnik korzenia na 0
	root->val=wart;							//ustawiam warto�� korzenia na warto�� wprowadzon� do zmiennej wart
	root->level=0;							//ustawiam poziom korzenia na 0
	root->wsp_rownowagi=0;					//ustawiam wsp�czynnik r�wnowagi korzenia na 0

	hold=0;										//ustawiam zmienn� hold na 0

while(hold==0)
{   printf("\n MENU:\n 1.dodaj nowy wezel\n 2.Wyswietl drzewo poprzecznie\n 3.podaj wspolczynnik rownowagi wybranego wezla\n 4.Wyjdz z programu\n 5.wyswietl z gory na dol \n 6.usun wybrany wezel (najmniejszy elem. praw. drzewa) \n 7.usun wybrany wezel (najwiekszy elem. lew. drzewa) \n ");//wy�wietl opcje dla u�ytkownika
	printf("8.Odtw�rz korzen(koncepcja) \n 9. Zniszcz drzewo(koncepcja)  \n 10.Sprawdz rownowage \n");


	scanf("%d",&menu);			//pobierz warto�� zmiennej steruj�cej switchem


	switch(menu)				//prze��cznik sterowany zmienn� menu

	{




		case 1://dodaj element do drzewa
	{
	printf("Podaj wartosc nowego wezla\n");

		scanf("%d",&wart);				//pobieram wartosc dla nowego w�z�a
		obecny=root;					//ustawiam wska�nik iteruj�cy na korze�

		if(obecny->val==wart)			//je�li warto�� podana wyst�puje ju� w korzeniu wy�wietlany jest komunikat
		{printf("Drzewo nie moze miec 2 wezlow o takiej samej wartosci\n");break;	}	//oraz przerywana jest akcja dodawania we��a


		k=0;								//zmienna przytrzymuj�ca p�tle while
		while(k!=1)							//je�li nie niej r�wne 1 wykonuj p�tle
		{
			if(obecny->val==wart)			//je�li podana warto�� wyst�puje ju� na obecnym we�le to anuluj akcj� dodawania w�z�a
		{printf("Drzewo nie moze miec 2 wezlow o takiej samej wartosci\n");break;} 			//wy�wietla komunikat o przerwaniu



		if((wart<obecny->val)&&(obecny->Lson==nullptr))//gdy warto�� tworzonego w�z�a jest mniejsza od obecnego w�z�a oraz  obecny w�ze� nie ma lewego nast�pnika wykonaj nast�puj�ce dzia�ania
		{

		tmp=obecny;										//ustawiam wska�nik tymczasowy na obecny
		obecny->Lson=malloc(sizeof(tree));				//alokuje pamie� rozmiaru w�z�a drzewa dla lewego nast�pnika obecnego w�z�a
		obecny=obecny->Lson;							//ustawiam wska�nik obecny na lewy nast�pnik
		obecny->parent=tmp;								//przypisuje wska�nik na rodzica
		obecny->val=wart;								//przypisuje warto�� int dla nowego w�z�a
		obecny->Lson=nullptr;							//ustawiam wska�nik lewego nat�pnika na NULL
		obecny->Rson=nullptr;							//ustawiam wska�nik prawego nat�pnika na NULL
		obecny->level=1+(obecny->parent->level);		//ustawiam wysoko�� na wysoko�� rodzica +1

		break;											//wyjd� z p�tli while
		}

		if((wart>obecny->val)&&(obecny->Rson==nullptr))//gdy warto�� tworzonego w�z�a jest wi�ksza od obecnego w�z�a oraz  obecny w�ze� nie ma prawego nast�pnika wykonaj nast�puj�ce dzia�ania
		{

		tmp=obecny;										//ustawiam wska�nik tymczasowy na obecny
		obecny->Rson=malloc(sizeof(tree));				//alokuje pamie� rozmiaru w�z�a drzewa dla prawego nast�pnika obecnego w�z�a
		obecny=obecny->Rson;							//ustawiam wska�nik obecny na prawy nast�pnik
		obecny->parent=tmp;								//przypisuje wska�nik na rodzica
		obecny->Rson=nullptr;							//ustawiam wska�nik prawego nat�pnika na NULL
		obecny->Lson=nullptr;							//ustawiam wska�nik lewego nat�pnika na NULL
		obecny->val=wart;								//przypisuje warto�� int dla nowego w�z�a
		obecny->level=1+(obecny->parent->level);		//ustawiam wysoko�� na wysoko�� rodzica +1

		break;											//wyjd� z p�tli while
		}

		if((wart>obecny->val)&&(obecny->Rson!=nullptr))	//je�li nowa warto�� jest wi�ksza od obecnego w�z�a ale istnieje ju� prawy nast�pnik to wykonaj:
		{obecny=obecny->Rson;		}					//ustaw wska�nik obecny na prawy nast�pnik

		if((wart<obecny->val)&&(obecny->Lson!=nullptr))	//je�li nowa warto�� jest wi�ksza od obecnego w�z�a ale istnieje ju� lewy nast�pnik to wykonaj:
		{obecny=obecny->Lson;		}					//ustaw wska�nik obecny na lewy nast�pnik





	}//koniec peli while

//******************************************************************
//sprawdzenie wsp�czynnika r�wnowagi


//balans_check=check_balance(root,balans_check);

//printf("%d",balans_check);




root->level=0;
level_asign(root);

wsk2=root;						//ustaw wska�nik pomocniczy wsk2 na root
balance_asign_all(wsk2);		//poczynaj�c od wsk2 przypisz warto�ci wsp�czynnik�w r�wnowagi

root->level=0;
level_asign(root);

if(root->Lson!=nullptr)			//je�li istnieje lewy nastpnik korzenia to:
	{
		wsk2=root->Lson;				//ustaw wska�nik pomocniczy wsk2 na lewy nast�pnik korzenia
		balancing_all(wsk2,root);
	}		//uruchom funkcj� r�wnowa�enia dla drzewa o korzeniu root poczynaj�c od poddrzewa o korzeniu wsk2

root->level=0;
level_asign(root);

if(root->Rson!=nullptr)			//je�li istnieje prawy nastpnik korzenia to:
	{
		wsk2=root->Rson;				//ustaw wska�nik pomocniczy wsk2 na prawy nast�pnik korzenia
		balancing_all(wsk2,root);
	}		//uruchom funkcj� r�wnowa�enia dla drzewa o korzeniu root poczynaj�c od poddrzewa o korzeniu wsk2

root->level=0;
level_asign(root);




root->level=0;
level_asign(root);					//na nowo przypisz warto�ci wysoko�ci w�z��w

balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w


root->level=0;
level_asign(root);



//***************************************************
//r�wnowa�eniu korzenia


if((root->Rson!=nullptr)&&(root->wsp_rownowagi<=-2)&&(((root->wsp_rownowagi)*(root->Rson->wsp_rownowagi))==-2))

	{ 
		right_right(root->Rson,root);
		balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
		root->level=0;level_asign(root);
	}

if((root->Lson!=nullptr)&&(root->wsp_rownowagi>=2)&&(((root->wsp_rownowagi)*(root->Lson->wsp_rownowagi))==-2))
{left_left(root->Lson,root);


balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);
}

if(root->wsp_rownowagi<=-2)		//je�li prawe popddrzewo jest wi�ksze od lewego o conajmniej  2 w�z�y
{

	node_A=root;				//zapisuje obecny korze� do wska�nika pomocniczego node_A


root=root->Rson;				//ustawiam korze� an prawy nast�pnik korzenia



node_A->Rson=root->Lson;		//prawym nast�pnikiem node_A staje sie lewy nast�pnik  obecnego korzenia

root->Lson=root->parent;		//nowym lewym nast�pnikiem staje si� rodzic owego root'a

node_A->parent=root;			//rodzicem node_A staje si� korze�


}

if(root->wsp_rownowagi>=2)		//je�li lewe popddrzewo jest wi�ksze od prawego o conajmniej  2 w�z�y
{


node_A=root;					//zapisuje obecny korze� do wska�nika pomocniczego node_A


root=root->Lson;


		node_A->Lson=root->Rson;		//lewym nast�pnikiem node_A staje si� prawy nast�pnik nowego root'a
	
		root->Rson=root->parent;		//prawym nast�pnikiem nowego korzenia staje si� jego by�y rodzic
		

		node_A->parent=root;			//nowym rodzicem node_A staje si� nowy korze� drzewa





}






//*****************************************************

root->level=0;level_asign(root);					//na nowo przypisz warto�ci wysoko�ci w�z��w
balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);

balans_check=check_balance(root,balans_check);

printf("%d",balans_check);

wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);




break;//wyjd� z case'a
	}	// koniec case 0




/**************************************************************************/



	case 2:{//wyswietl bokiem
		wsk2=root;		//ustaw wska�nik wsk2 na korze�
		int e=0;		// ustaw zmienn� steruj�ca spacjami na 0
	printopronto(e,wsk2);	//uruchom funkcj� wypisania printopronto

	break;				//wyjd� z case'a
	}//koniec case 3

/**************************************************************************/


	case 4:{//wyjscie z programu
	hold=1;			//ustaw zmienn� hold na 1 co ko�czy p�tle while
		break;		//wyjd� z case'a
	}	//koniec case 8


/**************************************************************************/

case 3:{//wy�wietlanie wsp�czynnik�w r�wnowagi
printf("\n Podaj klucz wezla by uzyskac jego wspolczynnik rownowagi\n ");//wy�wietl komunikat
	scanf("%d",&key);		//wprowadzanie kluczprzez u�ytkownika
	obecny=root;			//ustawiam wska�nik obecny na korze� drzewa
	obecny=search(obecny,key);	//zapisuje do wskaxnika obecny wynik funckji zwracaj�cej wska�nik na szukany w�ze�

	printf("Wspolczynnik rownowagi wezla %d rowna sie [%d]",obecny->val,obecny->wsp_rownowagi);		//wy�wietl komunikat z wynikiem


	break;		 //wyjd� ze switcha
} 		//koniec case'a

/**************************************************************************/



case 5:{// wypisanie z gory na dol

                head=malloc(sizeof(queue));		//przypisuje pami�� g�owie koljeki
                head->cell=root;				//warto�ci� g�owy kolejki staje si� root
                head->nast=nullptr;				//nast�pnikiem jest nullptr

				wsk_q=head;						//ustawiam wska�nik obecnego wez�a i w�z�a ostatniego na g�owe kolejki( czyli root'a)
				wsk_qlast=head;
                

max=wys=inordermax(root,0);						//uzyskuje wysoko�� listy potrzebn� do oblicze�


max=pow(2,max+1);								//wyliczam maksymaln� ilo�� wez�ow w drzewie o danej wysoko�ci
    max=max-2;
    
    loper=0;									//ustawiam sw�j licznik na 0
    
    while(loper<max)
 {


        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej cz�sci listy ( lewy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						//je�li obecnie analizowany weze� nie jest zerem
{
    if(wsk_q->cell->Lson!=nullptr)				//j�sli lewy syn obecnego wez�a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Lson;		//to staje si� on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;				// je�li syn analizowanego w�z�a jest zerem to ostatni element kolejki te� jest zerem
        }
}
else{wsk_qlast->cell=nullptr;					//je�li analizowny w�ze� jest zerem to ostatni element kolejki te� jest zerem
}
        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej cz�sci listy ( prawy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						///je�li obecnie analizowany weze� nie jest zerem
{
    if(wsk_q->cell->Rson!=nullptr)				//j�sli lewy syn obecnego wez�a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Rson;		///to staje si� on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;			// je�li syn analizowanego w�z�a jest zerem to ostatni element kolejki te� jest zerem
        }
}else{
wsk_qlast->cell=nullptr;					//je�li analizowny w�ze� jest zerem to ostatni element kolejki te� jest zerem
}
    wsk_q=wsk_q->nast;						// przesuwam wska�nik analiwowanego w�z�a o 1 

loper=loper+2;								// zwi�kszam licznik o 2
 }		// koniec while

 //i wyswietlanie

 wsk_q=head;								// ustawiam wska�nik pomocniczy na g�ow� kolejki
 for(i=0;i<=wys;i++)						//ilo�� powt�rze� p�tli r�wna si� wysoko�ci mask. drzewa
 {
 	loper=pow(2,i);							//ilo�� w�z�ow na poziom r�wna si� 2 do pot�gi wysoko�ci 
  for(j=0;j<loper;j++)						//jak wy�ej
   {
    space=pow(2,wys-i);						// liczenie ilo�ci spacji ( dla przejrzysto�ci [cho� przy liczbach dwu cyfrowych drzewo nieco si� rozje�d�a])
    space=space-1;							// jak wy�ej

	for(k=0;k<space;k++){printf(" ");	}	//wy�wietl odpowiedni� ilo�� spacji

         if(wsk_q->cell!=nullptr)			//j�sli w�ze� kolejki nie jest r�wny nullptr
         { printf("%d ",wsk_q->cell->val); }//wy�wietl zawarto�� w�z�a

		 else{								//j�sli w�ze� kolejki jest r�wny nullptr wyswietl _
            printf("_ ");					//
             }
         for(k=0;k<space;k++){printf(" ");	}//wy�wietl drug� po�owe spacji

              wsk_q=wsk_q->nast;			//przesu� wska�nik kolejki o 1 weze�
     }
printf("\n");								// po zako�czeniu wypisywania poziomu enter

    }
                break;
            }// koniec case'a

  //********************************************************************************************************************

    case 6:{// usuwanie wezla najmniejszy z prawego poddrzewa

    	scanf("%d",&key);		//wprowadzanie kluczprzez u�ytkownika
	obecny=root;			//ustawiam wska�nik obecny na korze� drzewa
	obecny=search(obecny,key);

if((obecny->Rson!=nullptr)&&(obecny->Lson!=nullptr))		//dla wez�ow z dwoma potomkami
{
	wsk=obecny;

wsk=wsk->Rson;

	while(wsk->Lson!=nullptr)
	{

	wsk=wsk->Lson;

	}

if(wsk->parent==obecny)
{
	obecny->val=wsk->val;
	obecny->Rson=nullptr;
	//free(wsk);
}
else
{
	if(wsk->Rson!=nullptr){
		
		wsk->parent->Lson=wsk->Rson;
	}else{
		
		wsk->parent->Lson=nullptr;
	}
	
	
	obecny->val=wsk->val;
	
}








}
else
{

if(obecny->parent->Rson==obecny)			//dla prawego syna
{

if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))
{
	obecny->parent->Rson=nullptr;
	//free(obecny);

}






if((obecny->Rson!=nullptr)&&(obecny->Lson==nullptr))
{
	obecny->parent->Rson=obecny->Rson;
	//	free(obecny);



}



if((obecny->Rson==nullptr)&&(obecny->Lson!=nullptr))
	{


	obecny->parent->Rson=obecny->Lson;
	//	free(obecny);



	}






}else{	// dla lewego syna ***************************************


if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	// �adnego potomka
{
	obecny->parent->Lson=nullptr;
//	free(obecny);

}






if((obecny->Rson!=nullptr)&&(obecny->Lson==nullptr))			//tylko lewy potomek
{
	obecny->parent->Lson=obecny->Rson;
	//	free(obecny);
}



if((obecny->Rson==nullptr)&&(obecny->Lson!=nullptr))		//tylko prawy potomek
{
	obecny->parent->Lson=obecny->Lson;
	//	free(obecny);
}






}// koniec opcji dla lewego syna
}
    wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);
			
			
			
		root->level=0;level_asign(root);

wsk2=root;						//ustaw wska�nik pomocniczy wsk2 na root
balance_asign_all(wsk2);		//poczynaj�c od wsk2 przypisz warto�ci wsp�czynnik�w r�wnowagi

root->level=0;level_asign(root);

if(root->Lson!=nullptr)			//je�li istnieje lewy nastpnik korzenia to:
{wsk2=root->Lson;				//ustaw wska�nik pomocniczy wsk2 na lewy nast�pnik korzenia
balancing_all(wsk2,root);}		//uruchom funkcj� r�wnowa�enia dla drzewa o korzeniu root poczynaj�c od poddrzewa o korzeniu wsk2

root->level=0;level_asign(root);

if(root->Rson!=nullptr)			//je�li istnieje prawy nastpnik korzenia to:
{
wsk2=root->Rson;				//ustaw wska�nik pomocniczy wsk2 na prawy nast�pnik korzenia
balancing_all(wsk2,root);}		//uruchom funkcj� r�wnowa�enia dla drzewa o korzeniu root poczynaj�c od poddrzewa o korzeniu wsk2

root->level=0;level_asign(root);




root->level=0;level_asign(root);					//na nowo przypisz warto�ci wysoko�ci w�z��w
balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);



//***************************************************
//r�wnowa�eniu korzenia


if((root->Rson!=nullptr)&&(root->wsp_rownowagi<=-2)&&(((root->wsp_rownowagi)*(root->Rson->wsp_rownowagi))==-2))

{ right_right(root->Rson,root);


balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);
}

if((root->Lson!=nullptr)&&(root->wsp_rownowagi>=2)&&(((root->wsp_rownowagi)*(root->Lson->wsp_rownowagi))==-2))
{left_left(root->Lson,root);


balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);
}

if(root->wsp_rownowagi<=-2)		//je�li prawe popddrzewo jest wi�ksze od lewego o conajmniej  2 w�z�y
{

	node_A=root;				//zapisuje obecny korze� do wska�nika pomocniczego node_A


root=root->Rson;				//ustawiam korze� an prawy nast�pnik korzenia



node_A->Rson=root->Lson;		//prawym nast�pnikiem node_A staje sie lewy nast�pnik  obecnego korzenia

root->Lson=root->parent;		//nowym lewym nast�pnikiem staje si� rodzic owego root'a

node_A->parent=root;			//rodzicem node_A staje si� korze�


}

if(root->wsp_rownowagi>=2)		//je�li lewe popddrzewo jest wi�ksze od prawego o conajmniej  2 w�z�y
{


node_A=root;					//zapisuje obecny korze� do wska�nika pomocniczego node_A


root=root->Lson;


		node_A->Lson=root->Rson;		//lewym nast�pnikiem node_A staje si� prawy nast�pnik nowego root'a
	
		root->Rson=root->parent;		//prawym nast�pnikiem nowego korzenia staje si� jego by�y rodzic
		

		node_A->parent=root;			//nowym rodzicem node_A staje si� nowy korze� drzewa





}






//*****************************************************

root->level=0;level_asign(root);					//na nowo przypisz warto�ci wysoko�ci w�z��w
balance_asign_all(root);				//przypisz wsp�czynniki r�wnowagi do w�z��w
root->level=0;level_asign(root);

balans_check=check_balance(root,balans_check);

printf("%d",balans_check);

wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);
	
			
			
			
			
			
			
			

		break;
	}


//******************************************************************************************************************************************************

     case 7:{// usuwanie wezla najwi�szky z lewego poddrzewa

    // usuwanie wezla najmniejszy z prawego poddrzewa

    	scanf("%d",&key);		//wprowadzanie kluczprzez u�ytkownika
	obecny=root;			//ustawiam wska�nik obecny na korze� drzewa
	obecny=search(obecny,key);

if((obecny->Rson!=nullptr)&&(obecny->Lson!=nullptr))		//dla wez�ow z dwoma potomkami
{
	wsk=obecny;						//przypisanie

wsk=wsk->Lson;						//przej�cie do lewego poddrzewa

	while(wsk->Rson!=nullptr)		//przej�cie do najwi�kszego elementu lewego poddrzewa
	{

	wsk=wsk->Rson;

	}

if(wsk->parent==obecny)				// je�li najwi�kszym elementem lewego poddrzewa jest bezpo�redni potomek korzenia
{
	obecny->val=wsk->val;			//zamie� ich warto�ci
	obecny->Lson=nullptr;			//ustaw wska�nik na lewego potomka na zero
	//free(wsk);					// usuwanie krashuje
}
else								// je�li nie jest bezpo�rednim nastepnikiem
{
	if(wsk->Lson!=nullptr){			//je�li najwi�szy element ma lewy nastepnik
		
		wsk->parent->Rson=wsk->Lson;//ustaw wska�nik na prawego potomka rodzica na lewy nastepnik
	}else{							// je�li nie posiada lewego potomka
		
		wsk->parent->Rson=nullptr;	// ustaw wska�nik na prawego potomka na zaero
	}
	
	
	obecny->val=wsk->val;
	
}








}
else
{

if(obecny->parent->Rson==obecny)			//gdy usuwany jest czyi� prawy syn
{

if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	//gdy usuwany weze� nie ma potomk�w
{
	obecny->parent->Rson=nullptr;						//wska�nik na prawego syna ustawiany na zero
	free(obecny);

}






if((obecny->Rson!=nullptr)&&(obecny->Lson==nullptr))		//gdy weze� ma tylko prawego potomka
{
	obecny->parent->Rson=obecny->Rson;
		free(obecny);



}



if((obecny->Rson==nullptr)&&(obecny->Lson!=nullptr))	// gdy weze� ma tylko lewego potomka
	{


	obecny->parent->Rson=obecny->Lson;
		free(obecny);



	}






}else{	// dla lewego syna ***************************************


if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	// �adnego potomka
{
	obecny->parent->Lson=nullptr;
	free(obecny);

}






if((obecny->Rson!=nullptr)&&(obecny->Lson==nullptr))			//tylko lewy potomek
{
	obecny->parent->Lson=obecny->Rson;
		free(obecny);
}



if((obecny->Rson==nullptr)&&(obecny->Lson!=nullptr))		//tylko prawy potomek
{
	obecny->parent->Lson=obecny->Lson;
		free(obecny);
}






}// koniec opcji dla lewego syna
}
    wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);

		break;






		
	}





/*
		case 8:{	// NIEU�YWANA


			wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);




			break;
		}
*/


case 8:{

print_from_top();		// funkcja dzia�a tylko w trybie debugowania????

	break;
}



	}//koniec switcha

	}//koniec while'a


system("PAUSE")	;
return 0;
}
