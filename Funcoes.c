#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"
#include <locale.h>
#include <string.h>
#include <time.h>

//implementaçao das funções

void geraid(char id[], char tipo[])
{
	int jatem = 0;
	int aux;
	int i = 0;
	FILE* ArquivoIDs;// arquivo que precisa ser verificado para ver se ja tem a id antes de gerar um cliente ou video com essa id.
	ArquivoIDs = fopen(tipo, "r");
	if (ArquivoIDs == NULL)
	{
		itoa(i, id, 10);//converte int em string 
		return;
	}
	for (i = 0; 1; i++)
	{
		jatem = 0;//inicia zerada a condiçao se tem no arquivo o numero i atual.
		rewind(ArquivoIDs);
		while (1)
		{
			fscanf(ArquivoIDs, "%d", &aux);//percorre todo o arquivo para ver se tem essa id
			if (feof(ArquivoIDs))
				break;
			if (i == aux)
			{
				jatem = 1;
				rewind(ArquivoIDs);
				break;
			}
		}

		if (jatem == 0)//se nao trocar para 1 significa que varreu o arquivo e n encontrou essa id,portanto está disponivel para uso.
		{
			itoa(i, id, 10);//converte int em string 
			break;
		}
	}
	fclose(ArquivoIDs);
}
int existe(char id[], char tipo[])
{
	char aux[20];
	FILE* ArquivoIDs;// arquivo a ser aberto pra ser verfiicado, no caso um arquivo que lista todos os ids de algo, video ou clientes neste caso.
	ArquivoIDs = fopen(tipo, "r");

	while (1)
	{
		fscanf(ArquivoIDs, "%[^\n]s", aux);
		fscanf(ArquivoIDs, "%*c");
		if (feof(ArquivoIDs))
			break;
		if (strcmp(aux, id) == 0)
		{
			fclose(ArquivoIDs);
			return 1;
		}
	}
	fclose(ArquivoIDs);
	return 0;
}

void inicializacliente(CadastroCliente* cliente)
{
	cliente->quantidade_historico = 0;//inicia o historico com 0
	cliente->NomeCompleto[0] = '\0';//inicia a string como vazia
}

void inicializavideo(CadastroVideo* video)
{
	video->Nome[0] = '\0';// inica o nome com string vazia
	video->NomeDiretor[0] = '\0'; // inicia o nome do diretor com string vazia
	video->quantidade_generos = 0;//incia a quantidade de generos em 0;
	video->AnoLancamento = 0; // incia o ano de lancamento em 0
	video->tipo.filme = 0;//incia o tipo filme em 0(falso);
	video->tipo.seriado = 0;// incia o tipo seriado em 0(falso)
	video->Temporadas = 0;// inicia temporadas em 0;
}

void printIDvideos(SistemaStreaming* sistema)
{
	FILE* videos_txt;//ponteiro para abrir o arquivo com as ids dos vídeos;
	char str[20];//string auxiliar para ajudar a ler e imprimir as ids;

	videos_txt = fopen("videos.txt", "r");

	printf("\n\n");
	printf("Vídeos Cadastrados:\n");
	while (1)
	{
		fscanf(videos_txt, "%[^\n]s", str);//le até encrontar um \n;
		fscanf(videos_txt, "%*c");//descarta o \n;
		if (feof(videos_txt))
			break;
		printf("ID: %s\n", str);//imprime a string, que na vdd é um int do id do video
		
	}
	printf("\n");
	fclose(videos_txt);//fecha o arquivo
	
}

void printIDclientes(SistemaStreaming* sistema)
{
	FILE* clientes_txt;//ponteiro para abrir o arquivo com as ids dos vídeos;
	char str[20];//string auxiliar para ajudar a ler e imprimir as ids;

	clientes_txt = fopen("clientes.txt", "r");

	printf("\n\n");
	printf("Clientes Cadastrados:\n");
	while (1)
	{
		
		fscanf(clientes_txt, "%[^\n]s", str);//le até encrontar um \n;
		fscanf(clientes_txt, "%*c");//descarta o \n;
		if (feof(clientes_txt))
			break;
		printf("ID: %s\n", str);//imprime a string
	}
	printf("\n");
	fclose(clientes_txt);//fecha o arquivo;
}

void menu(SistemaStreaming* sistema)
{
	int numero;

	printf("Escolha uma opção\n");
	printf("1.Video\n");
	printf("2.Cliente\n");
	printf("3.Relatórios\n");
	printf("4.Sair\n");

	scanf("%d", &numero);
	system("cls");
	switch (numero)
	{
	case 1:
		video(sistema);
		break;
	case 2:
		cliente(sistema);
		break;
	case 3:
		relatorios(sistema);
		break;
	case 4:
		printf("Até mais\n");
		system("pause");
		exit(0);
	default:
		printf("Opção inválida, tente novamente\n");// caso nao seja um opçao valida
		menu(sistema);//volta ao menu 
	}
}

void video(SistemaStreaming* sistema)
{
	int numero;

	printf("Escolha uma opção\n");
	printf("1.Inserir vídeo\n");
	printf("2.Consultar vídeo\n");
	printf("3.Alterar vídeo\n");
	printf("4.Remover vídeo\n");
	printf("5.Menu Principal\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");

	switch (numero)
	{
	case 1:
		inserirvideo(sistema);
		break;
	case 2:
		consultarvideo(sistema);
		break;
	case 3:
		alterarvideo(sistema);
		break;
	case 4:
		removervideo(sistema);
		break;
	case 5:
		menu(sistema);//volta ao menu principal
		break;
	default:
		printf("Opção inválida, tente novamente\n");// caso nao seja um opçao valida
		video(sistema);
	}

}

void cliente(SistemaStreaming* sistema)
{
	int numero;
	//pede para digitar o numero da opçao desejada e redireciona pra outra funçao que trata de cada caso
	printf("Escolha uma opção\n");
	printf("1.Inserir cliente\n");
	printf("2.Consultar cliente\n");
	printf("3.Alterar cliente\n");
	printf("4.Remover cliente\n");
	printf("5.Menu Principal\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		inserircliente(sistema);
		break;
	case 2:
		consultarcliente(sistema);
		break;
	case 3:
		alterarcliente(sistema);
		break;
	case 4:
		removercliente(sistema);
		break;
	case 5:
		menu(sistema);//volta ao menu principal
		break;
	default:
		printf("Opção inválida, tente novamente\n");// caso nao seja um opçao valida
		cliente(sistema);//chama o menu cliente de novo
	}
}

