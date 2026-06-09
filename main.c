#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>   
#define VIDAS_MAX    3
#define MAX_LINHAS   25
#define MAX_COLUNAS  25
#define MAX_MONSTROS 10


#define PAREDE   '*'
#define ESPINHO  '#'
#define CAIXA    'k'
#define BOTAO    'O'
#define PORTA_F  'D'
#define CHAVE    '@'
#define PORTA_A  '='
#define ESCADA   'L'
#define MON1     'X'
#define MON2     'Y'
#define BOSS     'Z'
#define VAZIO    '.'
#define NPC      'N'


#define CIMA   0
#define BAIXO  1
#define ESQ    2
#define DIR    3


#define ESPADA  0
#define ARCO    1
#define CAJADO  2


#define FASE_VILA  0
#define FASE_1     1
#define FASE_2     2
#define FASE_3     3


int jogador_linha;
int jogador_coluna;
int jogador_direcao;
int jogador_vidas;
int jogador_arma;
int jogador_chaves;


int fase_atual;
int linhas_mapa;
int colunas_mapa;
int botao_apertado;
int game_over;
int vitoria;
int turno_boss;  

char mapa[MAX_LINHAS][MAX_COLUNAS];


int mon_linha[MAX_MONSTROS];
int mon_coluna[MAX_MONSTROS];
int mon_vivo[MAX_MONSTROS];
int mon_tipo[MAX_MONSTROS];
int mon_hp[MAX_MONSTROS];
int num_monstros;


void limpar_tela() {
    system("cls");
}


void esperar_enter() {
    printf("\nPressione Enter para continuar...");
    fflush(stdin);  //limpa o buffer de entrada
    getchar();
}


char ler_tecla() {
    return getch(); //sem apertar enter
}

int abs_val(int n) {
    if (n < 0) return -n;
    return n;
}



void carregar_vila() {
    linhas_mapa    = 10;
    colunas_mapa   = 10;
    num_monstros   = 0;
    botao_apertado = 0;

    strcpy(mapa[0], "**********");
    strcpy(mapa[1], "*........*");
    strcpy(mapa[2], "*..N.....*");
    strcpy(mapa[3], "*........*");
    strcpy(mapa[4], "*........*");
    strcpy(mapa[5], "*........*");
    strcpy(mapa[6], "*........*");
    strcpy(mapa[7], "*........*");
    strcpy(mapa[8], "*......L.*");
    strcpy(mapa[9], "**********");

    jogador_linha   = 1;
    jogador_coluna  = 1;
    jogador_direcao = DIR;
}

void carregar_andar1() {
    linhas_mapa    = 10;
    colunas_mapa   = 10;
    num_monstros   = 0;
    botao_apertado = 0;

    strcpy(mapa[0], "**********");
    strcpy(mapa[1], "*........*");
    strcpy(mapa[2], "*..k.....*");
    strcpy(mapa[3], "**..*....*");
    strcpy(mapa[4], "*...D....*");
    strcpy(mapa[5], "*...@....*");
    strcpy(mapa[6], "**..*.**..*");
    strcpy(mapa[7], "*........*");
    strcpy(mapa[8], "*.......L*");
    strcpy(mapa[9], "**********");

    
    mapa[6][10] = '\0';

    jogador_linha   = 1;
    jogador_coluna  = 1;
    jogador_direcao = DIR;
    jogador_chaves  = 0;
}

void carregar_andar2() {
    linhas_mapa    = 15;
    colunas_mapa   = 15;
    botao_apertado = 0;

    strcpy(mapa[0],  "***************");
    strcpy(mapa[1],  "*.............*");
    strcpy(mapa[2],  "*..###........*");
    strcpy(mapa[3],  "*....D........*");
    strcpy(mapa[4],  "*..@..........*");
    strcpy(mapa[5],  "*....****.....*");
    strcpy(mapa[6],  "*..O..........*");
    strcpy(mapa[7],  "*....D........*");
    strcpy(mapa[8],  "*..@..........*");
    strcpy(mapa[9],  "*.............*");
    strcpy(mapa[10], "***.*.........*");
    strcpy(mapa[11], "*.............*");
    strcpy(mapa[12], "*.............*");
    strcpy(mapa[13], "*...........L.*");
    strcpy(mapa[14], "***************");

    num_monstros = 2;

    mon_linha[0]  = 9;  mon_coluna[0]  = 8;
    mon_vivo[0]   = 1;  mon_tipo[0]    = 1;  mon_hp[0] = 1;

    mon_linha[1]  = 11; mon_coluna[1]  = 10;
    mon_vivo[1]   = 1;  mon_tipo[1]    = 1;  mon_hp[1] = 1;

    jogador_linha   = 1;
    jogador_coluna  = 1;
    jogador_direcao = DIR;
    jogador_chaves  = 0;
}

