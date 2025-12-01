# L-System Generator

## Autores
- Gustavo Costa Duarte
- Leonardo Nascimento dos Santos
- Vinícius Berger

## Descrição do Projeto

Este projeto implementa um **gerador de L-Systems (Lindenmayer Systems)** em C, capaz de produzir fractais e padrões complexos através de regras de substituição recursivas. O programa lê uma especificação de L-System de um arquivo, processa as regras de produção e gera saídas visuais em formato **PostScript**.

### O que são L-Systems?

L-Systems são sistemas de reescrita paralela desenvolvidos pelo biólogo Aristid Lindenmayer em 1968, originalmente para modelar o crescimento de plantas. O sistema funciona através de:
- Um **axioma** (string inicial)
- **Regras de produção** que substituem símbolos
- **Iterações** sucessivas aplicando as regras

## Funcionalidades

### Principais Características

1. **Leitura de Arquivos `.lsy`**: Processa especificações de L-Systems
2. **Estrutura em Árvore**: Representa as derivações através de uma árvore n-ária
3. **Geração Recursiva**: Aplica regras de produção por n iterações
4. **Saída PostScript**: Gera dois tipos de arquivos `.ps`:
   - Visualização básica do L-System
   - Visualização com interpretação turtle graphics

### Parâmetros do Sistema

O arquivo de entrada define:
- `angle`: Ângulo de rotação (360/angle graus)
- `order`: Número de iterações/derivações
- `axiom`: String inicial
- `Regra de produção`: Define como cada símbolo é substituído

## Estrutura do Código

### Estruturas de Dados

```c
// Árvore n-ária para representar derivações
typedef struct arvore {
    char info;           // Símbolo
    tpArvore *prim;      // Primeiro filho
    tpArvore *prox;      // Próximo irmão
} tpArvore;

// Pilha para coordenadas (usado em branches)
typedef struct pilha {
    tpLista *prim;
} tpPilha;
```

### Funções Principais

- `lerArquivo()`: Lê e parseia o arquivo .lsy
- `criarArvore()`: Cria nós da árvore
- `criarMaisUmNivel()`: Aplica regras de produção recursivamente
- `formarStringFinal()`: Percorre a árvore gerando a string resultante
- `transformaStringFinalEmStringPs()`: Converte para comandos PostScript

## Interpretação dos Símbolos

| Símbolo | Significado |
|---------|-------------|
| `F` | Desenha linha e avança |
| `G` | Move sem desenhar |
| `+` | Rotação positiva |
| `-` | Rotação negativa |
| `[` | Salva posição (push) |
| `]` | Restaura posição (pop) |

## Como Usar

### Compilação

```bash
gcc trab2.c lsystem.c psinterface.c -o lsystem -lm
```

### Execução

```bash
./lsystem
```

O programa solicitará o nome do arquivo `.lsy` (atualmente hardcoded para `teste.lsy`).

### Formato do Arquivo de Entrada

```
angle 8
order 1
axiom F
F = [++F++F++F[-F][+F][--F][++F][+++F]]
```

### Saídas Geradas

- `teste.ps`: Visualização básica
- `testePs.ps`: Visualização com turtle graphics

## Exemplo de Uso

Com o arquivo `teste.lsy` fornecido:
- **Ângulo**: 8 (45° de rotação)
- **Ordem**: 1 iteração
- **Axioma**: F
- **Regra**: F expande para uma estrutura com múltiplos branches

## Constantes Configuráveis

```c
#define z 50              // Tamanho do passo
#define PI 3.14159265359  // Valor de π
#define T 300             // Tamanho máximo de strings
#define rotacao 0.00      // Rotação inicial
```

## Limitações Conhecidas

- String final pode ter problemas com última posição da pilha
- Validação limitada de caracteres especiais
- Apenas aceita caracteres maiúsculos (preparação para parte II)
- Tamanho máximo de instruções PostScript definido estaticamente

## Dependências

- `lsystem.h`: Funções específicas do L-System
- `psinterface.h`: Interface para geração PostScript
- Bibliotecas padrão: `stdio.h`, `stdlib.h`, `string.h`, `math.h`

## Melhorias Futuras

- [ ] Corrigir problema na geração da string final
- [ ] Organizar como tipo abstrato de dados (TAD)
- [ ] Melhorar validação de entrada
- [ ] Documentação completa
- [ ] Refatoração de nomes de variáveis
- [ ] Tratamento de erros mais robusto

## Aplicações

L-Systems são amplamente utilizados para:
- Modelagem de plantas e vegetação
- Geração procedural de terrenos
- Arte fractal e generativa
- Simulação de crescimento biológico
- Computer graphics

## Licença

Projeto acadêmico - uso educacional.