void relatorios(SistemaStreaming* sistema)
{
	int numero;//numero da opçao a ser escolhida

	printf("Escolha uma opção\n");

	printf("1.Relatório Simples\n");
	printf("2.Relatório com estatísticas\n");
	printf("3.Relatório com metadados\n");
	printf("4.Menu Principal\n");

	scanf("%d", &numero);
	scanf("%*c");//descarata o \n

	switch (numero)
	{
	case 1:
		simpleReport(sistema);
		break;
	case 2:
		statisticsReport(sistema);
		break;
	case 3:
		metadateReport(sistema);
		break;
	case 4:
		menu(sistema);
	default:
		printf("Opção inválida, tente novamente\n");
		relatorios(sistema);
	}
}

void simpleReport(SistemaStreaming* sistema)
{
	//lista todas as informaçoes de todos os vídeos e clientes cadastrados no momento em um arquivo.
	FILE* videos, * idvideo, * clientes, * idcliente, * relatorio;
	//ponteiro para aruqivo com ids dos videos, ponteiro para arquivo com id dos clientes e ponteiro para o arquivo do relatório.
	char id[80];// variáve para armazenar o id tanto de cliente como de videos
	char aux[80];// string auxiliar para construir o nome do arquivo que contem o vídeo ou cliente.
	char aux_nome_arquivo_relatorio[80];// string para construir o nome do arquivo de relatório.
	struct tm* horaedata;
	time_t segundos;//variável para os segundos

	aux_nome_arquivo_relatorio[0] = '\0';
	strcat(aux_nome_arquivo_relatorio, "RS");
	
	time(&segundos);
	horaedata = localtime(&segundos);//converte os segundos para hora local.
	strcat(aux_nome_arquivo_relatorio, asctime(horaedata));// concatena data e hora no nome do arquivo de relatório
	
	formataString(aux_nome_arquivo_relatorio);// ajeita a string para ser um formato valdio de nome de arquivo
	strcat(aux_nome_arquivo_relatorio, ".txt");// concatena a extensao .txt ao nome do arquivo
	printf("%s", aux_nome_arquivo_relatorio);// imprime o nome do arquivo para o usuário visualizar

	clientes = fopen("clientes.txt", "r");//abre clientes para leitura
	videos = fopen("videos.txt", "r");// abre videos para leitura
	relatorio = fopen(aux_nome_arquivo_relatorio, "w");//abre para escrita o arquivo .

	fprintf(relatorio, "Clientes Cadastrados:\n\n");

	while (1)
	{
		aux[0] = '\0';
		strcat(aux, "cl");
		fscanf(clientes, "%[^\n]s", id);
		fscanf(clientes, "%*c");//descarta o \n
		if (feof(clientes))
		{
			break;// sai do while se terminar o arquivo
		}
		strcat(aux, id);
		strcat(aux, ".txt");

		idcliente = fopen(aux, "r");//abre o cliente para leitura


		fscanf(idcliente, "%[^\n]s", aux);
		fscanf(idcliente, "%*c");
		
		fprintf(relatorio, "ID: %s\n", aux);

		fscanf(idcliente, "%[^\n]s", aux);
		fscanf(idcliente, "%*c");
		fprintf(relatorio, "Nome: %s\n", aux);

		fscanf(idcliente, "%[^\n]s", aux);
		fscanf(idcliente, "%*c");
		fprintf(relatorio, "Data de nascimento: %s\n", aux);

		fprintf(relatorio, "Histórico:\n");
		int i = 1;
		while (1)
		{
			fscanf(idcliente, "%[^\n]s", aux);
			fscanf(idcliente, "%*c");
			if (feof(idcliente))
			{
				break;
			}
			fprintf(relatorio, "IDvídeo%d:  %s\n", i,aux);
			i++;
		}
		fprintf(relatorio, "\n");
		fclose(idcliente);
	}
	fclose(clientes);
	fprintf(relatorio, "\nVídeos Cadastrados:\n\n");

	while (1)
	{
		aux[0] = '\0';
		strcat(aux, "vid");
		fscanf(videos, "%[^\n]s", id);
		fscanf(videos, "%*c");//descarta o \n
		if (feof(videos))
		{
			break;// sai do while se terminar o arquivo
		}
		strcat(aux, id);
		strcat(aux, ".txt");

		idvideo = fopen(aux, "r");//abre o video para leitura

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "ID: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Tipo: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Nome do filme: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Diretor: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Duração: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Temporadas: %s\n", aux);

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		fprintf(relatorio, "Ano de lançamento: %s\n", aux);

		fprintf(relatorio, "Gênero(s)\n");
		int i = 1;
		while (1)
		{
			fscanf(idvideo, "%[^\n]s", aux);
			fscanf(idvideo, "%*c");
			if (feof(idvideo))
			{
				break;
			}
			fprintf(relatorio, "Gênero%d: %s\n", i, aux);
			i++;
		}
		fprintf(relatorio, "\n");
		fclose(idvideo);
	}
	fclose(videos);
	fclose(relatorio);
	printf("Relatório gerado com sucesso\n");
	relatorios(sistema);
}

void formataString(char str[])// deixa a string no padrão para o arquivo.
{
	char aux[40];
	int i = 0, j = 0;

	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != ':')
		{
			aux[j] = str[i];
			j++;
		}
	}
	aux[j] = '\0';
	strcpy(str, aux);
}

void statisticsReport(SistemaStreaming* sistema)
{
	
	FILE* relatorio;
	char id[80];//id do video
	char aux2[80];
	aux2[0] = '\0';

	strcat(aux2, "RE");
	time_t segundos;//variável para os segundos
	struct tm* horaedata;

	time(&segundos);
	horaedata = localtime(&segundos);//converte os segundos para hora local.
	strcat(aux2, asctime(horaedata));

	formataString(aux2);
	strcat(aux2, ".txt");
	printf("%s", aux2);

	relatorio = fopen(aux2, "w");//abre para escrita o arquivo de relatório .


	fprintf(relatorio, "Quantidade de vídeos por tipo filme ou seriado:\n");
	fprintf(relatorio, "Filmes: %d\n", conta_video_tipo("filmes"));
	fprintf(relatorio, "Seriados: %d\n\n", conta_video_tipo("seriados"));

	fprintf(relatorio, "Quantidade de vídeos por gêneros:\n");
	printa_videos_qtd_genero(relatorio);

	fprintf(relatorio, "\nQuantidade de vídeos assistidos por cada cliente\n");
	printa_clientes_quantidade_videos(relatorio);

	fclose(relatorio);
	printf("Relatório gerado com sucesso\n");
	relatorios(sistema);
}

