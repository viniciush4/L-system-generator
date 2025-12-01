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


struct arvore
{
	char info;
	tpArvore *prim;
	tpArvore *prox;	
};

struct lista
{
	double aux1, aux2, aux3;
	struct lista *prox;
};

struct pilha
{
	tpLista *prim;
};



// FUNÇÕES AUXILIARES

void imprimirInterface (tpArvore *arvore, char *axiom, char *param, double numAngle, int numOrder, char subst)
{
	printf("\n== P R E A M B L E\n");
	printf("\tAngle = %f\n", numAngle);
	printf("\tOrder = %d\n", numOrder);
	printf("\tImage global rotate = %f\n\n", rotacao);
	printf("== P R O D U C T I O N S\n");
	printf("\tAxiom = %s\n", axiom);
	printf("\t%c = %s\n\n", subst, param);
	printf("== T R E E\n");
	imprimirArvore(arvore);
	printf("\n\n");
}

void liberarArvore (tpArvore *a)
{
	tpArvore *p = a->prim;
	while(p!=NULL)
	{
		tpArvore *t = p->prox;
		liberarArvore(p);
		p = t;
	}
	free(a);
}

tpArvore *criarArvore (char c)
{
	tpArvore *a = (tpArvore*)malloc(sizeof(tpArvore));
	a->info = c;
	a->prim = NULL;
	a->prox = NULL;
	return a;
}

void inserirArvore (tpArvore *a, tpArvore *sa)
{
	sa->prox = a->prim;
	a->prim = sa;
}

void imprimirArvore (tpArvore *a)
{
	tpArvore *p;
	printf("<%c", a->info);
	for (p=a->prim; p!=NULL; p=p->prox)
		imprimirArvore(p);
	printf(">");
}

void criarMaisUmNivel(tpArvore *a, char param[T], char subst)
{
	int i=0;
	
	if(a->prim == NULL)
	{
		if(a->info == subst)
		{
			for(i=(strlen(param)-1); param[i]!='\0'; i--)
				inserirArvore(a, criarArvore(param[i]));
			
			if(a->prox != NULL)
				criarMaisUmNivel(a->prox, param, subst);
		}
		else
		{			
			if(a->prox != NULL)
				criarMaisUmNivel(a->prox, param, subst);
		}	
	}
	else
	{
		criarMaisUmNivel(a->prim, param, subst);
		
		if(a->prox != NULL)
			criarMaisUmNivel(a->prox, param, subst);
	}
}

void contarFolhas (tpArvore *a, char subst, int *quantidadeFolhas, int *ocorrenciasDeFeG)
{
	
	if(a->prim == NULL)
	{
		*quantidadeFolhas = *quantidadeFolhas + 1;
		
		if(a->info == 'F' || a->info == 'G')
			*ocorrenciasDeFeG = *ocorrenciasDeFeG + 1;
					
		if(a->prox != NULL)
			contarFolhas(a->prox, subst, quantidadeFolhas, ocorrenciasDeFeG);	
	}
	else
	{
		contarFolhas(a->prim, subst, quantidadeFolhas, ocorrenciasDeFeG);
		
		if(a->prox != NULL)
			contarFolhas(a->prox, subst, quantidadeFolhas, ocorrenciasDeFeG);
	}
}

void formarStringFinal(tpArvore *a, char subst, char *stringFinal)
{
	if(a->prim == NULL)
	{
		sprintf(stringFinal, "%s%c", stringFinal, a->info);
		
		if(a->prox != NULL)
			formarStringFinal(a->prox, subst, stringFinal);
	
	}
	else
	{
		formarStringFinal(a->prim, subst, stringFinal);
		
		if(a->prox != NULL)
			formarStringFinal(a->prox, subst, stringFinal);
	}
}

