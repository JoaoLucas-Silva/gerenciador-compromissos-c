/*
   Projeto disciplina Algoritmos 2
*/

// Bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criações das structs que serão utilizadas ao decorrer do programa
typedef struct { // Struct p/ data
    int dia;
    int mes;
    int ano;
} td_data;

typedef struct { // Struct p/ horário
    int hora;
    int min;
    int seg;
} td_hora;

typedef struct { // Struct p/ disciplina
    int codigo_dis;
    td_data matricula;
    char disciplina[100];
    float notas[4];
    float media;
} td_disciplina;

typedef struct { // Struct p/ dados dos alunos
    int ra;
    char nome[100];
    td_data matricula;
    td_disciplina disciplinas[4];
    char email[100];
} td_aluno;

typedef struct { // Struct p/ compromisso
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;

// Protótipo das funções
void cadastra_aluno(td_aluno [], int *);
td_aluno *aloca_vetor_alunos(int);
td_aluno *realoca_vetor_alunos(td_aluno *, int);
void cadastra_compromissos(td_compromisso vc[], int *i);
td_compromisso *aloca_vetor_compromissos(int);
td_compromisso *realoca_vetor_compromissos(td_compromisso *, int);
void imprime_vetor_de_alunos(td_aluno va[], int d);
void imprime_vetor_de_compromissos(td_compromisso vc[], int d);
void le_data(td_data *d);
void le_data_mat(td_data *d);
int verifica_data(td_data *d);
void le_horario(td_hora *h);
int verifica_horario(td_hora *h);
void cadastra_disciplina(td_aluno va[], int *i);
int compara_ra(const void *a, const void *b);
int compararCompromisso(const void *a, const void *b);
int compararCompromisso_ra(const void *a, const void *b);

// Main
int main(void)
{
    // Declaração das variáveis
    int dva = 10, iva = 0, dvc = 15, ivc = 0, num, ra, encontrado, novo_tamanho, i, 
    data_d, data_m, data_a, qtd_filtrados = 0;
    td_aluno *va = NULL;
    td_compromisso *vc = NULL;
    char verif_cad_al, verif_cad_comp, letra_compromisso, verifica_case = 's';

    // Alocação inicial dos vetores
    va = aloca_vetor_alunos(dva);
    if (va == NULL) {
        printf("\nErro ao alocar memoria para o vetor de alunos.\n");
        return 1;
    }

    vc = aloca_vetor_compromissos(dvc);
    if (vc == NULL) {
        printf("\nErro ao alocar memoria para o vetor de compromissos.\n");
        free(va);  // Libera memória antes de sair
        return 1;
    }

    // Entrada para o switch case
    while (verifica_case == 's')
    {   
        // Menu de opções
        printf("\nDigite o numero correspondente a acao que deseja fazer\n"
               "1: Cadastrar disciplina\n"
               "2: Cadastrar aluno\n"
               "3: Cadastrar compromisso\n"
               "4: Imprimir compromissos\n"
               "5: Imprimir dados de um aluno\n"
               "6: Imprimir dados de todos os alunos\n"
               "7: Sair\n"
               "\nNumero:");
        scanf("%d", &num);

        // Início do switch case conforme a escolha do usuário
        switch (num)
        {
            case 1:
                // Cadastrar disciplinas para os alunos
                cadastra_disciplina(va, &iva);
                break;

            case 2:
                // Cadastrar alunos
                for (i = 0; i < dva; i++) {
                    cadastra_aluno(va, &iva);
                }

                verif_cad_al = 's';
                while (verif_cad_al == 's') // Verificação se o usuário deseja cadastrar mais alunos
                {
                    printf("\nDeseja cadastrar mais alunos? (s/n): ");
                    scanf(" %c", &verif_cad_al);

                    if (verif_cad_al == 's') 
                    {
                        // Realocar o vetor de alunos para um novo tamanho
                        novo_tamanho = dva * 10;
                        va = realoca_vetor_alunos(va, novo_tamanho);
                        if (va == NULL) 
                        {
                            printf("\nErro com realocacao de memoria para vetor de alunos\n");
                            return 0;
                        }

                        printf("\nVetor de alunos foi realocado para %d posicoes.\n", novo_tamanho);

                        // Atualizar a dimensão atual do vetor
                        dva = novo_tamanho;

                        // Cadastrar novos alunos
                        for (i = iva; i < novo_tamanho; i++) 
                        {
                            cadastra_aluno(va, &iva);
                        }
                    }
                }
                break;

            case 3:
                // Cadastrar compromissos
                for (i = 0; i < dvc; i++) 
                {
                    cadastra_compromissos(vc, &ivc);
                }

                verif_cad_comp = 's';
                while (verif_cad_comp == 's') 
                {
                    printf("\nDeseja cadastrar mais compromissos? (s/n): ");
                    scanf(" %c", &verif_cad_comp);

                    if (verif_cad_comp == 's') 
                    {
                        // Realocar o vetor de compromissos para um novo tamanho
                        novo_tamanho = dvc * 5;
                        vc = realoca_vetor_compromissos(vc, novo_tamanho);
                        if (vc == NULL) 
                        {
                            printf("\nErro com realocacao de memoria para vetor de compromissos\n");
                            return 0;
                        }

                        printf("\nVetor de compromissos foi realocado para %d posicoes.\n", novo_tamanho);

                        // Atualizar a dimensão atual do vetor
                        dvc = novo_tamanho;

                        // Cadastrar novos compromissos
                        for (i = ivc; i < novo_tamanho; i++) 
                        {
                            cadastra_compromissos(vc, &ivc);
                        }
                    }
                }
                break;

            case 4:
                if (ivc == 0)  // Verifica se há compromissos cadastrados
                {
                    printf("\nNao ha compromissos cadastrados.\n");
                    break;
                }

                printf("\nSelecione a subopcao:\n");
                printf("a) Compromissos de um aluno\n");
                printf("b) Compromissos de todos os alunos\n");
                printf("c) Compromissos de uma data\n");
                printf("d) Compromissos de todas as datas\n");
                printf("\nEscolha: ");
                scanf(" %c", &letra_compromisso);

                switch (letra_compromisso) 
                {
                    case 'a':
                        printf("\nDigite o RA do aluno: ");
                        scanf("%d", &ra);

                        encontrado = 0;
                        for (int i = 0; i < ivc; i++)
                        {
                            if (vc[i].aluno.ra == ra) 
                            {
                                encontrado = 1;
                                printf("\nAluno: %s", vc[i].aluno.nome);
                                printf("\nHorario: %02d:%02d:%02d", vc[i].horario.hora, vc[i].horario.min, vc[i].horario.seg);
                                printf("\nData do compromisso: %02d/%02d/%04d",
                                    vc[i].data.dia, vc[i].data.mes, vc[i].data.ano);
                                printf("\nDescricao: %s\n", vc[i].descricao);
                            }
                        }

                        if (!encontrado) 
                        {
                            printf("\nAluno nao encontrado ou sem compromissos.\n");
                        }
                        break;

                    case 'b':
                        qsort(vc, ivc, sizeof(td_compromisso), compararCompromisso_ra); // Função de ordenação
                        imprime_vetor_de_compromissos(vc, ivc);
                        break;

                    case 'c':
                        printf("\nDigite a data do(s) compromisso(s) -> (dia/mes/ano): ");
                        scanf("%d/%d/%d", &data_d, &data_m, &data_a);

                        encontrado = 0;
                        qtd_filtrados = 0;

                        // Contar compromissos que correspondem à data
                        for (int i = 0; i < ivc; i++) 
                        {
                            if (vc[i].data.dia == data_d && vc[i].data.mes == data_m && vc[i].data.ano == data_a) 
                            {
                                qtd_filtrados++;
                            }
                        }

                        if (qtd_filtrados == 0) 
                        {
                            printf("\nNenhum compromisso cadastrado nessa data.\n");
                            return 0;
                        }

                        // Aloca apenas o espaço necessário para os compromissos filtrados
                        td_compromisso *compromissos_filtrados = malloc(qtd_filtrados * sizeof(td_compromisso));
                        if (compromissos_filtrados == NULL) 
                        {
                            printf("\nErro ao alocar memoria para compromissos filtrados.\n");
                            return 0;
                        }

                        // Preencher vetor filtrado
                        qtd_filtrados = 0;
                        for (int i = 0; i < ivc; i++) 
                        {
                            if (vc[i].data.dia == data_d && vc[i].data.mes == data_m && vc[i].data.ano == data_a) 
                            {
                                compromissos_filtrados[qtd_filtrados++] = vc[i];
                            }
                        }

                        // Ordenar e imprimir
                        qsort(compromissos_filtrados, qtd_filtrados, sizeof(td_compromisso), compararCompromisso);
                        imprime_vetor_de_compromissos(compromissos_filtrados, qtd_filtrados);

                        // Liberação de memória
                        free(compromissos_filtrados);
                        break;

                    case 'd':
                        qsort(vc, ivc, sizeof(td_compromisso), compararCompromisso_ra); // Função de ordenação
                        imprime_vetor_de_compromissos(vc, ivc);
                        break;

                    default:
                        printf("Subopcao invalida!\n");
                }
                break;

            case 5:
                if (iva == 0)  // Verifica se há alunos cadastrados
                {
                    printf("\nNao ha alunos cadastrados.\n");
                    break;
                }

                printf("\nDigite o RA do aluno: ");
                scanf("%d", &ra);

                encontrado = 0;
                for (int i = 0; i < iva; i++) 
                {
                    if (va[i].ra == ra) 
                    {
                        encontrado = 1;

                        printf("\nNome: %s\n", va[i].nome);
                        printf("E-mail: %s\n", va[i].email);
                        printf("Data de Matricula: %02d/%02d/%04d\n",
                            va[i].matricula.dia,
                            va[i].matricula.mes,
                            va[i].matricula.ano);

                        printf("\nDisciplinas:\n");
                        for (int j = 0; j < 4; j++) 
                        {
                            printf("Codigo: %d\n", va[i].disciplinas[j].codigo_dis);
                            printf("Nome: %s\n", va[i].disciplinas[j].disciplina);
                            printf("Media: %.2f\n", va[i].disciplinas[j].media);
                            printf("\n");
                        }
                        break;
                    }
                }

                if (!encontrado) 
                {
                    printf("\nAluno nao encontrado.\n");
                }
                break;

            case 6:
                if (iva == 0)  // Verifica se há alunos cadastrados
                {
                    printf("\nNao ha alunos cadastrados.\n");
                    break;
                }
                qsort(va, iva, sizeof(td_aluno), compara_ra);
                imprime_vetor_de_alunos(va, iva);
                break;
            case 7:
                printf("\nSaindo do programa...\n");
                free(va);
                free(vc);
                return 0;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }

        printf("\nDeseja continuar no menu? (s/n): ");
        scanf(" %c", &verifica_case);
    }

    // Libera memória antes de sair
    free(va);
    free(vc);

    return 0;
}

// Funções utilizadas no programa
void cadastra_aluno(td_aluno va[], int *i)
{
    int j, k;
    float soma;

    printf("\nCadastrando aluno %d\n", *i + 1);
    printf("\nRA .......: ");
    scanf("%d", &va[*i].ra);
    printf("\nNome .....: ");
    scanf(" %[^\n]%*c", va[*i].nome);
    printf("\ne-mail ...: ");
    scanf(" %[^\n]%*c", va[*i].email);
    le_data_mat(&va[*i].matricula);

    for (j = 0; j < 4; j++) 
    {
        printf("\n%d Disciplina\n", j + 1);
        printf("\tCodigo ...: ");
        scanf("%d", &va[*i].disciplinas[j].codigo_dis);
        printf("\tNome da disciplina ...: ");
        scanf(" %[^\n]%*c", va[*i].disciplinas[j].disciplina);
        printf("\tNotas\n");

        soma = 0;  // Inicialize a soma antes de somar as notas
        for (k = 0; k < 4; k++) 
        {
            printf("\t%d nota ...: ", k + 1);
            scanf("%f", &va[*i].disciplinas[j].notas[k]);
            soma += va[*i].disciplinas[j].notas[k];
        }
        
        // Calcule a média da disciplina e atribua ao campo 'media'
        va[*i].disciplinas[j].media = soma / 4;  // Média de 4 notas
    }
    (*i)++;
}

td_aluno *aloca_vetor_alunos(int d)
{
    return (td_aluno *)malloc(d * sizeof(td_aluno));
}

td_aluno *realoca_vetor_alunos(td_aluno *vetor, int novo_tamanho)
{
    return (td_aluno *)realloc(vetor, novo_tamanho * sizeof(td_aluno));
}

void le_data_mat(td_data *d)
{
    do {
        printf("Informe a data da matricula (dd/mm/aaaa):");
        scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);
    } while (!verifica_data(d));
}

