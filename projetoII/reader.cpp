#include <fstream>
#include <iostream>
#include <string>

#include "reader.h"

#define LONGER_NAME 52
#define LARGER_FILE 139715
#define OFFSET 139767

Reader::Reader(PrimaryIndexing *indicePrimario, SecondaryIndexing *indiceSecundario)
{
    primaryIndex = indicePrimario;
    secondIndex = indiceSecundario;
}

Reader::~Reader()
{
    //dtor
}

/* Incompleto: Falta inserir os conteúdos das manpages na árvore, que também
está incompleta. */
void Reader::insertPrimaryKeys(int argc, char *argv[])
{
    ifstream file;
    struct manpage {
        char name[LONGER_NAME];
        char contents[LARGER_FILE];
    };
    struct manpage registro;

    file.open("dados/manpage.dat");

    for (int i = 1; i < argc; i++) {
        file.read((char *) &registro, sizeof(struct manpage));

        cout << i << ". Inserindo na árvore: " << argv[i] << "\n";

        primaryIndex->addIndexKey(argv[i], (i-1));
    }
    cout << "\n";
}

void Reader::insertSecondaryKeys()
{
    std::ifstream file;
    std::string word;
    file.open("dados/secondaryKeys.dat");
    while (!file.eof()) {
        getline(file, word);
        if (word[0] != '\0') {
            if (secondIndex->addIndexKey(word)) {
                insertRegisters(word);
            }
        }
    }
    cout << "\n";
    file.close();
}

void Reader::insertRegisters(string pivo)
{
    ifstream file;
    file.open("dados/manpage.dat");
    long posicaoName, posicaoContents;
    std::size_t counter;
    string name, contents;
    int numRegistro = 0;

    struct manpage {
        char name[LONGER_NAME];
        char contents[LARGER_FILE];
    };

    struct manpage registro;


    while (!file.eof()) {
        counter = 0;
        file.seekg((LONGER_NAME+LARGER_FILE)*numRegistro);
        file.read((char *) &registro, sizeof(struct manpage));
        name = registro.name;
        contents = registro.contents;

        posicaoName = 0;
        while (posicaoName != -1) {
            posicaoName = name.find(pivo);
            if (posicaoName != -1) {
                counter++;
                name[posicaoName] = '\0';
            }
        }


        posicaoContents = 0;
        while (posicaoContents != -1) {
            posicaoContents = contents.find(pivo);
            if (posicaoContents != -1) {
                counter++;
                contents[posicaoContents] = '\0';
            }
        }

        if (counter > 0)
            secondIndex->addRegister(name, pivo, counter);
        numRegistro++;

    }
    cont++;
    cout << cont << ". " << pivo << "\n";
    file.close();


}

IndexList* Reader::mountInvertedList()
{
    IndexList *indexKeys = new IndexList();
    string index;
    size_t qtdeIndex, qtdeRegister;
    string register_;
    ifstream file;
    file.open("dados/invertedList.dat");

    int sizeIndex, sizeRegister;

    file >> sizeIndex;

    for (int i = 0; i < sizeIndex; i++) {
        file >> index >> qtdeIndex;
        RegisterList *registerList = new RegisterList();
        cout << index << endl;
        indexKeys->push_back(index, registerList);
        for (int j = 0; j < qtdeIndex; j++) {
            file >> register_ >> qtdeRegister;
            registerList->push_back_register(register_, qtdeRegister);
        }
    }

    return indexKeys;
}

int Reader::longerName(int argc, char* argv[])
{
    unsigned long longer_name = 0;
    for (int i = 0; i < argc; i++) {
        if (strlen(argv[i]) > longer_name)
            longer_name = strlen(argv[i]);
    }
    return longer_name;
}

int Reader::largerFile(int argc, char* argv[])
{
    unsigned long larger_file = 0, counter = 0;
    string word;
    ifstream file;

    int i, t;
    FILE *arq;

    for (i = 1; i < argc; ++i) {
        if(!(arq = fopen(argv[i], "r"))) {
            fprintf(stderr, "Erro ao tentar abrir %s\n", argv[i]);
            continue;
        }
        fseek(arq, 0, SEEK_END);
        t = ftell(arq);
        fclose(arq);

        if (t > larger_file) larger_file = t;
    }
    return larger_file;
}

