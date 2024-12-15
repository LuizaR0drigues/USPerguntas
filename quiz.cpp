#include "quiz.h"
// CLASSE JOGADOR E SUAS FUNÇÔES
// construtor
/*
Jogador::Jogador(const std::string aux_id = "", const std::string aux_senha = "")
{
    _id = aux_id;
    _senha = aux_senha;
    _scoregeral = 0;
    _scores = {};
};

// Metodos
// Verifica se as credenciais do jogador estao corretas
bool Jogador::identificar_player(std::string nome, std::string senha)
{
    if (_id.compare(nome) == 0 && _senha.compare(senha) == 0)
        return true;
    else
        return false;
};

// operadores
// operador responsavel por compara se a pont_playerA > pont_playerB
bool operator>(const Jogador &player_A, const Jogador &player_B)
{
    return player_A._scoregeral > player_B._scoregeral;
}

// operador responsavel por compara se a pont_playerA < pont_playerB
bool operator<(const Jogador &player_A, const Jogador &player_B)
{
    return player_A._scoregeral < player_B._scoregeral;
}
// operador responsavel por compara se a pont_playerA == pont_playerB
bool operator==(const Jogador &player_A, const Jogador &player_B)
{
    return player_A._scoregeral == player_B._scoregeral;
}

// getters
int Jogador::get_scoregeral() const
{
    return _scoregeral;
};

std::string Jogador::get_Id() const
{
    return _id;
};

// setters
void Jogador::set_scoregeral(const int pontuacao)
{
    _scoregeral = pontuacao;
}
void Jogador::set_id(const std::string id)
{
    _id = id;
}
*/
// CLASSE PERGUNTAS


// CLASSE ArquivosCSV

// Construtores e destrutores:
ArquivosCSV::ArquivosCSV (std::string arqPerguntas, std::string arqJogadores){
    
    if(!arqPerguntas.empty())
    _perguntasCSV.open(arqPerguntas);

    if(!arqJogadores.empty())
        _jogadoresCSV.open(arqJogadores);

}

ArquivosCSV::~ArquivosCSV(){

    if (_perguntasCSV.is_open()){
        _perguntasCSV.close();
    }

    if (_jogadoresCSV.is_open()){
        _jogadoresCSV.close();
    }
}

int ArquivosCSV::fazerPerguntas(int N){
    int n;
    std::string linha;

    if (!_perguntasCSV.is_open()){
        printf("Nao foi possivel abrir o arquivo de perguntas");
        return 1;
    }

    // Descobrir quantas perguntas tem no arquivo
    int numPerguntas = 0;
    while (getline(_perguntasCSV, linha)){
        numPerguntas++;
    }

    numPerguntas--;
    int num = numPerguntas;

    // Gerar os indexadores para as perguntas aleatórias:

    if ((numPerguntas) < N){
        printf ("ERROR: Number of integers in the interval is lesser than the"
         "range of the interval.");
        return -1;
    }

    int* numbers = (int*) malloc(sizeof(int) * (numPerguntas));
    int* noRepeat = (int*) malloc(sizeof(int) * (N));

    if (numbers == NULL || noRepeat == NULL){
        printf ("ERROR: Unable to allocate space for integer vectors");
    };

    for (int i = 0; i < numPerguntas; i++) {
        numbers[i] = i+1;
    }

    int randN;

    for (int i = 0; i < N; i++) {

        if (numPerguntas == 1){
            noRepeat[i] = numbers[0];
            continue;
        }

        randN = rand() % numPerguntas;

        noRepeat[i] = numbers[randN];
        numbers[randN] = numbers[numPerguntas-1];
        numPerguntas--;
    }

    /*
    for (int i = 0; i <num ; i++){
        std::cout << noRepeat[i] << std::endl;
    } */

free (numbers);
free(noRepeat);

}
