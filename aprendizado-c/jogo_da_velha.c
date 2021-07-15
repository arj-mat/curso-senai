#include <stdio.h>
#include <string.h>
#include <locale.h>

/*
	Jogo da Velha em C
	
	Mateus Araújo - https://github.com/arj-mat/curso-senai/
	Senai 2021
*/

#define ESTADO_EM_ANDAMENTO 1
#define ESTADO_VITORIA 2
#define ESTADO_EMPATE 3

const int true = 1;
const int false = 0;

const char LETRAS_PONTOS[9] = {
	'a', 'b', 'c',
	'd', 'e', 'f',
	'g', 'h', 'i'
};

const char PONTO_VAZIO = '-';
const char JOGADOR_A = 'X';
const char JOGADOR_B = 'O';

char jogadorAtual;

char tabuleiro[3][3];

void imprimirTabuleiro() {
	int i, j, indice;
	
	system("cls");
	
	printf("Tabuleiro:\n\n");
	
	indice = 0;
	
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if (tabuleiro[i][j] == PONTO_VAZIO)
				printf("| %c ", LETRAS_PONTOS[indice]);
			else
				printf("| %c ", tabuleiro[i][j]);
			
			indice++;
		}
		
		printf("|\n");
	}
	
	printf("\n");
}

int verificarSequenciaVitoria(char *sequencia) {
	char sequenciaVencedora[4] = {jogadorAtual, jogadorAtual, jogadorAtual, '\0'};
	
	if (strcmp(sequencia, sequenciaVencedora) == 0)
		return true;
	else 
		return false;
}

int verificarEstadoPartida() {
	int i, j;
	
	// Verificar vitória horizontal:
	for(i = 0; i < 3; i++) {
		char sequencia[3] = {tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]};
		
		if (verificarSequenciaVitoria(sequencia) == true) {
			return ESTADO_VITORIA;
		}
	}
	
	// Verificar vitória vertical:
	for(i = 0; i < 3; i++) {
		char sequencia[3] = {tabuleiro[0][i], tabuleiro[1][i], tabuleiro[2][i]};
		
		if (verificarSequenciaVitoria(sequencia) == true) {
			return ESTADO_VITORIA;
		}
	}

	// Verificar vitória na diagonal principal:
	char sequenciaDiag1[3] = {tabuleiro[0][0], tabuleiro[1][1], tabuleiro[2][2]};
	
	if (verificarSequenciaVitoria(sequenciaDiag1) == true) {
		return ESTADO_VITORIA;
	}
	
	// Verificar vitória na diagonal secundária:
	char sequenciaDiag2[3] = {tabuleiro[2][0], tabuleiro[1][1], tabuleiro[0][2]};
	
	if (verificarSequenciaVitoria(sequenciaDiag2) == true) {
		return ESTADO_VITORIA;
	}
	
	// Verificar se existe algum ponto vazio que ainda pode ser jogado (caso contrário houve empate):
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if (tabuleiro[i][j] == PONTO_VAZIO)
				return ESTADO_EM_ANDAMENTO;
		}
	}
	
	return ESTADO_EMPATE;
}

void registrarJogada(char letra) {
	int i, j, linha = -1, coluna = -1, indice = 0;
	
	// Obter a linha e a coluna que a letra da jogada representa:
	for(i = 0; i < 3; i++) {
		if (linha != -1 && coluna != -1)
			break; // Linha e coluna já foram encontradas, então parar o loop principal.
		
		for(j = 0; j < 3; j++) {
			if (LETRAS_PONTOS[indice] == letra) {
				linha = i;
				coluna = j;
				break;
			}
			
			indice++;
		}
	}
	
	if (linha == -1 && coluna == -1) {
		proximaJogada(false); // Linha e coluna não foram encontradas. Logo, a jogada foi inválida.
	} else {
		if (tabuleiro[linha][coluna] == PONTO_VAZIO) {
			tabuleiro[linha][coluna] = jogadorAtual;
			
			int estadoPartida = verificarEstadoPartida();
			
			switch(estadoPartida) {
				case ESTADO_EM_ANDAMENTO:
					proximaJogada(true);
					break;
				case ESTADO_VITORIA:
					imprimirTabuleiro();
					printf("%c venceu!\n\n", jogadorAtual);
					system("pause");
					break;
				case ESTADO_EMPATE:
					imprimirTabuleiro();
					printf("Ninguém ganhou.\n\n");
					system("pause");
					break;
			}
		} else
			proximaJogada(false); // Jogada inválida pois o ponto escolhido já foi jogado.
	}
}

void proximaJogada(int jogadaAnteriorFoiValida) {
	char letraJogada;
	
	imprimirTabuleiro();
	
	if (jogadaAnteriorFoiValida == true) {
		// Trocar jogador atual:
		
		if (jogadorAtual == JOGADOR_A)
			jogadorAtual = JOGADOR_B;
		else
			jogadorAtual = JOGADOR_A;
	}
	else
		printf("Jogada inválida. Tente novamente.\n");
	
	printf("É a vez do jogador %c.\nInforme a letra: ", jogadorAtual);
	
	fflush(stdin);
	
	scanf("%c", &letraJogada);
	
	registrarJogada(letraJogada);
}

main() {
	setlocale(LC_ALL, "Portuguese");
	
	int i, j;
	
	// Preencher o tabuleiro:
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			tabuleiro[i][j] = PONTO_VAZIO;
	
	// Iniciar o jogo:
	proximaJogada(true);
}
