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
    friend bool operator>(const Jogador& player_A, const Jogador& player_B);
    friend bool operator<(const Jogador& player_A, const Jogador& player_B);
    friend bool operator==(const Jogador& player_A, const Jogador& player_B);
    
    //getters
    int get_scoregeral() const;
    std::string get_Id() const;
    std::string get_Senha() const;

    //setters
    void set_scoregeral(const int pontuacao);
    void set_id(const std::string id);

   
};

// CLASSE PERGUNTA e DERIVADAS
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
    bool verifica_texto();
    bool verifica_alternativa();

    //getters
    char get_resposta();
    std::string get_dissertativa();
    
    
};

class ArquivosCSV{

private:
    std::fstream _perguntasCSV;
    std::fstream _jogadoresCSV;
    std::string _stringPerguntas;
    std::string _stringJogadores;
    

public:

    // Construtor da classe ArquivosCSV
    ArquivosCSV(std::string arqPerguntas, std::string arqJogadores);
    /* São inseridos os nomes dos dois arquivos, para que possam ser abertos e
    manipulados pela classe, se não for necessário manipular um dos arquivos, 
    deixar a string vazia */

    // Destrutor da classe ArquivosCSV
    ~ArquivosCSV();

    void setPerguntas(std::string arquivo);
    void setJogadores(std::string arquivo);
    int fazerPerguntas(int N);
    bool adicionarJogador(std::string nome, std::string senha);
    bool alterarJogador(std::string nome, std::string scoreType, int score);
    /* Essa função altera o score "scoreType" do jogador dado por "nome", no
    caso em que o score fornecido é maior que o atual */
    

};


class Jogo: private Jogador, private Pergunta, private ArquivosCSV{
    public:

    private:
    int fazerPerguntas(int n);

};

#endif