int verifica_data(td_data *d)
{
    if (d->ano <= 0 || d->mes < 1 || d->mes > 12 || d->dia < 1 || d->dia > 31)
        return 0;
    if ((d->mes == 4 || d->mes == 6 || d->mes == 9 || d->mes == 11) && d->dia > 30)
        return 0;
    if (d->mes == 2) {
        int bissexto = (d->ano % 4 == 0 && (d->ano % 100 != 0 || d->ano % 400 == 0));
        if (d->dia > 29 || (d->dia == 29 && !bissexto))
            return 0;
    }
    return 1;
}

void imprime_vetor_de_alunos(td_aluno va[], int d)
{
    for (int i = 0; i < d; i++) {
        printf("\nDado do aluno %d", i + 1);
        printf("\nRA .......: %d", va[i].ra);
        printf("\nNome .....: %s", va[i].nome);
        printf("\ne-mail ...: %s", va[i].email);
        printf("\nData da matricula (%d/%d/%d):", va[i].matricula.dia, va[i].matricula.mes, va[i].matricula.ano);
        for (int j = 0; j < 4; j++) {
            printf("\n%d Disciplina\n", j + 1);
            printf("\tCodigo ...: %d,", va[i].disciplinas[j].codigo_dis);
            printf("\tNome da disciplina ...: %s\n", va[i].disciplinas[j].disciplina);
            printf("\tMedia ....: %.2f\n", va[i].disciplinas[j].media);
        }
    }
}

