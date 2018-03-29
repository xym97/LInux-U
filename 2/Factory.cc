#include<iostream>

using namespace std;

enum{ typeA, typeB };
/*
class product{
public:
    virtual void show() = 0;
};

class productA : public product{
public:
    virtual void show(){
        cout<< "productA" << endl;
    }
};

class productB : public product{
public:
    virtual void show(){
        cout<< "productB" << endl;
    }
};

class Factory{
public:
    static product* createproduct(int type){
        switch(type){
        case typeA:
            return new productA();
            break;
        case typeB:
            return new productB();
            break;
        }
    }
};

int main()
{
    Factory f;
    product* pA = f.createproduct(typeA);
    product* pB = f.createproduct(typeB);
    pA->show();
    pB->show();
    return 0;
}
*/
/*
class product{
public:
    virtual void show() = 0;
};

class productA: public product{
public:
    virtual void show(){
        cout<< "productA"<<endl;
    }
};

class productB: public product{
public:
    virtual void show(){
        cout<<"productB"<<endl;
    }
};

class Factory{
public:
    virtual product* createproduct() = 0;
};

class FactoryA: public Factory{
public:
    virtual product* createproduct(){
        return new productA();
    }
};

class FactoryB: public Factory{
public:
    virtual product* createproduct(){
        return new productB();
    }
};

int main()
{
    Factory* pFA = new FactoryA();
    Factory* pFB = new FactoryB();
    pFA->createproduct()->show();
    pFB->createproduct()->show();
    return 0;
}
*/

class pen{
public:
    virtual void show() = 0;
};

class pen1 :public pen{
public:
    virtual void show(){
        cout<< "good pen"<<endl;
    }
};

class pen2 :public pen{
public:
    virtual void show(){
        cout<< "bad pen"<<endl;
    }
}; 

class pencil{
public:
    virtual void show() = 0;
};

class pencil1 :public pencil{
public:
    virtual void show(){
        cout<<"good pencil"<<endl;
    }
};

class pencil2 :public pencil{
public:
    virtual void show(){
        cout<<"bad pencil"<<endl;
    }
};

class Factory{
public:
    virtual pen* createpen() = 0;
    virtual pencil* createpencil() = 0;
};

class Factory1 : public Factory{
public:
    virtual pen* createpen(){
        return new pen1();
    }
    virtual pencil* createpencil(){
        return new pencil1();
    }
};

class Factory2 : public Factory{
public:
    virtual pen* createpen(){
        return new pen2();
    }
    virtual pencil* createpencil(){
        return new pencil2();
    }
};

int main()
{
    Factory* f1 = new Factory1();
    f1->createpen()->show();
    f1->createpencil()->show();

    Factory* f2 = new Factory2();
    f2->createpen()->show();
    f2->createpencil()->show();
    return 0;
}


