void carregar_andar3() {
    int i, j;
    linhas_mapa    = 25;
    colunas_mapa   = 25;
    botao_apertado = 0;

    
    for (i = 0; i < 25; i++)
        for (j = 0; j < 25; j++)
            mapa[i][j] = PAREDE;

    
    for (i = 1; i < 24; i++)
        for (j = 1; j < 24; j++)
            mapa[i][j] = VAZIO;

    
    for (j = 1; j < 24; j++) mapa[10][j] = PAREDE;
    mapa[10][12] = PORTA_F;   

    
    for (j = 1; j < 24; j++) mapa[18][j] = PAREDE;
    mapa[18][6]  = PORTA_F;  
    mapa[18][18] = PORTA_F;   

    
    mapa[6][20] = ESPINHO;
    mapa[7][20] = ESPINHO;

    
    mapa[3][3]   = CHAVE;   
    mapa[3][21]  = CHAVE;  
    mapa[14][3]  = CHAVE;   

    // Botao remove espinhos (recompensa, nao punição)
    mapa[14][21] = BOTAO;

    //Escada acessivel apos as 3 portas
    mapa[22][12] = ESCADA;

    num_monstros = 3;

    
    mon_linha[0]=4;  mon_coluna[0]=18; mon_vivo[0]=1; mon_tipo[0]=1; mon_hp[0]=1;

    
    mon_linha[1]=14; mon_coluna[1]=12; mon_vivo[1]=1; mon_tipo[1]=2; mon_hp[1]=2;

    
    mon_linha[2]=21; mon_coluna[2]=12; mon_vivo[2]=1; mon_tipo[2]=3; mon_hp[2]=3;

    jogador_linha   = 1;
    jogador_coluna  = 1;
    jogador_direcao = DIR;
    jogador_chaves  = 0;
}


   //DESENHAR O MAPA
  
void desenhar_mapa() {
    int i, j;

    
    char tela[MAX_LINHAS][MAX_COLUNAS];
    for (i = 0; i < linhas_mapa; i++)
        for (j = 0; j < colunas_mapa; j++)
            tela[i][j] = mapa[i][j];

    // monstros vivos
    for (i = 0; i < num_monstros; i++) {
        if (!mon_vivo[i]) continue;
        char s;
        if      (mon_tipo[i] == 1) s = MON1;
        else if (mon_tipo[i] == 2) s = MON2;
        else                       s = BOSS;
        tela[mon_linha[i]][mon_coluna[i]] = s;
    }

    //jogador
    char simbolo;
    if      (jogador_direcao == CIMA)  simbolo = '^';
    else if (jogador_direcao == BAIXO) simbolo = 'v';
    else if (jogador_direcao == ESQ)   simbolo = '<';
    else                               simbolo = '>';
    tela[jogador_linha][jogador_coluna] = simbolo;

    
    limpar_tela();
    printf("=== DUNGEON CRAWLER ===\n");
    printf("Vidas: ");
    for (i = 0; i < jogador_vidas; i++) printf("* ");
    printf("  Chaves: %d", jogador_chaves);
    if (fase_atual > FASE_VILA) {
        char *nomes[] = {"Espada", "Arco", "Cajado"};
        printf("  Arma: %s", nomes[jogador_arma]);
    }
    printf("\n\n");

    // imp mapa
    for (i = 0; i < linhas_mapa; i++) {
        for (j = 0; j < colunas_mapa; j++)
            printf("%c", tela[i][j]);
        printf("\n");
    }
    printf("\n");
}


int e_solido(char c) {
    return c == PAREDE || c == CAIXA || c == PORTA_F;
}

//atacar uma celula
void atacar_celula(int l, int c) {
    int i;
    if (l < 0 || l >= linhas_mapa || c < 0 || c >= colunas_mapa) return;

    if (mapa[l][c] == CAIXA) {
        mapa[l][c] = VAZIO;
        printf("Caixa destruida!\n");
    }

    for (i = 0; i < num_monstros; i++) {
        if (!mon_vivo[i]) continue;
        if (mon_linha[i] == l && mon_coluna[i] == c) {
            mon_hp[i]--;
            if (mon_hp[i] <= 0) {
                mon_vivo[i] = 0;
                printf("Monstro eliminado!\n");
            } else {
                printf("Monstro acertado! HP: %d\n", mon_hp[i]);
            }
        }
    }
}

