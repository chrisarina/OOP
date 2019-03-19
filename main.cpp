#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

class Nod
{
    char Info;
    Nod *next;
public:
    Nod(char, Nod*);
    ~Nod();
    char get_char()
    {
        return Info;
    }
    Nod* get_next()
    {
        return next;
    }
    friend class Coada_de_caractere;
};


class Coada_de_caractere
{
    Nod *first;
    Nod *last;
public:
    Coada_de_caractere();
    ~Coada_de_caractere();
    void push(Nod);
    void pop();
    int isempty(){return first==0;} ///verifica daca e coada goala sau nu
    friend ostream & operator<<(ostream&, Coada_de_caractere &); ///supraincarcarea operatorului <<
    friend istream & operator<<(istream&, Coada_de_caractere &); ///supraincarcarea operatorului >>
    friend Coada_de_caractere& operator+(Coada_de_caractere&, Coada_de_caractere&); ///supraincarcarea operatorului + (concateneaza doua cozi)
    friend Coada_de_caractere& operator-(Coada_de_caractere&, Coada_de_caractere&); ///diferenta pe cod asci
};

///constructor de initializare, parametrizat
Nod::Nod(char i='\0', Nod *p=NULL)///constructor nod
{
    Info=i;
    next=p;
}
Nod::~Nod() ///desctructor nod
{
   // cout<<"Destructor nod"<<endl;
}

Coada_de_caractere::Coada_de_caractere() ///constructor coada
{
    first=last=NULL;
}

Coada_de_caractere::~Coada_de_caractere() ///dezaloc
{
    Nod *p=first;
    Nod *q;
    while(p!=0)
    {
        q=p;
        p=p->next;
        delete q;
    }
    first=last=0;
    //cout<<"Destructor lista"<<endl;
}

///Adaugare elemente in coada
void Coada_de_caractere::push(Nod a)
{
    Nod *p=new Nod(a.Info,a.next);
    if (isempty()) ///coada e goala atunci setez ca fiind primul, respectiv ultimul nod, cel pe care il adaug
    {
        first=last=p;
    }
    else
    {
        last->next=p;
        last=p;
    }
    //cout<<"element adaugat in coada"<<endl;
}
///Stergere elemente din coada
void Coada_de_caractere::pop()
{
    Nod *fifo=first;
    first=first->next;
    delete(fifo);
}

///Supraincarcarea operatorului <<
ostream& operator<<(ostream& out, Coada_de_caractere& l) ///output stream - bufferul de iesire
{
    while(!l.isempty())
    {
        out<<(l.first)->get_char()<<"\n";
        l.pop();
    }
    return out;
}

///Supraincarcare operatorului >>
istream& operator>>(istream& in, Coada_de_caractere& l) ///input stream - bufferul de intrare
{
    char c;
    int n;
    cout<<"Introduceti numarul elementelor din coada: ";
    in>>n;
    cout<<"Cititi "<<n<<" caractere de la tastatura: "<<"\n";
    for(int i=0;i<n;i++)
    {
        in>>c;
        l.push(*new Nod(c));
    }
    return in;
}

///supraincarcarea operatorului +
Coada_de_caractere& operator+(Coada_de_caractere& x, Coada_de_caractere& y) ///concatenarea a doua cozi
{
    Coada_de_caractere *sum=new Coada_de_caractere;
    Nod *p=x.first;
    Nod *q=y.first;
    while (p)
    {
        sum->push(*new Nod(p->get_char()));
        p=p->get_next();
    }
    while (q)
    {
        sum->push(*new Nod(q->get_char()));
        q=q->get_next();
    }
    return *sum;
}

///supraincarcarea operatorului -
Coada_de_caractere& operator-(Coada_de_caractere& x, Coada_de_caractere& y)
{
    Coada_de_caractere *dif=new Coada_de_caractere;
    char c1,c2;
    while(!x.isempty() && !y.isempty())
    {
        c1=(x.first)->get_char();
        c2=(y.first)->get_char();
        if(c1>=c2)
            dif->push(*new Nod(c1));
        else
            dif->push(*new Nod(c2));
        x.pop();
        y.pop();
    }
    return *dif;
}

int main()
{   SetConsoleOutputCP(65001);
    cout<< ("\n");
    cout<< ("  \u00A9");
    cout<< ("Chris-Arina Badara\n  Facultatea de Matematica si Informatica\n  2018");
    cout<< ("\n\n\n");
    cout<<( "\t\t     =CLASA COADA DE CARACTERE=\n");
    cout<< ("  -------------------------------------------------------------------------------------------------------------------");



    cout<< ("\n    Se considera Class Nod{ char Info; Nod *next;}\n   -constructori de initializare si parametrizati pentru clasa Nod;\n   destructor pentru clasa Nod\n\n.     Clasa Coada_de_caractere are:\n   -membri privati, 'Nod*,Nod*(primul si ultimul element al cozii);\n   -un constructor care initializeaza coada cu NULL;\n   -un destructor care dezaloca toate elementele cozii;\n   -metode publice de adaugare a unui element in stiva (push) de stergere  unui element (pop) si pentru a testa \ndaca e vida (isempty);\n   -metoda publica de afisare a cozii, concomitend cu golirea ei realizata prin supraincarcarea operatorului <<;\n   -supraincarcarea operatorului >>, realizata prin push-uri succesive;\n   -metoda publica pentru concatenarea a doua cozi de caractere, obtinand o alta coada de caractere, implementata \nprin supraincarcarea operatorului +;\n   -metoda publica, realizata prin supraincarcarea operatorului -, care sa considere doua cozi sa elimine, concomitent,\n elementele din ambele cozi adaugand caracterul ce are codul ASCII mai mare intr-o coada.\n");
    cout<< ("  -------------------------------------------------------------------------------------------------------------------");
    cout<< ("\n\n\t\t      URMATI CU GRIJA URMATORII PASI:\n");


    Coada_de_caractere l1;
    Coada_de_caractere l2;
    ///apel >> supraincarcat
    cin>>l1;
    cin>>l2;
    cout<<"Afisarea sumei a doua cozi (supraincarcare operator +), prin supraincarcarea operatorului <<:"<<"\n";
    cout<<l1+l2;
    cout<<"\n\n";
    cout<<"Afisarea diferentei a doua cozi (supraincarcare operator -), prin supraincarcare operator <<:\n";
    cout<<l1-l2;
    return 0;
}
