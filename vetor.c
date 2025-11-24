#include "vetor.h"
// Puxa o cabeçalho onde a struct vetor_t e as funções foram declaradas

#include <stdlib.h>
// Necessário para usar calloc() e free()

#include <stdio.h>
// Usado para perror() — imprime mensagens de erro no terminal

// -------------------------------------------------------------------
// Função que CRIA um vetor na memória
// -------------------------------------------------------------------
vetor_t vetor_criar(size_t tamanho){
    vetor_t v;               
    // Cria a variável que vai guardar o vetor final

    v.tamanho = tamanho;    
    // Guarda o tamanho do vetor (quantos elementos ele terá)

    v.dados = calloc(tamanho, sizeof(double));
    // Aloca memória para 'tamanho' elementos double
    // calloc zera tudo automaticamente (diferente de malloc)

    if(!v.dados){           
        // Se a alocação der errado...
        perror("calloc vetor");  // Mostra mensagem de erro
        exit(1);                 // Encerra o programa
    }

    return v;  
    // Retorna o vetor montado e pronto pra uso
}

// -------------------------------------------------------------------
// Função que LIBERA um vetor criado anteriormente
// -------------------------------------------------------------------
void vetor_liberar(vetor_t *v){
    if(!v) return;          
    // Se o ponteiro for nulo, nem tenta liberar

    free(v->dados);         
    // Libera a memória onde ficavam os números

    v->dados = NULL;        
    // Garante que o ponteiro não fique apontando pra lixo

    v->tamanho = 0;         
    // Zera o tamanho (boa prática)
}

// -------------------------------------------------------------------
// Função que calcula o PRODUTO ESCALAR entre dois vetores
// -------------------------------------------------------------------
double vetor_produto(const vetor_t *a, const vetor_t *b){

    // Determina o menor tamanho dos dois vetores, para evitar estouro
    size_t n = a->tamanho < b->tamanho ? a->tamanho : b->tamanho;

    double s = 0;           
    // Acumulador da soma

    for(size_t i = 0; i < n; i++)
        s += a->dados[i] * b->dados[i];
        // Produto elemento a elemento (a[i] * b[i]) e acumula

    return s;               
    // Retorna o resultado final
}
