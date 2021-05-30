     /*

    UNIVALI - Universidade do Vale do Itajaí
    Luigi Anacleto Giancoli e Leônidas Augusto Amaro
    Ciência da Computação - Algoritmos e Programação
    Jogo: ARKANOID
    Dezembro       2012

    */

//Bibliotecas
#include <iostream>
#include <conio2.h>
#include <windows.h>
#include <stdlib.h>

#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77

using namespace std;

//Rotinas
void telainicial(); //Constrói a tela inicial (bordas e título)
void menu(); //Inicia o Menu inicial para seleção das opições
void jogo(); //Inicia o Jogo
void gameover(); //Inicia a tela de fim de jogo
void rebatedor(); //Cria o ebatedor

//Variáveis
int tecla; //Tecla apertada pelo jogador
int lifes; //Vidas
int score; //Pontuação
int rx, ry; //Coluna e linha do rebatedor
int bx, by; //Coluna e linha da bolinha
int direcaos; //Direções Superiores
int direcaoi; //Direções Inferiores
int velo; //Velocidade
int bstart; //Variável para auxiliar o início aleatório da bolinha
int rebatidas; //Variável que conta o número de vezes que a bolinha rebate

//___Principal____________________________________

int main()
{

    system ("cls"); //Limpa a tela
    system ("mode 80, 40"); //Ajusta o tamanho da janela do Jogo
    SetCursor(_NOCURSOR);

    srand(time(NULL)); //Auxilia a criação de número aleatórios

    telainicial(); //Constrói a tela inicial (bordas e título)
    menu();  //Inicia o Menu inicial para seleção das opições

    textcolor(BLUE); //Muda a cor do texto para Azul

}

//_______________________________________________

//__________Jogo_________________________________

void jogo ()
{

    clrscr(); //Limpa a tela
    Sleep(100); //Aguarda 100 milisegundos

//Efeito Sonoro Inicial
    Beep (660 , 100);
    Beep (660 , 100);
    Beep (660 , 100);
    Beep (510 , 100);
    Beep (660 , 100);
    Beep (770 , 100);
    Beep (380 , 100);

//Desenhar Bordas
    textcolor(10);

     //Canto Superior Esquerdo.
    gotoxy(1,2);
    cout << "É";

    //Canto Superior Direito.
    gotoxy(80,2);
    cout << "»";

    //Borda Superior
    gotoxy(2,2);
      for (int cont=0; cont<78; cont++){
      cout << "Í";
      }

     //Borda Lateral Esquerda
     gotoxy(1,3);
       for (int cont=0; cont<33; cont++){
       cout <<"º\n";
       }

      //Borda Lateral Direita
      for (int cont=3; cont<36; cont++){
      gotoxy(80,cont);
      cout <<"º\n";
      }

    rebatedor(); //Cria o ebatedor

}

//________________________________________________________

//_______Rebatedor_________________________________________

