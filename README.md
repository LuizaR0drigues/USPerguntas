# USPerguntas
Faltaria uma quinta classe, estou pensando o que poderia ser...
---

Etapas do Desenvolvimento


---

1) Criação dos Arquivos CSV

Será necessário criar diferentes arquivos CSV para cada combinação de área de conhecimento e nível de dificuldade.

Exemplo de Arquivos:

matematica_dificil.csv

quimica_facil.csv


Cada arquivo conterá:

Perguntas

Respostas possíveis

Resposta correta (no caso de múltipla escolha, indica o número da questão correta)

Pontuação da questão


As perguntas serão divididas em:

Múltipla Escolha: Incluem várias respostas possíveis, com apenas uma correta.

Dissertativas: Requerem que o jogador forneça uma resposta textual, sendo apenas uma a resposta esperada.



---

2) Classe Jogador

Essa classe será responsável por armazenar informações do jogador e realizar sua autenticação.

Atributos:

std::string id: Identificação do jogador.

std::string senha: Senha do jogador.

std::map<std::string, int> scores: Um mapa contendo os scores por matéria e nível (Ex.: "matematica_dificil" -> 50).

int scoreGeral: Pontuação total do jogador.


Métodos:

bool identificar(std::string nome, std::string senha)

Verifica se as credenciais do jogador estão corretas.

Retorna true para credenciais válidas e false caso contrário.



Sobrecarga de Operadores:

Utilizar os operadores > e < para comparar dois jogadores por seu score geral.



---

3) Classe Abstrata Pergunta e Classes Derivadas

A classe Pergunta será abstrata, com as classes derivadas implementando os diferentes tipos de perguntas.

Métodos:

bool gerarPergunta(std::string linhaCSV)

Recebe uma linha do CSV.

Gera a pergunta e solicita a resposta do jogador.

Retorna true se a resposta for correta e false caso contrário.



Implementações nas Classes Derivadas:

PerguntaMultiplaEscolha:

Exibe as opções de resposta e valida a escolha do jogador.


PerguntaDissertativa:

Verifica se a resposta textual fornecida corresponde à esperada.



Conceitos Aplicados:

Polimorfismo e Herança: Os métodos são implementados de forma diferente em cada subclasse, exemplificando esses conceitos.



---

4) Classe ArquivosCSV

Esta classe será responsável pela leitura e manipulação dos arquivos CSV, utilizando a biblioteca <fstream> para maior flexibilidade e segurança.

Atributos:

std::ifstream perguntasCSV: Para leitura dos arquivos de perguntas.

std::ofstream jogadoresCSV: Para gravação e leitura dos dados dos jogadores.

Pergunta pergunta: Objeto responsável por gerar e validar perguntas.


Métodos:

void abrirPerguntas(std::string tipo)

Fecha o arquivo anterior (se houver um aberto).

Abre o arquivo correspondente ao tipo (Ex.: "matematica facil").


int fazerPerguntas(int N)

Seleciona N perguntas aleatórias de perguntasCSV.

Utiliza o método gerarPergunta para interagir com o jogador.

Evita repetir perguntas durante a mesma partida.

Retorna o score obtido na partida.


bool adicionarJogador(std::string nome, std::string senha)

Adiciona um novo jogador ao arquivo jogadoresCSV.




---

5) Classe Jogo

Essa será a classe principal, responsável pela execução do jogo e pela integração das outras classes.

Atributos:

std::vector<Jogador> jogadores: Estrutura de dados contendo todos os jogadores, ordenados pelo score geral.

ArquivosCSV arquivos: Instância para manipulação de arquivos CSV.


Métodos:

void imprimeRanking()

Exibe os 10 jogadores com os maiores scores gerais.


bool autenticacao(std::string nome, std::string senha)

Verifica se o jogador está registrado e se as credenciais são válidas.


bool adicionarJogador(std::string nome, std::string senha)

Verifica se o nome já existe na base de dados.

Se não existir, cria um novo jogador e o adiciona ao sistema.

Utiliza o método adicionarJogador da classe ArquivosCSV.


void iniciarJogo()

Solicita que o jogador se autentique ou crie uma conta.

Permite escolher a matéria e o nível de dificuldade.

Usa os métodos abrirPerguntas e fazerPerguntas da classe ArquivosCSV para gerar perguntas e calcular o score.

Atualiza os scores do jogador se a pontuação obtida for maior