/**
Tema 4. liste de numere întregi 1 (implementate dinamic)
Se dau urmatoarele clase:
- Nod (int info, nod*next)
- Nod_dublu (nod * ante) :Nod
- LDI (elemente de tip Nod_dublu); // lista dublu inlantuita;
- LSI : LDI ; // lista simplu inlantuita, obtinuta mostenind caracteriticile unei LDI adaptate la o inlantuire simpla;
Clasele derivate trebuie sa contina cel puțin constructori parametrizati (prin
care sa se evidentieze transmiterea parametrilor către constructorul din clasa
de baza) si destructor. Să se exemplifice sortarea prin insertie directa
utilizand LDI. */
/*#include <iostream>

using namespace std;

class Baza
{
public:
    void afis(){ cout<<"Baza\n";}
    virtual void afis2() {cout<<"Baza 2\n";}
};

class Derivata: public Baza
{
public:
    void afis(){ cout<<"Derivata\n";}
    void afis2(){ cout<<"Derivata 2\n";}
};

class AltaDerivata: public Baza
{
public:
    void afis(){ cout<<"Alta Derivata\n";}
    void afis2(){ cout<<"Alta Derivata 2\n";}
};


void functie(Baza &x)
{
    x.afis();
}

void functie2(Baza &x)
{
    x.afis2();
}

int main()
{
// Upcasting - clasa derivata poate lua locul clasei de baza
    Derivata d;
    functie(d); // afiseaza Baza
// Upcasting + Late binding - functii virtuale
    functie2(d); // afiseaza Derivata2
// Downcasting - exemplificare
    Baza *b = new Derivata; //upcasting
    Derivata *a = dynamic_cast<Derivata*>(b);
    functie(*a);
    functie2(*a);
    AltaDerivata * c = dynamic_cast<AltaDerivata*>(b);
    functie(*c);
    return 0;
}

*/

#include <iostream>
#include <cstdlib>

using namespace std;

class LDI;
class LSI;

bool okd,oks;

class nod {
protected:
    int info;
    nod *next;
public:
     nod(int,nod*);
     nod(nod&);
     ~nod();
     virtual nod& operator =(nod&);
     int get_info() {return info;}
     nod *get_next() {return next;}
     void set_next(nod *p) {next=p;}
     friend istream& operator >>(istream&, nod&);
     friend ostream& operator <<(ostream&, nod&);
     friend class LDI;
     friend class LSI;
};

nod::nod(int n=0, nod *p=NULL) {
    info=n;
    next=p;
    //cout<<"Cons n";
}

nod::nod(nod &p) {
    info=p.info;
    next=p.next;
    //cout<<"Cons c n";
}

nod::~nod() {
    //<<"Destructor n";
}

nod& nod::operator =(nod &p) {
    info=p.info;
    next=p.next;
    return *this;
}

istream& operator >>(istream &in, nod &p) {
    int n;
    in>>n;
    p.info=n;
    p.next=NULL;
    return in;
}

ostream& operator <<(ostream &out, nod &p) {
    out<<p.info<<endl;
    return out;
}

class nod_dublu:public nod {
protected:
    nod *ante;
public:
    nod_dublu(int n, nod *p, nod *q);
    nod_dublu(nod_dublu&);
    ~nod_dublu();
    nod_dublu& operator =(nod_dublu&);
    void set_ante(nod *p){ante=p;}
    nod *get_ante(){return ante;}
    friend istream& operator >>(istream&, nod_dublu&);
    friend ostream& operator <<(ostream&, nod_dublu&);
    friend class LDI;
};

nod_dublu::nod_dublu(int n=0,nod *p=NULL, nod *q=NULL):nod(n,p) {
    ante=q;
    //cout<<"Constr nd";
}

nod_dublu::nod_dublu(nod_dublu &p):nod(p) {
    ante=p.ante;
    //cout<<"Constr c nd";
}

nod_dublu::~nod_dublu() {
    //cout<<"Destr nd";
}

nod_dublu& nod_dublu::operator =(nod_dublu &p){
    (nod&)(*this)=p;
    ante=p.ante;
    return *this;
}

istream& operator >>(istream& in, nod_dublu &p) {
    in>>(nod&)p;
    p.ante=NULL;
    return in;
}

ostream& operator <<(ostream& out, nod_dublu &p) {
    out<<(nod&)p;
    return out;
}

