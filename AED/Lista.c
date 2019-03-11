/*
    Lista

    Uma estrutura do tipo "Lista" é uma sequência de elementos do mesmo tipo.
    Os seus elementos possuem estutura interna abstraída, ou seja, sua complexidade
    é arbitrária e não afeta o seu funcionamento.

    Lista » | 33 | 23 | 16 | 15 | 43 | 58 |

    Uma "Lista" pode ter N elementos, sendo N >= 0.
    Se N = 0, então a "Lista" está vazia.

    Aplicações:
    - Registo de funcionários
    - Controlo de stock
    - Cartas de um baralho
    - etc...

    Algumas operações básicas de uma "Lista":
    - Criação da lista
    - Inserção de elementos
    - Remoção de elementos
    - Acesso aos elementos
    - Apagar a lista
    - etc

    Essas operações dependem do tipo de alocação
    de memória ussda:
    - estática
    - dinâmica

    Alocação estática:
    - O espaço de memória é alocada no momento da compilação
    - Exige a definição do número máximo de elementos da "Lista"
    - Acesso sequencial: elementos consecutivos na memória

    NElem » 8
    idx » 0 - 7
    Dados » | 12 | 32 | 1 | 7 | 3 |   |   |   |

    Alocação Dinâmica:
    - O espaço de memória é alocado em tempo de execução
    - A "Lista" cresce à medida que novos elementos são armazenados,
    e diminui à medida que elementos são removidos
    - A cesso encadeado: cada elemento pode estar em um área distinta
    da memória. Para aceder a um elemento, é preciso percorrer
    todos os seus antecessores da "Lista"

    Dados » | 2 : | -> | 9 : | -> | 3 : | -> NULL
*/