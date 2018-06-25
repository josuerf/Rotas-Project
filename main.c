/* 
 * File:   main.c
 * Author: Josue
 *
 * Created on 16 de Junho de 2018, 22:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#include "main.h"


Distancias *distancias = NULL;
Visitados *visitados = NULL;
Excluidos *excluidos = NULL;
CidVert vert[50] = {};
Incid incid[50] = {};
int oldIni;
int remIdx = -1;
int globalIdx = 9;
int start = 1;
int distancia = 0;
float rotaAtual = 1.00;
int primeiro = 0;
int distEscolhida = 0;
float rotaEscolhida = 0;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Portuguese");
    fillList();
    menuPrincipal();
    return (EXIT_SUCCESS);
}

void buscaCid(int ini, char dest[], int dist) {
    if (primeiro == 0) {
        primeiro = ini;
    }
    CidNo *holder = vert[ini].adjacentes;
    if (strcasecmp(vert[ini].nome, dest) == 0) {
        int menor = 0;
        printf("- Distância: %dkm\n", distancia);
        if (distancias == NULL) {
            distancias = (Distancias*) malloc(sizeof (distancias));
            distancias->dist = distancia;
            distancias->prox = NULL;
            distEscolhida = distancia;
            rotaEscolhida = rotaAtual;
        } else {
            Distancias *distHolder = distancias;
            while (distHolder->prox != NULL) {
                if (distancia <= distHolder->dist) {
                    menor = 1;
                } else {
                    menor = 0;
                }
                distHolder = distHolder->prox;
            }
            if (menor == 1) {
                distEscolhida = distancia;
                rotaEscolhida = rotaAtual;
            }
            Distancias *novo = (Distancias*) malloc(sizeof (Distancias));
            novo->dist = distancia;
            novo->prox = NULL;
            distHolder->prox = novo;
        }
        distancia = 0;
        start = 1;
        printf(">> FIM COM SUCESSO <<\n\n");
        return;
    } else if (ini == oldIni) {
        return;
    } else {
        for (; holder != NULL; holder = holder->prox) {
            int num = holder->cidade;
            if (holder->visitado != 1) {
                if (start == 1) {
                    int inteira;
                    float centena, dezena;
                    inteira = rotaAtual;
                    dezena = ((rotaAtual - inteira)*10);
                    inteira = dezena;
                    centena = ((dezena - inteira)*10);
                    inteira = rotaAtual;
                    printf("\nRota %d.%.0f.%.0f\n", inteira, dezena, centena);
                    printf("\n>> Início <<\n");
                    start++;
                }
                printf("de %s -> %s\n", vert[ini].nome, vert[holder->cidade].nome);
                oldIni = ini;
                distancia = dist + holder->distancia;
                holder->visitado = 1;
                if (visitados == NULL) {
                    visitados = (Visitados*) malloc(sizeof (Visitados));
                    visitados->visitado = &holder->visitado;
                    visitados->prox = NULL;
                } else {
                    Visitados *novoV = (Visitados*) malloc(sizeof (Visitados));
                    Visitados *hold = visitados;
                    while (hold->prox != NULL) {
                        hold = hold->prox;
                    }
                    novoV->visitado = &holder->visitado;
                    novoV->prox = NULL;
                    hold->prox = novoV;
                }
                buscaCid(num, dest, distancia);
            } else {
                printf(">> FIM INESPERADO <<\n\n");
                rotaAtual = rotaAtual + 0.01;
                int inteira;
                float centena, dezena;
                inteira = rotaAtual;
                dezena = ((rotaAtual - inteira)*10);
                inteira = dezena;
                centena = ((dezena - inteira)*10);
                inteira = rotaAtual;
                printf("Rota %d.%.0f.%.0f\n\n", inteira, dezena, centena);
                printf(">> Início <<\n");
                break;
            }
            if (primeiro == ini) {
                int volta = rotaAtual;
                volta++;
                rotaAtual = volta;
            }
        }
    }
}

void alteraDistancia(int idxOrigem, int idxDestino, int distancia) {
    CidNo *no = vert[idxOrigem].adjacentes;
    for (; no != NULL; no = no->prox) {
        if (no->cidade == idxDestino) {
            no->distancia = distancia;
        }
    }
    getchar();
}

void mostraVizinhas() {
    CidNo *holder;
    int i, j = 0;
    for (i = 0; i <= globalIdx; i++) {
        if (vert[i].ativo) {
            printf("%s: {  ", vert[i].nome);
            for (holder = vert[i].adjacentes; holder != NULL; holder = holder->prox) {
                if (j == 0) {
                    printf("%s(%d KM)", vert[holder->cidade].nome, holder->distancia);
                } else {
                    printf(", %s(%d KM)", vert[holder->cidade].nome, holder->distancia);
                }
                j++;
            }
            j = 0;
            printf("  }\n");
        }
    }
}

void buscaVizinhas(int ini) {
    CidNo *holder;
    system("cls");
    if (vert[ini].adjacentes == NULL) {
        printf("Não Há Ligações Com %s\n", vert[ini].nome);
    } else {
        puts(vert[ini].nome);
        printf("Destino%28s\n", "Distância");
        for (holder = vert[ini].adjacentes; holder != NULL; holder = holder->prox) {
            printf("%s%20d\n", vert[holder->cidade].nome, holder->distancia);
        }
    }
    getchar();
}

void insereVertice(char nome[]) {
    int idxHolder;
    Excluidos *holder = excluidos;
    if (excluidos != NULL) {
        idxHolder = excluidos->index;
        if (excluidos->prox != NULL) {
            excluidos = excluidos->prox;
        } else {
            excluidos = NULL;
        }
        free(holder);
    } else {
        globalIdx++;
        idxHolder = globalIdx;
    }
    vert[idxHolder].ativo = 1;
    strncpy(vert[idxHolder].nome, nome, 20);
    vert[idxHolder].adjacentes = NULL;
    remIdx = -1;
}

IncidNo *insereIncid(IncidNo *incid, int num) {
    IncidNo *aux = incid;
    IncidNo *novo = (IncidNo*) malloc(sizeof (IncidNo));
    novo->num = num;
    novo->prox = NULL;
    if (aux == NULL) {
        return novo;
    }
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return incid;
}

CidNo *insereNo(CidNo *nos, int destinoIdx, int distancia, int origemIdx) {
    CidNo *noAux = nos;
    CidNo *novo = (CidNo*) malloc(sizeof (CidNo));
    novo->cidade = destinoIdx;
    novo->distancia = distancia;
    novo->visitado = 0;
    novo->prox = NULL;
    if (nos != NULL) {
        while (noAux->prox != NULL) {
            noAux = noAux->prox;
        }
        noAux->prox = novo;
    } else {
        return novo;
    }
    insereIncid(incid[destinoIdx].adjacentes, origemIdx);
    return nos;
}

void limparVisitados(Visitados* visitado) {
    if (visitado->prox != NULL) {
        limparVisitados(visitado->prox);
    }
    *visitado->visitado = 0;
    free(visitado);
}

void limparDistancias(Distancias *dist) {
    if (dist->prox != NULL) {
        limparDistancias(dist->prox);
    }
    dist = NULL;
    free(dist);
}

void removerCidade(int index) {
    removerNo(vert[index].adjacentes);
    vert[index].adjacentes = NULL;
    vert[index].ativo = 0;
    excluidos = insereExcluido(excluidos, index);
    IncidNo *holder = incid[index].adjacentes;
    for (; holder != NULL; holder = holder->prox) {
        buscaLigaRemove(holder->num, index);
    }
    removerNoIncid(incid[index].adjacentes);
}

Excluidos *insereExcluido(Excluidos *excluido, int index) {
    Excluidos *holdEx = excluido;
    Excluidos *novo = (Excluidos*) malloc(sizeof (Excluidos));
    novo->index = index;
    novo->prox = NULL;
    if (excluido == NULL) {
        return novo;
    } else {
        while (holdEx->prox != NULL) {
            holdEx = holdEx->prox;
        }
        holdEx->prox = novo;
    }
    return excluido;
}

void buscaLigaRemove(int incidIdx, int cidIndex) {
    CidNo *hold, *ant;
    int i = 0;
    for (hold = vert[incidIdx].adjacentes; hold != NULL; hold = hold->prox) {
        if (hold->cidade == cidIndex) {
            if (hold->prox != NULL) {
                ant->prox = hold->prox;
            } else if (hold->prox == NULL && i == 0) {
                vert[incidIdx].adjacentes = NULL;
            } else {
                ant->prox = NULL;
            }
            free(hold);
            break;
        }
        i++;
        ant = hold;
    }
}

void removerNoIncid(IncidNo * incidNo) {
    if (incidNo->prox != NULL) {

        removerNoIncid(incidNo->prox);
    }
    incidNo = NULL;
    free(incidNo);
}

void removerCaminho(int origem, int destino) {
    CidNo *hold, *ant;
    int i = 0;
    for (hold = vert[origem].adjacentes; hold != NULL; hold = hold->prox) {
        if (hold->cidade == destino) {
            if (hold->prox != NULL) {
                ant->prox = hold->prox;
            } else if (hold->prox == NULL && i == 0) {
                vert[origem].adjacentes = NULL;
            } else {
                ant->prox = NULL;
            }
            free(hold);
            removeIncid(destino, origem);
            break;
        }
        ant = hold;
        i++;
    }
}

void removeIncid(int incidIdx, int origem) {
    IncidNo *hold, *ant;
    int i = 0;
    for (hold = incid[incidIdx].adjacentes; hold != NULL; hold = hold->prox) {
        if (hold->num == origem) {
            if (hold->prox != NULL) {
                ant->prox = hold->prox;
            } else if (hold->prox == NULL && i == 0) {
                vert[incidIdx].adjacentes = NULL;
            } else {
                ant->prox = NULL;
            }
            free(hold);
            break;
        }
        ant = hold;
        i++;
    }
}

void listarTodas() {
    printf(">> Cidades Cadastradas <<\n");
    int i, j = 1;
    for (i = 0; i <= globalIdx; i++) {
        if (vert[i].ativo) {
            printf("%s\n", vert[i].nome);
        }
    }
    printf("\n");
}

void removerNo(CidNo * no) {
    if (no->prox != NULL) {
        removerNo(no->prox);
    }
    no = NULL;
    free(no);
}

void alteraNome(char *nome) {
    strtok(nome, "\n");
}

void atualizaCidade(int idxVert, char nome[], int distancia, int idxNo) {
    if (sizeof (nome) > 0) {
        strcpy(vert[idxVert].nome, nome);
    }
    if (distancia != -1) {
        CidNo *hold = vert[idxVert].adjacentes;
        for (; hold != NULL; hold = hold->prox) {
            if (hold->cidade == idxNo) {

                hold->distancia = distancia;
            }
        }
    }
}

void listarNos(int idxVert) {
    CidNo *hold = vert[idxVert].adjacentes;
    printf("Cidade %s\n", vert[idxVert].nome);
    printf("Destinos: \n");
    for (; hold != NULL; hold = hold->prox) {

        printf("Nome: %s\tDistância: %d\n", vert[hold->cidade].nome, hold->distancia);
    }
}

void fillList() {

    strcpy(vert[0].nome, "Alegrete");
    incid[0].num = 0;
    incid[0].adjacentes = NULL;
    strcpy(vert[1].nome, "Bage");
    incid[1].num = 1;
    incid[1].adjacentes = NULL;
    strcpy(vert[2].nome, "Cruz Alta");
    incid[2].num = 2;
    incid[2].adjacentes = NULL;
    strcpy(vert[3].nome, "Passo Fundo");
    incid[3].num = 3;
    incid[3].adjacentes = NULL;
    strcpy(vert[4].nome, "Pelotas");
    incid[4].num = 4;
    incid[4].adjacentes = NULL;
    strcpy(vert[5].nome, "POA");
    incid[5].num = 5;
    incid[5].adjacentes = NULL;
    strcpy(vert[6].nome, "São Borja");
    incid[6].num = 6;
    incid[6].adjacentes = NULL;
    strcpy(vert[7].nome, "São Gabriel");
    incid[7].num = 7;
    incid[7].adjacentes = NULL;
    strcpy(vert[8].nome, "Santiago");
    incid[8].num = 8;
    incid[8].adjacentes = NULL;
    strcpy(vert[9].nome, "SM");
    incid[9].num = 9;
    incid[9].adjacentes = NULL;
    int i;
    for (i = 0; i <= globalIdx; i++) {
        vert[i].ativo = 1;
    }
    vert[0].adjacentes = insereNo(vert[0].adjacentes, 6, 315, 0);
    vert[1].adjacentes = insereNo(vert[1].adjacentes, 7, 268, 1);
    vert[2].adjacentes = insereNo(vert[2].adjacentes, 3, 149, 2);
    vert[2].adjacentes = insereNo(vert[2].adjacentes, 9, 134, 2);
    vert[3].adjacentes = insereNo(vert[3].adjacentes, 5, 289, 3);
    vert[4].adjacentes = insereNo(vert[4].adjacentes, 1, 189, 4);
    vert[5].adjacentes = insereNo(vert[5].adjacentes, 4, 261, 5);
    vert[5].adjacentes = insereNo(vert[5].adjacentes, 1, 377, 6);
    vert[6].adjacentes = insereNo(vert[6].adjacentes, 8, 141, 6);
    vert[7].adjacentes = insereNo(vert[7].adjacentes, 0, 204, 7);
    vert[8].adjacentes = insereNo(vert[8].adjacentes, 2, 242, 8);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 8, 152, 9);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 0, 258, 9);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 7, 182, 9);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 1, 239, 9);
    vert[9].adjacentes = insereNo(vert[9].adjacentes, 5, 291, 9);
    incid[6].adjacentes = insereIncid(incid[6].adjacentes, 0);
    incid[7].adjacentes = insereIncid(incid[7].adjacentes, 1);
    incid[7].adjacentes = insereIncid(incid[7].adjacentes, 9);
    incid[5].adjacentes = insereIncid(incid[5].adjacentes, 3);
    incid[5].adjacentes = insereIncid(incid[5].adjacentes, 9);
    incid[4].adjacentes = insereIncid(incid[4].adjacentes, 5);
    incid[3].adjacentes = insereIncid(incid[3].adjacentes, 2);
    incid[2].adjacentes = insereIncid(incid[2].adjacentes, 8);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 4);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 5);
    incid[1].adjacentes = insereIncid(incid[1].adjacentes, 9);
    incid[0].adjacentes = insereIncid(incid[0].adjacentes, 9);
    incid[0].adjacentes = insereIncid(incid[0].adjacentes, 7);
    incid[8].adjacentes = insereIncid(incid[8].adjacentes, 9);
    incid[8].adjacentes = insereIncid(incid[8].adjacentes, 6);
    incid[9].adjacentes = insereIncid(incid[9].adjacentes, 2);
}

void menuPrincipal() {
    int opc;
    while (opc != 9) {
        system("cls");
        printf(">> Bem Vindo Ao Mapa Rodoviário <<\n \n1. Visualizar Rotas\n2. Cadastrar Dados"
                "\n3. Remover Dados\n4. Alterar Dados de Uma Cidade\n9. Sair\nOPC: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                menuVisualizar();
                break;
            case 2:
                menuCadastrar();
                break;
            case 3:
                menuRemover();
                break;
            case 4:
                menuAlterar();
                break;
            case 9:
                return;
            default:
                printf("Opção Inválida");

                break;
        }
    }
}

void menuVisualizar() {
    int opc;
    while (opc != 9) {
        system("cls");
        printf(">> Vizualizar <<\n \n1. Visualizar Cidades Vizinhas\n2. Visualizar Rotas Entre Cidades\n9. Retornar\nOPC: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                menuCidadesVizinhas();
                break;
            case 2:
                menuRotaCidades();
                break;
            case 9:
                return;
            default:
                printf("Opção Inválida!");

                break;
        }
    }
}

void menuCadastrar() {
    int opc;
    while (opc != 9) {
        system("cls");

        printf(">> Cadastrar <<\n \n1. Cadastrar Cidade\n2. Cadastrar Caminho\n9. Retornar\nOPC: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                menuInserirCidade();
                break;
            case 2:
                menuInserirCaminho();
                break;
            case 9:
                return;
            default:
                printf("Opção Inválida!");

                break;
        }
    }
}

void menuRemover() {
    int opc;
    while (opc != 9) {
        system("cls");
        printf(">> Remover <<\n \n1. Remover Cidade\n2. Remover Caminho\n9. Retornar\nOPC: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                menuRemoverCidade();
                break;
            case 2:
                menuRemoverCaminho();
                break;
            case 9:
                return;
            default:
                printf("Opção Inválida!");

                break;
        }
    }
}

void menuAlterar() {
    int opc;
    while (opc != 9) {
        system("cls");
        printf(">> Alterar <<\n \n1. Alterar Dados Cidade\n2. Alterar Distância Entre Cidades\n9. Retornar\nOPC: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                menuAlterarNome();
                break;
            case 2:
                menuAlterarDistancia();
                break;
            case 9:
                return;
            default:
                printf("Opção Inválida!");

                break;
        }
    }
}

void menuCidadesVizinhas() {
    system("cls");
    printf("\t\t\t\t\tCidades Vizinhas\n");
    listarTodas();
    printf("Digite a Cidade Desejada\n");
    char nome[20];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof (nome), stdin);
    alteraNome(nome);
    printf("%s\n", nome);
    int idx = buscaIndice(nome);
    if (idx == -1) {
        printf("Cidade Não Cadastrada!\n");
        system("pause");
    } else {
        buscaVizinhas(buscaIndice(nome));
    }
}

void menuRotaCidades() {
    system("cls");
    printf("\t\t\t\t\tRota Entre Cidades\n");
    listarTodas();
    printf(" \nDigite a Origem e o Destino Desejada\n");
    char nomeO[20], nomeD[20];
    printf("Cidade Origem: ");
    fflush(stdin);
    fgets(nomeO, sizeof (nomeO), stdin);
    alteraNome(nomeO);
    printf("Cidade Destino: ");
    fflush(stdin);
    fgets(nomeD, sizeof (nomeD), stdin);
    alteraNome(nomeD);
    int idxO = buscaIndice(nomeO);
    int idxD = buscaIndice(nomeD);
    if (idxO == -1) {
        printf("Cidade %s Não Cadastrada!\n", nomeO);
        getchar();
    } else if (idxD == -1) {
        printf("Cidade %s Não Cadastrada!\n", nomeD);
        getchar();
    } else {
        if (vert[idxO].adjacentes != NULL && vert[idxD].adjacentes != NULL) {
            buscaCid(idxO, nomeD, 0);
            primeiro = 0;
            int inteira;
            float centena, dezena;
            inteira = rotaEscolhida;
            dezena = ((rotaEscolhida - inteira)*10);
            inteira = dezena;
            centena = ((dezena - inteira)*10);
            inteira = rotaEscolhida;
            printf("Rota Mais Curta: %d.%.0f.%.0f\t Distância(KM): %d\n", inteira, dezena, centena, distEscolhida);
            getchar();
            limparDistancias(distancias);
            limparVisitados(visitados);
            visitados = NULL;
            distancias = NULL;
            start = 1;
            rotaAtual = 1;
        } else {
            printf("Não há rotas entre estas cidades.");
        }
    }
}

void menuInserirCidade() {
    system("cls");
    puts("\t\t\t\t\tInserir Cidade");
    printf("Informe o Nome da Cidade\n");
    char nome[20];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof (nome), stdin);
    alteraNome(nome);
    int idx = buscaIndice(nome);
    int i, x = 0;
    for (i < 0; i < strlen(nome); i++) {
        if (isdigit(nome[i])) {
            x = 1;
        }
    }
    if (x == 1) {
        printf("Números Não São Permitidos!\n");
        getchar();
    } else {
        if (idx != -1) {
            printf("%s já está cadastrada!\n", nome);
            getchar();
        } else {
            insereVertice(nome);
        }
    }
}

void menuInserirCaminho() {
    system("cls");
    printf("\t\t\t\t\tInserir Caminho\n");
    listarTodas();
    printf("Informe o Nome da Cidade de Origem\n");
    char nome[20];
    char destino[20];
    int distancia;
    printf("Cidade Origem: ");
    fflush(stdin);
    fgets(nome, sizeof (nome), stdin);
    alteraNome(nome);
    printf("Cidade Destino: ");
    fflush(stdin);
    fgets(destino, sizeof (destino), stdin);
    alteraNome(destino);
    printf("Distância(KM): ");
    scanf("%d", &distancia);
    int origemIdx = buscaIndice(nome);
    int destIdx = buscaIndice(destino);
    if (origemIdx == -1) {
        printf("Cidade %s Não Cadastrada!\n", nome);
        getchar();
    } else if (destIdx == -1) {
        printf("Cidade %s Não Cadastrada!\n", destino);
        getchar();
    } else {
        vert[origemIdx].adjacentes = insereNo(vert[origemIdx].adjacentes, destIdx, distancia, origemIdx);
    }
}

void menuRemoverCidade() {
    system("cls");
    printf("\t\t\t\t\tRemover Cidade\n");
    listarTodas();
    printf("Informe a Cidade a ser removida\n");
    char nome[20];
    printf("Nome: ");
    fflush(stdin);
    fgets(nome, sizeof (nome), stdin);
    alteraNome(nome);
    int idx = buscaIndice(nome);
    if (idx == -1) {
        printf("%s Não está cadastrada!\n", nome);
        getchar();
    } else {
        removerCidade(idx);
    }
}

void menuRemoverCaminho() {
    system("cls");
    printf("\t\t\t\t\tRemover Caminho\n");
    printf(">> Cidades Vizinhas <<\n");
    mostraVizinhas();
    char de[20];
    char para[20];
    printf("Remover Caminho\n");
    printf("de: ");
    fflush(stdin);
    fgets(de, sizeof (de), stdin);
    alteraNome(de);
    printf("para: ");
    fflush(stdin);
    fgets(para, sizeof (para), stdin);
    alteraNome(para);
    int origemIdx = buscaIndice(de);
    int destIdx = buscaIndice(para);
    if (origemIdx == -1 || destIdx == -1) {
        printf("Caminho Inexistente");
        getchar();
    } else {
        removerCaminho(origemIdx, destIdx);
    }
}

void menuAlterarNome() {
    system("cls");
    printf("\t\t\t\t\tAlterar Nome\n");
    listarTodas();
    char antigo[20];
    char novo[20];
    printf("Informe os Dados de Alteração\n");
    printf("Cidade: ");
    fflush(stdin);
    fgets(antigo, sizeof (antigo), stdin);
    alteraNome(antigo);
    int ant = buscaIndice(antigo);
    if (ant == -1) {
        printf("Cidade Inexistente!\n");
        system("pause");
    } else {
        printf("Novo Nome: ");
        fflush(stdin);
        fgets(novo, sizeof (novo), stdin);
        alteraNome(novo);
        strncpy(vert[ant].nome, novo, 20);
    }
}

void menuAlterarDistancia() {
    system("cls");
    printf("\t\t\t\t\tAlterar Distância\n");
    printf(">> Cidades Vizinhas <<\n");
    mostraVizinhas();
    printf("\n");
    char de[20];
    char para[20];
    int distancia;
    printf("Informe os Dados de Alteração\n");
    printf("Cidade Origem: ");
    fflush(stdin);
    fgets(de, sizeof (de), stdin);
    alteraNome(de);
    printf("Cidade Destino: ");
    fflush(stdin);
    fgets(para, sizeof (para), stdin);
    alteraNome(para);
    int origem = buscaIndice(de);
    int destino = buscaIndice(para);
    if (origem == -1 || destino == -1) {
        printf("Caminho Inexistente!\n");
        getchar();
    } else {
        printf("Nova Distância: ");
        scanf("%d", &distancia);
        alteraDistancia(origem, destino, distancia);
        getchar();
    }
}

int buscaIndice(char cidade[]) {
    int x = 0, i;
    for (i = 0; i < strlen(cidade); i++) {
        switch (cidade[i]) {
            case -58:
                cidade[i] = 'ã';
                break;
            case -98:
                cidade[i] = 'á';
                break;
            case -123:
                cidade[i] = 'à';
                break;
            case -125:
                cidade[i] = 'â';
                break;
            case -126:
                cidade[i] = 'é';
                break;
            case -118:
                cidade[i] = 'è';
                break;
            case -120:
                cidade[i] = 'ê';
                break;
            case -94:
                cidade[i] = 'ó';
                break;
            case -107:
                cidade[i] = 'ò';
                break;
            case -109:
                cidade[i] = 'ô';
                break;
            case -28:
                cidade[i] = 'õ';
                break;
            case -95:
                cidade[i] = 'í';
                break;
            case -115:
                cidade[i] = 'ì';
                break;
            case -116:
                cidade[i] = 'î';
                break;
        }
    }
    printf("\n");
    for (; x <= globalIdx; x++) {
        if (strcasecmp(vert[x].nome, cidade) == 0) {
            return x;
        }
    }
    return -1;
}