int conta_video_tipo(char str[])
{
	int f = 0;
	int s = 0;// variaveis para contar os filmes e seriados
	FILE* videos, * idvideo;
	char aux[50];//variavel auxiliar para abrir o video
	char id[50];// id do video

	videos = fopen("videos.txt", "r");//abre arquivo com ids dos videos

	while (1)
	{
		aux[0] = '\0';
		strcat(aux, "vid");
		fscanf(videos, "%[^\n]s", id);
		fscanf(videos, "%*c");//descarta o \n
		if (feof(videos))
		{
			break;// sai do while se terminar o arquivo
		}
		strcat(aux, id);
		strcat(aux, ".txt");

		idvideo = fopen(aux, "r");//abre o video para leitura

		fscanf(idvideo, "%[^\n]*s");//descarta o id
		fscanf(idvideo, "%*c");
		

		fscanf(idvideo, "%[^\n]s", aux);
		fscanf(idvideo, "%*c");
		if (strcmp(aux, "Filme") == 0)
		{
			f++;
		}
		else
		{
			s++;
		}

		fclose(idvideo);// fecha o arquivo do video
	}
	fclose(videos);

	if (strcmp(str, "filmes") == 0)
	{
		return f;
	}
	else
	{
		return s;
	}
}

void printa_videos_qtd_genero(FILE* relatorio)
{
	objeto* generos;//variável auxiliar para controle dos videos por genero
	generos = (objeto*)malloc(1 * sizeof(objeto));// aloca inicialmente 1 espaço para genero
	int count = 0;//variavel auxiliar para o vetor de generos
	char aux[50];//variavel auxiliar para abrir o video
	char idVideo[50];// id do video
	FILE* idsVideos, *video;

	idsVideos = fopen("videos.txt", "r");//abre arquivo com ids dos videos

	while (1)
	{
		aux[0] = '\0';
		strcat(aux, "vid");
		fscanf(idsVideos, "%[^\n]s", idVideo);
		fscanf(idsVideos, "%*c");//descarta o \n
		if (feof(idsVideos))
		{
			break;// sai do while se terminar o arquivo
		}
		strcat(aux, idVideo);
		strcat(aux, ".txt");

		video = fopen(aux, "r");//abre o video para leitura

		fscanf(video, "%[^\n]*s");//descarta o id
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarta o tipo
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarta o nome do filme
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarata o diretor
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarata a duraçao
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarta temporadas
		fscanf(video, "%*c");
		fscanf(video, "%[^\n]*s");//descarta o ano de lançamento
		fscanf(video, "%*c");

		while (1)
		{
			fscanf(video, "%[^\n]s", aux);// le os gêneros
			fscanf(video, "%*c");
			if (feof(video))
			{
				break;
			}
			
			if (naotem(aux,generos,count))//verifica se ja tem o genero contabilizado
			{
				
				count++;// adiciona mais um elemento 
				generos = (objeto*)realloc(generos,count * sizeof(objeto));//realloca o vetor
				strcpy(generos[count-1].NomeObjeto, aux);//copia o genero da string auxiliar para string genero do vetor.
				generos[count - 1].quantidade = 0;
				generos[count - 1].quantidade++;
			}
			else
			{
				int i = 0;
				for (i = 0; i < count; i++)
					if (strcmp(aux, generos[i].NomeObjeto) == 0)
					{//se for igual ao gênero incrementa a quantidade
						generos[i].quantidade++;//aumenta em 1 o video dessse gênero
						break;//sai do for
					}
			}
		}
		fclose(video);
	}
	fclose(idsVideos);
	
	char c = 'a';
	for (int i = 0; i < count; i++)
	{
		fprintf(relatorio, "%c.%s: %d\n", c, generos[i].NomeObjeto, generos[i].quantidade);
		c++;
	}
	free(generos);//libera a memoria dos generos.
}



int naotem(char NomeASerPesquisado[], objeto* Frequencias, int tamanho)//verifica se ja tem esse nome no vetor Frequencias.
{
	int i = 0;
	for (i = 0; i < tamanho; i++)
	{
		if (strcmp(Frequencias[i].NomeObjeto, NomeASerPesquisado) == 0)
			return 0;
	}
	return 1;
}

void printa_clientes_quantidade_videos(FILE* relatorio)//imprime a quantidade de vídeos assistidos por cada cliente.
{
	FILE* cliente, * clientes;
	char aux[50];
	char aux2[50];
	char c = 'a';
	int total = 0;

	clientes = fopen("clientes.txt", "r");// abre o arquivo com ids dos clientes para leitura
	while (1)
	{
		aux2[0] = '\0';
		strcat(aux2, "cl");

		fscanf(clientes, "%[^\n]s", aux);// le uma id do arquivo de ids de clientes
		fscanf(clientes, "%*c");//descarta o \n
		if (feof(clientes))
		{
			break;// sai do while quando for fim de arquivo.
		}
		strcat(aux2, aux);//concatena a id na string aux
		strcat(aux2, ".txt");//concatena .txt na string aux

		cliente = fopen(aux2,"r");// abre o clientee do id para leitura.

		fscanf(cliente, "%[^\n]s", aux);// le o id
		fscanf(cliente, "%*c");//descarta o \n

		fprintf(relatorio, "%c.ID %s: ", c, aux);// imprime no relatório a letra do char c e o id.
		c++;

		fscanf(cliente, "%[^\n]*s");// le o nome e descarta
		fscanf(cliente, "%*c");//descarta o \n

		fscanf(cliente, "%[^\n]*s");// le a data de nascimento e descarta
		fscanf(cliente, "%*c");//descarta o \n

		total = 0;
		while (1)
		{
			fscanf(cliente, "%[^\n]s", aux);
			fscanf(cliente, "%*c");//descarta o \n
			if (feof(cliente))
				break;
			total++;
		}
		fprintf(relatorio, "%d\n", total);
		fclose(cliente);// fecha o arquivo do cliente
	}
	fclose(clientes);//fecha o arquivo de clienttes
}

