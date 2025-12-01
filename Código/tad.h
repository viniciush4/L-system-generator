// GUSTAVO COSTA DUARTE
// LEONARDO NASCIMENTO DOS SANTOS
// VINÍCIUS BERGER

typedef struct arvore tpArvore;
typedef struct lista tpLista;
typedef struct pilha tpPilha;

#define z 70
#define PI 3.14159265359
#define T 300
#define rotacao 0.00	// Com a rotação = 0.00, árvores serão desenhadas na horizontal
#define TAMINSTRUCAOPS 100

// ASSINATURA DAS FUNÇÕES

void lerArquivo (char nomeArquivo[T], char* subst, char* axiom, char* param, double *numAngle, int *numOrder);

tpArvore *criarArvore (char c);

void inserirArvore (tpArvore *a, tpArvore *sa);

void imprimirArvore (tpArvore *a);

void criarMaisUmNivel(tpArvore *a, char param[T], char subst);

void formarStringFinal(tpArvore *a, char subst, char *stringFinal);

void contarFolhas (tpArvore *a, char subst, int *quantidadeFolhas, int *ocorrenciasDeFeG);

void transformaStringFinalEmStringPs (char stringFinal[T], char *stringFinalPs, double numAngle);

tpPilha* criaPilha(void);

int pilhaVazia(tpPilha* p);

void pushPilha (tpPilha* p, double aux1, double aux2, double aux3);

void popPilha (tpPilha* p, double *aux1, double *aux2, double *aux3);

void liberaPilha(tpPilha* p);

void imprimePilha(tpPilha *p);

void imprimirInterface (tpArvore *arvore, char *axiom, char *param, double numAngle, int numOrder, char subst);

void liberarArvore (tpArvore *a);
