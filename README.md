# Interpretador de Sistema Lindenmayer (L-System)

Sistema de interpretação e visualização de gramáticas formais de Lindenmayer, desenvolvido como trabalho acadêmico da disciplina de Estrutura de Dados I.

## 📋 Sobre o Projeto

Este interpretador lê arquivos com especificações de L-Systems (extensão `.lsy`) e gera visualizações gráficas em formato PostScript. O sistema utiliza estruturas de dados hierárquicas (árvores) para armazenar as iterações das regras de produção e implementa um sistema de tartaruga gráfica para renderização.

## 👥 Autores

- Gustavo Costa Duarte
- Leonardo Nascimento dos Santos
- Vinícius Berger

**Instituição:** Universidade Federal do Espírito Santo (UFES)  
**Professor:** Thomas Walter Rauber  
**Ano:** 2015

## 🎯 Funcionalidades

- Leitura e parsing de arquivos `.lsy`
- Aplicação iterativa de regras de produção
- Geração de árvore de derivação com número variável de filhos
- Conversão para comandos de tartaruga gráfica
- Geração de dois arquivos PostScript de saída
- Tratamento de erros de sintaxe
- Gerenciamento eficiente de memória

## 🏗️ Estrutura do Projeto

```
.
├── trab2.c           # Programa principal
├── tad.c             # Implementação das estruturas de dados
├── tad.h             # Interface do TAD
├── psinterface.c     # Interface PostScript
├── psinterface.h     # Cabeçalho da interface PS
├── lsystem.h         # Definições do L-System
├── makefile          # Script de compilação
└── *.lsy             # Arquivos de exemplo
```

## 🔧 Compilação e Execução

### Requisitos

- GCC (GNU Compiler Collection)
- Sistema operacional Linux/Unix
- Biblioteca matemática (`-lm`)

### Compilar

```bash
make
```

Ou manualmente:

```bash
gcc -c tad.c
gcc -c psinterface.c
gcc -c trab2.c
gcc -o trab2 tad.o psinterface.o trab2.o -lm
```

### Executar

```bash
./trab2
```

O programa solicitará:
1. Nome do arquivo de entrada (`.lsy`)
2. Nome do primeiro arquivo de saída (`.ps`)
3. Nome do segundo arquivo de saída (`.ps`)

## 📝 Formato do Arquivo de Entrada

Sintaxe de um arquivo `.lsy`:

```
angle <número>    ; Ângulo de rotação (360/n graus)
order <número>    ; Número de iterações
axiom <string>    ; String inicial (ordem 0)
<char> = <string> ; Regra de produção
```

### Exemplo

```
angle 8           ; means 360/8
order 3
axiom ++F
F = F+F
```

### Símbolos de Tartaruga Gráfica

| Símbolo | Descrição |
|---------|-----------|
| `F` | Mover com caneta baixada (desenha) |
| `G` | Mover com caneta levantada (não desenha) |
| `+` | Rotacionar por ângulo positivo |
| `-` | Rotacionar por ângulo negativo |
| `[` | Empilhar estado da tartaruga |
| `]` | Desempilhar estado da tartaruga |

## 🌳 Estruturas de Dados

### Árvore
Estrutura hierárquica com número variável de filhos que armazena:
- Raiz: símbolo a ser substituído
- Níveis intermediários: iterações da regra
- Folhas: string final do L-System

### Pilha
Utilizada para gerenciar o estado da tartaruga (posição e orientação) durante o desenho, permitindo ramificações através dos comandos `[` e `]`.

## 📊 Exemplos Incluídos

- `helloworld.lsy` - Exemplo básico
- `helloworld1.lsy` - Árvore fractal simples
- `helloworld2.lsy` - Curva de Koch
- `helloworld3.lsy` - Padrão com ramificações
- `teste.lsy` - Quadrado de Koch
- `teste1.lsy` - Planta fractal
- `teste2.lsy` - Floco de neve

## ⚠️ Tratamento de Erros

O sistema detecta e reporta:
- Arquivo de entrada não encontrado
- Valor de ângulo ausente ou inválido
- Valor de ordem ausente ou inválido
- Informações faltantes no arquivo
- Instância de substituição inválida

Caracteres não permitidos como instância: `=`, `+`, `-`, `!`, `|`, `[`, `]`, `<`, `>`, `@`, `/`, `\`, `_`, `c`, espaço

## 🔍 Verificação de Memória

O projeto foi testado com Valgrind para garantir:
- Ausência de vazamentos de memória
- Liberação adequada de recursos alocados
- Gerenciamento correto de ponteiros

```bash
valgrind --leak-check=full ./trab2
```

## 📐 Algoritmo de Renderização

A conversão da string final para PostScript utiliza:

```
x1 = x0 + z * cos(α)
y1 = y0 + z * sin(α)
```

Onde:
- `z` = comprimento do traço (70 unidades)
- `α` = orientação atual da tartaruga
- `(x0, y0)` = posição inicial
- `(x1, y1)` = posição final

## 📚 Referências

CELES, Waldemar; CERQUEIRA, Renato; RANGEL, José Lucas. **Introdução a estruturas de dados: com técnicas de programação em C**. 11ª triagem. Rio de Janeiro: Elsevier, 2004.

## 📄 Licença

Projeto acadêmico desenvolvido para fins educacionais na UFES.

---

**Nota:** Este projeto foi desenvolvido em 2015 como parte do curso de Ciência da Computação da UFES.