void cadastra_compromissos(td_compromisso vc[], int *i) 
{
    td_compromisso novo;
    int countCompromissos = 0;

    printf("\nCadastrando compromisso %d\n", *i + 1);
    printf("RA do aluno: ");
    scanf("%d", &novo.aluno.ra);
    printf("Nome do aluno: ");
    scanf(" %[^\n]%*c", novo.aluno.nome);
    printf("Descricao: ");
    scanf(" %[^\n]%*c", novo.descricao);

    le_data(&novo.data);
    le_horario(&novo.horario);

    // Verificar compromissos existentes
    for (int j = 0; j < *i; j++) {
        if (vc[j].aluno.ra == novo.aluno.ra &&
            vc[j].data.dia == novo.data.dia &&
            vc[j].data.mes == novo.data.mes &&
            vc[j].data.ano == novo.data.ano) {
            
            countCompromissos++;
            
            // Verificar sobreposição de horários (hora, minuto, segundo)
            if (vc[j].horario.hora == novo.horario.hora &&
                vc[j].horario.min == novo.horario.min &&
                vc[j].horario.seg == novo.horario.seg) {
                printf("Erro: horario de compromisso sobreposto com outro compromisso do mesmo aluno.\n");
                return;
            }
        }
    }

    // Verificar limite de compromissos (máximo de 2 no mesmo dia)
    if (countCompromissos >= 2) {
        printf("Erro: aluno ja possui dois compromissos na mesma data.\n");
        return;
    }

    // Adicionar compromisso ao vetor
    vc[*i] = novo;
    (*i)++;
    printf("Compromisso cadastrado com sucesso.\n");
}