bool Reader::selectWord(string word)
{
    // if (word.size() == 2) {
    //     return false;
    // }

    if(word[1] == '\0')
        return false;
    if(word[0] == '{' || word[0] == '}')
        return false;

    int i = 0;
    while (word[i] != '\0') {
        for (int j = 33; j <= 64; ++j) {
            if (word[i] == j)
                return false;
        }
        for (int k = 91; k <= 96; ++k) {
            if (word[i] == k)
                return false;
        }
        ++i;
    }

    string prepositions[] = {"in", "on", "at", "of"};
    string conjunctions[] = {"and", "but", "or", "so", "althoug", "because",
                            "for", "if", "since", "either", "neither"};
    string pronouns[] = {"I", "you", "he", "she", "it", "we", "you", "they",
                        "me", "him", "her", "us", "them", "my", "your", "his",
                        "her", "its", "out", "their", "mine", "hers", "ours",
                        "yours", "theirs", "somebody", "someone", "something",
                        "nobody", "nothing", "nowhere", "who", "which", "that",
                        "this", "these", "that", "those"};
    string articles[] = {"the", "an", "a", "The", "An", "A", "THE", "AN", "A"};


    for (int i = 0; i < (sizeof(prepositions)/sizeof(string)); i++) {
        if (word == prepositions[i])
            return false;
    }

    for (int i = 0; i < (sizeof(conjunctions)/sizeof(string)); i++) {
        if (word == conjunctions[i])
            return false;
    }

    for (int i = 0; i < (sizeof(pronouns)/sizeof(string)); i++) {
        if (word == pronouns[i])
            return false;
    }

    for (int i = 0; i < (sizeof(articles)/sizeof(string)); i++) {
        if (word == articles[i])
            return false;
    }

    return true;
}

string Reader::removePuntuaction(string word)
{
    char aux[word.size()-2];
    if (word[word.size()-1] == '.' || word[word.size()-1] == ',' || word[word.size()-1] == ';') {
        for (int i = 0; i < word.size()-1; i++) {
            aux[i] = word[i];
        }
        word = aux;
    }
    return word;
}

void Reader::searchSecondaryKeys(int argc, char *argv[])
{
    std::ifstream f;
    std::ofstream output;
    std::string word;
    int counter = 0;

    output.open("dados/words.dat");

    for (int i = 1; i < argc; ++i) {
        f.open(argv[i]);
        f>> word;

        while (!f.eof()) {
            f >> word;
            word = removePuntuaction(word);
            if (selectWord(word)) {
                cout << "Procurando Chaves: " << counter << "\n";
                output << word << std::endl;
                counter++;
            }
        }
        f.close();
    }
    output.close();
}

void Reader::createRegisters(int argc, char *argv[])
{
    struct manpages {
        char name[52];
        char contents[139715];
    };

    struct manpages registro;

    ifstream g;
    ofstream manpage;
    manpage.open("dados/manpage.dat");

    for (int i = 1; i < argc; i++) {
        cout << "Criando Registros: " << i-1 << "\n";
        struct manpages registro;
        g.open(argv[i]);

        int k = 0;
        while (argv[i][k] != '\0') {
            registro.name[k] = argv[i][k];
            k++;
        }

        g.read((char *) &registro.contents, sizeof(struct manpages));

        g.close();
        manpage.write((char *) &registro, sizeof(struct manpages));

        int m = 0;
        while (registro.name[m] != '\0') {
            registro.name[m] = '\0';
            m++;
        }

        int n = 0;
        while (registro.contents[n] != '\0') {
            registro.contents[n] = '\0';
            n++;
        }

    }
    manpage.close();
}

unsigned long Reader::numberOfWordsInFile(string source)
{
    ifstream file;
    string word;
    unsigned long counter = 0;
    file.open(source);

    while (!file.eof()) {
        getline(file, word);
        counter++;
    }

    return counter;
}

void Reader::removeRepeatedWords(int argc, char *argv[])
{
    fstream input, output;
    LinkedList* list = new LinkedList();

    input.open("dados/words.dat");
    output.open("dados/secondaryKeys.dat");
    string word, word2;
    bool teste = false;
    int cont;

    while (!input.eof()) {
        input >> word;

        if (!list->contains(word)) {
            list->push_back(word);
            cont++;
            cout << "Inserindo na Lista: " << list->size() << "\n";
        }
    }

    int size = list->size();
    for (int i = 0; i < size; i++) {
        output << list->pop_front() << endl;
        cout << "Inserindo no Arquivo: " << list->size() << "\n";
    }

    cout << "\n";

    input.close();
    output.close();
}
