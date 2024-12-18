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
            jogo.Login(partida.jogador);

           /* std::cout << "Jogador após o LOGIN: " << partida.jogador.get_Id() << "," << partida.jogador.get_Senha() << "," <<
            partida.jogador.get_scoregeral() << "," << partida.jogador.get_scores()["mat_facil"] <<
            ","<< partida.jogador.get_scores()["mat_dificil"] << "," 
            << partida.jogador.get_scores()["humanas_facil"]<< "," << partida.jogador.get_scores()["humanas_dificil"]
            << "," << partida.jogador.get_scores()["bio_facil"]<< "," << partida.jogador.get_scores()["bio_dificil"]
            << "," << partida.jogador.get_scores()["lp_facil"]<< "," << partida.jogador.get_scores()["lp_dificil"] << std::endl;*/

            area = jogo.iniciarPartida(cntPartidas);
            partida.setFile(area);
            // *. Perguntar quantas perguntas fazer na partida
            partida.fazerPerguntas(3, area);

            caso = jogo.menu();
            break;

            case 3:
            caso = jogo.menu();
            break;

            case 4:
            jogo.ranking();
            return 0;
        }
    }



    return 0;
}