// atacar dependendo da arma
void atacar() {
    int l = jogador_linha;
    int c = jogador_coluna;
    int dl = 0, dc = 0;

    if (jogador_direcao == CIMA)  dl = -1;
    if (jogador_direcao == BAIXO) dl =  1;
    if (jogador_direcao == ESQ)   dc = -1;
    if (jogador_direcao == DIR)   dc =  1;

    if (jogador_arma == ESPADA) {
        
        int pl = dc, pc = dl;
        int prof, lado;
        for (prof = 1; prof <= 2; prof++)
            for (lado = -1; lado <= 1; lado++)
                atacar_celula(l + dl*prof + pl*lado,
                              c + dc*prof + pc*lado);

    } else if (jogador_arma == ARCO) {
      
        int dist;
        for (dist = 1; dist <= 4; dist++)
            atacar_celula(l + dl*dist, c + dc*dist);

    } else {
       
        int rl, rc;
        for (rl = -1; rl <= 1; rl++)
            for (rc = -1; rc <= 1; rc++)
                if (rl != 0 || rc != 0)
                    atacar_celula(l + rl, c + rc);
    }
}

//reiniciar a fase
void reiniciar_fase() {
    int vidas_salvas = jogador_vidas;
    int arma_salva   = jogador_arma;

    turno_boss = 0; //reseta o boss

    if      (fase_atual == FASE_VILA) carregar_vila();
    else if (fase_atual == FASE_1)    carregar_andar1();
    else if (fase_atual == FASE_2)    carregar_andar2();
    else if (fase_atual == FASE_3)    carregar_andar3();

    jogador_vidas = vidas_salvas;
    jogador_arma  = arma_salva;
}


void verificar_colisao_monstro() {
    int i;
    for (i = 0; i < num_monstros; i++) {
        if (!mon_vivo[i]) continue;
        if (mon_linha[i] == jogador_linha && mon_coluna[i] == jogador_coluna) {
            jogador_vidas--;
            printf("Um monstro te acertou! Vidas: %d\n", jogador_vidas);
            esperar_enter();
            if (jogador_vidas <= 0) {
                game_over = 1;
                return;
            }
            reiniciar_fase();
            return;
        }
    }
}


void mover_jogador(int dl, int dc, int nova_dir) {
    int nl, nc;
    char destino;

    jogador_direcao = nova_dir;

    nl = jogador_linha  + dl;
    nc = jogador_coluna + dc;

    if (nl < 0 || nl >= linhas_mapa || nc < 0 || nc >= colunas_mapa) return;

    destino = mapa[nl][nc];

    if (e_solido(destino)) return;

    jogador_linha  = nl;
    jogador_coluna = nc;

    
    if (destino == ESPINHO) {
        jogador_vidas--;
        printf("Voce pisou em um espinho! Vidas: %d\n", jogador_vidas);
        esperar_enter();
        if (jogador_vidas <= 0) { game_over = 1; return; }
        reiniciar_fase();
        return;
    }

 
    if (destino == ESCADA) {
        int vidas_salvas = jogador_vidas;
        int arma_salva   = jogador_arma;
        limpar_tela();

        if (fase_atual == FASE_VILA) {
            printf("Voce entra na masmorra!\n");
            esperar_enter();
            fase_atual = FASE_1;
            carregar_andar1();
        } else if (fase_atual == FASE_1) {
            printf("Subindo para o 2o andar!\n");
            esperar_enter();
            fase_atual = FASE_2;
            carregar_andar2();
        } else if (fase_atual == FASE_2) {
            printf("Subindo para o 3o andar! Cuidado com o Boss!\n");
            esperar_enter();
            fase_atual = FASE_3;
            carregar_andar3();
        }

        jogador_vidas = vidas_salvas;
        jogador_arma  = arma_salva;
        return;
    }

    verificar_colisao_monstro();
}


