#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <regex>
#include <map>
#include <fstream>
#include <vector>
#include "sstream"
#include <time.h>

//classe responsavel por identificar e armazenar informacoes sobre o jogador
//tambem realizara a autentificacao
class Jogador
{
private:
    /* data */
    std::string _id;
    std::string _senha;
    std::map<std::string, int>_scores;
    int _scoregeral;
public:
    //construtor da classe jogador
    Jogador(const std::string aux_id = "", const std::string aux_senha = "");

    //metodos e operadores
    bool identificar_player(std::string nome, std::string senha);
    void leJogador(std::string linha);
    friend bool operator>(const Jogador& player_A, const Jogador& player_B);
    friend bool operator<(const Jogador& player_A, const Jogador& player_B);
    friend bool operator==(const Jogador& player_A, const Jogador& player_B);
    
    //getters
    int get_scoregeral() const;
    std::string get_Id() const;
    std::string get_Senha() const;
    std::map<std::string, int> get_scores() const;


    //setters
    void set_scoregeral(const int pontuacao);
    void set_id(const std::string id);
    void set_senha(const std::string senha);
    void set_score(const std::string& chave, int valor);
   
};

// CLASSE PERGUNTA 
class Pergunta
{
private:
    std::string _linha;
    std::array <std::string, 4> _alternativa;
    std::string _explic;
    std::string _resposta_diss; //resposta para o caso dissertativo
    char _resposta;
    
public:
    Pergunta(const std::string& linhaCSV = "");
    bool gerar_perguntas(std::string linhaCSV);
    bool gerar_perguntasDissertativas(std::string linhaCSV);
    bool verifica_texto();
    bool verifica_alternativa();

    //getters
    char get_resposta();
    std::string get_dissertativa();
    std::string get_explic();
    std::string get_linha();
    void set_dissertativa(std::string aux);
    void set_explic(std::string aux);
    void set_linha(std::string auxLinha);
    void set_resposta(char resp);
    
};

class ArquivosCSV{

private:
    std::fstream _perguntasCSV;
    std::fstream _jogadoresCSV;
    std::string _stringPerguntas;
    std::string _stringJogadores;
    

public:

    // Construtores da classe ArquivosCSV
    ArquivosCSV(std::string arqPerguntas, std::string arqJogadores);
    /* São inseridos os nomes dos dois arquivos, para que possam ser abertos e
    manipulados pela classe, se não for necessário manipular um dos arquivos, 
    deixar a string vazia */

    ArquivosCSV();
    /* Nesse construtor, ambas as strings são inicializadas vazias*/

    // Destrutor da classe ArquivosCSV
    ~ArquivosCSV();

    void setPerguntas(std::string arquivo);
    void setJogadores(std::string arquivo);
    bool adicionarJogador(std::string nome, std::string senha);
    bool alterarJogador(Jogador& jogador, std::string scoreType, int score);
    /* Essa função altera o score "scoreType" do jogador dado por "nome", no
    caso em que o score fornecido é maior que o atual */
    std::string encontrarJogador(std::string nome, std::string senha);
    std::vector <std::string> listaRanking();
    
    // Getters:
    std::fstream& getPerguntasCSV() {
        return _perguntasCSV;
    }

    std::fstream& getJogadoresCSV() {
        return _jogadoresCSV;
    }

    const std::string& getStringPerguntas() const {
        return _stringPerguntas;
    }

    const std::string& getStringJogadores() const {
        return _stringJogadores;
    }

    void setStringPerguntas(const std::string& stringPerguntas) {
        _stringPerguntas = stringPerguntas;
    }

    void setStringJogadores(const std::string& stringJogadores) {
        _stringJogadores = stringJogadores;
    }
    // Setters:

};


class Partida: private Pergunta, public ArquivosCSV{
    private:

    public:
    Jogador jogador;
    int fazerPerguntas(int File);
    std::string setFile(int N);
    int setTipo();

};

class Jogo {
    private:
        std::string _nick, _senha;
        ArquivosCSV _arquivo;

    public:
        Jogo();
        void descricaoInicial();
        void criarUsuario();
        bool Login(Jogador& jogador);
        int iniciarPartida(int cntPartida);
        int menu();
        void ranking();
};

#endif