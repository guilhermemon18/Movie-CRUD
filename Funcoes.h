#pragma once
//Definições de estrututuras e protótipos de funções

typedef struct DataNascimento
{
	int dia;
	int mes;
	int ano;
}DataNascimento;

typedef struct Tipo
{
	int filme;
	int seriado;
}Tipo;
typedef struct Duracao
{
	int horas;
	int min;
}Duracao;

typedef struct CadastroVideo
{
	char Nome[30];
	char ID[30];
	Tipo tipo;
	char NomeDiretor[30];
	Duracao duracao;
	int Temporadas;
	int AnoLancamento;
	char Generos[5][20];
	int quantidade_generos;

}CadastroVideo;

typedef struct CadastroCliente
{
	char ID[30];
	char NomeCompleto[30];
	DataNascimento datadenascimento;
	int Historico[30];
	int quantidade_historico;
}CadastroCliente;

typedef struct SistemaStreaming
{
	CadastroCliente cadastro_cliente;
	CadastroVideo cadastro_video;
}SistemaStreaming;

typedef struct objeto//struct para organizar os objeto em nome e quantidade, um nome que aperece tantas vezes, controle da quantidade.
{
	char NomeObjeto[50];//nome que aparece.
	int quantidade;// quantidade do objeto.
}objeto;

typedef struct cliente_videos_assistidos
{
	char id[50];
	char nome[50];
	int idade;
	int quantidade;// quantia de filmes assistidos.
}cliente_videos_assistidos;

void geraid(char id[], char tipo[]);
int existe(char id[], char tipo[]);

void inicializacliente(CadastroCliente* cliente);
void inicializavideo(CadastroVideo* video);

void menu(SistemaStreaming* sistema);//menu principal
void video(SistemaStreaming* sistema);// menu de videos
void cliente(SistemaStreaming* sistema);// menu de clientes

void printIDvideos(SistemaStreaming* sistema);
void printIDclientes(SistemaStreaming* sistema);

void consultarcliente(SistemaStreaming* sistema);
void submenuconsultarcliente(SistemaStreaming* sistema);
void inserircliente(SistemaStreaming* sistema);
void submenuinserircliente(SistemaStreaming* sistema);
void alterarcliente(SistemaStreaming* sistema);
void submenualterarcliente(SistemaStreaming* sistema);
void removercliente(SistemaStreaming* sistema);
void submenuremovercliente(SistemaStreaming* sistema);

void inserirvideo(SistemaStreaming* sistema);
int ValidaVideo(CadastroVideo* aux);
void submenuinserirvideo(SistemaStreaming* sistema);
void consultarvideo(SistemaStreaming* sistema);
void submenuconsultarvideo(SistemaStreaming* sistema);
void alterarvideo(SistemaStreaming* sistema);
void submenualterarvideo(SistemaStreaming* sistema);
void removervideo(SistemaStreaming* sistema);
void submenuremovervideo(SistemaStreaming* sistema);

void relatorios(SistemaStreaming* sistema);//menu de relatorios
void simpleReport(SistemaStreaming* sistema);// relatório simples
void statisticsReport(SistemaStreaming* sistema);//relatório com estatisticas
void metadateReport(SistemaStreaming* sistema);//relatório com metadados
void formataString(char str[]);//deixa string no formato aceito para um nome de arquivo
int conta_video_tipo(char str[]);// str pode ser "filmes" ou "seriado", dependendo ela retorna a quantidade do tipo contido na string.
void printa_videos_qtd_genero(FILE* relatorio);// imprime a quantidade de videos por genero
void printa_clientes_quantidade_videos(FILE* relatorio);// imprime a quantidade de videos assistidos por cada cliente
int naotem(char NomeASerPesquisado[], objeto* Frequencias, int tamanho);// verifica se ja existe um elemento no vetor.
void diretorfrequente(FILE* relatorio);// acha e imrpime o diretor mais frequente
void cliente_frequente(FILE* relatorio);// acha e imprime o cliente que mais assistiu vídeos