void interagir() {
    int tl = jogador_linha;
    int tc = jogador_coluna;
    char obj, op;

    if (jogador_direcao == CIMA)  tl--;
    if (jogador_direcao == BAIXO) tl++;
    if (jogador_direcao == ESQ)   tc--;
    if (jogador_direcao == DIR)   tc++;

    if (tl < 0 || tl >= linhas_mapa || tc < 0 || tc >= colunas_mapa) return;

    obj = mapa[tl][tc];

    if (obj == NPC) {
        do {
            limpar_tela();
            printf("=== NPC ===\n");
            printf("Heroi! Escolha sua arma:\n\n");
            printf("1 - Espada  (ataca 3x2 a frente)\n");
            printf("2 - Arco    (4 celulas em linha reta)\n");
            printf("3 - Cajado  (8 celulas ao redor)\n\n");
            printf("Escolha (1, 2 ou 3): ");
            op = ler_tecla();
            printf("%c\n", op);
        } while (op != '1' && op != '2' && op != '3');

        if      (op == '1') jogador_arma = ESPADA;
        else if (op == '2') jogador_arma = ARCO;
        else                jogador_arma = CAJADO;

        {
            char *nomes[] = {"Espada", "Arco", "Cajado"};
            printf("Voce pegou: %s!\n", nomes[jogador_arma]);
        }
        esperar_enter();

    } else if (obj == CHAVE) {
        mapa[tl][tc] = VAZIO;
        jogador_chaves++;
        printf("Chave coletada! Total: %d\n", jogador_chaves);

    } else if (obj == PORTA_F) {
        if (jogador_chaves > 0) {
            mapa[tl][tc] = PORTA_A;
            jogador_chaves--;
            printf("Porta aberta!\n");
        } else {
            printf("Voce precisa de uma chave!\n");
        }

    } else if (obj == BOTAO) {
        if (!botao_apertado) {
            botao_apertado = 1;
            printf("Botao pressionado! ");
            if (fase_atual == FASE_2) {
                mapa[10][3] = VAZIO;
                printf("Uma passagem secreta se abriu!\n");
            } else if (fase_atual == FASE_3) {
                
                mapa[6][20] = VAZIO;
                mapa[7][20] = VAZIO;
                printf("Os espinhos desapareceram!\n");
            }
        } else {
            printf("O botao ja foi pressionado.\n");
        }
    }
}


void mover_monstros() {
    int i, j;
    
    turno_boss++;

    for (i = 0; i < num_monstros; i++) {
        int dl = 0, dc = 0;
        int nl, nc, ocupado;
        char dest;

        if (!mon_vivo[i]) continue;

        if (mon_tipo[i] == 1) {
            
            int r = rand() % 4;
            if      (r == 0) dl = -1;
            else if (r == 1) dl =  1;
            else if (r == 2) dc = -1;
            else             dc =  1;

        } else if (mon_tipo[i] == 2) {

            int diff_l = jogador_linha  - mon_linha[i];
            int diff_c = jogador_coluna - mon_coluna[i];

            if (abs_val(diff_l) >= abs_val(diff_c)) {
                if (diff_l > 0) dl =  1;
                else            dl = -1;
            } else {
                if (diff_c > 0) dc =  1;
                else            dc = -1;
            }

        } else if (mon_tipo[i] == 3) {

            int diff_l = jogador_linha  - mon_linha[i];
            int diff_c = jogador_coluna - mon_coluna[i];

            if (abs_val(diff_l) >= abs_val(diff_c)) {
                if (diff_l > 0) dl =  1;
                else            dl = -1;
            } else {
                if (diff_c > 0) dc =  1;
                else            dc = -1;
            }

            
            if (turno_boss % 4 == 0) {
                int nl2 = mon_linha[i]  + dl;
                int nc2 = mon_coluna[i] + dc;
             
                if (nl2 >= 1 && nl2 <= linhas_mapa-2 &&
                    nc2 >= 1 && nc2 <= colunas_mapa-2 &&
                    mapa[nl2][nc2] != PAREDE &&
                    mapa[nl2][nc2] != PORTA_F) {
                    mon_linha[i]  = nl2;
                    mon_coluna[i] = nc2;
                }
            }
        }

        nl = mon_linha[i]  + dl;
        nc = mon_coluna[i] + dc;

        // limites
        if (nl < 0 || nl >= linhas_mapa || nc < 0 || nc >= colunas_mapa) continue;

        dest = mapa[nl][nc];
        if (dest == PAREDE || dest == PORTA_F || dest == CAIXA) continue;

     
        ocupado = 0;
        for (j = 0; j < num_monstros; j++) {
            if (j == i || !mon_vivo[j]) continue;
            if (mon_linha[j] == nl && mon_coluna[j] == nc) {
                ocupado = 1;
                break;
            }
        }
        if (ocupado) continue;

        mon_linha[i]  = nl;
        mon_coluna[i] = nc;
    }

    verificar_colisao_monstro();
}


