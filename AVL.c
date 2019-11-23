//wykona³ Konrad Matusiak
#include<stdlib.h>			//dodajê bibliotekê stdlib.h
#include<string.h>			//dodajê bibliotekê string.h
#include<stdio.h>			//dodajê bibliotekê stdio.h
#include<math.h>
/**************************************************************************/
typedef struct leaf{		//deklaruje typ zmiennej do budowy drzewa, zawiera on
struct	leaf *parent;		//wskaŸnik na poprzednik wêz³a
struct	leaf *Lson;			//wskaŸnik na lewy nastêpnik wêz³a
struct	leaf *Rson;			//wskaŸnik na prawy nastêpnik wêz³a
	int val;				//wartoœæ wêz³a
	int level;				//poziom wêz³a
	int wsp_rownowagi;		//wspó³czynnik równowagi wêz³a

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
int i;				//zmienna steruj¹ca pêtl¹ for
int j;				//zmienna steruj¹ca pêtl¹ for
int balans_check;
int menu;			//zmienna steruj¹ca switchem
int wart;			//zmienna przechowuj¹ca wartoœæ która ma zostaæ dodana do wêz³a drzewa
int hold;			//zmienna przytrzymuj¹ca dzia³anie switcha

int k;				//zmienna przytrzymuj¹ca while'a dodaj¹cego element do drzewa

int left;			//zmienna pomocnicza przy wyznaczaniu wspó³czynników równowagi
int right;			//zmienna pomocnicza przy wyznaczaniu wspó³czynników równowagi

int e;
int loper;
int key;			//zmienna przechowuje wartoœæ wez³a którago wskaŸnik jest poszukiwany
int max;			//zmienna przechowuje wysokoœæ drzewa
int wys;
int l;				//zmienna tymczasowo przechwuj¹ca iloœæ lewych nastêpników
int lw;				//zmienna przechowuj¹ca iloœæ lewych nastêpników
tree *node_A,*node_B,*node_B_synL,*node_B_synR,*prawe,*lewe, *node_C,*node_A_parent,*node_BR;	//deklaruje pomocnicze wskaŸniki wêz³a u¿ywane przy funkcjach rotacji
tree *tmp,*node,*wsk;		//deklaruje wskaŸniki na elementy drzewa BST tmp,wsk2,node
tree *root,*obecny,*wsk2;				//deklaruje wskaŸnik na korzeñ drzewa , wskaŸniki pomocnicze obecny i wsk2

#define nullptr 0	//dla estetyki ustawiam jako wskaŸnik zerowy nullptr


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
                head=malloc(sizeof(queue));		//przypisuje pamiêæ g³owie koljeki
                head->cell=root;				//wartoœci¹ g³owy kolejki staje siê root
                head->nast=nullptr;				//nastêpnikiem jest nullptr

				wsk_q=head;						//ustawiam wskaŸnik obecnego wez³a i wêz³a ostatniego na g³owe kolejki( czyli root'a)
				wsk_qlast=head;
                

max=wys=inordermax(root,0);						//uzyskuje wysokoœæ listy potrzebn¹ do obliczeñ


max=pow(2,max+1);								//wyliczam maksymaln¹ iloœæ wez³ow w drzewie o danej wysokoœci
    max=max-2;
    
    loper=0;									//ustawiam swój licznik na 0
    
    while(loper<max)
 {


        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej czêsci listy ( lewy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						//jeœli obecnie analizowany weze³ nie jest zerem
{
    if(wsk_q->cell->Lson!=nullptr)				//jêsli lewy syn obecnego wez³a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Lson;		//to staje siê on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;				// jeœli syn analizowanego wêz³a jest zerem to ostatni element kolejki te¿ jest zerem
        }
}
else{wsk_qlast->cell=nullptr;					//jeœli analizowny wêze³ jest zerem to ostatni element kolejki te¿ jest zerem
}
        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej czêsci listy ( prawy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						///jeœli obecnie analizowany weze³ nie jest zerem
{
    if(wsk_q->cell->Rson!=nullptr)				//jêsli lewy syn obecnego wez³a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Rson;		///to staje siê on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;			// jeœli syn analizowanego wêz³a jest zerem to ostatni element kolejki te¿ jest zerem
        }
}else{
wsk_qlast->cell=nullptr;					//jeœli analizowny wêze³ jest zerem to ostatni element kolejki te¿ jest zerem
}
    wsk_q=wsk_q->nast;						// przesuwam wskaŸnik analiwowanego wêz³a o 1 

loper=loper+2;								// zwiêkszam licznik o 2
 }		// koniec while

 //i wyswietlanie

 wsk_q=head;								// ustawiam wskaŸnik pomocniczy na g³owê kolejki
 for(i=0;i<=wys;i++)						//iloœæ powtórzeñ pêtli równa siê wysokoœci mask. drzewa
 {
 	loper=pow(2,i);							//iloœæ wêz³ow na poziom równa siê 2 do potêgi wysokoœci 
  for(j=0;j<loper;j++)						//jak wy¿ej
   {
    space=pow(2,wys-i);						// liczenie iloœci spacji ( dla przejrzystoœci [choæ przy liczbach dwu cyfrowych drzewo nieco siê rozje¿d¿a])
    space=space-1;							// jak wy¿ej

	for(k=0;k<space;k++){printf(" ");	}	//wyœwietl odpowiedni¹ iloœæ spacji

         if(wsk_q->cell!=nullptr)			//jêsli wêze³ kolejki nie jest równy nullptr
         { printf("%d ",wsk_q->cell->val); }//wyœwietl zawartoœæ wêz³a

		 else{								//jêsli wêze³ kolejki jest równy nullptr wyswietl _
            printf("_ ");					//
             }
         for(k=0;k<space;k++){printf(" ");	}//wyœwietl drug¹ po³owe spacji

              wsk_q=wsk_q->nast;			//przesuñ wskaŸnik kolejki o 1 weze³
     }
printf("\n");								// po zakoñczeniu wypisywania poziomu enter

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

//funkcja przypisuj¹ca wspó³czynnik równowagi do danego pojedyñczego wêz³a drzewa
void balance_asign(tree *wsk2)
{



if(wsk2->Lson!=nullptr)				//jeœl wêze³ ma lewy nastêpnik  to:

{left=inordermax(wsk2->Lson,0)	;	//zapisz wynik funckji inorder max do zmiennej left (czyli najwiêksza wartoœæ level w lewym poddrzewie
left=left-(wsk2->level);			//do zmiennej left zapisz wartoœæ left pomniejszon¹ o wartoœæ level obecnego korzenia
}
else{left=0;}						//jeœli nie ma lwego nastêpnika to left =0

//level_asign(wsk2->Rson);
if(wsk2->Rson!=nullptr)				//jeœl wêze³ ma prawy nastêpnik  to:

{right=inordermax(wsk2->Rson,0);	//zapisz wynik funckji inorder max do zmiennej prawy (czyli najwiêksza wartoœæ level w prawym poddrzewie
right=right-(wsk2->level);			//do zmiennej prawy zapisz wartoœæ prawy pomniejszon¹ o wartoœæ level obecnego korzenia
}

else{right=0;}						//jeœli nie ma lwego nastêpnika to right =0
wsk2->wsp_rownowagi=left-right;		//do zmiennej wspó³czynnik równowagi wprowadŸ ró¿nicê left - right (czyli ró¿nicê d³ugoœci poddrzew lewego i prawego)


}//koniec deklaracji funkcji

/**************************************************************************/

//przypisz ka¿demu wêz³u wartoœæ wspó³czynnika równowagi

void balance_asign_all(tree *wsk2)//deklaracji funkcji balance asign all
{


	balance_asign(wsk2);			//uruchom funkcjê przypisuj¹c¹ wspó³czynnik równowagi pojedyñczenia wêz³a

	if(wsk2->Lson!=nullptr)			//jeœli isnieje lewy nastêpnik to
	{balance_asign_all(wsk2->Lson);	}		//wywowa³ funkcjê inorder dla wskaŸnika na lewy nastêpnik



	if(wsk2->Rson!=nullptr)						//jeœli isnieje prawy nastêpnik to
	{balance_asign_all(wsk2->Rson);	}					//wywowa³ funkcjê inorder dla wskaŸnika na prawy nastêpnik


}		//koniec deklaracji funkcji



/**************************************************************************/
//funkcja równowa¿¹ca drzewo avl, nie dzia³a dla root'a
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


if((wsk2->wsp_rownowagi<=-2)	)		//jesli wspó³czynnik równowagi jest wiêkszy lub równy 2 (prawe poddrzewo jest d³u¿sze od lewego o 2
{

	left_left(wsk2,root);			//wywo³aj funkcjê left_left (wykonaj rotacjê w lewo)
}

if(wsk2->wsp_rownowagi>=2)			//jesli wspó³czynnik równowagi jest mniejszy lub równy 2 (prawe poddrzewo jest d³u¿sze od lewego o 2
{
	right_right(wsk2,root);			//wywo³aj funkcjê right_right (wykonaj rotacjê w prawo)

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

void balancing_all(tree * wsk2,tree * root)//deklaracja funckji balancing all (z wyj¹tkiem root'a)
{


if(wsk2->Lson!=nullptr)					//jêœli istnieje lewy nastêpnik obecnego wez³a
{balancing_all(wsk2->Lson,root);}		//wywo³aj funckjê balancing _all dla lewego nastêpnika obecnego wêz³a

	if(wsk2->Rson!=nullptr)				//jêœli istnieje prawy nastêpnik obecnego wez³a
{balancing_all(wsk2->Rson,root);}		//wywo³aj funckjê balancing _all dla prawego nastêpnika obecnego wêz³a

lewe=wsk2->Lson;
prawe=wsk2->Rson;		//jyyyyyyyyyyyyyyyyyssssssssssssssssssssssss

balancing(wsk2,root,lewe,prawe);					//wywo³aj funckjê równowa¿enia pojedynczego wêz³a dla obecnego wêz³a

}			//koniec deklaracji funkcji

/**************************************************************************/

void right_right(tree *wsk2,tree *root)			//deklaracja funkcji rotacji w prawo(nie dla korzenia)
{
	node_A=wsk2;					//ustawiam wskaŸnik pomocniczy na wêze³ na którym wykonujê rotacje
node_B=wsk2->Lson;					//ustawiam wskaŸnik pomocniczy node_B na lewy nastêpnik wskaŸnika na krórym wykoujemy rotacje

if(wsk2->parent->Rson==wsk2)		//jesli wskaŸnik na którym dokonujemy roatcji jest czyimœ prawym nastepnikiem to:
	{
		node_A->parent->Rson=node_B;	//ustawiamy wskaŸnik na prawy nastêpnik rodzica node_A na node_B

		node_A->Lson=node_B->Rson;		//ustawiamy wskaŸnik lewego nastêpnika node_A na node_B
	//	node_B_synR->parent=node_A;
		node_B->Rson=node_A;	//ustawiam wskaŸnik prawego nastêpnika node_B na swojego rodzica czyli node_A
		node_B->parent=node_A->parent;	//rodzicem node_B staje siê rodzic node_A

		node_A->parent=node_B;		//rodzicem node_A staje siê node_B

	}
	else			//jesli wskaŸnik na którym dokonujemy roatcji jest czyimœ lewym nastepnikiem to:
	{
		node_A->parent->Lson=node_B;			//ustawiamy wskaŸnik na lewy nastêpnik rodzica node_A na node_B

		node_A->Lson=node_B->Rson;				//ustawiamy wskaŸnik lewego nastêpnika node_A na node_B
//node_B_synL->parent=node_A;
		node_B->Rson=node_B->parent;			//ustawiam wskaŸnik prawego nastêpnika node_B na swojego rodzica czyli node_A
		node_B->parent=node_A->parent;			//rodzicem node_B staje siê rodzic node_A

		node_A->parent=node_B;					//rodzicem node_A staje siê node_B

	}

root->level=0;level_asign(root);			//na nowo przypisujê wartoœæ wysokoœci wszystkich wêz³ów

balance_asign_all(root);		//na nowo przypisujê wspó³czynniki równowagi

root->level=0;level_asign(root);

}		//koniec deklaracji funkcji

/**************************************************************************/

/**************************************************************************/
void left_left(tree *wsk2,tree *root)		//deklaracja funckji rotacji w lewo(nie dla korzenia)
{

node_A=wsk2;								//ustawiam wskaŸnik pomocniczy node_A na wêze³ wokó³ którego bêdziemy robiæ rotacjê
node_B=wsk2->Rson;							//ustawiam wskaŸnik pomocniczy na prawy nastêpnik node_A
node_BR=node_B->Lson;
if(wsk2->parent->Rson==wsk2)				//jeœli node_A jest prawym nastêpnikiem to:
{
node_A->parent->Rson=node_B;		//ustawiamy wskaŸnik na prawy nastêpnik rodzica nde_A na node_B
//node_BR->parent=node_A;			//DZIA£AJ
node_A->Rson=node_B->Lson;			//lewy nastepnik node_B staje siê prawym nastêpnikiem node_A

node_B->Lson=node_A;		//rodziæ node_B staje lewym nastêpnikiem node_B
node_B->parent=node_A->parent;		//rodzicem node_B staje siê rodzic node_A
node_A->parent=node_B;				//rodzicem node_A stajenssiê node_B



}
else						//jeœli node_A jest lweym nastêpnikiem to:
{
node_A->parent->Lson=node_B;	//ustawiam wskaxnik lewego nastêpnika rodzica node_A na node_B

node_A->Rson=node_B->Lson;		//lewy nastêpnik node_B staje siê prawym nastêpnikiem node_A
//node_B->Lson->parent=node_A;
node_B->Lson=node_A;		//rodzic node_B staje siê lewym nastêpnikiem node_B
node_B->parent=node_A->parent;		//rodzicem node_A staje siê rodzic node_B
node_A->parent=node_B;				//rodzicem node_A staje siê node_B


}

root->level=0;level_asign(root);		//na nowo przypisujê poziomy wêz³ów
balance_asign_all(root);		// na nowo przypisujê wspó³czynniki rówowagi

root->level=0;level_asign(root);

}//konie deklaracji funkcji rotacji

/**************************************************************************/


/**************************************************************************/


//dlugosc poddrzewa

int inordermax(tree *wsk2,int max)
{	//deklaracja funkcji obliczaj¹cej wysokoœæ poddrzewa o korzeniu w wsk2 z argumentami wsk2 i licznikiem wyskokoœci drzewa max


	if(wsk2->Lson!=nullptr)						//jeœli istnieje lewy natêpnik
	{max=inordermax(wsk2->Lson,max);	}		//przypisz licznikowi wynik funkcji inordermax



	if(wsk2->Rson!=nullptr)						//jeœli istnieje lewy natêpnik
	{max=inordermax(wsk2->Rson,max);	}		//przypisz licznikowi wynik funkcji inordermax

	if(max<wsk2->level){max=wsk2->level;}		//jeœli wartoœæ poziomu obecnego wêz³a jestwiêksza od obecnej wartoœci max to ustaw wartoœæ max na wartoœæ level

return max;										//zwróæ wartoœæ zmiennej max


}//koniec deklaracji funkcji

/**************************************************************************/








/**************************************************************************/

//wyszukiwanie klucza w poddrzewie zwraca wskaznik na klucz

struct tree *search(tree *obecny,int key)//deklaracja funckji wyszukuj¹cej wskaŸnik drzewa BST na podstawie podanego klucza

{//	obecny=root;//umiescic przed wywo³aniem funckji


if(key==obecny->val)			//jeœli wartoœæ wêz³a i klucza s¹ takie same to:
		{

		return obecny;			//zwróæ wskaŸnik na obecny element

		}
		else{					//w przeciwnym przypadku to:


	if(key>obecny->val)			//sprawdŸ czy wartoœæ klucza jest wieksza od wartoœci obecnego  wêz³a jeœli tak to:
		{

			if(obecny->Rson!=nullptr)		//jeœli istnieje prawy nastepnik
			{
			obecny=search(obecny->Rson,key);//uruchom funkcjê search dla poddrzewa z korzeniem w prawym nastêpniku
			}
			else		//jeœli nie ma prawego nastêpnika to:
			{printf("W drzewie nie ma takiego wez³a"); 	}		//wyœwietl komunikat
		}

	if(key<obecny->val)							//sprawdŸ czy wartoœæ klucza jest mniejsza od wartoœci obecnego  wêz³a jeœli tak to:
		{

			if(obecny->Lson!=nullptr)			//jeœli istnieje lewy nastepnik
			{
			obecny=search(obecny->Lson,key);	//uruchom funkcjê search dla poddrzewa z korzeniem w lewym nastêpniku
			}
			else									//jeœli nie ma lewego nastêpnika to:
			{printf("W drzewie nie ma takiego wez³a"); 	}	//wyœwietl komunikat
		}
}





	return obecny;			//zwróæ  wskaŸnik na wêze³ z szukanym kluczem
}//koniec deklaracji funkcji

/**************************************************************************/



//wypisuje poprzecznie drzewo

int printopronto(int e,tree *wsk2)					//deklaracja funkcji rysowania drzewa z z argumentami :e-wartoœæ steruj¹ca spacjami,wsk2 wska¿nik na rysowane poddrzewa
{
int i;						//zmienna steruj¹ca pêtl¹ for
  if(!wsk2) return;			//jesli nie istnieje poddrzewa  okorzeniu wsk2 wyjdŸ z funkcji
  printopronto(e+1,wsk2->Rson);		//wywo³aj funkcjê printopronto ze zwiêkszonym iloœci¹ spacji dla drzewa z korzeniem wsk2->Rson
  for(i=0; i<e; ++i){				//wykonaj e spacji
   printf("     ");}				//wyœwietl spacje
  printf("%d (%d)\n ", wsk2->val,wsk2->parent->val );	//wyœwietl wartoœæ obecnego wez³a i jego wysokoœæ w drzewie
  printopronto(e+1,wsk2->Lson);					//wywo³aj funkcjê printopronto ze zwiêkszonym iloœci¹ spacji dla drzewa z korzeniem wsk2->Lson

}//koniec deklaracji funkcji

/**************************************************************************/
//root->level=0;level_asign(root);
void level_asign(tree *wsk2)
{


		if(wsk2->Lson!=nullptr)				//jesli istnieje lewy nastêpnik wêz³a to:
		{wsk2->Lson->level=(wsk2->level)+1;level_asign(wsk2->Lson);}			//ustaw wysokoœæ lewego nastêpnika wsk2 na wysokoœæ wsk2 zwiêkszon¹ o 1

			if(wsk2->Rson!=nullptr)			//jesli istnieje prawy nastêpnik wêz³a to:
		{wsk2->Rson->level=(wsk2->level)+1;level_asign(wsk2->Rson);}			//ustaw wysokoœæ prawego nastêpnika wsk2 na wysokoœæ wsk2 zwiêkszon¹ o 1


}//koniec deklaracji funkcji


//funckja przypisuje na nowo wartoœci level pocz¹wszy od wskazanego wez³a by odczytaæ wartoœci poddrzew poczynaj¹c od danego wêz³a
//funkcja nie dzia³a dla root'a


//***************************************************************************************************

//***************************************************************************************************


int main()			//pocz¹tek funkcji g³ownej
{


	balans_check=0;


	printf("Podaj wartosc korzenia\n");		//wyœwietl komunikat dla u¿ytkownika
	scanf("%d",&wart);						//wprowadŸ wartoœæ korzenia

	
	root=malloc(sizeof(tree));				//przydziel pamiêæ rozmiaru wêz³a drzewa dla korzenia
	root->parent=root;					//ustawiam wskaŸnik na rodzica korzenia na 0
	root->Lson=nullptr;						//ustawiam wskaŸnik na lewy nastêpnik korzenia na 0
	root->Rson=nullptr;						//ustawiam wskaŸnik na prawy nastêpnik korzenia na 0
	root->val=wart;							//ustawiam wartoœæ korzenia na wartoœæ wprowadzon¹ do zmiennej wart
	root->level=0;							//ustawiam poziom korzenia na 0
	root->wsp_rownowagi=0;					//ustawiam wspó³czynnik równowagi korzenia na 0

	hold=0;										//ustawiam zmienn¹ hold na 0

while(hold==0)
{   printf("\n MENU:\n 1.dodaj nowy wezel\n 2.Wyswietl drzewo poprzecznie\n 3.podaj wspolczynnik rownowagi wybranego wezla\n 4.Wyjdz z programu\n 5.wyswietl z gory na dol \n 6.usun wybrany wezel (najmniejszy elem. praw. drzewa) \n 7.usun wybrany wezel (najwiekszy elem. lew. drzewa) \n ");//wyœwietl opcje dla u¿ytkownika
	printf("8.Odtwórz korzen(koncepcja) \n 9. Zniszcz drzewo(koncepcja)  \n 10.Sprawdz rownowage \n");


	scanf("%d",&menu);			//pobierz wartoœæ zmiennej steruj¹cej switchem


	switch(menu)				//prze³¹cznik sterowany zmienn¹ menu

	{




		case 1://dodaj element do drzewa
	{
	printf("Podaj wartosc nowego wezla\n");

		scanf("%d",&wart);				//pobieram wartosc dla nowego wêz³a
		obecny=root;					//ustawiam wskaŸnik iteruj¹cy na korzeñ

		if(obecny->val==wart)			//jeœli wartoœæ podana wystêpuje ju¿ w korzeniu wyœwietlany jest komunikat
		{printf("Drzewo nie moze miec 2 wezlow o takiej samej wartosci\n");break;	}	//oraz przerywana jest akcja dodawania weœ³a


		k=0;								//zmienna przytrzymuj¹ca pêtle while
		while(k!=1)							//jeœli nie niej równe 1 wykonuj pêtle
		{
			if(obecny->val==wart)			//jeœli podana wartoœæ wystêpuje ju¿ na obecnym weŸle to anuluj akcjê dodawania wêz³a
		{printf("Drzewo nie moze miec 2 wezlow o takiej samej wartosci\n");break;} 			//wyœwietla komunikat o przerwaniu



		if((wart<obecny->val)&&(obecny->Lson==nullptr))//gdy wartoœæ tworzonego wêz³a jest mniejsza od obecnego wêz³a oraz  obecny wêze³ nie ma lewego nastêpnika wykonaj nastêpuj¹ce dzia³ania
		{

		tmp=obecny;										//ustawiam wskaŸnik tymczasowy na obecny
		obecny->Lson=malloc(sizeof(tree));				//alokuje pamieæ rozmiaru wêz³a drzewa dla lewego nastêpnika obecnego wêz³a
		obecny=obecny->Lson;							//ustawiam wskaŸnik obecny na lewy nastêpnik
		obecny->parent=tmp;								//przypisuje wskaŸnik na rodzica
		obecny->val=wart;								//przypisuje wartoœæ int dla nowego wêz³a
		obecny->Lson=nullptr;							//ustawiam wskaŸnik lewego natêpnika na NULL
		obecny->Rson=nullptr;							//ustawiam wskaŸnik prawego natêpnika na NULL
		obecny->level=1+(obecny->parent->level);		//ustawiam wysokoœæ na wysokoœæ rodzica +1

		break;											//wyjdŸ z pêtli while
		}

		if((wart>obecny->val)&&(obecny->Rson==nullptr))//gdy wartoœæ tworzonego wêz³a jest wiêksza od obecnego wêz³a oraz  obecny wêze³ nie ma prawego nastêpnika wykonaj nastêpuj¹ce dzia³ania
		{

		tmp=obecny;										//ustawiam wskaŸnik tymczasowy na obecny
		obecny->Rson=malloc(sizeof(tree));				//alokuje pamieæ rozmiaru wêz³a drzewa dla prawego nastêpnika obecnego wêz³a
		obecny=obecny->Rson;							//ustawiam wskaŸnik obecny na prawy nastêpnik
		obecny->parent=tmp;								//przypisuje wskaŸnik na rodzica
		obecny->Rson=nullptr;							//ustawiam wskaŸnik prawego natêpnika na NULL
		obecny->Lson=nullptr;							//ustawiam wskaŸnik lewego natêpnika na NULL
		obecny->val=wart;								//przypisuje wartoœæ int dla nowego wêz³a
		obecny->level=1+(obecny->parent->level);		//ustawiam wysokoœæ na wysokoœæ rodzica +1

		break;											//wyjdŸ z pêtli while
		}

		if((wart>obecny->val)&&(obecny->Rson!=nullptr))	//jeœli nowa wartoœæ jest wiêksza od obecnego wêz³a ale istnieje ju¿ prawy nastêpnik to wykonaj:
		{obecny=obecny->Rson;		}					//ustaw wskaŸnik obecny na prawy nastêpnik

		if((wart<obecny->val)&&(obecny->Lson!=nullptr))	//jeœli nowa wartoœæ jest wiêksza od obecnego wêz³a ale istnieje ju¿ lewy nastêpnik to wykonaj:
		{obecny=obecny->Lson;		}					//ustaw wskaŸnik obecny na lewy nastêpnik





	}//koniec peli while

//******************************************************************
//sprawdzenie wspó³czynnika równowagi


//balans_check=check_balance(root,balans_check);

//printf("%d",balans_check);




root->level=0;
level_asign(root);

wsk2=root;						//ustaw wskaŸnik pomocniczy wsk2 na root
balance_asign_all(wsk2);		//poczynaj¹c od wsk2 przypisz wartoœci wspó³czynników równowagi

root->level=0;
level_asign(root);

if(root->Lson!=nullptr)			//jeœli istnieje lewy nastpnik korzenia to:
	{
		wsk2=root->Lson;				//ustaw wskaŸnik pomocniczy wsk2 na lewy nastêpnik korzenia
		balancing_all(wsk2,root);
	}		//uruchom funkcjê równowa¿enia dla drzewa o korzeniu root poczynaj¹c od poddrzewa o korzeniu wsk2

root->level=0;
level_asign(root);

if(root->Rson!=nullptr)			//jeœli istnieje prawy nastpnik korzenia to:
	{
		wsk2=root->Rson;				//ustaw wskaŸnik pomocniczy wsk2 na prawy nastêpnik korzenia
		balancing_all(wsk2,root);
	}		//uruchom funkcjê równowa¿enia dla drzewa o korzeniu root poczynaj¹c od poddrzewa o korzeniu wsk2

root->level=0;
level_asign(root);




root->level=0;
level_asign(root);					//na nowo przypisz wartoœci wysokoœci wêz³ów

balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów


root->level=0;
level_asign(root);



//***************************************************
//równowa¿eniu korzenia


if((root->Rson!=nullptr)&&(root->wsp_rownowagi<=-2)&&(((root->wsp_rownowagi)*(root->Rson->wsp_rownowagi))==-2))

	{ 
		right_right(root->Rson,root);
		balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
		root->level=0;level_asign(root);
	}

if((root->Lson!=nullptr)&&(root->wsp_rownowagi>=2)&&(((root->wsp_rownowagi)*(root->Lson->wsp_rownowagi))==-2))
{left_left(root->Lson,root);


balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);
}

if(root->wsp_rownowagi<=-2)		//jeœli prawe popddrzewo jest wiêksze od lewego o conajmniej  2 wêz³y
{

	node_A=root;				//zapisuje obecny korzeñ do wskaŸnika pomocniczego node_A


root=root->Rson;				//ustawiam korzeñ an prawy nastêpnik korzenia



node_A->Rson=root->Lson;		//prawym nastêpnikiem node_A staje sie lewy nastêpnik  obecnego korzenia

root->Lson=root->parent;		//nowym lewym nastêpnikiem staje siê rodzic owego root'a

node_A->parent=root;			//rodzicem node_A staje siê korzeñ


}

if(root->wsp_rownowagi>=2)		//jeœli lewe popddrzewo jest wiêksze od prawego o conajmniej  2 wêz³y
{


node_A=root;					//zapisuje obecny korzeñ do wskaŸnika pomocniczego node_A


root=root->Lson;


		node_A->Lson=root->Rson;		//lewym nastêpnikiem node_A staje siê prawy nastêpnik nowego root'a
	
		root->Rson=root->parent;		//prawym nastêpnikiem nowego korzenia staje siê jego by³y rodzic
		

		node_A->parent=root;			//nowym rodzicem node_A staje siê nowy korzeñ drzewa





}






//*****************************************************

root->level=0;level_asign(root);					//na nowo przypisz wartoœci wysokoœci wêz³ów
balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);

balans_check=check_balance(root,balans_check);

printf("%d",balans_check);

wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);




break;//wyjdŸ z case'a
	}	// koniec case 0




/**************************************************************************/



	case 2:{//wyswietl bokiem
		wsk2=root;		//ustaw wskaŸnik wsk2 na korzeñ
		int e=0;		// ustaw zmienn¹ steruj¹ca spacjami na 0
	printopronto(e,wsk2);	//uruchom funkcjê wypisania printopronto

	break;				//wyjdŸ z case'a
	}//koniec case 3

/**************************************************************************/


	case 4:{//wyjscie z programu
	hold=1;			//ustaw zmienn¹ hold na 1 co koñczy pêtle while
		break;		//wyjdŸ z case'a
	}	//koniec case 8


/**************************************************************************/

case 3:{//wyœwietlanie wspó³czynników równowagi
printf("\n Podaj klucz wezla by uzyskac jego wspolczynnik rownowagi\n ");//wyœwietl komunikat
	scanf("%d",&key);		//wprowadzanie kluczprzez u¿ytkownika
	obecny=root;			//ustawiam wskaŸnik obecny na korzeñ drzewa
	obecny=search(obecny,key);	//zapisuje do wskaxnika obecny wynik funckji zwracaj¹cej wskaŸnik na szukany wêze³

	printf("Wspolczynnik rownowagi wezla %d rowna sie [%d]",obecny->val,obecny->wsp_rownowagi);		//wyœwietl komunikat z wynikiem


	break;		 //wyjdŸ ze switcha
} 		//koniec case'a

/**************************************************************************/



case 5:{// wypisanie z gory na dol

                head=malloc(sizeof(queue));		//przypisuje pamiêæ g³owie koljeki
                head->cell=root;				//wartoœci¹ g³owy kolejki staje siê root
                head->nast=nullptr;				//nastêpnikiem jest nullptr

				wsk_q=head;						//ustawiam wskaŸnik obecnego wez³a i wêz³a ostatniego na g³owe kolejki( czyli root'a)
				wsk_qlast=head;
                

max=wys=inordermax(root,0);						//uzyskuje wysokoœæ listy potrzebn¹ do obliczeñ


max=pow(2,max+1);								//wyliczam maksymaln¹ iloœæ wez³ow w drzewie o danej wysokoœci
    max=max-2;
    
    loper=0;									//ustawiam swój licznik na 0
    
    while(loper<max)
 {


        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej czêsci listy ( lewy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						//jeœli obecnie analizowany weze³ nie jest zerem
{
    if(wsk_q->cell->Lson!=nullptr)				//jêsli lewy syn obecnego wez³a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Lson;		//to staje siê on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;				// jeœli syn analizowanego wêz³a jest zerem to ostatni element kolejki te¿ jest zerem
        }
}
else{wsk_qlast->cell=nullptr;					//jeœli analizowny wêze³ jest zerem to ostatni element kolejki te¿ jest zerem
}
        wsk_qlast->nast=malloc(sizeof(queue));	//dokonuje alokacji kolejnej czêsci listy ( prawy syn)
        wsk_qlast=wsk_qlast->nast;
        wsk_qlast->nast=nullptr;

if(wsk_q->cell!=nullptr)						///jeœli obecnie analizowany weze³ nie jest zerem
{
    if(wsk_q->cell->Rson!=nullptr)				//jêsli lewy syn obecnego wez³a nie jest zerem
    {
       wsk_qlast->cell=wsk_q->cell->Rson;		///to staje siê on ostatnim elementem kolejki

    }
    else{
        wsk_qlast->cell=nullptr;			// jeœli syn analizowanego wêz³a jest zerem to ostatni element kolejki te¿ jest zerem
        }
}else{
wsk_qlast->cell=nullptr;					//jeœli analizowny wêze³ jest zerem to ostatni element kolejki te¿ jest zerem
}
    wsk_q=wsk_q->nast;						// przesuwam wskaŸnik analiwowanego wêz³a o 1 

loper=loper+2;								// zwiêkszam licznik o 2
 }		// koniec while

 //i wyswietlanie

 wsk_q=head;								// ustawiam wskaŸnik pomocniczy na g³owê kolejki
 for(i=0;i<=wys;i++)						//iloœæ powtórzeñ pêtli równa siê wysokoœci mask. drzewa
 {
 	loper=pow(2,i);							//iloœæ wêz³ow na poziom równa siê 2 do potêgi wysokoœci 
  for(j=0;j<loper;j++)						//jak wy¿ej
   {
    space=pow(2,wys-i);						// liczenie iloœci spacji ( dla przejrzystoœci [choæ przy liczbach dwu cyfrowych drzewo nieco siê rozje¿d¿a])
    space=space-1;							// jak wy¿ej

	for(k=0;k<space;k++){printf(" ");	}	//wyœwietl odpowiedni¹ iloœæ spacji

         if(wsk_q->cell!=nullptr)			//jêsli wêze³ kolejki nie jest równy nullptr
         { printf("%d ",wsk_q->cell->val); }//wyœwietl zawartoœæ wêz³a

		 else{								//jêsli wêze³ kolejki jest równy nullptr wyswietl _
            printf("_ ");					//
             }
         for(k=0;k<space;k++){printf(" ");	}//wyœwietl drug¹ po³owe spacji

              wsk_q=wsk_q->nast;			//przesuñ wskaŸnik kolejki o 1 weze³
     }
printf("\n");								// po zakoñczeniu wypisywania poziomu enter

    }
                break;
            }// koniec case'a

  //********************************************************************************************************************

    case 6:{// usuwanie wezla najmniejszy z prawego poddrzewa

    	scanf("%d",&key);		//wprowadzanie kluczprzez u¿ytkownika
	obecny=root;			//ustawiam wskaŸnik obecny na korzeñ drzewa
	obecny=search(obecny,key);

if((obecny->Rson!=nullptr)&&(obecny->Lson!=nullptr))		//dla wez³ow z dwoma potomkami
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


if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	// ¿adnego potomka
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

wsk2=root;						//ustaw wskaŸnik pomocniczy wsk2 na root
balance_asign_all(wsk2);		//poczynaj¹c od wsk2 przypisz wartoœci wspó³czynników równowagi

root->level=0;level_asign(root);

if(root->Lson!=nullptr)			//jeœli istnieje lewy nastpnik korzenia to:
{wsk2=root->Lson;				//ustaw wskaŸnik pomocniczy wsk2 na lewy nastêpnik korzenia
balancing_all(wsk2,root);}		//uruchom funkcjê równowa¿enia dla drzewa o korzeniu root poczynaj¹c od poddrzewa o korzeniu wsk2

root->level=0;level_asign(root);

if(root->Rson!=nullptr)			//jeœli istnieje prawy nastpnik korzenia to:
{
wsk2=root->Rson;				//ustaw wskaŸnik pomocniczy wsk2 na prawy nastêpnik korzenia
balancing_all(wsk2,root);}		//uruchom funkcjê równowa¿enia dla drzewa o korzeniu root poczynaj¹c od poddrzewa o korzeniu wsk2

root->level=0;level_asign(root);




root->level=0;level_asign(root);					//na nowo przypisz wartoœci wysokoœci wêz³ów
balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);



//***************************************************
//równowa¿eniu korzenia


if((root->Rson!=nullptr)&&(root->wsp_rownowagi<=-2)&&(((root->wsp_rownowagi)*(root->Rson->wsp_rownowagi))==-2))

{ right_right(root->Rson,root);


balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);
}

if((root->Lson!=nullptr)&&(root->wsp_rownowagi>=2)&&(((root->wsp_rownowagi)*(root->Lson->wsp_rownowagi))==-2))
{left_left(root->Lson,root);


balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);
}

if(root->wsp_rownowagi<=-2)		//jeœli prawe popddrzewo jest wiêksze od lewego o conajmniej  2 wêz³y
{

	node_A=root;				//zapisuje obecny korzeñ do wskaŸnika pomocniczego node_A


root=root->Rson;				//ustawiam korzeñ an prawy nastêpnik korzenia



node_A->Rson=root->Lson;		//prawym nastêpnikiem node_A staje sie lewy nastêpnik  obecnego korzenia

root->Lson=root->parent;		//nowym lewym nastêpnikiem staje siê rodzic owego root'a

node_A->parent=root;			//rodzicem node_A staje siê korzeñ


}

if(root->wsp_rownowagi>=2)		//jeœli lewe popddrzewo jest wiêksze od prawego o conajmniej  2 wêz³y
{


node_A=root;					//zapisuje obecny korzeñ do wskaŸnika pomocniczego node_A


root=root->Lson;


		node_A->Lson=root->Rson;		//lewym nastêpnikiem node_A staje siê prawy nastêpnik nowego root'a
	
		root->Rson=root->parent;		//prawym nastêpnikiem nowego korzenia staje siê jego by³y rodzic
		

		node_A->parent=root;			//nowym rodzicem node_A staje siê nowy korzeñ drzewa





}






//*****************************************************

root->level=0;level_asign(root);					//na nowo przypisz wartoœci wysokoœci wêz³ów
balance_asign_all(root);				//przypisz wspó³czynniki równowagi do wêz³ów
root->level=0;level_asign(root);

balans_check=check_balance(root,balans_check);

printf("%d",balans_check);

wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);
	
			
			
			
			
			
			
			

		break;
	}