class LDI {
protected:
    nod_dublu *prim, *ultim;
    static int nr;
public:
    LDI();
    LDI(LDI&);
    ~LDI();
    virtual LDI& operator =(LDI&);
    static void numarListe();
    nod_dublu* get_prim(){return prim;}
    nod_dublu* get_ultim() {return ultim;}
    friend istream& operator >>(istream&,LDI&);
    friend ostream& operator <<(ostream&,LDI&);
    friend void sortare();
    friend void numarListe();
};

int LDI::nr;

void LDI::numarListe() {
    cout<<"Numarul de liste construite este "<<nr<<endl;
}

LDI::LDI() {
    prim=ultim=NULL;
    nr++;
}

LDI::LDI(LDI &l) {
    nod_dublu *a = l.prim;
    prim=ultim=new nod_dublu(*a);
    a=(nod_dublu *)a->next;
    while(a) {
        nod_dublu *aux=new nod_dublu(*a);
        aux->ante=(nod*)ultim;
        ultim->next=(nod*)aux;
        ultim=aux;
        a=(nod_dublu *)a->next;
      }
    nr++;
}

LDI::~LDI() {
    nod_dublu *ant(prim);
    while(ant!=ultim) {
        prim=(nod_dublu*) prim->next;
        delete ant;
        ant=prim;
    }
    delete ant;
    //cout<<"Destr ld";
}

LDI& LDI::operator =(LDI &l) {
    while(prim!=ultim) {
        nod_dublu *aux=(nod_dublu*)ultim->ante;
        aux->next=NULL;
        delete(ultim);
        ultim=aux;
    }
    delete(ultim);
    nod_dublu *a = l.prim;
    prim=ultim=new nod_dublu(*a);
    a=(nod_dublu *)a->next;
    while(a) {
        nod_dublu *aux=new nod_dublu(*a);
        aux->ante=(nod*)ultim;
        ultim->next=(nod*)aux;
        ultim=aux;
        a=(nod_dublu *)a->next;
      }
    return *this;
}

istream& operator >>(istream &in, LDI &l) {
    cout<<"Introduceti numarul de elemente ";
    int n;
    in>>n;
    cout<<"Introduceti elementele "<<endl;
    nod_dublu *aux=new nod_dublu;
    in>>*aux;
    l.ultim=l.prim=aux;
    for(int i=2;i<=n;i++) {
        aux=new nod_dublu;
        in>>*aux;
        l.ultim->set_next(aux);
        aux->set_ante((nod*)l.ultim);
        l.ultim=aux;
    }
    return in;
}

ostream& operator <<(ostream &out, LDI &l) {
    out<<"Afis stanga-dreapta: ";
    for(nod_dublu *p = l.prim; p!=NULL; p = (nod_dublu*)p->get_next())
        out<<p->get_info()<<" ";
    out<<endl;
    if(l.ultim!=l.prim)
        if(l.ultim->get_ante()) {
            out<<"Afis drepata-stanga: ";
            for(nod_dublu*p = l.ultim; p!=NULL; p = (nod_dublu*)p->get_ante())
                out<<p->get_info()<<" ";
            out<<endl;
        } else;
    else {
        out<<"\nAfis dreapta-stanga: ";
        out<<l.prim->get_info()<<" "<<endl;
    }
    return out;
}

class LSI:public LDI {
public:
    LSI();
    LSI(LSI&);
    ~LSI();
    LSI& operator =(LSI&);
    friend istream& operator >>(istream&,LSI&);
    friend ostream& operator <<(ostream&,LSI&);
};

LSI::LSI():LDI(){}

LSI::LSI(LSI &l):LDI(l){}

LSI::~LSI(){
    //cout<<"Destr ls";
}

LSI& LSI::operator =(LSI &l) {
    (LDI&)(*this)=l;
    nod_dublu *aux=prim;
    while(aux) {
        aux->set_ante(NULL);
        aux=(nod_dublu*)aux->get_next();
    }
    return *this;
}

istream& operator >>(istream &in, LSI &l) {
    in>>(LDI&)l;
    nod_dublu *aux=l.prim;
    while(aux) {
        aux->set_ante(NULL);
        aux=(nod_dublu*)aux->get_next();
    }
    return in;
}
ostream& operator <<(ostream &out, LSI &l) {
    out<<(LDI&)l;
    return out;
}