void lerArquivo (char nomeArquivo[T], char *subst, char *axiom, char *param, double *numAngle, int *numOrder)
{

	char nome[T], aux1[T]; 
 	int lidos = 0;
 
	FILE* arq; 
	arq = fopen(nomeArquivo,"r"); 
     
	if(arq == NULL) 
	{ 
		printf ("Erro na abertura do arquivo !\n"); 
		exit (1); 
	} 
     
	while (fscanf(arq,"%s",nome) != EOF) 
	{ 
		if(strcmp(nome,"angle") == 0) 
		{ 
			fscanf(arq," %[^\n]", aux1);
			if(sscanf(aux1,"%lf", numAngle) == 0)
			{
				printf("\n== E R R O R\n\tProblema ao ler o Angulo fornecido.\n");
				exit (1);
			}
			lidos+=1;
		} 
		else 
		{ 
			if(strcmp(nome,"order") == 0) 
			{ 
				fscanf(arq," %[^\n]", aux1);
				if(sscanf(aux1,"%d", numOrder) == 0)
				{
					printf("\n== E R R O R\n\tProblema ao ler a Ordem fornecida.\n");
					exit (1);
				}
				lidos+=1;
			} 
			else 
			{ 
				if(strcmp(nome,"axiom") == 0) 
				{ 
					fscanf(arq," %[^\n]", aux1);
					if(sscanf(aux1,"%s", axiom) == 0)
					{
						printf("\n== E R R O R\n\tProblema ao ler o Axioma fornecido.\n");
						exit (1);
					}
					lidos+=1;
				} 
				else 
				{            	                	
					fscanf(arq," %[^\n]", aux1);
					sscanf(aux1,"= %s", param);
					lidos+=1;
					if(nome[0] == '=' ||
					nome[0] == '+' ||
					nome[0] == '-' ||
					nome[0] == '!' ||
					nome[0] == '|' ||
					nome[0] == '[' ||
					nome[0] == ']' ||
					nome[0] == '<' ||
					nome[0] == '>' ||
					nome[0] == '@' ||
					nome[0] == '/' ||
					nome[0] == '\\' ||
					nome[0] == '_' ||
					nome[0] == 'c' ||
					nome[0] == ' '
					)
					{
						printf("\n== E R R O R\n\tA instancia a ser substituida é inválida.\n");
						exit (1);
					}
					else
					{
						*subst = nome[0];
						lidos+=1;
					}
				}
			}
		} 
	}     
	fclose (arq);
	
	if(lidos!=5)
	{
		printf("\n== E R R O R\n\tFaltam informações no arquivo de entrada.\n");
		exit (1);
	}
}

void transformaStringFinalEmStringPs (char *stringFinal, char *stringFinalPs, double numAngle)
{
	int i=0;
	double x0=0.0, x1=0.0, y0=0.0, y1=0.0, rot = 0.0, aux1=0.0, aux2=0.0, aux3=0.0;
	tpPilha* p = criaPilha();
	
	for(i=0; stringFinal[i] != '\0'; i++)
	{
		switch(stringFinal[i])
		{
			case 'F':
				x1 = x0 + z * cos(rot);
				y1 = y0 + z * sin(rot);
				if(i!=0)
				{
					sprintf(stringFinalPs, "%s n %.2f %.2f m %.2f %.2f l s\n",stringFinalPs,x0,y0,x1,y1);
				}
				else 
				{
					sprintf(stringFinalPs, "n %.2f %.2f m %.2f %.2f l s\n",x0,y0,x1,y1);
				}
				x0 = x1;
				y0 = y1;
				break;
			case 'G':
				x1 = x0 + z * cos(rot);
				y1 = y0 + z * sin(rot);
				if(i!=0)
				{
					sprintf(stringFinalPs, "%s n %.2f %.2f m %.2f %.2f l\n",stringFinalPs,x0,y0,x1,y1);
				}
				else
				{
					sprintf(stringFinalPs, "n %.2f %.2f m %.2f %.2f l\n",x0,y0,x1,y1);
				}
				x0 = x1;
				y0 = y1;
				break;
			case '+':
				if(numAngle == 0.0)
				{
					rot = 0.0;
				}
				else
				{
					rot += ((360.0/numAngle)*PI)/180.0;
				} 
				break;
			case '-':
				if(numAngle == 0.0)
				{
					rot = 0.0;
				}
				else
				{
					rot -= ((360.0/numAngle)*PI)/180.0;
				} 
				break;
			case '[':
				pushPilha (p, x0, y0, rot);
				break;
			case ']':
				popPilha (p, &x0, &y0, &rot);
				break;	
		}	
	}
	liberaPilha(p);
}

void imprimePilha(tpPilha *p)
{
	tpLista *q;
	
	for(q=p->prim;q!=NULL;q=q->prox)
		printf("\n\n\nx: %lf y: %lf\n", q->aux1, q->aux2);
}

tpPilha* criaPilha(void)
{
	tpPilha* p = (tpPilha*) malloc(sizeof(tpPilha));
	p->prim = NULL;
	return p;
}

int pilhaVazia(tpPilha* p)
{
	return (p->prim == NULL);
}

void pushPilha (tpPilha* p, double aux1, double aux2, double aux3)
{
	tpLista* n = (tpLista*) malloc(sizeof(tpLista));
	n->aux1 = aux1;
	n->aux2 = aux2;
	n->aux3 = aux3;
	n->prox = p->prim;
	p->prim = n;
}

void popPilha (tpPilha* p, double *aux1, double *aux2, double *aux3)
{
	tpLista* t;
	
	if(pilhaVazia(p))
	{
		printf("Pilha vazia !\n");
		exit(1);
	}
	
	t = p->prim;
	*aux1 = t->aux1;
	*aux2 = t->aux2;
	*aux3 = t->aux3;
	p->prim = t->prox;
	free(t);
}

void liberaPilha(tpPilha* p)
{
	tpLista* q = p->prim;
	
	while(q!=NULL)
	{
		tpLista* t = q->prox;
		free(q);
		q = t;
	} 
	free (p);
}

