#include "quiz.h"

int main(){
   
    Jogo jogo;
    Partida partida;

    jogo.descricaoInicial();
    int caso = jogo.menu();

    int area;
    int cntPartidas = 0;
    int qtd;


    while (1){
        switch (caso){
            case 1:
            jogo.criarUsuario();
            caso = jogo.menu();
            break;

            case 2:
            jogo.Login(partida.jogador);

            area = jogo.iniciarPartida(cntPartidas);
            partida.setFile(area);
            // *. Perguntar quantas perguntas fazer na partida
            std::cout<< "Quantas perguntas voce gostaria de responder? \nObs: Máximo 10\n";
            std::cin >>qtd;;
            partida.fazerPerguntas(qtd, area);

            caso = jogo.menu();
            break;

            case 3:
            jogo.ranking();
            partida.listaRanking();
            caso = jogo.menu();
            break;

            case 4:
            return 0;
        }
    }



    return 0;
}