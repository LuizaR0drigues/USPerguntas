#include "quiz.h"
//construtor
Jogador::Jogador(const std::string aux_id = "", const std::string aux_senha = "")
   {
        _id = aux_id;
        _senha =  aux_senha;
        _scoregeral = 0;
        _scores = {};
   };

//Metodos
    //Verifica se as credenciais do jogador estao corretas
    bool Jogador::identificar_player(std::string nome, std::string senha){
        if(_id.compare(nome) == 0  && _senha.compare(senha) == 0)
            return true;
        else 
            return false;
    };

    
    //operadores
    //operador responsavel por compara se a pont_playerA > pont_playerB
    bool operator>(const Jogador& player_A, const Jogador& player_B) {
        return player_A._scoregeral > player_B._scoregeral;
    }

    bool operator<(const Jogador& player_A, const Jogador& player_B) {
        return player_A._scoregeral < player_B._scoregeral;
    }

    bool operator==(const Jogador& player_A, const Jogador& player_B) {
        return player_A._scoregeral == player_B._scoregeral;
    }

    //getters
    
    int Jogador:: get_scoregeral() const {
        return _scoregeral;
    };

    std::string Jogador::get_Id() const{
        return _id;
    };

    //setters
    void Jogador::set_scoregeral(const int pontuacao)
    {
        _scoregeral = pontuacao;
    }
    void Jogador::set_id(const std::string id)
    {
        _id = id;
    }

  