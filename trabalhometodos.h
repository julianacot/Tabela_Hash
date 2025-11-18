#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct usuario {
    char login[30]; 
    int senha;      
    struct usuario* prox;
} Usuario;

typedef struct tabela {
    int capacidade;   
    int qtd;   
    Usuario **p;
} Hash;

Hash* Criar_Hash();
void Print_Hash(Hash *h);
int TransformaCharacterEmInteiro(const char *a);
int HashSenha(const char *senha);
int PosSenha(int chave, int size);
int CreateLogin(Hash* t, const char* nome);
int Remove_Login(Hash* tabela, const char* nome);
int AprovarLogin(Hash* tabela, const char* nome);
int Login(Hash* tabela, const char* nome, const char* senha); 
Usuario* buscaHash(Hash* tabela, const char* nome);
void liberaHash(Hash* tabela);

// Cria a tabela hash
Hash* Criar_Hash() {
    Hash* tabela = malloc(sizeof(Hash));
    if (tabela != NULL) {
        tabela->capacidade = 31;
        tabela->qtd = 0;
        tabela->p = calloc(tabela->capacidade, sizeof(Usuario*));
    }
    return tabela;
}

// Insere login na tabela
int CreateLogin(Hash* t, const char* nome) {

    char senhaDigitada[30];
    printf("Digite a senha para %s: ", nome);
    scanf("%s", senhaDigitada);

    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, t->capacidade);

    Usuario* no = malloc(sizeof(Usuario));
    strcpy(no->login, nome);
    no->senha = HashSenha(senhaDigitada);
    no->prox = NULL;

    if (t->p[pos] == NULL) {
        t->p[pos] = no;
        t->qtd++;
        printf("Login %s cadastrado com senha hash %d\n", nome, no->senha);
        return 1;
    } else {
        Usuario* atual = t->p[pos];
        while (atual->prox != NULL) {
            if (strcmp(atual->login, nome) == 0) {
                printf("Login %s já existe.\n", nome);
                free(no);
                return 0;
            }
            atual = atual->prox;
        }
        if (strcmp(atual->login, nome) == 0) {
            printf("Login %s já existe.\n", nome);
            free(no);
            return 0;
        }
        atual->prox = no;
        t->qtd++;
        printf("Login %s cadastrado com senha hash %d (colisão resolvida por encadeamento)\n", nome, no->senha);
        return 1;
    }
}

// Imprime tabela
void Print_Hash(Hash* t) {
    printf("Tabela Hash (qtd = %d, capacidade = %d)\n", t->qtd, t->capacidade);
    
    for (int i = 0; i < t->capacidade; i++) {
        printf("[%d] = ", i);
        Usuario* atual = t->p[i];

        if (atual == NULL) {
            printf("NULL\n");
        } else {
            while (atual != NULL) {
                printf("%s (hash=%d) -> ", atual->login, atual->senha);
                atual = atual->prox;
            }
            printf("NULL\n");
        }
    }
}

// Transforma string em número
int TransformaCharacterEmInteiro(const char *a) {
    int val = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        val = 31 * val + a[i];
    }
    return val;
}

// Posição final na tabela
int PosSenha(int chave, int size) {
    return chave % size;
}

// Hash da senha
int HashSenha(const char *senha) {
    unsigned long hash = 0;
    int primo = 31;
    for (int i = 0; senha[i] != '\0'; i++) {
        hash = hash * primo + senha[i];
    }
    return (int)(hash & 0x7FFFFFFF);
}

// Remove login
int Remove_Login(Hash* tabela, const char* nome) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    Usuario* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            if (anterior == NULL) {
                tabela->p[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            tabela->qtd--;
            printf("Login %s removido.\n", nome);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Login %s não encontrado.\n", nome);
    return 0;
}

// Aprovar login
int AprovarLogin(Hash* tabela, const char* nome) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            return 0;
        }
        atual = atual->prox;
    }
    return 1;
}

// Login
int Login(Hash* tabela, const char* nome, const char* senha) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    int senhaHash = HashSenha(senha);

    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0) {
            if (atual->senha == senhaHash) {
                printf("Login realizado com sucesso!\n");
                return 1;
            } else {
                printf("Senha incorreta!\n");
                return 0;
            }
        }
        atual = atual->prox;
    }

    printf("Usuário não encontrado!\n");
    return 0;
}

// Busca (obrigatória)
Usuario* buscaHash(Hash* tabela, const char* nome) {
    int chave = TransformaCharacterEmInteiro(nome);
    int pos = PosSenha(chave, tabela->capacidade);

    Usuario* atual = tabela->p[pos];
    while (atual != NULL) {
        if (strcmp(atual->login, nome) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

// Libera memória 
void liberaHash(Hash* tabela) {
    if (tabela == NULL) return;

    for (int i = 0; i < tabela->capacidade; i++) {
        Usuario* atual = tabela->p[i];
        while (atual != NULL) {
            Usuario* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(tabela->p);
    free(tabela);
}
