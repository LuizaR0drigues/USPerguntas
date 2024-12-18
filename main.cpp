#include "quiz.h"

int main(){
     Interface *menu = new Interface();
    menu->run_Interface();
    delete menu;
    
   /*0
    Jogo jogo;
    Partida partida;

    jogo.descricaoInicial();
    int caso = jogo.menu();

    int area;
    int cntPartidas = 0;


    while (1){
        switch (caso){
            case 1:
            jogo.criarUsuario();
            caso = jogo.menu();
            break;

            case 2:
            area = jogo.iniciarPartida(cntPartidas);
            partida.setFile(area);
            partida.fazerPerguntas(5, area);

            caso = jogo.menu();
            break;

            case 3:

            caso = jogo.menu();
            break;

            case 4:
            return 0;
        }
    }
*/


    return 0;
}