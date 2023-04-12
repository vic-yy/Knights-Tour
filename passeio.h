#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int movimentoLin[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int movimentoCol[8] = {2, -2, 1, -1, -2, 2, -1, 1};
int visitadas;

bool LimitadorDoTabuleiro(int x, int y)
//Essa função avalia se o movimento do cavalo dado se mantém dentro do tabuleiro.
{
    if ((x >= 0 && y >= 0) && (x < 8 && y < 8))
    {
        return 1;
    }
    return 0;
}

bool ChecadorDeVazio(int tabuleiro[], int x, int y)
//Essa função checa a existência de vazios.
{
    if ((LimitadorDoTabuleiro(x, y)) && (tabuleiro[x + y * 8] == -1))
    //Se o movimento do cavalo é valido E se a posição seguinte no tabuleiro está vazia, retorna 1.
    {
        return 1;
    }
    return 0;
}


int ContaVazios(int tabuleiro[], int x, int y)
//Essa função checa o número de vazios
{
    int i, count = 0;
    for (i = 0; i < 8; ++i)
    {
        if (ChecadorDeVazio(tabuleiro, (x + movimentoLin[i]), (y + movimentoCol[i]))) 
        //Verifica quais posições que o cavalo pode realizar e soma 1 caso o movimento seja possível
        {
            count++;
        }
    }
    return count;
}


int Movimentador(int tabuleiro[], int *x, int *y)
//Essa função verifica compara o número de vazios em relação a uma posição x e y inicial e transforma esses 2 valores em novos x e y possíveis
//Essa nova posição  (x,y) representa um movimento do cavalo 
{
    int seed, count, i, flag = -1, Vazios, min = 9, nx, ny;
    seed = rand() % 8;
    //O primeiro movimento é aleatório e deve ser menor que 8
    for (count = 0; count < 8; ++count)
    {   
        i = (seed + count) % 8;
        //O número da posição dos vetores de movimentos x e y variam com esse laço
        nx = *x + movimentoLin[i];
        ny = *y + movimentoCol[i];
        //x e y são valores das posições recebidas pelo próprio usuário
        if ((ChecadorDeVazio(tabuleiro, nx, ny)))
        //Se o movimento do cavalo é valido E se a posição seguinte no tabuleiro está vazia, retorna 1.
        {
            visitadas ++;
            //Aqui somamos 1 toda vez que um movimento possível for válido
            Vazios = ContaVazios(tabuleiro, nx, ny);
            //Contamos quantos movimentos do cavalo serão válidos
            if (Vazios < min)
            //Esse laço serve para buscarmos o movimento que nos dará o movimento com menor quantidade de mais movimentos
            //Entramos nesse laço se a quantidade de vazios for menor que uma variável mínimo
            {      
                            
                flag = i;
                //Se o movimento do cavalo for aquele com menor movimentos possíveis, armazenarzamos no flag
                min = Vazios;
                //Aqui atualizamos o mínimo
                
            }
        
    }
    }
        
    if (min == 9)
    {
        return 0;
    }
    nx = *x + movimentoLin[flag];
    //Aqui armazenamos em nx o movimento do cavalo que produzirá a menor quantidade de movimentos futuros
    ny = *y + movimentoCol[flag];
    //Aqui armazenamos em ny o movimento do cavalo que produzirá a menor quantidade de movimentos futuros
    

    tabuleiro[ny * 8 + nx] = tabuleiro[(*y) * 8 + (*x)] + 1;
    //Aqui atualizamos o tabuleiro e preenchemos a posição de acordo com a Regra de Warnsdorff
    *x = nx;
    *y = ny;
    return 1;
}

void Impressor(int tabuleiro[])
{
    FILE *file;
    file = fopen("saida.txt", "a");
    if (file == NULL)
    {
        printf("Couldn't open the file");
        exit(1);
    }
    fprintf(file, "\n");
    int i, j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            fprintf(file, "%d ", tabuleiro[i + j * 8]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "%d\n", visitadas);
    fprintf(file, "%d\n", visitadas - 64);
    visitadas = 0;
    fclose(file);
}

//Essa função checa se o movimento do cavalo é válido
int CavaloValido(int x, int y, int start_x, int start_y)
{
    int i;
    for (i = 0; i < 8; ++i)
    {
        if (((x + movimentoLin[i]) == start_x) && ((y + movimentoCol[i]) == start_y))
        {
            return 1;
        }
    }
    return 0;
}
// Set default moves
void ConfiguradorDeBase(int tabuleiro[])
{
    // fill the chess board matrix with -1's
    for (int i = 0; i < 8 * 8; ++i)
    {
        tabuleiro[i] = -1;
    }
}


int AvaliadorDeMovimentos(int tabuleiro[], int Xinicial, int Yinicial)
//Aqui avaliamos se o movimento feito pela função "movimentador" é válida e imprimimos o tabuleiro quando encontramos uma solução 
{
    ConfiguradorDeBase(tabuleiro);
    int i, x, y;
    // Os valores de Xinicial e Yinicial entre [1,8] são convertidos para o intervalo utilizado pelo programa [0,7]
    x = Xinicial - 1;
    y = Yinicial - 1;
    

    tabuleiro[y * 8 + x] = 1;
    //Inserimos no tabuleiro a primeira posição

    for (i = 0; i < (64) - 1; ++i)
    {
        if (Movimentador(tabuleiro, &x, &y) == 0)
        {
            return 0;
        }
    }
    //Esse laço e função servem para calcular e alterar x e y para valores de uma posição x e y candidata


    if (CavaloValido(x, y, Xinicial, Yinicial) == 0)
    {
        return 0;
    }
    // Aqui avaliamos se a nova posição do cavalo é um movimento válido em relação ao x e y anterior

    Impressor(tabuleiro);

    return 1;
}
    


void passeio(int x, int y)
//Essa função cria o tabuleiro (vetor de 64 posições) e chamar a função que cria tabuleiros (soluções)
{
    srand(time(NULL));

    int tabuleiro[64];


    while (!AvaliadorDeMovimentos(tabuleiro, x, y));

}

