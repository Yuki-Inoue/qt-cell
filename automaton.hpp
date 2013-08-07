#ifndef _L_AUTOMATON
#define _L_AUTOMATON

#include "lmatrix.hpp"
#include <QSet>
#include <QString>
#include <QObject>
#include <map>

typedef unsigned char statecode;

class Automaton : public QObject {
    Q_OBJECT
private:


    int cellCount;


    // for BZ
    statecode ill_state;
    double k1, k2, g;



    int awidth, aheight;

    LMatrix <statecode> field1;
    LMatrix <statecode> field2;
    LMatrix <statecode> *back;
    statecode Cellcode(int x, int y);
    int counter, counter_max;
    statecode drawingnow;
    bool running;
public:
    LMatrix <statecode> *front;
    statecode &operator () (int i, int j)
    {
        return (*front)(i,j);
    }
    
    Automaton(int cellCount=40, statecode ill_state=255, double k1=0.1, double k2=0.1, double g=0.1, QObject *parent=0) :
	QObject(parent), cellCount(cellCount), ill_state(ill_state), k1(k1), k2(k2), g(g)
    {
        awidth = 600;
        aheight = 600;
        field1 = LMatrix <statecode> (aheight, awidth);
        field2 = LMatrix <statecode> (aheight, awidth);
        front = &field1;
        back = &field2;
        counter = 0;
        counter_max = 5;

        for (int i=0; i<aheight; i++)
            for (int j=0; j<awidth; j++)
                field1(i,j) = field2(i,j) = 0;

        running = true;
    }

    Automaton &operator = (const Automaton &right)
    {
        if (this == &right)
            return *this;
        cellCount = right.cellCount;
        field1 = right.field1;
        field2 = right.field2;
        front = &field1;
        back = &field2;
        return *this;
    }
    void Draw(int x, int y, statecode val);
    int getCellCount();
    statecode getIllState() const { return ill_state; }
public slots:
    void Randomize();
    void Clear();
    void Update();
    void ChangeSpeed(int speed);
    void MouseMove(int x, int y);
    void MouseDown(int x, int y);
    void start();
    void stop();
signals:
    void updated();
    void statusChanged(const QString &message, int timeout);
};
#endif
