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
   Jogador(const std::string aux_id = "", const std::string aux_senha = "")
   {
        _id = aux_id;
        _senha =  aux_senha;
        _scoregeral = 0;
        _scores = {};
   };
    //Verifica se as credenciais do jogador estao corretas
    bool identificar_player(std::string nome, std::string senha){
        if(_id.compare(nome) == 0  && _senha.compare(senha) == 0)
            return true;
        else 
            return false;
    };

    //operadores
    
    
};
