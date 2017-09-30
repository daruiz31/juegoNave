#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>

using namespace std;

// Definir teclas código ASCII
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESPACIO 32

int puntos = 0;

void gotoxy(int x, int y){
	
	// Tomar control de la ventana
	HANDLE hVentana;
    hVentana = GetStdHandle(STD_OUTPUT_HANDLE);

    // Modificar cordenadas
        
    COORD dwCordenadas;
    dwCordenadas.X = x;
    dwCordenadas.Y = y;

    // Gestionar argumentos
    SetConsoleCursorPosition(hVentana, dwCordenadas);
    
}

void ocultarCursor(){
	
    HANDLE hVentana;
    hVentana = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Configurar cursor
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 2;
    cursor.bVisible = FALSE; 
    
    
    //Propiedades del cursor
    SetConsoleCursorInfo(hVentana,&cursor);
}

void pintar_limites(){
	for(int i=2; i<78 ; i++){
         gotoxy(i, 1); printf("%c", 205);
         gotoxy(i,32); printf("%c", 205);
}
    for(int i = 4; i< 30 ; i++){
    	gotoxy(0,i); printf(",%c", 176);
    	gotoxy(78,i); printf("%c,", 176);
	}
	
	gotoxy(1,2); printf("%c",278);
	gotoxy(1,3); printf("%c",278);
	gotoxy(78,2); printf("%c",278);
	gotoxy(78,3); printf("%c",278);
	gotoxy(78,30); printf("%c",278);
	gotoxy(78,31); printf("%c",278); 
	gotoxy(1,30); printf("%c",278);
	gotoxy(1,31); printf("%c",278);
	
		
}


class NAVE{
	
	int x,y;
	int corazones;
	int vidas;
public:
	
	NAVE(int _x, INT _y, int _corazones, int _vidas): x(_x), y(_y), corazones(_corazones), vidas(_vidas){};	
	
	int X(){return x;}
	int Y(){return y;}
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void morir();
	void reducir_corazon(){ corazones--;}
	int Vidas(){return vidas;}
	
	
};

void NAVE::pintar(){
	gotoxy(x,y);   printf("  %c", 30);
	gotoxy(x,y+1); printf(" %c%c%c", 40, 207, 41);
	gotoxy(x,y+2); printf("%c%c %c%c", 196, 33, 33, 196);
}

void NAVE::borrar(){
	gotoxy(x,y);   printf("         ");
	gotoxy(x,y+1); printf("         ");
	gotoxy(x,y+2); printf("         ");
}

void NAVE::mover(){
	
	// Si se oprime una tecla
		if(kbhit()){
			
			char tecla = getch();
			
			// Borrar rastro de caracter
			borrar();
						
						
			// Condicion por tecla + limitar movimientos			
			if(tecla == IZQUIERDA && x>2) x--;
			if(tecla == DERECHA && x+6 < 78) x++;
			if(tecla == ARRIBA && y>2) y--;
			if(tecla == ABAJO && y+3 <32) y++;
			if(tecla == 'e') corazones--;
			// Dibujar caracter
			pintar();
			pintar_corazones();
			
			
                   }
}

void NAVE::pintar_corazones(){
	
	gotoxy(16,33); printf("Vidas %d", vidas);
	gotoxy(3,33); printf("Salud");
	gotoxy(10,33); printf("      ");
	for(int i = 0 ; i < corazones; i++){
		
		gotoxy(10+i,33); printf("%c",3);
	}
}

void NAVE::morir(){
	
	if(corazones == 0){
		borrar();
		gotoxy(x,y);   printf("   @@   ");
		gotoxy(x,y+1); printf("  *@@*  ");
		gotoxy(x,y+2); printf("   **   ");
		Sleep(200);
		
		borrar();
		gotoxy(x,y);   printf(" * **  @");
		gotoxy(x,y+1); printf("  *@**  ");
		gotoxy(x,y+2); printf(" * **  @");
		Sleep(200);
		
		borrar();		
		gotoxy(x,y);   printf(" * *  ");
		gotoxy(x,y+1); printf("  ***  ");
		gotoxy(x,y+2); printf(" * **  ");
		Sleep(200);
		
		borrar();		
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();
	}
}

