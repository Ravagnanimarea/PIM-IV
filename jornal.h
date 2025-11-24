#ifndef JORNAL_H // Proteção pra evitar que esse arquivo seja incluído duas vezes no código
#define JORNAL_H // Marca que o arquivo já foi incluído

#include <stddef.h> // Traz o tipo size_t, usado pra representar tamanhos com segurança
#include <stdint.h> // Traz tipos numéricos com tamanho fixo, como uint8_t (1 byte certinho)


// Função responsável pela GRAVAÇÃO SEGURA em arquivo binário
// path -> nome do arquivo final que vai ser salvo (ex: "registro.bin")
// data -> ponteiro para os dados que vamos gravar no arquivo
// len -> tamanho desses dados em bytes
// Retorno:
//   0 -> deu tudo certo na gravação
//  -1 -> deu erro em alguma etapa (abrir, escrever, sincronizar ou renomear)
int jornal_escrever(const char *path, const uint8_t *data, size_t len);

#endif // Fim da proteção contra inclusão múltipla
