#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

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

    //setters
    void set_scoregeral(const int pontuacao);
    void set_id(const std::string id);

    //destrutor
   
};






#endif