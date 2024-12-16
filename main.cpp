#include "quiz.h"

int main(){
    ArquivosCSV arquivos("perguntas.csv","jogadores.csv");
    arquivos.fazerPerguntas(10);

    Pergunta p;
    std::string texto = "Qual é o valor de x na equação 3x−5=10?,5,3,7,15,C)5,Resolva a equação: 3x−5=10 Adicione 5 em ambos os lados: 3x=15 Agora, divida ambos os lados por 3: x=5";

    p.gerar_perguntas(texto);
}