void rebatedor()
{

    textcolor(WHITE); //Muda a cor do texto para branco

    rx=35; //Atribui um valor a variável da coluna do rebatedor
    ry=35; //Atribui um valor a variável da linha do rebatedor
    bx=rand()%76+4; //Atribui um valor aleatório a variável da coluna da bolinha
    by=14; //Atribui um valor a variável da linha da bolinha
    velo=120; //Atribui um valor inicial a variável que controla a velocidade
    bstart=0; //Auxilia o inicio aleatório da bolinha
    lifes=3; //Número inicial de vidas
    direcaoi=rand()%2; //Atribui um valor aleatório as Direções Inferiores da bolinha, para que ela começe caindo em um sentido aleatório
    direcaos=3; //Desativa inicialmente as Direções Superiores, para que a bolinha nunca comece no jogo subindo
    rebatidas=0; //Variável que conta o número de vezes que a bolinha rebate

//Rebatedor e Bolinha
    while (tecla != 27){ //Enqunanto a tecla ESC não for apertada...

//Verifica a tecla apertada
    if (kbhit()){
    tecla=getch(); // Variável "tecla" recebe o valor da tecla apertada
    }

//Verifica se a bolinha caiu
    if (by>ry){ //Verifica se a bolinha foi em uma linha igual maior que a linha do rebatedor
    Beep(300,100); //Efeito Sonoro
    Beep(350,120); //Efeito Sonoro
    lifes--; //Diminui 1 vida
    Sleep (1000); //Aguarda 1000 milisegundos para o jogo retornar
    bx=rand()%76+4; //Atribui um valor aleatório para a variável da coluna da bolinha, para que ela reinicie no jogo em um local aleatório
    by=14; //Atribui um valor a variável da linha da bolinha, para que ela reinicie no jogo sempre abaixo dos blocos
    direcaoi=rand()%2;//Caso o jogador perca uma vida, o sentido infeior da bolinha tem que mudar
    rebatidas=0;
    velo=120;
    }

//Desenha rebatedor.
    gotoxy(rx,ry);
    cout << "ÜÜÜÜÜÜÜÜÜ";

//Desenha bolinha
    gotoxy(bx,by);
    cout << "ø";

    Sleep(velo); // Velocidade da bolinha

    gotoxy(rx,ry);
    cout << "         ";

    gotoxy(bx, by);
    cout<< " ";

//Verifica se a seta direita foi apertada
     if (tecla==RIGHT){
     rx++; //Move para a direita
       if (rx>=72){
       rx--;
       }
     }

//Verifica se a seta esquerda foi apertada
     if (tecla==LEFT){
     rx--; //Move para a esquerda
       if (rx<=1){
       rx++;
       }
     }

//Verifica se a bolinha encosta no rebatedor
    if (by==34){
        if (bx==rx || bx==rx+1 || bx==rx+2 || bx==rx+3 || bx==rx+4 || bx==rx+5 || bx==rx+6 || bx==rx+7 || bx==rx+8){ //Verifica o contato com toda a área do rebatedor
            if (direcaoi!=3){ //Verifica se está caindo
            rebatidas=rebatidas+1; //Contagem de Rebatidas
            Beep(1000,100); //Efeito Sonoro

                if (direcaoi==2){ //Verifica se a bolinha encostou no rebatedor vindo no sentido Sudoeste
                direcaoi=3;//Desativa as Direções Inferiores para que a bolinha possa ser rebatida apenas para Direções Superiores
                direcaos=1;//Rebate ela no sentido Noroeste
                }

                if (direcaoi==1){ //Verifica se a bolinha encostou no rebatedor vindo no sentido Sudeste
                direcaoi=3; //Desativa as Direções Inferiores para que a bolinha possa ser rebatida apenas para Direções Superiores
                direcaos=2;//Rebate ela no sentido Nordeste
                }

                if (direcaoi==0){ //Verifica se a bolinha encostou no rebatedor vindo no sentido Sul
                direcaoi=3; //Desativa as Direções Inferiores para que a bolinha possa ser rebatida apenas para Direções Superiores
                direcaos=rand()%2; //Atribui um valor aleatório para as Direções Superiores
                }

            }
        }
    }

//Verifica se a bolinha encosta nas bordas

//Teto
    if (by==3){
    rebatidas=rebatidas+1; //Contagem de Rebatidas
    Beep(300,100); //Efeito Sonoro
        if (direcaos==0){
        direcaoi=rand()%2;
        }
        if (direcaos==1){
        direcaoi=2;
        }
        if (direcaos==2){
        direcaoi=1;
        }
    direcaos=3;
    }

//Borda Esquerda
    if (bx==2){
    rebatidas=rebatidas+1; //Contagem de Rebatidas
    Beep(300,100); //Efeito Sonoro
        if (direcaos!=3){ //Testa se está subindo
            if (direcaos==1){ //Testa se está vindo da direita
            direcaos=2; //Rebate para esquerda
            }
        }
        if(direcaoi!=3){ //Testa se está descendo
            if (direcaoi==2){ // Testa se está vindo da direita
            direcaoi=1; //Rebate para esquerda
            }
        }
    }

//Borda Direita
    if (bx==79){
    rebatidas=rebatidas+1; //Contagem de Rebatidas
    Beep(300,100); //Efeito Sonoro
        if (direcaos!=3){ //Testa se está subindo
            if (direcaos==2){ //Testa se está vindo da esquerda
            direcaos=1; //Rebate para esquerda
            }
        }
        if(direcaoi!=3){ //Testa se está descendo
            if (direcaoi==1){ // Testa se está vindo da esquerda
            direcaoi=2; //Rebate para esquerda
            }
        }
    }


//Direções superiores da Bolinha

//Verifica primeiro se abolinha está subindo
    if (direcaos!=3){

//Norte
    if(direcaos==0){
    by--;
    }

//Noroeste
    if (direcaos==1){
    bx--;
    by--;
    }

//Nordeste
    if (direcaos==2){
    bx++;
    by--;
    }

    }

//Direções inferiores da Bolinha

//Verifica primeiro se abolinha está subindo
     if(direcaoi!=3){

//Sul
    if (direcaoi==0){
    by++;
    }

//Sudeste
    if (direcaoi==1){
    bx++;
    by++;
    }

//Sudoeste
    if (direcaoi==2){
    bx--;
    by++;
    }

    }

//Aumenta 40% da velocidade a cada 10 rebatidas
    if (rebatidas==10){
    rebatidas=0;
    velo=velo-((velo*40)/100);
    }

//Pontuação
    textcolor(WHITE);

    gotoxy(2,1);
    cout << "ARKANOID - ";

//Score
    gotoxy(30,1);
    cout << "SCORE: " << score;

//Verifica se a tecla ESC foi apertada
     if(tecla==27){
     gameover();//Fecha o jogo;
     }

//Lifes
    gotoxy(15,1);

//3 vidas
        if (lifes==3){
        cout << "LIFES: ";
        textcolor(4);
        gotoxy(23,1);
        cout  <<(char)3;
        gotoxy(24,1);
        cout  <<(char)3;
        gotoxy(25,1);
        cout  <<(char)3;
        textcolor(WHITE);
        }

//2 vidas
        if (lifes==2){
        cout << "LIFES: ";
        textcolor(4);
        gotoxy(23,1);
        cout << (char)3;
        gotoxy(24,1);
        cout  <<(char)3;
         gotoxy(25,1);
        cout  <<" ";
        textcolor(WHITE);
        }

//1 vida
        if (lifes==1){
        cout << "LIFES: ";
        textcolor(4);
        gotoxy(23,1);
        cout  << (char)3;
        gotoxy(24,1);
        cout  <<" ";
        gotoxy(25,1);
        cout  <<" ";
        textcolor(WHITE);
        }
        if (lifes==0){
        gameover();
        }



    }

   textcolor(10);
}