//******************************************************************************************************************************************************

     case 7:{// usuwanie wezla najwiêszky z lewego poddrzewa

    // usuwanie wezla najmniejszy z prawego poddrzewa

    	scanf("%d",&key);		//wprowadzanie kluczprzez u¿ytkownika
	obecny=root;			//ustawiam wskaŸnik obecny na korzeñ drzewa
	obecny=search(obecny,key);

if((obecny->Rson!=nullptr)&&(obecny->Lson!=nullptr))		//dla wez³ow z dwoma potomkami
{
	wsk=obecny;						//przypisanie

wsk=wsk->Lson;						//przejœcie do lewego poddrzewa

	while(wsk->Rson!=nullptr)		//przejœcie do najwiêkszego elementu lewego poddrzewa
	{

	wsk=wsk->Rson;

	}

if(wsk->parent==obecny)				// jeœli najwiêkszym elementem lewego poddrzewa jest bezpoœredni potomek korzenia
{
	obecny->val=wsk->val;			//zamieñ ich wartoœci
	obecny->Lson=nullptr;			//ustaw wskaŸnik na lewego potomka na zero
	//free(wsk);					// usuwanie krashuje
}
else								// jeœli nie jest bezpoœrednim nastepnikiem
{
	if(wsk->Lson!=nullptr){			//jeœli najwiêszy element ma lewy nastepnik
		
		wsk->parent->Rson=wsk->Lson;//ustaw wskaŸnik na prawego potomka rodzica na lewy nastepnik
	}else{							// jeœli nie posiada lewego potomka
		
		wsk->parent->Rson=nullptr;	// ustaw wskaŸnik na prawego potomka na zaero
	}
	
	
	obecny->val=wsk->val;
	
}








}
else
{

if(obecny->parent->Rson==obecny)			//gdy usuwany jest czyiœ prawy syn
{

if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	//gdy usuwany weze³ nie ma potomków
{
	obecny->parent->Rson=nullptr;						//wskaŸnik na prawego syna ustawiany na zero
	free(obecny);

}






if((obecny->Rson!=nullptr)&&(obecny->Lson==nullptr))		//gdy weze³ ma tylko prawego potomka
{
	obecny->parent->Rson=obecny->Rson;
		free(obecny);



}



if((obecny->Rson==nullptr)&&(obecny->Lson!=nullptr))	// gdy weze³ ma tylko lewego potomka
	{


	obecny->parent->Rson=obecny->Lson;
		free(obecny);



	}






}else{	// dla lewego syna ***************************************


if((obecny->Rson==nullptr)&&(obecny->Lson==nullptr))	// ¿adnego potomka
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
		case 8:{	// NIEU¯YWANA


			wsk=root;
			wsk2=root;
			restore_parents(root,wsk,wsk2);




			break;
		}
*/


case 8:{

print_from_top();		// funkcja dzia³a tylko w trybie debugowania????

	break;
}



	}//koniec switcha

	}//koniec while'a


system("PAUSE")	;
return 0;
}