td_compromisso *aloca_vetor_compromissos(int d)
{
	return (td_compromisso *)malloc(d * sizeof(td_compromisso));
}

td_compromisso *realoca_vetor_compromissos(td_compromisso *vetor, int novo_tamanho)
{
    return (td_compromisso *)realloc(vetor, novo_tamanho * sizeof(td_compromisso));
}

void le_data(td_data *d)
{
    do {
        printf("Informe a data do compromisso(dd/mm/aaaa):");
        scanf("%d/%d/%d", &d->dia, &d->mes, &d->ano);
    } while (!verifica_data(d));
}

void imprime_vetor_de_compromissos(td_compromisso vc[], int d) 
{
    for (int i = 0; i < d; i++) {
        printf("\nCompromisso %d: RA: %d, \nNome: %s, \nDescricao: %s, \nData: %02d/%02d/%04d," 
        "\nHorario: %02d:%02d:%02d\n",
               i + 1, vc[i].aluno.ra, vc[i].aluno.nome, vc[i].descricao, vc[i].data.dia, vc[i].data.mes,
               vc[i].data.ano, vc[i].horario.hora,vc[i].horario.min,vc[i].horario.seg);
    }
}

int verifica_horario(td_hora *h) 
{
    return (h->hora >= 0 && h->hora < 24 && h->min >= 0 && h->min < 60 && h->seg >= 0 && h->seg < 60);
}

