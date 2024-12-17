#include "quiz.h"
#include "sstream"

// CLASSE JOGADOR E SUAS FUNÇÔES
// construtor

Jogador::Jogador(const std::string aux_id , const std::string aux_senha )
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

std::string Jogador::get_Senha() const
{
    return _senha;
};

// setters
void Jogador::set_scoregeral(const int pontuacao)
{
    _scoregeral += pontuacao;
}
void Jogador::set_id(const std::string id)
{
    _id = id;
}


// CLASSE PERGUNTAS
//construtor da classe perguntas
Pergunta::Pergunta(const std::string& linhaCSV )
{
    _linha = linhaCSV;
    _alternativa = {};
    _resposta = '0';
}

bool Pergunta::gerar_perguntas(std::string linhacsv)
{
    //usando o regex para encontrar as vrigulas do csv
    std::regex item(R"([^,]+)");
    std::smatch resultado;
    std::vector<std::string> aux_valores;

    std::string aux_linha = linhacsv;

    //percorre a linha, encontra a virgula, quebra a string e armazena no auxiliar linha
    while(std::regex_search(aux_linha, resultado, item)){
        aux_valores.push_back(resultado.str(0));
        aux_linha = resultado.suffix().str();
    }

    //verificação
    if(aux_valores.size() < 7){ //linha = pergunat, 4 alternativa, resposta, explicação
        return false;
    }

    //passa a pergunta para a linha
    _linha = aux_valores[0];

    //transferes as alternativas pro seu vetor
    for(size_t i=0; i< 4; i++){
        _alternativa[i]= aux_valores[i+1];
    }

    //transfere a resposta e explicacao para seus respectivos espacos
    _resposta = aux_valores[5][0]; //pegando somente um caractere -> um char
    _explic = aux_valores[6];



    //impressão de perguntas
    std::cout << _linha << std::endl;
    std::cout << "A)" << _alternativa[0] <<  "    " << "B)" << _alternativa[1] <<std::endl;
    std::cout << "C)" << _alternativa[2] <<  "    " << "D)" << _alternativa[3] <<std::endl;
    return true;

}

char Pergunta::get_resposta(){
    return _resposta;
}

std::string Pergunta::get_dissertativa(){
    return _resposta_diss;
}

bool Pergunta::verifica_texto(){
    std::cout <<"Escreva sua resposta  somente com letras minusculas e sem caracteres especias";
    std::cout <<"A resposta correta é: \n";
    std::string resposta_jogador;
    std::string aux =std::string(1, get_resposta()); //tranformando em string

    //requisitando a resposta do jagador
    std::cin >> resposta_jogador;

    //verificando a partir de substrings
    std::string resposta_correta = get_dissertativa();

    size_t pos = resposta_correta.find(resposta_jogador);

    if(pos != std::string::npos){
        std::cout << "RESPOSTA CORRETA! +1 ponto";
        return true;
    }  
    else{
        return false;
    }

}

bool Pergunta::verifica_alternativa()
{   
    //declaracao e requisicao da resposta do jogador 
    char escolha;
    std::cin >> escolha;

    //verificao da alternativa correta
    switch (escolha)
    {
    case 'A':
        if(escolha == get_resposta())
        {
            std::cout << "PARABENS! RESPOSTA CORRETA! +1 ponto";
        }
        return true;
    case 'B':
        if(escolha == get_resposta())
        {
            std::cout << "PARABENS! RESPOSTA CORRETA! +1 ponto";
        }
        return true;
    case 'C':
        if(escolha == get_resposta())
        {
            std::cout << "PARABENS! RESPOSTA CORRETA! +1 ponto";
        }
        return true;
    case 'D':
        if(escolha == get_resposta())
        {
            std::cout << "PARABENS! RESPOSTA CORRETA! +1 ponto";
        }
        return true;
    
    default:
        return false;
    }

    return false;
}


// CLASSE ArquivosCSV

// Construtores e destrutores:
ArquivosCSV::ArquivosCSV (std::string arqPerguntas, std::string arqJogadores){
    
    _stringJogadores = arqJogadores;
    _stringPerguntas = arqPerguntas;
    
    if (!arqPerguntas.empty()){
        _perguntasCSV.open(arqPerguntas, std::ios_base::in);
        //std::cout << "Aberto o arquivo de perguntas no construtor" << std::endl;
    }


    if (!arqJogadores.empty()){
        _jogadoresCSV.open(arqJogadores, std::ios_base::in);
        //std::cout << "Aberto o arquivo de jogadores no construtor" << std::endl;
    }
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
    std::vector <std::streampos> posicoes;

    if(!_stringPerguntas.empty()){
        if (_perguntasCSV.is_open()){
            _perguntasCSV.close();
        }
        _perguntasCSV.open(_stringPerguntas, std::ios::in);
    }

    if (!_perguntasCSV.is_open()){
        printf("Nao foi possivel abrir o arquivo de perguntas");
        return 1;
    }

    // Descobrir quantas perguntas tem no arquivo
    int numPerguntas = 0;
    while (getline(_perguntasCSV, linha)){
        numPerguntas++;
     //   std::cout << _perguntasCSV.tellg() << std::endl;
        posicoes.push_back(_perguntasCSV.tellg());
    }

    _perguntasCSV.clear(); 

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


    int score = 0;

    for (int i = 0; i <num ; i++){
        _perguntasCSV.seekg(posicoes[noRepeat[i]-1], _perguntasCSV.beg);
        getline (_perguntasCSV, linha);
        //score += _pergunta.GerarPergunta();

        //std::cout << noRepeat[i] << ": " << linha << std::endl;
    } 

free (numbers);
free(noRepeat);
return 0;
}