//_____________________________________________________


//_______Game_Over____________________________________

void gameover()
{

    clrscr();
    textcolor(4);
    Sleep(100);

//Desenha o Título
    gotoxy(6,3);
    cout << " #####     #    #     # #######    ####### #     # ####### ######  ";
    Beep(800,100);
    Sleep (200);

    gotoxy(6,4);
    cout << "#     #   # #   ##   ## #          #     # #     # #       #     # ";
    Beep(775,100);
    Sleep (100);

    gotoxy(6,5);
    cout << "#        #   #  # # # # #          #     # #     # #       #     # ";
    Beep(750,100);
    Sleep (100);

    gotoxy(6,6);
    cout << "#  #### #     # #  #  # #####      #     # #     # #####   ######  ";
    Beep(725,100);
    Sleep (100);

    gotoxy(6,7);
    cout << "#     # ####### #     # #          #     #  #   #  #       #   #   ";
    Beep(700,100);
    Sleep (100);

    gotoxy(6,8);
    cout << "#     # #     # #     # #          #     #   # #   #       #    #  ";
    Beep(675,100);
    Sleep (100);

    gotoxy(6,9);
    cout << " #####  #     # #     # #######    #######    #    ####### #     # ";
    Beep(650,100);
    Sleep (100);

//Efeito Sonoro
    Beep(600,100);
    Beep(575,100);
    Beep(600,100);
    Beep(575,100);
    Beep(600,100);
    Beep(575,100);
    Beep(600,100);
    Beep(575,100);


//Recomeçar

//Mostra a Pontuação
        gotoxy(30,18);
        cout << "Vocˆ fez " << score << " pontos.";

//Desenha as opições
        gotoxy(30,20);
        cout <<"[1] Reiniciar Jogo";
        gotoxy(30,22);
        cout <<"[ESC] Sair";

//Verifica a tecla apertada
        kbhit();
        tecla=getch();

//Se apertar 1 recomeça o Jogo
        if(tecla==49){
        Beep (1200,100);
        jogo();
        }

//Se apertar ESC fecha o Jogo
        if(tecla==27)
        {
            Beep (1200,100);
            textcolor(WHITE);
            textbackground(BLUE);
            clrscr();

            gotoxy(3,3);
            cout<<"UNIVALI - Universidade do Vale do Itaja¡";
            gotoxy(3,4);
            cout<<"Luigi Anacleto Giancoli e Le“nidas Augusto Amaro";
            gotoxy(3,5);
            cout<<"Ciˆncia da Computa‡Æo - Algoritmos e Programa‡Æo";
            gotoxy(3,6);
            cout<<"Jogo: ARKANOID";
            gotoxy(3,7);
            cout<<"Dezembro/2012";
            gotoxy(3,12);
            cout<<"Precione qualquer tecla para fechar.";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        }

}
//_____________________________________________________

