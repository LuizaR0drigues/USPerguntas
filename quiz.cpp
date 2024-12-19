#include "quiz.h"

// CLASSE JOGADOR E SUAS FUNÇÔES
// construtor
Jogador::Jogador(const std::string aux_id, const std::string aux_senha)
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

std::map <std::string, int> Jogador::get_scores() const
{
    return _scores;
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
void Jogador::set_senha(const std::string senha)
{
    _senha = senha;
}
void Jogador::set_score(const std::string& chave, int valor) {
    _scores[chave] = valor;
}

void Jogador::leJogador(std::string linha){
    std::stringstream sLinha;
    std::string temp;

    //std::cout << linha << std::endl;

    sLinha.str(linha);

    getline(sLinha,temp,',');
    set_id(temp);

    getline(sLinha,temp,',');
    set_senha(temp);

    getline(sLinha,temp,',');
    set_scoregeral(stoi(temp));

    getline(sLinha,temp,',');
    _scores["mat_facil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["mat_difiil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["humanas_facil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["humanas_dificil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["bio_facil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["bio_dificil"] = stoi(temp);

    getline(sLinha,temp,',');
    _scores["lp_facil"] = stoi(temp);

    getline(sLinha,temp);
    _scores["lp_dificil"] = stoi(temp);

}

// CLASSE PERGUNTAS
// construtor da classe perguntas
Pergunta::Pergunta(const std::string &linhaCSV)
{
    _linha = linhaCSV;
    _alternativa = {};
    _resposta = '0';
}

//getters Perguntas
char Pergunta::get_resposta()
{
    return _resposta;
}

std::string Pergunta::get_dissertativa()
{
    return _resposta_diss;
}
std::string Pergunta::get_explic()
{
    return _explic;
}
std::string Pergunta::get_linha()
{
    return _linha;
}

//setters Perguntas
void Pergunta::set_linha(std::string auxlinha)
{
     _linha = auxlinha;
}
void Pergunta::set_dissertativa(std::string aux)
{
     _resposta_diss = aux;
}
void Pergunta::set_explic(std::string aux)
{
     _explic = aux;
}
void Pergunta::set_resposta(char resp)
{
     _resposta = resp;
}
//funcao responsavel por ler o arquivo, retirar os separadores e distribuir os dados entre as variaveos
bool Pergunta::gerar_perguntas(std::string linhacsv)
{
    // usando o regex para encontrar as vrigulas do csv
    std::regex item(R"([^;]+)");
    std::smatch resultado;
    std::vector<std::string> aux_valores;

    std::string aux_linha = linhacsv;

    // percorre a linha, encontra a virgula, quebra a string e armazena no auxiliar linha
    while (std::regex_search(aux_linha, resultado, item))
    {
        aux_valores.push_back(resultado.str(0));
        aux_linha = resultado.suffix().str();
    }

    // verificação
    if (aux_valores.size() < 7)
    { // linha = pergunat, 4 alternativa, resposta, explicação
        return false;
    }

    // passa a pergunta para a linha
    set_linha(aux_valores[0]);

    // transferes as alternativas pro seu vetor
    for (size_t i = 0; i < 4; i++)
    {
        _alternativa[i] = aux_valores[i + 1];
    }

    // transfere a resposta e explicacao para seus respectivos espacos
    set_resposta(aux_valores[5][0]); // pegando somente um caractere -> um char
    set_explic( aux_valores[6]);

    // impressão de perguntas
    std::cout << _linha << std::endl;
    std::cout << "A)" << _alternativa[0] << "    " << "B)" << _alternativa[1] << std::endl;
    std::cout << "C)" << _alternativa[2] << "    " << "D)" << _alternativa[3] << std::endl;

    if (verifica_alternativa()) //verificao da resposta do usuario
    {
        return true;
    }

    return false;
}

//funcao que gera perguntas e verifica resposta dissertativas
bool Pergunta::gerar_perguntasDissertativas(std::string linhacsv)
{
    // usando o regex para encontrar as vrigulas do csv
    std::regex item(R"([^;]+)");
    std::smatch resultado;
    std::vector<std::string> aux_valores;

    std::string aux_linha = linhacsv;

    // percorre a linha, encontra a virgula, quebra a string e armazena no auxiliar linha
    while (std::regex_search(aux_linha, resultado, item))
    {
        aux_valores.push_back(resultado.str(0));
        aux_linha = resultado.suffix().str();
    }

    // verificação
    if (aux_valores.size() < 7)
    { // linha = pergunta, 4 alternativa, resposta, explicação
        return false;
    }

    // passa a pergunta para a linha
    set_linha( aux_valores[0]);

    // transferes as alternativas pro seu vetor
    for (size_t i = 1; i < 5; i++)
    {
        _alternativa[i] = aux_valores[i + 1];
    }

    // transfere a resposta e explicacao para seus respectivos espacos
    set_dissertativa(aux_valores[6]);
    set_explic(aux_valores[7]);

    // impressão de perguntas
    std::cout << get_linha() << std::endl;
    if (verifica_texto())
    {
        return true; // validacao da resposta
    }

    return false;
}

bool Pergunta::verifica_texto()
{
    std::cout << "Escreva sua resposta: \n";
    std::string resposta_jogador;

    // requisitando a resposta do jagador
    std::cin >> resposta_jogador;

    // verificando a partir de substrings
    std::string resposta_correta = get_dissertativa();

    size_t pos = resposta_correta.find(resposta_jogador);
    
    if (pos != std::string::npos)
    {
        std::cout << "RESPOSTA CORRETA! +1 ponto \n";

        return true;
    }
    else
    {
        std::cout << "Resposta Incorreta!\n A resposta correta era: " << resposta_correta<< std::endl;
        return false;
    }
}

bool Pergunta::verifica_alternativa()
{
    // declaracao e requisicao da resposta do jogador
    char escolha, resposta;
    resposta = get_resposta();
    std::cin >> escolha;

    std::cout << "A resposta esperada era: " << resposta << std::endl;

    // verificao da alternativa correta

    switch (escolha){
    
    case 'A': case 'a': case 'B': case 'b': case 'C': case 'c': case 'D': case 'd':

        if (escolha == resposta || escolha == tolower(resposta))
        {
            std::cout << "PARABENS! RESPOSTA CORRETA! +1 ponto \n";
            return true;
        }
        else
        {
            std::cout << "Resposta Incorreta!\n"
                      << std::endl;
            std::cout << "A resposta esperada era: " << resposta << std::endl;
            return false;
        }
    default:

        std::cout << "Alternativa nao reconhecida, tente novamente.\n";
        return verifica_alternativa();
    }
}

// CLASSE ArquivosCSV

// Construtores e destrutores:

ArquivosCSV::ArquivosCSV()
{
    _stringJogadores = "jogadores.csv";
    _stringPerguntas = "";
}

ArquivosCSV::ArquivosCSV(std::string arqPerguntas, std::string arqJogadores)
{

    _stringJogadores = arqJogadores;
    _stringPerguntas = arqPerguntas;

    if (!arqPerguntas.empty())
    {
        _perguntasCSV.open(arqPerguntas, std::ios_base::in);
    }

    if (!arqJogadores.empty())
    {
        _jogadoresCSV.open(arqJogadores, std::ios_base::in);
    }
}

ArquivosCSV::~ArquivosCSV()
{

    if (_perguntasCSV.is_open())
    {
        _perguntasCSV.close();
    }

    if (_jogadoresCSV.is_open())
    {
        _jogadoresCSV.close();
    }
}

std::string ArquivosCSV::encontrarJogador(std::string nome, std::string senha){

std::string linha;
std::string nomeAtual;
std::stringstream sTemp;

    if (!_stringJogadores.empty())
    {
        if (_jogadoresCSV.is_open())
        {
            _jogadoresCSV.close();

        }
        _jogadoresCSV.open(_stringJogadores, std::ios::in);
    } else { 
        
        std::cout << "Não há nada em stringJogadores" << std::endl;
        return "";}

    if (!_jogadoresCSV.is_open())
    {
        _jogadoresCSV.open(_stringJogadores, std::ios::out);
    }

    if (!_jogadoresCSV.is_open())
    {
        std::cout << "O arquivo de jogadores não pode ser aberto" << std::endl;
        return "";
    }

    while (getline(_jogadoresCSV, linha)){
        sTemp.str(linha);
        getline(sTemp, nomeAtual, ',');
        if (nomeAtual == nome){

            return linha;
        }
    }

    return "";

}

bool ArquivosCSV::adicionarJogador(std::string nome, std::string senha)
{

    std::string nomeSalvo;

    if (!_stringJogadores.empty())
    {
        if (_jogadoresCSV.is_open())
        {
            _jogadoresCSV.close();
        }
        _jogadoresCSV.open(_stringJogadores, std::ios::in);
    }

    if (!_jogadoresCSV.is_open())
    {
        _jogadoresCSV.open(_stringJogadores, std::ios::out);
    }

    if (!_jogadoresCSV.is_open())
    {
        // std::cout << "O arquivo de jogadores não pode ser aberto" << std::endl;
        return false;
    }

    std::fstream jogadoresTemp;
    std::stringstream sTemp;
    jogadoresTemp.open("jogadores_temp.csv", std::ios::in);

    while (getline(_jogadoresCSV, nomeSalvo))
    {
         sTemp.str(nomeSalvo);
         getline(sTemp, nomeSalvo, ',');
         
        if (nomeSalvo == nome)
        {
            std::cout << "Erro: Nome de jogador ja existe. Tente outro nome..." << std::endl;
            _jogadoresCSV.close();
            jogadoresTemp.close();
            return false;
        } 
    }

    _jogadoresCSV.close();

    _jogadoresCSV.open(_stringJogadores, std::ios_base::out | std::ios_base::app);

    _jogadoresCSV << nome << "," << senha << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << "," << 0 << std::endl;

    jogadoresTemp.close();
    _jogadoresCSV.close();
    return true;
}

bool ArquivosCSV::alterarJogador(Jogador& jogador, std::string scoreType, int score)
{

    std::string linha, nomeSalvo;
    std::fstream jogadorTemp;
    std::stringstream sLinha, sLinha2;

    jogadorTemp.open("jogadores_temp.csv", std::ios::out);

    if (!jogadorTemp)
    {
        printf("Erro ao criar o arquivo temporario de jogadores");
        return false;
    }

    if (!_stringJogadores.empty())
    {
        if (_jogadoresCSV.is_open())
        {
            _jogadoresCSV.close();
        }
        _jogadoresCSV.open(_stringJogadores, std::ios::in);
    }

    if (!_jogadoresCSV.is_open())
    {
        _jogadoresCSV.open(_stringJogadores, std::ios::out);
    }

    if (!_jogadoresCSV.is_open())
    {
        return false;
    }

    Jogador temp;
    bool escrito = false;

    sLinha2 << jogador.get_Id() << "," << jogador.get_Senha() << ","  <<
    jogador.get_scoregeral() << "," << jogador.get_scores()["mat_facil"] <<
    ","<< jogador.get_scores()["mat_dificil"]
    << "," << jogador.get_scores()["humanas_facil"]<< "," << jogador.get_scores()["humanas_dificil"]
    << "," << jogador.get_scores()["bio_facil"]<< "," << jogador.get_scores()["bio_dificil"]
    << "," << jogador.get_scores()["lp_facil"]<< "," << jogador.get_scores()["lp_dificil"];


    std::string linhaJogador = sLinha2.str();

    
    if (_jogadoresCSV.eof()){

        jogadorTemp << linhaJogador << std::endl;

    } else {while (getline(_jogadoresCSV, linha)){


       temp.leJogador(linha);


        if ((temp < jogador || temp == jogador) && !escrito){
            jogadorTemp << linhaJogador << std::endl;
            escrito = true;

        }
        if (temp.get_Id() != jogador.get_Id()){
            jogadorTemp << linha << std::endl;
        }
    }}


    _jogadoresCSV.close();

    _jogadoresCSV.open(_stringJogadores, std::ios::out);

    jogadorTemp.close();
    jogadorTemp.open("jogadores_temp.csv", std::ios::in);
    
    jogadorTemp.seekg(0, std::ios_base::beg);

    while (getline(jogadorTemp, linha))
    {
        _jogadoresCSV << linha <<std::endl;
    }

    return false;
}

std::vector<std::string> ArquivosCSV::listaRanking(){

std::vector<std::string> nomesRanking(4);
std::string nome;
std::stringstream sNome;

    _jogadoresCSV.close();

    if(getStringJogadores().empty()){

        std::cout << "Não há um arguivo definido para jogadores." << std::endl;
        return nomesRanking;
    }

    _jogadoresCSV.open(_stringJogadores, std::ios::in);
 
    if (!_jogadoresCSV.is_open())
    {
        std::cout << "O arquivo de jogadores não pode ser aberto" << std::endl;
        return nomesRanking;
    }

    int i = 0;

    while( getline(_jogadoresCSV, nome)){
        sNome.str(nome);
        getline(sNome,nome,',');
        nomesRanking[i] = nome;
        std::cout << (i + 1) << " lugar: " << nomesRanking[i] << std::endl;
        i++;
    }
    return nomesRanking;
}

// Classe partida
std::string Partida::setFile(int N)
{
    switch (N)
    {
    case 1:
        setStringPerguntas("mat_facil.csv");
        break;
    case 2:
        setStringPerguntas("mat_dificil.csv");
        break;
    case 3:
        setStringPerguntas("humanas_facil.csv");
        break;
    case 4:
        setStringPerguntas("humanas_dificil.csv");
        break;
    case 5:
        setStringPerguntas("bio_facil.csv");
        break;
    case 6:
        setStringPerguntas("bio_dificil.csv");
        break;
    case 7:
        setStringPerguntas("lp_facil.csv");
        break;
    case 8:
        setStringPerguntas("lp_dificil.csv");
        break;
    }

    setStringJogadores("jogadores.csv");
    return getStringPerguntas();
}

int Partida::setTipo()
{
    std::cout << "Você prefere as ver as alternativas(1) ou escrever as respostas(2)?" << std::endl;
    int resp;
    std::cin >> resp;
    return resp;
}
int Partida::fazerPerguntas(int File)
{
    int N = 0;
    srand(time(NULL));

    std::string chave = setFile(File);
    std::stringstream sChave;
    sChave.str(chave);
    getline(sChave, chave, '.');

    std::string linha;
    std::vector<std::streampos> posicoes;

    if (!getStringPerguntas().empty())
    {
        if (getPerguntasCSV().is_open())
        {
            getPerguntasCSV().close();
        }
        getPerguntasCSV().open(getStringPerguntas(), std::ios::in);
    }

    if (!getPerguntasCSV().is_open())
    {
        printf("Nao foi possivel abrir o arquivo de perguntas");
        return 1;
    }

    // Descobrir quantas perguntas tem no arquivo
    int numPerguntas = 0;

    posicoes.push_back(getPerguntasCSV().tellg());

    while (getline(getPerguntasCSV(), linha))
    {
        numPerguntas++;
        posicoes.push_back(getPerguntasCSV().tellg());
    }

    getPerguntasCSV().clear();

    // Gerar os indexadores para as perguntas aleatórias:

    std::cout << "Quantas perguntas deseja resolver? Selecione um valor de 1 a "
    << numPerguntas << "." << std::endl;

    std::cin.exceptions(std::ios::failbit); 
    
    bool valido = false;

    while (!valido){
    try{
        std::cin >> N;
        if (N <= numPerguntas && N > 0){
            valido = true;} else {
                std::cout << "O numero digitado nao e valido. Tente novamente: " << std::endl;}
    }
    catch(std::ios_base::failure& ex){
        std::cout << "O numero digitado nao e valido. Tente novamente: " << std::endl;
    }}

    if ((numPerguntas) < N)
    {
        printf("ERROR: Number of integers in the interval is lesser than the"
               "range of the interval.");
        return -1;
    }

    int *numbers = (int *)malloc(sizeof(int) * (numPerguntas));
    int *noRepeat = (int *)malloc(sizeof(int) * (N));

    if (numbers == NULL || noRepeat == NULL)
    {
        printf("ERROR: Unable to allocate space for integer vectors");
    };

    for (int i = 0; i < numPerguntas; i++)
    {
        numbers[i] = i + 1;
    }

    int randN;

    for (int i = 0; i < N; i++)
    {

        if (numPerguntas == 1)
        {
            noRepeat[i] = numbers[0];
            continue;
        }

        randN = rand() % numPerguntas;

        noRepeat[i] = numbers[randN];
        numbers[randN] = numbers[numPerguntas - 1];
        numPerguntas--;
    }

    int score = 0;
    int opcao = setTipo();
    for (int i = 0; i < N; i++)
    {
        getPerguntasCSV().seekg(posicoes[noRepeat[i] - 1], getPerguntasCSV().beg);
        getline(getPerguntasCSV(), linha);
        if (opcao == 1)
        {
            score += gerar_perguntas(linha); // verificação ja esta dentro da função
        }
        if (opcao == 2)
        {
            score += gerar_perguntasDissertativas(linha); // verificação ja esta dentro da função
        }

    }

    free(numbers);
    free(noRepeat);

    int scoreGeral = 0;

    std::cout << "Sua pontuacao nessa partida foi de " << score << " pontos!" << std::endl;

    if (jogador.get_scores()[chave] < score){
        jogador.set_score(chave, score);

        std::cout << "Novo score: (" << jogador.get_scores()[chave] << ")" << std::endl;
        
        for (const auto& nota : jogador.get_scores()) {
            scoreGeral += nota.second;
        }
        jogador.set_scoregeral(scoreGeral);
        
        alterarJogador(jogador, chave, score);
    }

    return score;
}

// Classe jogo
Jogo::Jogo() : _arquivo("", "jogadores.csv")
{
}

void Jogo::descricaoInicial()
{

    std::cout << " *******************************************************\n";
    std::cout << "                         USPerguntas             \n";
    std::cout << " ********************************************************\n";

    std::cout << "O USPergunta é um jogo baseado no Jogo do Milhão, porém voltado para alunos do ensino médio\n";
    std::cout << "Há questões de 4 áreas do conhecimento e 2 níveis de dificuldades: \n"
              << " *mat_facil - mat_dificil\n"
              << " *humanas_facil - humanas_dificil\n"
              << " *bio_facil - bio_dificil\n"
              << " *lp_facil - lp_dificil\n"
              << std::endl;
}

int Jogo::menu()
{

    std::string sOpcao;

    std::cout << " *******************************************************\n";
    std::cout << "                         Menu             \n";
    std::cout << " ********************************************************\n";

    std::cout << "Deseja:\n"
              << "1) Criar seu usuario.\n"
              << "2) Inicia partida (deve ter criado um usuário).\n"
              << "3) Ver o ranking.\n"
              << "4) Sair do jogo.\n";

    std::cin >> sOpcao;

    while (sOpcao.size() > 1 || std::stoi(sOpcao) > 4 || std::stoi(sOpcao) < 1)
    {
        std::cout << "A opcao digitada é invalida, digite um numero entre 1 e 4.\n";
        std::cin >> sOpcao;
    }

    return std::stoi(sOpcao);
}

void Jogo::criarUsuario()
{

    std::string nick, senha;

    std::cout << " *******************************************************\n";
    std::cout << "                      Crie sua conta:                   \n";
    std::cout << " ********************************************************\n";

    std::cout << "Digite abaixo o seu Nick: \n";
    std::cin >> nick;
    std::cout << "Digite sua senha: \n";
    std::cin >> senha;

    std::cout << std::endl;

    bool valido = true;

    if (nick.find(',', 0) != std::string::npos){
            std::cout << "O Nick nao pode ter virgulas, tente novamente: " << std::endl;
            valido = false;
    }

    while (!valido || _arquivo.adicionarJogador(nick, senha) == false)
    {
        valido = true;

        std::cout << "Digite abaixo o seu Nick: \n";
        std::cin >> nick;
        std::cout << "Digite sua senha: \n";
        std::cin >> senha;

        std::cout << std::endl;

        if (nick.find(',', 0) != std::string::npos){
            std::cout << "O Nick nao pode ter virgulas, tente novamente: " << std::endl;
            valido = false;
        }
    }
}

bool Jogo::Login(Jogador& jogador)
{

    ArquivosCSV arquivo;
    std::string nick, senha;
    bool valido = false;
    std::string linha;

    std::cout << " *******************************************************\n";
    std::cout << "                      Faça seu login:                   \n";
    std::cout << " ********************************************************\n";

    while (!valido)
    {
        valido = true;
        std::cout << "Digite abaixo o seu Nick: \n";
        std::cin >> nick;
        std::cout << "Digite sua senha: \n";
        std::cin >> senha;

        std::cout << std::endl;

        linha = arquivo.encontrarJogador(nick,senha);

        if (linha.empty()){
            valido = false;
            std::cout << "Credenciais inválidas, tente novamente.";
        }
    }

    jogador.leJogador(linha);
    return true;
}

int Jogo::iniciarPartida(int cnt)
{

    std::string area;

    std::cout << " *******************************************************\n";
    std::cout << "                      Partida" << cnt << " \n";
    std::cout << " ********************************************************\n";

    std::cout << "Deseja iniciar qual tipo de partida?: \n"
              << "1) Matematica (facil).\n"
              << "2) Matematica (dificil).\n"
              << "3) Humanas (facil).\n"
              << "4) Humanas (dificil).\n"
              << "5) Biologia (facil)\n"
              << "6) Biologia (dificil).\n"
              << "7) Lingua Portuguesa (facil).\n"
              << "8) Lingua Portuguesa (dificil). \n"
              << std::endl;

    std::cin >> area;

    while (area.size() > 1 || std::stoi(area) > 8 || std::stoi(area) < 1)
    {
        std::cout << "A opcao digitada é invalida, digite um numero entre 1 e 8.\n";
        std::cin >> area;
    }

    return std::stoi(area);
}

void Jogo::ranking()
{

    std::string area;

    std::cout << " *******************************************************\n";
    std::cout << "                      Ranking! \n";
    std::cout << " ********************************************************\n";

    return ;
}