void verificar_vitoria() {
    int i;
    if (fase_atual != FASE_3) return;
    for (i = 0; i < num_monstros; i++) {
        if (mon_tipo[i] == 3 && mon_vivo[i]) return;
    }
    vitoria = 1;
}


void tela_tutorial() {
    limpar_tela();
    printf("=== HISTORIA ===\n\n");
    printf("O vilarejo esta em perigo!\n");
    printf("Forcas sombrias dominam a masmorra proxima.\n");
    printf("Voce deve descer os tres andares e derrotar o Boss!\n\n");
    printf("=== SIMBOLOS ===\n\n");
    printf("  ^ v < >   Jogador (mostra a direcao)\n");
    printf("  *         Parede\n");
    printf("  #         Espinho (mata ao pisar)\n");
    printf("  k         Caixa (destruivel com 'o')\n");
    printf("  O         Botao\n");
    printf("  D         Porta fechada\n");
    printf("  @         Chave (coletar com 'i')\n");
    printf("  =         Porta aberta\n");
    printf("  L         Escada (proxima fase)\n");
    printf("  X         Monstro 1 (aleatorio)\n");
    printf("  Y         Monstro 2 (perseguicao)\n");
    printf("  Z         Boss Final\n");
    printf("  N         NPC\n\n");
    printf("=== CONTROLES ===\n\n");
    printf("  w  Cima     s  Baixo\n");
    printf("  a  Esq      d  Direita\n");
    printf("  i  Interagir\n");
    printf("  o  Atacar\n");
    printf("  q  Sair\n\n");
    esperar_enter();
}

void tela_game_over() {
    limpar_tela();
    printf("+-----------------------+\n");
    printf("|       GAME OVER       |\n");
    printf("+-----------------------+\n\n");
    printf("Voce perdeu todas as vidas :(\n\n");
    esperar_enter();
}

void tela_vitoria() {
    limpar_tela();
    printf("+-------------------------------+\n");
    printf("|          VITORIA!!!           |\n");
    printf("+-------------------------------+\n\n");
    printf("O Boss das Sombras foi derrotado!\n");
    printf("A luz volta ao vilarejo.\n");
    printf("Voce e o heroi das lendas!\n\n");
    esperar_enter();
}

void tela_creditos() {
    limpar_tela();
    printf("=== CREDITOS ===\n\n");
    printf("Espero que voce tenha gostado!\n");
    printf("Ate a proxima :)\n\n");
    esperar_enter();
}


void jogar() {
    char tecla;

    game_over  = 0;
    vitoria    = 0;
    fase_atual = FASE_VILA;
    turno_boss = 0;

    jogador_vidas  = VIDAS_MAX;
    jogador_arma   = ESPADA;
    jogador_chaves = 0;

    carregar_vila();

    while (!game_over && !vitoria) {
        desenhar_mapa();
        printf("w/a/s/d=mover  i=interagir  o=atacar  q=sair\n");

        tecla = ler_tecla();

        if      (tecla == 'q') break;
        else if (tecla == 'w') mover_jogador(-1,  0, CIMA);
        else if (tecla == 's') mover_jogador( 1,  0, BAIXO);
        else if (tecla == 'a') mover_jogador( 0, -1, ESQ);
        else if (tecla == 'd') mover_jogador( 0,  1, DIR);
        else if (tecla == 'i') interagir();
        else if (tecla == 'o') atacar();

        if (game_over) break;

        mover_monstros();
        verificar_vitoria();
    }

    if (game_over) tela_game_over();
    if (vitoria)   tela_vitoria();
}


int main() {
    char op;

    srand(time(NULL));

    while (1) {
        limpar_tela();
        printf("+---------------------------+\n");
        printf("|     DUNGEON  CRAWLER      |\n");
        printf("+---------------------------+\n");
        printf("|  1 - Jogar                |\n");
        printf("|  2 - Tutorial             |\n");
        printf("|  3 - Sair                 |\n");
        printf("+---------------------------+\n");
        printf("Escolha: ");

        op = ler_tecla();
        printf("%c\n", op);

        if      (op == '1') jogar();
        else if (op == '2') tela_tutorial();
        else if (op == '3') {
            tela_creditos();
   
            break;
        }
    }

    return 0;
}