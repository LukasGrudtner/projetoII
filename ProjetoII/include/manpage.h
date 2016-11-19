#ifndef MANPAGE_H
#define MANPAGE_H


class manpage
{
    public:
        manpage();
        virtual ~manpage();
        char name[200];         // comando
        char contents[200];     // conteúdo

    protected:

    private:
};

#endif // MANPAGE_H