void metadateReport(SistemaStreaming* sistema)//relatório com metadados
{
	FILE* relatorio;
	char id[80];//id do video
	char aux[80];// auxilia 
	char aux2[80];
	aux2[0] = '\0';

	strcat(aux2, "RM");
	time_t segundos;//variável para os segundos
	struct tm* horaedata;

	time(&segundos);
	horaedata = localtime(&segundos);//converte os segundos para hora local.
	strcat(aux2, asctime(horaedata));

	formataString(aux2);
	strcat(aux2, ".txt");
	printf("%s\n", aux2);//imprime o nome do arquivo

	relatorio = fopen(aux2, "w");//abre para escrita o arquivo de relatório.

	fprintf(relatorio, "Tipo de vídeo mais frequente: ");
	if (conta_video_tipo("filmes") == conta_video_tipo("seriados"))
		fprintf(relatorio,"Ambos(filmes e seriados) possuem a mesma frequência\n");
	if (conta_video_tipo("filmes") > conta_video_tipo("seriados"))
		fprintf(relatorio,"Filmes\n");
	else
		fprintf(relatorio,"Seriados\n");

	fprintf(relatorio, "Nome de diretor(es) mais frequente:\n");
	diretorfrequente(relatorio);//imprime os nomes dos diretores mais frequente.
	
	fprintf(relatorio, "Cliente(s) que mais assistiu(assistiram) vídeos:\n");
	cliente_frequente(relatorio);

	fclose(relatorio);
	printf("Relatório gerado com sucesso\n");
	relatorios(sistema);
}

void cliente_frequente(FILE* relatorio)// encontra o cliente que mais assistiu vídeos
{
	cliente_videos_assistidos* clientes;// estrutura auxiliar para comportar os clientes temporariamente
	int count = 0;// controle da quantidade de clientes

	clientes = (cliente_videos_assistidos*)malloc(1 * sizeof(cliente_videos_assistidos)); // aloca inicialmente 1 espaço para  o vetor.

	FILE* cliente, * clientestxt;//arquivos com os clientes.
	char aux[50];// auxiliar outras strings
	char aux2[50];// auxiliar para abrir o cliente
	int total = 0;//contar os videos
	int ano_nascimento = 0;// para armazenar o ano de nascimento do cliente
	struct tm* data;// estrutura para controlar o tempo 
	time_t segundos ;//retornar o tempo em segudnos


	time(&segundos);// obeter o tempo em segundos
	data = localtime(&segundos);

	clientestxt = fopen("clientes.txt", "r");// abre o arquivo com ids dos clientes para leitura
	while (1)
	{
		aux2[0] = '\0';
		strcat(aux2, "cl");

		fscanf(clientestxt, "%[^\n]s", aux);// le uma id do arquivo de ids de clientes
		fscanf(clientestxt, "%*c");//descarta o \n
		if (feof(clientestxt))
		{
			break;// sai do while quando for fim de arquivo.
		}
		strcat(aux2, aux);//concatena a id na string aux
		strcat(aux2, ".txt");//concatena .txt na string aux

		cliente = fopen(aux2, "r");// abre o clientee do id para leitura
		count++; // incrementa a quantidade de clientes.
		clientes = (cliente_videos_assistidos*)realloc(clientes, count * sizeof(cliente_videos_assistidos));//realoca a quantidade de clientes

		fscanf(cliente, "%[^\n]s", clientes[count - 1].id);// le o id do cliente count - 1.
		fscanf(cliente, "%*c");//descarta o \n

		fscanf(cliente, "%[^\n]s",clientes[count - 1].nome);// le o nome 
		fscanf(cliente, "%*c");//descarta o \n

		fscanf(cliente, "%[^/]*s");// le o dia de nascimento e descarta
		fscanf(cliente, "%*c");//descarta o /

		fscanf(cliente, "%[^/]*s");// le o mes de nascimento e descarta
		fscanf(cliente, "%*c");//descarta o /

		fscanf(cliente, "%d",&ano_nascimento);// le o ano  de nascimento.
		fscanf(cliente, "%*c");//descarta o \n

		clientes[count - 1].idade = (data->tm_year + 1900) - ano_nascimento;// idade é o ano atual menos o ano de nascimento.

		total = 0;
		while (1)
		{
			fscanf(cliente, "%[^\n]s",aux);//le um id de video e descarta
			fscanf(cliente, "%*c");//descarta o \n
			if (feof(cliente))
				break;
			total++;//aumenta o total em 1 apos ler o vídeo.
		}
		clientes[count - 1].quantidade = total;
		fclose(cliente);// fecha o arquivo do cliente
	}
	fclose(clientestxt);//fecha o arquivo de clienttes

	// agora precisa achar o cliente com mais videos.
	int i = 0;
	int maior = 0;// acha o maior.
	for (i = 0; i < count; i++)
	{
		if (clientes[i].quantidade > maior)
			maior = clientes[i].quantidade;
	}
	// agora imprime todos os com mais videos
	for (i = 0; i < count; i++)
	{
		if (clientes[i].quantidade == maior)
			fprintf(relatorio, "ID: %s\nNome: %s\nIdade: %d\n", clientes[i].id, clientes[i].nome, clientes[i].idade);
	}

	free(clientes);//libera a memoria alocada para clientes.
}

void diretorfrequente(FILE * relatorio)// acha o nome de diretor mais frequente
{

	objeto* diretores;//variável auxiliar para controle dos videos por diretor
	diretores = (objeto*)malloc(1 * sizeof(objeto));// aloca inicialmente 1 espaço para diretores
	int count = 0;//variavel para o vetor de diretores
	char aux[50];//variavel auxiliar para abrir o video
	char id[50];// id do video
	FILE* videos, * idvideo;

	videos = fopen("videos.txt", "r");//abre arquivo com ids dos videos

	while (1)
	{
		aux[0] = '\0';
		strcat(aux, "vid");
		fscanf(videos, "%[^\n]s", id);
		fscanf(videos, "%*c");//descarta o \n
		if (feof(videos))
		{
			break;// sai do while se terminar o arquivo
		}
		strcat(aux, id);
		strcat(aux, ".txt");

		idvideo = fopen(aux, "r");//abre o video para leitura

		fscanf(idvideo, "%[^\n]*s");//descarta o id
		fscanf(idvideo, "%*c");
		fscanf(idvideo, "%[^\n]*s");//descarta o tipo
		fscanf(idvideo, "%*c");
		fscanf(idvideo, "%[^\n]*s");//descarta o nome do filme
		fscanf(idvideo, "%*c");
		fscanf(idvideo, "%[^\n]s", aux);//le o nome do  diretor

		if (naotem(aux, diretores, count))//verifica se ja tem o genero contabilizado
		{

			count++;// adiciona mais um elemento 
			diretores = (objeto*)realloc(diretores, count * sizeof(objeto));//realloca o vetor
			strcpy(diretores[count - 1].NomeObjeto, aux);//copia o genero da string auxiliar para string genero do vetor.
			diretores[count - 1].quantidade = 0;
			diretores[count - 1].quantidade++;
		}
		else
		{
			int i = 0;
			for (i = 0; i < count; i++)
				if (strcmp(aux, diretores[i].NomeObjeto) == 0)
				{//se for igual ao gênero incrementa a quantidade
					diretores[i].quantidade++;//aumenta em 1 o video dessse gênero
					break;//sai do for
				}

			fclose(idvideo);
		}
	}
	fclose(videos);
	int i = 0;// achar o diretor com mais ocorrencia.
	int maior = 0;//inicia maior com zero.
	for (i = 0; i < count; i++)
	{
		if (diretores[i].quantidade > maior)
		{
			maior = diretores[i].quantidade;// se for maior que o maior, maior recebe quantidade do diretor.
		}
	}
	// agora fazer o for novamente e imprimir todos que possuem essa quantidade de ocorrencia maior.
	for (i = 0; i < count; i++)
	{
		if (diretores[i].quantidade == maior)
			fprintf(relatorio, "%s\n", diretores[i].NomeObjeto);//imprime o diretor, o genero se refere ao nome do diretor.
	}
	free(diretores);//libera a memoria alocada para diretores
}

