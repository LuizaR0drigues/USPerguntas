#include "quiz.h"

int main(){/*
    ArquivosCSV arquivos("perguntas.csv","jogadores.csv");
    arquivos.fazerPerguntas(10);

    Pergunta p;
    std::string texto = "Qual é o valor de x na equação 3x−5=10?,5,3,7,15,C)5,Resolva a equação: 3x−5=10 Adicione 5 em ambos os lados: 3x=15 Agora, divida ambos os lados por 3: x=5";

    p.gerar_perguntas(texto);*/

    ArquivosCSV arquivos("perguntas.csv","jogadores.csv");

    std::string nick, senha, area;

    std::cout << " *******************************************************\n";
    std::cout << "                         USPerguntas             \n";
    std::cout << " ********************************************************\n";

    std::cout << " O USPergunta é um jogo baseado no Jogo do Milhão, porém voltado para alunos do ensino médio\n";
    std::cout << "Há questões de 4 áreas do conhecimento e 2 níveis de dificuldades: \n"
              << " *mat_facil - mat_dificil\n"
              << " *humanas_facil - humanas_dificil\n"
              << " *bio_facil - bio_dificil\n"
              << " *lp_facil - lp_dificil\n"
              << "Digite abaixo o seu Nick: \n";
    std::cin >> nick;
    std::cout << "Senha: \n";
    std::cin >> senha;

    arquivos.adicionarJogador(nick, senha);
    arquivos.alterarJogador(nick, "mat_facil", 10);

    /*
    while (true) {
        std::cout << "\nDigite qual área/nível você gostaria, seguindo o padrão area_dificuldade (ou digite X para sair): \n";
        std::cin >> area;

        if (area == "X") {
            std::cout << "Saindo do jogo... Até a próxima!\n";
            break;
        } else if (area == "mat_facil") {
            
        } else if (area == "mat_dificil") {
           
        } else if (area == "humanas_facil") {
           
        } else if (area == "humanas_dificil") {
            
        } else if (area == "bio_facil") {
          
        } else if (area == "bio_dificil") {
            
        } else if (area == "lp_facil") {
           
        } else if (area == "lp_dificil") {
            
        } else {
            std::cout << "Área/dificuldade não reconhecida. Por favor, verifique o padrão e tente novamente!\n";
        }
    } */

    return 0;
}