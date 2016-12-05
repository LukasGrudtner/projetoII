#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <fstream>
#include <iostream>

#include "record_adresses_list.h"

using namespace std;

class SearchEngine
{
    public:
        SearchEngine();
        virtual ~SearchEngine();

        /*  Realiza uma busca primária pelo índice fornecido para encontrar
            o conteúdo de determinada manpage.

            A partir de um indice, recebido como parâmetro, é iniciada a busca
            dentro do arquivo "avlTree.dat" por um um nodo cuja chave case
            com o índice fornecido. Caso encontre, o ponteiro (que está junto
            com a chave no nodo) é utilizado para encontrar o   conteúdo desta
            manpage dentro do arquivo de registros "manpage.dat".
        */
        void primarySearch(string index);

        /*  Realiza uma busca secundária pelo índice fornecido para encontrar
            o nome de todas as manpages que contenham este índice.

            A partir de um índice, recebido como parâmetro, é iniciada a busca
            dentro do arquivo "invertedList.dat" por um nodo cuja chave case
            com o índice fornecido. Caso encontre, a Lista de Endereços de
            Registro deste índice é impresso na tela.
        */
        void secondarySearch(string index);

        /*  Realiza uma busca conjuntiva, com o índice 1 e o índice 2, para
            encontrar o nome de todas as manpages que contenham os dois índices.

            A partir dos índices, recebidos como parâmetro, é inicada a busca
            dentro do arquivo "invertedList" por um nodo cuja chave case com
            o índice 1, montando uma lista com todas as incidências. Depois,
            é iniciada a busca pelas incidências do índice 2. Então cruza-se
            ambas as listas, e os nodos que baterem serão impressos na tela.
        */
        void conjunctiveSearch(string index1, string index2);

    protected:

    private:
        /*  Método auxiliar para a checagem do formato do nome da manpage.
            Caso o usuário insira o nome sem ".txt", ele é inserido
            automáticamente para facilitar a pesquisa.
        */
        string checksFormat(string word);
};

#endif // SEARCHENGINE_H
