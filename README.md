# Sistema de Gerenciamento Acadêmico e de Compromissos em C

Um sistema interativo desenvolvido na linguagem C para o cadastro e gerenciamento de alunos, disciplinas, notas e controle de compromissos. 

Este projeto foi desenvolvido como aplicação prática da disciplina de **Algoritmos II**, com foco no domínio de conceitos de baixo nível, como gestão de memória, manipulação de ponteiros, estruturas de dados personalizadas e algoritmos de ordenação.

---

## Funcionalidades e Regras de Negócio

* **Gestão de Alunos e Matrículas:** Cadastro completo com Registro Acadêmico (RA), dados pessoais e validação rigorosa de datas de matrícula (com verificação de anos bissextos).
* **Controle de Disciplinas e Notas:** Cadastro de disciplinas associadas aos alunos, entrada de notas e cálculo automático das médias nominais.
* **Agendamento Inteligente de Compromissos:**
  * **Prevenção de Conflitos:** O sistema verifica automaticamente a existência de sobreposição de horários (hora, minuto e segundo) para um mesmo aluno antes de confirmar o agendamento.
  * **Limite de Agendamentos:** Aplicação de regra de negócio que limita a um máximo de **2 compromissos por dia** para cada estudante.
* **Filtros e Consultas:**
  * Busca individual de compromissos por RA.
  * Listagem geral ordenada por Registro Acadêmico ou cronologicamente.
  * Filtragem dinâmica de compromissos por data específica.

---

## Conceitos Técnicos e Arquitetura

Diferente de sistemas estáticos, este projeto foi desenhado para ser eficiente no uso da memória da máquina, aplicando conceitos centrais da programação estruturada:

1. **Alocação Dinâmica de Memória (`malloc` / `realloc`):**
   Os vetores de alunos e compromissos são iniciados com tamanhos base e **expandidos sob demanda**. Quando a capacidade máxima do vetor é atingida, a memória é realocada dinamicamente sem perda dos dados já registrados, evitando o desperdício de memória RAM.
2. **Estruturas Aninhadas (`structs`):**
   Mapeamento limpo de entidades relacionais através da composição de estruturas (`td_data`, `td_hora`, `td_disciplina`, `td_aluno` e `td_compromisso`), simulando modelagem de dados do mundo real.
3. **Algoritmos de Ordenação (`qsort` e Callbacks):**
   Uso da função nativa de ordenação do C com funções de comparação personalizadas (`compararCompromisso`, `compararCompromisso_ra` e `compara_ra`), permitindo ordenar os dados tanto de forma crescente por RA quanto temporalmente por carimbo de data e hora.
4. **Alocação Sob Demanda para Filtros:**
   Nas consultas por data específica, o sistema calcula a quantidade exata de registros encontrados e aloca dinamicamente apenas o espaço necessário para o subvetor de exibição, liberando a memória imediatamente após o uso (`free`).

---

### Pré-requisitos e Execução
* Compilador GCC (GNU Compiler Collection) instalado.

### Passo a Passo

### 1. Compile o código fonte utilizando o GCC (ou no caso do uso de uma IDE pode ser compilado e executado diretamente):

    gcc -Wall -o gerenciador main.c

### 2. Execute o programa no terminal
Após a compilação é gerado um .exe com o mesmo nome do arquivo do projeto, basta executar e pode ser realizado os testes.