bool ArquivosCSV::adicionarJogador(std::string nome, std::string senha){

    std::string nomeSalvo;
  
    if(!_stringJogadores.empty()){
         //   std::cout << "Temos uma string de jogadores" << std::endl;
        if (_jogadoresCSV.is_open()){
            _jogadoresCSV.close();
         //   std::cout << "Fechando o arquivo de jogadores que estava aberto" << std::endl;
        }
        _jogadoresCSV.open(_stringJogadores, std::ios::in);
    }

    if (!_jogadoresCSV.is_open()){
        _jogadoresCSV.open(_stringJogadores, std::ios::out);
    }

    if (!_jogadoresCSV.is_open()){
        //std::cout << "O arquivo de jogadores não pode ser aberto" << std::endl;
        return false;
    }

    while (getline(_jogadoresCSV, nomeSalvo, ',')){
        //std::cout << "("<< nomeSalvo << "=" << nome << ")" << std::endl;
        if (nomeSalvo == nome){
            std::cout << "Erro: Nome de jogador ja existe." << std::endl;
            _jogadoresCSV.close();
            return false;
        }
        getline(_jogadoresCSV,nomeSalvo);
    }

    _jogadoresCSV.close();

    _jogadoresCSV.open(_stringJogadores, std::ios_base::out | std::ios_base::app);
    _jogadoresCSV << nome << "," << senha << "," << 0 << "," << 0  << "," << 0 <<
     "," << 0 << "," << 0 << "," << 0 <<"," << 0 <<"," << 0 <<"," << 0 <<std::endl;

    return true;
}

std::string alterarScores(std::string linha, std::string scoreType, int score){

    std::stringstream sLinha(linha);
    //std::cout << linha << std::endl;

    std::vector <std::string> vScores;
    int i = 0;
    int scoreNum = 0;

    if (scoreType == "geral"){
        scoreNum = 2;
    } else if (scoreType == "mat_facil"){
        scoreNum = 3;
    } else if (scoreType == "mat_dificil"){
        scoreNum = 4;
    } else if (scoreType == "humanas_facil"){
        scoreNum = 5;
    } else if (scoreType == "humanas_dificil"){
        scoreNum = 6;
    } else if (scoreType == "bio_facil"){
        scoreNum = 7;
    } else if (scoreType == "bio_facil"){
        scoreNum = 8;
    } else if (scoreType == "lp_facil"){
        scoreNum = 9;
    } else if (scoreType == "lp_facil"){
        scoreNum = 10;
    }

    std::string temp;

    while (getline(sLinha, temp, ',')){
        vScores.push_back(temp);
       // std::cout << vScores[i] << ",";
        i++;
    }

    getline(sLinha, temp);
    vScores.push_back(temp);

    std::stringstream sLinha2;

    //std::cout << "vScore[" << scoreNum << "] " << std::stoi(vScores[scoreNum]) << " < " << score << "?" << std::endl;

    if (std::stoi(vScores[scoreNum]) < score){
        vScores[scoreNum] = std::to_string(score);
        std::cout << "vscore[3] = " << vScores[3] << std::endl;

        sLinha2 << vScores[0] << "," << vScores[1] << "," << vScores[2] << "," 
       << vScores[3] << "," << vScores[4] << "," << vScores[5] << "," 
       << vScores[6] << "," << vScores[7] << "," << vScores[8] << "," 
       << vScores[9] << "," << vScores[10] << std::endl;

       linha = sLinha2.str();
       //std::cout << linha << std::endl;
    } 

    //std::cout << linha;

return linha;
}

bool ArquivosCSV::alterarJogador(std::string nome, std::string scoreType, int score){

    std::string linha, nomeSalvo;
    std::fstream jogadorTemp;
    std::stringstream sLinha;

    jogadorTemp.open("jogadores_temp.csv", std::ios::out | std::ios::in);

    if (!jogadorTemp){
        printf("Erro ao criar o arquivo temporario de jogadores");
        return false;
    }

    if(!_stringJogadores.empty()){
         //   std::cout << "Temos uma string de jogadores" << std::endl;
        if (_jogadoresCSV.is_open()){
            _jogadoresCSV.close();
         //   std::cout << "Fechando o arquivo de jogadores que estava aberto" << std::endl;
        }
        _jogadoresCSV.open(_stringJogadores, std::ios::in);
    }

    if (!_jogadoresCSV.is_open()){
        _jogadoresCSV.open(_stringJogadores, std::ios::out);
    }

    if (!_jogadoresCSV.is_open()){
        //std::cout << "O arquivo de jogadores não pode ser aberto" << std::endl;
        return false;
    }

    while (getline(_jogadoresCSV, linha)){
        //std::cout << "("<< nomeSalvo << "=" << nome << ")" << std::endl;
        sLinha.str(linha);
        getline(sLinha, nomeSalvo, ',');
        if (nomeSalvo != nome){
            jogadorTemp << linha;
        } else {
            jogadorTemp << alterarScores(linha, scoreType, score);
        }
    }

    _jogadoresCSV.close();

    _jogadoresCSV.open(_stringJogadores, std::ios::in);

    jogadorTemp.seekg(0,std::ios_base::beg);

    while (getline(jogadorTemp, linha)){
        _jogadoresCSV << linha;
        //std::cout << "_jogadoresCSV recebeu: " << linha << std::endl;
    }

    return false;

}

//Classe Jogo