//_________Tela_Inicial___________________________________

void telainicial()
{

//Desenhar Bordas
    textcolor(10);

 //Canto Superior Esquerdo.
        gotoxy(1,1);
        cout << "É";

 //Canto Superior Direito.
        gotoxy(80,1);
        cout << "»";

 //Canto Inferior Esquerdo.
        gotoxy(1,39);
        cout << "È";

//Canto Inferior Direito.
        gotoxy(80,39);
        cout << "¼";

//Borda Superior
        gotoxy(2,1);
          for (int cont=0; cont<78; cont++){
          cout << "Í";
          }

//Borda Inferior.
        gotoxy(2,39);
          for (int cont=0; cont<78; cont++){
          cout << "Í";
          }

 //Borda Lateral Esquerda
          gotoxy(1,2);
            for (int cont=0; cont<37; cont++){
            cout <<"º\n";
            }

 //Borda Lateral Direita
            for (int cont=2; cont<39; cont++){
            gotoxy(80,cont);
            cout <<"º\n";
            }

//Título
    textbackground(BLACK);

//Desenha o Título
            for (int cor=0, cont=0; cor<=10, cont<5; cor++, cont++){
            textcolor(cor);

            gotoxy(4,3);
            cout<<"   ###    ########  ##    ##    ###    ##    ##  #######  #### ########  ";
            Beep (510 , 100);

            gotoxy(4,4);
            cout<<"  ## ##   ##     ## ##   ##    ## ##   ###   ## ##     ##  ##  ##     ## ";
            Beep (310 , 100);

            gotoxy(4,5);
            cout<<" ##   ##  ##     ## ##  ##    ##   ##  ####  ## ##     ##  ##  ##     ## ";
            Beep (200 , 100);

            gotoxy(4,6);
            cout<<"##     ## ########  #####    ##     ## ## ## ## ##     ##  ##  ##     ## ";
            Beep (910 , 70);

            gotoxy(4,7);
            cout<<"######### ##   ##   ##  ##   ######### ##  #### ##     ##  ##  ##     ##";
            Beep (600 , 70);

            gotoxy(4,8);
            cout<<"##     ## ##    ##  ##   ##  ##     ## ##   ### ##     ##  ##  ##     ## ";


            gotoxy(4,9);
            cout<< "##     ## ##     ## ##    ## ##     ## ##    ##  #######  #### ########  ";

            Sleep (200);
            }

//Efeito Sonoro
            Beep (510 , 100);
            Beep (310 , 100);
            Beep (510 , 120);
            Beep (1000 , 120);
            Beep (1000 , 70);
            Beep (1000 , 70);

}

//_____________________________________________________

//_________Menu________________________________________

void menu()
{

    textcolor(10);

//Desenha opições.
        gotoxy(30,20);
        cout <<"[1] Iniciar Jogo";
        gotoxy(30,22);
        cout <<"[ESC] Sair";

//Verifica a tecla digitada
    while (tecla!=49|| tecla!=27){

        kbhit();
        tecla=getch();

//Se apertar 1 recomeça o Jogo
        if(tecla==49){
        Beep (1200,100);
        jogo();
        break;
        }

//Se apertar ESC fecha o Jogo.
        if(tecla==27)
        {
            Beep (1200,100);
            textcolor(WHITE);
            textbackground(BLUE);
            clrscr();
            gotoxy(3,3);
            cout<<"UNIVALI - Universidade do Vale do Itaja¡";
            gotoxy(3,4);
            cout<<"Luigi Anacleto Giancoli e Le“nidas Augusto Amaro";
            gotoxy(3,5);
            cout<<"Ciˆncia da Computa‡Æo - Algoritmos e Programa‡Æo";
            gotoxy(3,6);
            cout<<"Jogo: ARKANOID";
            gotoxy(3,7);
            cout<<"Dezembro/2012";
            gotoxy(3,12);
            cout<<"Precione qualquer tecla para fechar.";
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            break;
            }
         }

}

//_____________________________________________________