void le_horario(td_hora *h) 
{ 
    do 
    {
        printf("Digite o horario (hh:mm:ss): ");
        scanf("%d:%d:%d", &h->hora, &h->min, &h->seg);
    } while (!verifica_horario(h));
}

int compararCompromisso_ra(const void *a, const void *b) 
{
    td_compromisso *compA = (td_compromisso *)a;
    td_compromisso *compB = (td_compromisso *)b;

    // Comparar RA
    if (compA->aluno.ra != compB->aluno.ra) {
        return compA->aluno.ra - compB->aluno.ra;
    }

    // Se RA for igual, comparar a data
    if (compA->data.ano != compB->data.ano) {
        return compA->data.ano - compB->data.ano;
    }
    if (compA->data.mes != compB->data.mes) {
        return compA->data.mes - compB->data.mes;
    }
    if (compA->data.dia != compB->data.dia) {
        return compA->data.dia - compB->data.dia;
    }

    // Se data for igual, comparar hora
    if (compA->horario.hora != compB->horario.hora) {
        return compA->horario.hora - compB->horario.hora;
    }
    if (compA->horario.min != compB->horario.min) {
        return compA->horario.min - compB->horario.min;
    }
    return compA->horario.seg - compB->horario.seg;
}

int compararCompromisso(const void *a, const void *b) {
    td_compromisso *comp1 = (td_compromisso *)a;
    td_compromisso *comp2 = (td_compromisso *)b;

    if (comp1->data.ano != comp2->data.ano)
        return comp1->data.ano - comp2->data.ano;
    if (comp1->data.mes != comp2->data.mes)
        return comp1->data.mes - comp2->data.mes;
    if (comp1->data.dia != comp2->data.dia)
        return comp1->data.dia - comp2->data.dia;
    if (comp1->horario.hora != comp2->horario.hora)
        return comp1->horario.hora - comp2->horario.hora;
    if (comp1->horario.min != comp2->horario.min)
        return comp1->horario.min - comp2->horario.min;
    return comp1->horario.seg - comp2->horario.seg;
}

void cadastra_disciplina(td_aluno va[], int *i) // Função para usar no menu
{
    int j, k;
    float soma;

    for (j = 0; j < 4; j++) {
        printf("\n%d Disciplina\n", j + 1);
        printf("\tCodigo ...: ");
        scanf("%d", &va[*i].disciplinas[j].codigo_dis);
        printf("\tNome da disciplina ...: ");
        scanf(" %[^\n]%*c", va[*i].disciplinas[j].disciplina);
        printf("\tNotas\n");

        for (k = 0, soma = 0; k < 4; k++) {
            printf("\t%d nota ...: ", k + 1);
            scanf("%f", &va[*i].disciplinas[j].notas[k]);
            soma += va[*i].disciplinas[j].notas[k];
        }
        va[*i].disciplinas[j].media = soma / 4;

        // Imprime a média da disciplina atual
        printf("\nMedia da disciplina %d: %0.2f\n", j + 1, va[*i].disciplinas[j].media);
    }

    // Incrementa o índice ao final do cadastro
    (*i)++;
}

int compara_ra(const void *a, const void *b) 
{
    td_aluno *aluno1 = (td_aluno *)a;
    td_aluno *aluno2 = (td_aluno *)b;
    return aluno1->ra - aluno2->ra; // Crescente
}