// GUSTAVO COSTA DUARTE
// LEONARDO NASCIMENTO DOS SANTOS
// VINÍCIUS BERGER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lsystem.h"
#include "psinterface.h"
#include "tad.h"

int main()
{
	// DECLARAÇÃO DAS VARIAVEIS
	char 
		subst, 
		axiom[T]="", 
		param[T]="", 
		nomeArquivo[T]="",
		nomeSaidaA[T]="",
		nomeSaidaB[T]="",
		*stringFinal="",
		*stringFinalPs="";
	int 
		quantidadeFolhas=0,
		ocorrenciasDeFeG=0, 
		numOrder=0,
		i=0;
	double
		numAngle=0.0;
		
    
    	// LÊ OS NOMES DOS ARQUIVOS DE ENTRADA E SAÍDA
    	system("clear");
    	printf("\nL I N D E N M A Y E R  S Y S T E M\n\n");
    	printf("== I N P U T\n");
	printf("\tDigite o nome do arquivo de entrada. (ex: arquivo.lsy): \n\t");
	scanf("%s",nomeArquivo);
	printf("\n");
	printf("== O U T P U T S\n");
	printf("\tDigite o nome do arquivo de saida 1. (ex: arquivo1.ps): \n\t");
	scanf("%s",nomeSaidaA);
	printf("\n");
	printf("\tDigite o nome do arquivo de saida 2. (ex: arquivo2.ps): \n\t");
	scanf("%s",nomeSaidaB);
	
    	// LÊ O CONTEÚDO DO ARQUIVO DE ENTRADA E ARMAZENA OS VALORES NAS VARIÁVEIS
	lerArquivo (nomeArquivo, &subst, axiom, param, &numAngle, &numOrder);
	
	// CRIA A RAIZ DA ARVORE
	tpArvore *arvore = criarArvore(subst);
	
	// CRIA O NIVEL ZERO (AXIOMA)
	for(i=(strlen(axiom)-1); axiom[i]!='\0'; i--)
		 inserirArvore (arvore, criarArvore(axiom[i]));
		
	// CHAMA A FUNÇÃO DE CRIAR MAIS UM NIVEL DE ACORDO COM O VALOR DE ORDER
	for(i=0; i<numOrder; i++)
		criarMaisUmNivel(arvore, param, subst);
	
	// CONTA QUANTAS FOLHAS TEM A ARVORE E QUANTOS FeG
	contarFolhas (arvore, subst, &quantidadeFolhas, &ocorrenciasDeFeG);
	
	// MALLOCA A QUANTIDADE DE ESPAÇO PARA A STRING FINAL
	stringFinal = (char*)malloc((quantidadeFolhas+1) * sizeof(char));
	
	// FORMA A STRING FINAL
	formarStringFinal(arvore, subst, stringFinal);
	
	// MALLOCA A QUANTIDADE DE ESPAÇO PARA STRING FINAL PS
	stringFinalPs = (char*)malloc(ocorrenciasDeFeG * TAMINSTRUCAOPS * sizeof(char));
	
	// TRANSFORMA A STRING FINAL EM UMA STRING POSTSCRIPT
	transformaStringFinalEmStringPs (stringFinal, stringFinalPs, numAngle);
	
	// INTERFACE DO PROGRAMA
	imprimirInterface (arvore, axiom, param, numAngle, numOrder, subst);
	
	// CRIA O ARQUIVO POSTSCRIPT DA PARTE 1 DO TRABALHO
	genps(numAngle, numOrder, rotacao, stringFinal, nomeSaidaA);
	
	// CRIA O ARQUIVO POSTSCRIPT DA PARTE 2 DO TRABALHO
	genpsTurtle(numAngle, numOrder, rotacao, stringFinalPs, nomeSaidaB);
		
	// LIBERA TODOS OS ESPAÇOS ALOCADOS
	free(stringFinal);
	free(stringFinalPs);
	liberarArvore(arvore);
	
	// ENCERRA O PROGRAMA
	return(EXIT_SUCCESS);

}
