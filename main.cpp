#include "quiz.h"

int main(){
   
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
            jogo.login();
            area = jogo.iniciarPartida(cntPartidas);
            partida.setFile(area);
            // *. Perguntar quantas perguntas fazer na partida
            partida.fazerPerguntas(10, area);

            caso = jogo.menu();
            break;

            case 3:

            caso = jogo.menu();
            break;

            case 4:
            return 0;
        }
    }



    return 0;
}