void consultarcliente(SistemaStreaming* sistema)
{
	FILE* arquivo_cliente = NULL;
	char id[30];
	char aux[30];
	aux[0] = '\0';
	strcat(aux, "cl");

	printf("Insira o ID do cliente\n");//pedi a id do cliente a ser consultado
	gets(id);
	strcat(aux, id);//concatena a string aux com o id para ficar no formato cl-iddocliente.txt
	strcat(aux,".txt");

	if(existe(id,"clientes.txt") == 0)// se existe esta id em clientes.txt é pq p cliente existe.
		printf("O cliente não existe\n");
	else
	{
		arquivo_cliente = fopen(aux, "r");//abre o arquivo com o cliente para leitura
			// imprime suas informaçoes 
		fscanf(arquivo_cliente, "%[^\n]s", aux);
		fscanf(arquivo_cliente, "%*c");//descarta o \n
		printf("ID : %s\n", aux);//imprime o id

		fscanf(arquivo_cliente, "%[^\n]s", aux);
		fscanf(arquivo_cliente, "%*c");//descarta o \n
		printf("Nome Completo : %s\n", aux);//imprime o nome completo

		fscanf(arquivo_cliente, "%[^\n]s", aux);
		fscanf(arquivo_cliente, "%*c");//descarta o \n
		printf("Data de nascimento : %s\n", aux);//imprime a data de nascimento


		printf("Histórico:\n");//imprime o historico
		while (1)
		{
			fscanf(arquivo_cliente, "%[^\n]s", aux);
			fscanf(arquivo_cliente, "%*c");//descarta o \n
			if (feof(arquivo_cliente))
				break;
			printf("%s\n", aux);
		}
		fclose(arquivo_cliente);
	}
		printIDclientes(sistema);//imprime as ids dos clientes
		submenuconsultarcliente(sistema);//depois que consultou apresenta um submenu com opçoes
}