class asteroides{
	int x,y;
	
	public:
		asteroides(int _x, int _y): x(_x), y(_y){}
		void pintar();
		void mover();
		void choque(class NAVE &Nave);
		int X(){ return x;}
		int Y(){ return y;}
		
};

void asteroides::pintar(){
	gotoxy(x,y); printf("%c", 184);
}

void asteroides::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y > 29){
		x = ((rand()% 75) + 2);
		y = 2;
	}
	pintar();
}

void asteroides::choque(NAVE &Nave){
	
	if(x >= Nave.X() && x < Nave.X()+6 && y>= Nave.Y() && y <= Nave.Y()+3)
	{
		Nave.reducir_corazon();
		
		Nave.borrar();
		Nave.pintar();
		
		Nave.pintar_corazones();
		x = rand()% 77 + 2;
		y = 2;
	}
}


class disparos{
   int x,y;
   
   public:
    disparos(int _x, int _y): x(_x), y(_y){}
    
    int X(){return x;}
    int Y(){return y;}
    void mover();
    bool quitar();
    
};

void disparos::mover(){
	gotoxy(x,y); printf(" ");
	y--;
	gotoxy(x,y); printf("%c", 30);
}

bool disparos::quitar(){
	if(y == 2) return true;
	return false;
}


int main(){ 

    ocultarCursor();
    pintar_limites();
    NAVE nave(37,29,3,3);
    nave.pintar();
    nave.pintar_corazones();
    
    list<asteroides*> aster;
    list<asteroides*>::iterator it_aster;
    int nAst = 5;
	for(int i=0; i<nAst; i++){
		aster.push_back(new asteroides(rand()%77+1, rand()%5 +2));		
	}
	    
    list<disparos*> disp;
    list<disparos*>::iterator it;
    
    bool game_over = false;
    
    int puntos = 0;
    
    while(!game_over){   	
    
    gotoxy(70,33); printf("Puntos %d", puntos);
    	
    	if(kbhit())
		{
    		char tecla = getch();
    		if(tecla == ESPACIO)
			disp.push_back(new disparos(nave.X() +2, nave.Y() -1));
			
		}
		for(it = disp.begin(); it != disp.end(); it++)
		{
			(*it)->mover(); 
			if((*it)->quitar()){
			gotoxy((*it)->X(), (*it)->Y()); printf(" ");
			delete(*it);
			it = disp.erase(it);	
			}
		}
    	
			
        
        for(it_aster = aster.begin(); it_aster != aster.end(); it_aster++){
        	(*it_aster)->mover();
        	(*it_aster)->choque(nave);
        	
		}
		
		for(it_aster = aster.begin(); it_aster != aster.end(); it_aster++ ){
			for(it = disp.begin(); it != disp.end(); it++){
				
				if((*it_aster)->X() == (*it)->X() && ((*it_aster)->Y() == (*it)->Y() || (*it_aster)->Y()+1 == (*it)->Y())){
					gotoxy((*it)->X(),(*it)->Y()); printf(" ");
					delete(*it);
					it = disp.erase(it);
					
					aster.push_back(new asteroides(rand()%77+1, 4));
					gotoxy((*it_aster)->X(),(*it_aster)->Y()); printf(" ");
					delete(*it_aster);
					it_aster = aster.erase(it_aster);
					
					puntos+=2;
				}
			}
		}
		int lvl = 1;
		int cant_punt = 50;
        nave.morir();
        nave.mover();
        Sleep(30);
        
    	if(nave.Vidas() < 0) game_over = true;
        
    	}
    	
    	nave.borrar();
    	gotoxy(37,14); printf("Game Over");	
    	gotoxy(16,33); printf("          ");
	    gotoxy(3,33); printf("           ");
	    gotoxy(70,33); printf("           ");
	    gotoxy(37,15); printf("Puntos %d ", puntos);
    
    	
    	
    	
    	
    	 
    return 0;
}


