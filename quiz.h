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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
    bool gerar_perguntasDIssertativas(std::string linhaCSV);
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
    //int fazerPerguntas(int N);
    bool adicionarJogador(std::string nome, std::string senha);
    bool alterarJogador(std::string nome, std::string scoreType, int score);
    /* Essa função altera o score "scoreType" do jogador dado por "nome", no
    caso em que o score fornecido é maior que o atual */
    
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


class Partida: private Jogador, private Pergunta, public ArquivosCSV{
    private:

    public:
    int fazerPerguntas(int n, int File);
    void setFile(int N);
    int setTipo();

};

class Jogo {
    private:
        std::string _nick, _senha;
        ArquivosCSV _arquivo;
        std::string texto;

    public:
        std::string descricaoInicial();
        void criarUsuario();
        int iniciarPartida(int cntPartida);
        int menu();
        Jogo();
};

//Interface
class Interface : private Partida, private Jogo
{
private:
    int pos;
    bool press, theselct;
    sf::RenderWindow *window;
    sf::RectangleShape *winclose;
    sf::Font *font;
    std::string descricao;

    sf::Vector2i posic_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char *> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    

protected:
    void loop_events();
    void draw_all();

public:
    Interface();
    ~Interface();
    void set_menu();
    void set_init();
    void set_retangulos(std::string& id, std::string& senha);
    void run_Interface();
    void caixa_textoUser(); //recebe os valores escritos

};

#endif