void submenuconsultarcliente(SistemaStreaming* sistema)
{
	int numero;

	printf("1.Menu principal\n");//pede o que se deseja fazer depois que consultou um cliente
	printf("2.Menu anterior\n");
	printf("3.Consultar outro cliente\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		cliente(sistema);
		break;
	case 3:
		consultarcliente(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");//novamente se digitar uma opçao invalida é redirecionad de volta ao submenu
		submenuconsultarcliente(sistema);
	}
}

void inserircliente(SistemaStreaming* sistema)
{
	int idvideo = 0;//variavel auxiliar para ids dos videos
	FILE* arquivo_cliente, *clientes_txt;// arquivo para o cliente e arquivo para ids dos clientes.
	char aux[30];//string auxiliar 
	

	aux[0] = '\0';
	strcat(aux, "cl");//precisa comecar com o prefixo cl pois é um cliente

	inicializacliente(&sistema->cadastro_cliente);//inicia o novo cliente com as configuraçoes certas

	geraid(sistema->cadastro_cliente.ID, "clientes.txt");
	
	clientes_txt = fopen("clientes.txt", "a");
	fprintf(clientes_txt, "%s\n", sistema->cadastro_cliente.ID);// abre o arquivo contendo todas as ids de clientes e salva nele a id
	fclose(clientes_txt);

	strcat(aux, sistema->cadastro_cliente.ID);//concatena a string para ficar no formato cl-ID.txt.
	strcat(aux, ".txt");

	arquivo_cliente = fopen(aux, "w");// abre um arquivo com o nome cl-ID.txt para escrever as informaçoes do cliente
	
	//daqui pra frente pede as informaçoes do cliente a ser adicionado e adiciona-o ao sistema
	printf("Insira o nome completo do cliente\n");
	gets(sistema->cadastro_cliente.NomeCompleto);

	printf("Insira a data de nascimento(dia/mês/ano)\n");
	scanf("%d/", &sistema->cadastro_cliente.datadenascimento.dia);
	scanf("%d", &sistema->cadastro_cliente.datadenascimento.mes);
	scanf("/%d", &sistema->cadastro_cliente.datadenascimento.ano);

	printf("Insira o histórico,digite o valor -1 para terminar\n");

	scanf("%d", &idvideo);
	for (int i = 0; idvideo != -1; i++)
	{
		sistema->cadastro_cliente.Historico[i] = idvideo;
		sistema->cadastro_cliente.quantidade_historico++;
		scanf("%d", &idvideo);
	}

    //imprimindo os dados no arquivo
	fprintf(arquivo_cliente, "%s\n", sistema->cadastro_cliente.ID);

	fprintf(arquivo_cliente, "%s\n", sistema->cadastro_cliente.NomeCompleto);

	fprintf(arquivo_cliente, "%.2d/", sistema->cadastro_cliente.datadenascimento.dia);
	fprintf(arquivo_cliente, "%.2d/", sistema->cadastro_cliente.datadenascimento.mes);
	fprintf(arquivo_cliente, "%.4d\n", sistema->cadastro_cliente.datadenascimento.ano);

	for (int i = 0; i < sistema->cadastro_cliente.quantidade_historico; i++)
	{
		fprintf(arquivo_cliente, "%d\n", sistema->cadastro_cliente.Historico[i]);
	}

	fclose(arquivo_cliente);//fecha o arquivo

	system("cls");//limpa tela
	printIDclientes(sistema);
	submenuinserircliente(sistema);//chama um submenu com opçoes 
}

void submenuinserircliente(SistemaStreaming* sistema)
{
	int numero;
	
	//submenu com opçoes pós adicionar cliente
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Inserir outro cliente\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		cliente(sistema);
		break;
	case 3:
		inserircliente(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenuinserircliente(sistema);// caso a opçao seja inválida
	}
}

void alterarcliente(SistemaStreaming* sistema)
{
	// se o id nao pode ser alterado, ja nem vai ser pedido pelo programa ao cliente, essa informaçao
	//melhor proteçao que pode ter

	    int idvideo = 0;//variavel auxiliar para ids dos videos   
		FILE* arquivo_cliente;
		char aux[30];//string auxiliar 

		aux[0] = '\0';
		strcat(aux, "cl");//precisa comecar com o prefixo cl pois é um cliente

		inicializacliente(&sistema->cadastro_cliente);//inicia o novo cliente com as configuraçoes certas

		printf("Insira o ID do cliente a ser alterado\n");
		gets(sistema->cadastro_cliente.ID);

		
		strcat(aux, sistema->cadastro_cliente.ID);//concatena a string para ficar no formato cl-ID.txt.
		strcat(aux, ".txt");

		arquivo_cliente = fopen(aux, "w");// abre um arquivo com o nome cl-ID.txt para escrever as informaçoes do cliente

		//daqui pra frente pede as informaçoes do cliente a ser adicionado e adiciona-o ao sistema
		printf("Insira o novo nome completo do cliente\n");
		gets(sistema->cadastro_cliente.NomeCompleto);

		printf("Insira a nova data de nascimento(dia/mês/ano)\n");
		scanf("%d/", &sistema->cadastro_cliente.datadenascimento.dia);
		scanf("%d", &sistema->cadastro_cliente.datadenascimento.mes);
		scanf("/%d", &sistema->cadastro_cliente.datadenascimento.ano);

		printf("Insira o novo histórico,digite o valor -1 para terminar\n");

		scanf("%d", &idvideo);
		for (int i = 0; idvideo != -1; i++)
		{
			sistema->cadastro_cliente.Historico[i] = idvideo;
			sistema->cadastro_cliente.quantidade_historico++;
			scanf("%d", &idvideo);
		}

		//imprimindo os dados no arquivo
		fprintf(arquivo_cliente, "%s\n", sistema->cadastro_cliente.ID);

		fprintf(arquivo_cliente, "%s\n", sistema->cadastro_cliente.NomeCompleto);

		fprintf(arquivo_cliente, "%.2d/", sistema->cadastro_cliente.datadenascimento.dia);
		fprintf(arquivo_cliente, "%.2d/", sistema->cadastro_cliente.datadenascimento.mes);
		fprintf(arquivo_cliente, "%.4d\n", sistema->cadastro_cliente.datadenascimento.ano);

		for (int i = 0; i < sistema->cadastro_cliente.quantidade_historico; i++)
		{
			fprintf(arquivo_cliente, "%d\n", sistema->cadastro_cliente.Historico[i]);
		}

	    fclose(arquivo_cliente);//fecha o arquivo
			
	system("cls");
	printIDclientes(sistema);
	submenualterarcliente(sistema);//chama um submenu com opções
}

void submenualterarcliente(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós alterar cliente
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Alterar outro cliente\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		cliente(sistema);
		break;
	case 3:
		alterarcliente(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenualterarcliente(sistema);// caso a opçao seja inválida
	}
}

void removercliente(SistemaStreaming* sistema)
{
	FILE *antigo_arquivo, *novo_arquivo;// arquivo antigo e novo arquivo contendo as ids dos clientes.
	char id[30];
	char aux[30];

	aux[0] = '\0';
	strcat(aux, "cl");

	printf("Insira o ID do cliente a ser removido\n");
	scanf("%[^\n]s", id);//id do cliente a ser removido
	scanf("%*c");//descarta o \n;

	strcat(aux, id);
	strcat(aux, ".txt");

	remove(aux);//exclui o arquivo que contem o cliente.

	//exclui o id da lista do arquivo de ids de clientes
	antigo_arquivo = fopen("clientes.txt", "r");// abre o arquivo com os clientes para leitura
	novo_arquivo = fopen("clientes2.txt", "w");// abre outro aruqivo para escrita

	while (1)
	{
		fscanf(antigo_arquivo, "%[^\n]s", aux);
		fscanf(antigo_arquivo, "%*c");//descarta o \n;
		if (feof(antigo_arquivo))
			break;
		if (strcmp(aux, id) != 0)// se for diferente do id a ser excluido imprime no novo arquivo
			fprintf(novo_arquivo, "%s\n", aux);
	}
	fclose(antigo_arquivo);
	fclose(novo_arquivo);

	remove("clientes.txt");//exclui o arquivo antigo
	rename("clientes2.txt", "clientes.txt");// renomeia o novo para o nome do antigo

	system("cls");
	printIDclientes(sistema);//imprime os clientes
	submenuremovercliente(sistema);
}

void submenuremovercliente(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós remover o cliente
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Remover outro cliente\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		cliente(sistema);
		break;
	case 3:
		removercliente(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenuremovercliente(sistema);// caso a opçao seja inválida
	}
}

void inserirvideo(SistemaStreaming* sistema)// precisa validaçao e gerar o arquivo de log
{
	FILE* arquivo_video = NULL, *videos_txt;//ponteiro para arquivo, inicializa com NULL, ponteiro para arquivo com ids de videos.
	CadastroVideo aux;//cria um cadastro de video auxiliar para armazenr as informaçoes temporariamente e testá-las
	inicializavideo(&aux);//inicializa aux corretamente
	char c;// char auxiliar;
	char str_aux_generos[20];//string auxiliar

	 geraid(aux.ID,"videos.txt");

	printf("Digite f para filme e s para seriado\n");
	scanf("%c", &c);//le o char associado a definiçao de filme ou seriado
	if (c == 'f')
		aux.tipo.filme = 1;
	else
		aux.tipo.seriado = 1;

	scanf("%*c");//elimana o outro \n da leitura do char anterior
	printf("Digite o nome do filme\\seriado\n");
	gets(aux.Nome);

	printf("Digite o nome completo do diretor\n");
	gets(aux.NomeDiretor);

	printf("Digite a duração hh:mm\n");
	scanf("%d:%d", &aux.duracao.horas, &aux.duracao.min);

	printf("Digite a quantidade de temporadas\n");
	scanf("%d", &aux.Temporadas);

	printf("Digite o ano de lançamento\n");
	scanf("%d", &aux.AnoLancamento);

	scanf("%*c");//elimina o \n

	printf("Digite os gêneros, digite fim para terminar\n");
	gets(str_aux_generos);

	for (int i = 0; strcmp(str_aux_generos, "fim") != 0; i++)
	{
		strcpy(aux.Generos[i], str_aux_generos);//copia a string lida para o vetor de strings de generos
		aux.quantidade_generos++;//incrementa a quantidade de generos
		gets(str_aux_generos);
		
	}
	//ok tudo foi lido, agora vem a verificaçao se realmente pode cadastrar esse video;
	if (ValidaVideo(&aux) == 1)
	{
		char aux_nome_arquiv0_video[30];// string para o nome do arquivo de vídeo.

		aux_nome_arquiv0_video[0] = '\0';
		strcat(aux_nome_arquiv0_video, "vid");
		strcat(aux_nome_arquiv0_video, aux.ID);
		strcat(aux_nome_arquiv0_video, ".txt");

		videos_txt = fopen("videos.txt", "a");// abre para escrita no fim do arquivo "append" =  acrescentar.
		fprintf(videos_txt, "%s\n", aux.ID);// adiciona o id do video ao arquivo com os ids dos videos.
		fclose(videos_txt);

		arquivo_video = fopen(aux_nome_arquiv0_video, "w"); // abre o arquivo para escrita e imprime todas as informaçoes validadas.

		fprintf(arquivo_video,"%s\n", aux.ID);
		if (aux.tipo.filme == 1)
			fprintf(arquivo_video,"Filme\n");
		else
			fprintf(arquivo_video,"Seriado\n");

		fprintf(arquivo_video, "%s\n", aux.Nome);
		fprintf(arquivo_video, "%s\n", aux.NomeDiretor);
		fprintf(arquivo_video, "%.2d:%.2d\n", aux.duracao.horas, aux.duracao.min);
		fprintf(arquivo_video, "%d\n", aux.Temporadas);
		fprintf(arquivo_video, "%d\n", aux.AnoLancamento);
		
		for (int i = 0; i < aux.quantidade_generos; i++)
			fprintf(arquivo_video, "%s\n", aux.Generos[i]);
		fclose(arquivo_video);
	}//n precisa else pq a propria funçao valida ja produz o arquivo com os logs

	system("cls");
	printIDvideos(sistema);
	submenuinserirvideo(sistema);
}



void submenuinserirvideo(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós inserir video
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Inserir outro vídeo\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		video(sistema);
		break;
	case 3:
		inserirvideo(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenuinserirvideo(sistema);// caso a opçao seja inválida
	}
}

int ValidaVideo(CadastroVideo* aux )
{
	FILE* p;
	int valido = 1;// se for igual a 0 signifca que é invalido,inicializa como valido e muda nas condiçoes
	int regra1 = 0;//nenhum campo vazio ou seja string n pode ser = "" ou string[0] = '\0'
	int regra2 = 0;//campos inteiros devem ser positivos >=0 se <0 desobedeceu
	int regra3 = 0;//horas e minutos validos 0<=hora<=24 e 0<=min<=59

	

	if (aux->ID[0] == '-')//se o primeiro campo da string for um sinal de menos signifca que o numero é negativo.
	{
		regra2 = 1;//regra 2 fica verdadeira
		valido = 0;// valido fica falso
	}
	
	if (aux->tipo.filme == 0 && aux->tipo.seriado == 0)//se os dois forem zero nao é nem filme nem feriado ou seja ele nao digitou nem f e nem s
	{
		regra1 = 1;//regra 1 fica verdadeira
		valido = 0;//valido fica falso
	}

	if (strcmp(aux->Nome, "") == 0)
	{
		regra1 = 1;//regra 1 verdadeira
		valido = 0;// valido fica falso
	}

	if (strcmp(aux->NomeDiretor, "") == 0)
	{
		regra1 = 1;//regra 1 fica verdadeira
		valido = 0;// valido fica falso
	}

	if (!(aux->duracao.horas >= 0 && aux->duracao.horas <= 24 && aux->duracao.min >= 0 && aux->duracao.min <= 59))
	{
		regra3 = 1;// regra3 fica verdadeira
		valido = 0;//valido fica falso
	}

	if (aux->Temporadas < 0)
	{
		regra2 = 1;// regra 2 fica valida
		valido = 0;//valido fica falso
	}

	if (strcmp(aux->Generos[0], "") == 0)// se o primeiro genero ja for igual a string vazia ja burlou um campo que ficou vazio
	{
		regra1 = 1;//regra 1 fica verdadeira
		valido = 0;//valido fica falso
	}
	//agora pede se valido é igual a 0(invalido)
	if (valido == 0)
	{
		p = fopen("log.txt", "a");// abre o arquivo para escrita.
		fprintf(p, "ID : %s\n", aux->ID);// imprime a id no arquivo
		
		//imprime as regras que foram desobedecidas
		if (regra1 == 1)
			fprintf(p,"Regra 1\n");
		if (regra2 == 1)
			fprintf(p,"Regra 2\n");
		if (regra3 == 1)
			fprintf(p,"Regra 3\n");
		fclose(p);//fecha o arquivo
		return 0;
	}
	else
		return 1;// se for valida vai retonar 1 para a funçao
}

void consultarvideo(SistemaStreaming* sistema)
{
	FILE* arquivo_video;
	char id[30];
	char aux[30];
    int i = 0;
	
	aux[0] = '\0';
	strcat(aux, "vid");

	printf("Insira o ID do vídeo\n");//pede a id do video a ser consultado
	gets(id);

	strcat(aux, id);
	strcat(aux, ".txt");

	system("cls");

	if(existe(id,"videos.txt") == 0)
		printf("O vídeo não existe\n");
	else
	{
		arquivo_video = fopen(aux, "r");
		fgets(aux, 30, arquivo_video);
		printf("ID : %s", aux);//imprime o id

		fgets(aux, 30, arquivo_video);
		printf("Tipo de vídeo: %s", aux);

		fgets(aux, 30, arquivo_video);
		printf("Nome do filme/seriado : %s", aux);

		fgets(aux, 30, arquivo_video);
		printf("Nome completo do diretor : %s", aux);

		fgets(aux, 30, arquivo_video);
		printf("Duração : %s", aux);

		fgets(aux, 30, arquivo_video);
		printf("Quantidade de temporadas : %s", aux);

		fgets(aux, 30, arquivo_video);
		printf("Ano de lançamento : %s", aux);


		printf("Gênero(s):\n");//imprime os generos
		while (1)
		{
			fgets(aux, 30, arquivo_video);
			if (feof(arquivo_video))
				break;
			printf("%s", aux);
		}
		fclose(arquivo_video);
	}

	printIDvideos(sistema);
	submenuconsultarvideo(sistema);//depois que consultou apresenta um submenu com opçoes
}

void submenuconsultarvideo(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós inserir video
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Consultar outro vídeo\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		video(sistema);
		break;
	case 3:
		consultarvideo(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenuconsultarvideo(sistema);// caso a opçao seja inválida
	}
}

void alterarvideo(SistemaStreaming* sistema)
{
	FILE* arquivo_video = NULL;//ponteiro para arquivo, inicializa com NULL.
	CadastroVideo aux;//cria um cadastro de video auxiliar para armazenr as informaçoes temporariamente e testá-las
	inicializavideo(&aux);//inicializa aux corretamente
	char c;// char auxiliar;
	char str_aux_genero[20];//string auxiliar

	printf("Digite o ID do vídeo\n");
	scanf("%s", aux.ID);

	scanf("%*c");///elimina o \n do teclado para o proximo char nao leer
	printf("Digite f para filme e s para seriado\n");
	scanf("%c", &c);//le o char associado a definiçao de filme ou seriado
	if (c == 'f')
		aux.tipo.filme = 1;
	else
		aux.tipo.seriado = 1;

	scanf("%*c");//elimana o outro \n da leitura do char anterior
	printf("Digite o novo nome do filme\\seriado\n");
	gets(aux.Nome);

	printf("Digite o novo nome completo do diretor\n");
	gets(aux.NomeDiretor);

	printf("Digite a nova duração hh:mm\n");
	scanf("%d:%d", &aux.duracao.horas, &aux.duracao.min);

	printf("Digite a nova quantidade de temporadas\n");
	scanf("%d", &aux.Temporadas);

	printf("Digite o novo ano de lançamento\n");
	scanf("%d", &aux.AnoLancamento);

	scanf("%*c");//elimina o \n

	printf("Digite os novos gêneros, digite fim para terminar\n");
	gets(str_aux_genero);

	for (int i = 0; strcmp(str_aux_genero, "fim") != 0; i++)
	{
		strcpy(aux.Generos[i], str_aux_genero);//copia a string lida para o vetor de strings de generos
		aux.quantidade_generos++;//incrementa a quantidade de generos
		gets(str_aux_genero);

	}
	//ok tudo foi lido, agora vem a verificaçao se realmente pode cadastrar esse video;
	if (ValidaVideo(&aux) == 1)
	{
		char aux_nome_arquivo_video[30];

		aux_nome_arquivo_video[0] = '\0';
		strcat(aux_nome_arquivo_video, "vid");
		strcat(aux_nome_arquivo_video, aux.ID);
		strcat(aux_nome_arquivo_video, ".txt");

		arquivo_video = fopen(aux_nome_arquivo_video, "w"); // abre o arquivo para escrita 

		fprintf(arquivo_video, "%s\n", aux.ID);
		if (aux.tipo.filme == 1)
			fprintf(arquivo_video, "Filme\n");
		else
			fprintf(arquivo_video, "Seriado\n");

		fprintf(arquivo_video, "%s\n", aux.Nome);
		fprintf(arquivo_video, "%s\n", aux.NomeDiretor);
		fprintf(arquivo_video, "%d:%d\n", aux.duracao.horas, aux.duracao.min);
		fprintf(arquivo_video, "%d\n", aux.Temporadas);
		fprintf(arquivo_video, "%d\n", aux.AnoLancamento);

		for (int i = 0; i < aux.quantidade_generos; i++)
			fprintf(arquivo_video, "%s\n", aux.Generos[i]);
		fclose(arquivo_video);
	}//n precisa else pq a propria funçao valida ja produz o arquivo com os logs


	system("cls");
	printIDvideos(sistema);
	submenualterarvideo(sistema);//chama um submenu com opções
}

void submenualterarvideo(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós alterar video
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Alterar outro vídeo\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		video(sistema);
		break;
	case 3:
		alterarvideo(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenualterarvideo(sistema);// caso a opçao seja inválida
	}
}

void removervideo(SistemaStreaming* sistema)
{
	FILE* arquivo_antigo,*arquivo_novo;
	char id[30];
	char aux[30];

	aux[0] = '\0';
	strcat(aux, "vid");

	printf("Insira o ID do vídeo a ser removido\n");
	gets(id);//id do video a ser removido
	strcat(aux, id);
	strcat(aux, ".txt");
	system("cls");

	remove(aux);//exclui o arquivo do video.

	arquivo_antigo = fopen("videos.txt", "r");
	arquivo_novo = fopen("videos2.txt","w");

	while (1)
	{
		fscanf(arquivo_antigo,"%[^\n]s",aux);
		fscanf(arquivo_antigo, "%*c");//descarta o \n;
		if (feof(arquivo_antigo))
			break;
		if (strcmp(aux, id) != 0)
			fprintf(arquivo_novo, "%s\n", aux);
	}
	fclose(arquivo_antigo);
	fclose(arquivo_novo);

	remove("videos.txt");
	rename("videos2.txt", "videos.txt");
	
	printIDvideos(sistema);//imprime os ids dos videos
	submenuremovervideo(sistema);
}

void submenuremovervideo(SistemaStreaming* sistema)
{
	int numero;

	//submenu com opçoes pós remover video
	printf("1.Menu principal\n");
	printf("2.Menu anterior\n");
	printf("3.Remover outro vídeo\n");

	scanf("%d", &numero);
	scanf("%*c");//descarta o \n da leitura do numero da opçao
	system("cls");
	switch (numero)
	{
	case 1:
		menu(sistema);
		break;
	case 2:
		video(sistema);
		break;
	case 3:
		removervideo(sistema);
		break;
	default:
		printf("Comando inválido, tente novamente\n");
		submenuremovervideo(sistema);// caso a opçao seja inválida
	}
}