void sortare() {
    cout<<"Introduceti numarul elementelor pe care doriti sa le sortati ";
    int n;
    cin>>n;
    cout<<"Introduceti elementele pe care le sortati"<<endl;
    LDI l;
    l.prim=new nod_dublu();
    cin>>*l.prim;
    l.ultim=l.prim;
    for(int i=2;i<=n;i++) {
        nod_dublu *aux=new nod_dublu(),*p=l.prim,*q;
        cin>>*aux;
        while(p && aux->get_info()>=p->get_info())
            p=(nod_dublu*)p->get_next();
        if(!p) {
            l.ultim->set_next((nod*)aux);
            aux->set_ante((nod*)l.ultim);
            l.ultim=aux;
        } else if(p==l.prim) {
                    aux->set_next((nod*)l.prim);
                    l.prim->set_ante((nod*)aux);
                    l.prim=aux;
                } else {
                           q=(nod_dublu*)p->get_ante();
                           aux->set_next((nod*)p);
                           p->set_ante((nod*)aux);
                           q->set_next((nod*)aux);
                           aux->set_ante((nod*)q);
                      }
    }
    cout<<l;
}

void citireLDI(LDI *&l, int n) {
    if(n>0) {
        okd=1;
        l=new LDI[n];
        for(int i=1;i<=n;i++) {
            cout<<"Lista "<<i<<endl;
            cin>>l[i];
        }
    okd=1;
    } else cout<<"Numarul este negativ"<<endl;
}

void afisareLDI(LDI *l,int n) {
    if(okd==1) {
        for(int i=1;i<=n;i++){
            cout<<"Lista "<<i<<endl;
            cout<<l[i];
        }
    okd=0;
    } else cout<<"Nu sunt construite liste dublu inlantuite"<<endl;
}

void citireLSI(LSI *&l, int n) {
    if(n>0) {
        oks=1;
        l=new LSI[n];
        for(int i=1;i<=n;i++) {
            cout<<"Lista "<<i<<endl;
            cin>>l[i];
        }
    } else cout<<"Numarul este negativ"<<endl;
}

void afisareLSI(LSI *l,int n) {
    if(oks==1) {
        for(int i=1;i<=n;i++){
            cout<<"Lista "<<i<<endl;
            cout<<l[i];
        }
    oks=0;
    } else  cout<<"Nu sunt construite liste simplu inlantuite"<<endl;
}

void menu() {
    cout<<"4)Lista de numere intregi implementata dinamic - varianta 1\n\n";
    cout<<"1.Citirea a n liste dublu inlantuite "<<endl;
    cout<<"2.Afisarea celor n liste dublu inlantuite "<<endl;
    cout<<"3.Citirea a n liste simplu inlantuite "<<endl;
    cout<<"4.Afisarea celor n liste simplu inlantuite "<<endl;
    cout<<"5.Sortarea a n numere"<<endl;
    cout<<"6.Afisarea numarului de liste construite"<<endl;
    cout<<"7.Upcast"<<endl;
    cout<<"8.Downcast"<<endl;
    cout<<"9.Iesire"<<endl;
}

int main()
{

    int i,n;
    bool k=0;
    LDI *l1;
    LSI *l2;
   do{
    menu();
    cin>>i;
    if(i>=1 && i<=9) {
        switch(i) {
        case 1: {
                cout<<"Tastati numarul de liste dublu inlantuite pe care doriti sa le introduceti ";
                cin>>n;
                citireLDI(l1,n);
                break;
                }
        case 2: {
                afisareLDI(l1,n);
                break;
                }
        case 3: {
                 cout<<"Tastati numarul de liste simplu inlantuite pe care doriti sa le introduceti ";
                 cin>>n;
                 citireLSI(l2,n);
                 break;
                 }
        case 4:{
                afisareLSI(l2,n);
                break;
                }

        case 5: {
                sortare();
                break;
                }
        case 6:{
                LDI::numarListe();
                break;
                }
        case 7:{
                LDI *l=new LSI;
                cin>>*l;
                cout<<*l;
                cout<<l->get_prim()->get_ante()<<endl;
                break;
                }
        case 8:{
                LSI *l=(LSI*)new LDI;
                cin>>*l;
                cout<<*l;
                break;
                }
        default:{break;}
        }
    } else cout<<"Nu a fost introdus un numar valid\n";
    system("pause");
    system("cls");
    }while(i!=9);

    return 0;
}
