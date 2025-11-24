#include "compressao.h"  
// Aqui a gente puxa o cabeçalho onde as funções são declaradas.
// Sem isso, o compilador nem sabe que as funções existem.

size_t rle_comprimir(const uint8_t *in, size_t in_len, uint8_t *out, size_t cap){
    size_t ip = 0, op = 0;
    // ip = "input pointer" -> posição de leitura nos dados originais
    // op = "output pointer" -> posição de escrita no vetor comprimido

    while(ip < in_len){  
        // Loop principal: enquanto ainda houver dados pra ler...

        uint8_t v = in[ip++];  
        // Pegamos o valor atual e avançamos o ponteiro
        // Esse é o valor que queremos contar repetições

        uint8_t cont = 1;  
        // Começamos com uma repetição, pois já lemos 1 vez o valor

        while(ip < in_len && in[ip] == v && cont < 255){
            // Enquanto:
            // - ainda tem dado
            // - o próximo byte for igual ao atual
            // - e não estourar o limite máximo (255)
            cont++;  
            ip++;    
            // Vamos contando repetição por repetição
        }

        if(op + 2 > cap) return 0;
        // Precisamos de 2 bytes pra cada "par" (valor + contagem)
        // Se não couber no buffer de saída → erro

        out[op++] = v;     
        // Primeiro armazenamos o valor

        out[op++] = cont;  
        // Depois quantas vezes ele repetiu
    }

    return op;  
    // No final, devolvemos quantos bytes foram gerados na compressão
}

size_t rle_descomprimir(const uint8_t *in, size_t in_len, uint8_t *out, size_t cap){
    size_t ip = 0, op = 0;
    // ip -> posição de leitura na versão comprimida
    // op -> posição onde vamos escrever os bytes descomprimidos

    while(ip + 1 < in_len){
        // Cada bloco comprimido tem 2 bytes:
        // [valor][quantas_vezes]
        // Então sempre lemos 2 bytes de cada vez

        uint8_t v = in[ip++];     
        // Lemos o valor

        uint8_t cont = in[ip++];  
        // Lemos quantas vezes ele se repete

        if(op + cont > cap) return 0;
        // Verifica se vai caber tudo no vetor de saída
        // Se não couber → erro

        for(uint8_t i = 0; i < cont; i++)
            out[op++] = v;
        // Aqui é o contrário da compressão:
        // A gente repete o valor "cont" vezes
    }

    return op;
    // Retorna quantos bytes foram gerados na descompressão
}

