#include "automaton.hpp"
#include <iostream>
#include <cstdlib>

void Automaton::Update(void)
{
    if (!running) return;
    if (counter_max == 20) return;
    if (counter < counter_max) {
        counter++;
        return;
    }

    counter = 0;
    for (int i = 0; i < aheight; i++)
        for (int j = 0; j < awidth; j++) {
            int current = (*front)(i,j);

	    if (current == ill_state){
		(*back)(i,j) = 0;
		continue;
	    }

	    int a=0,b=0, s=current;
	    for (int adj_i = std::max(0, i-1); adj_i < std::min(aheight, i+2); ++adj_i)
		for (int adj_j = std::max(0, j-1); adj_j < std::min(awidth, j+2); ++adj_j)
		    if (adj_i != i || adj_j != j) {
			const int adjacent = (*front)(adj_i, adj_j);
			s += adjacent;
			if (adjacent) {
			    if (adjacent == ill_state) b++;
			    else a++;
			}
		    }

	    const double next = current ?
		(double)s/(a+b+1) + g :
		a/k1 + b/k2;

	    (*back)(i,j) = std::min(255, (int)next);
        }
    LMatrix <statecode> *temp;
    temp = front;
    front = back;
    back = temp;
    emit updated();
}

int Automaton::getCellCount()
{
    return cellCount;
}

void Automaton::Randomize()
{
    for (int i=0; i<aheight; i++)
        for (int j=0; j<awidth; j++) {
            (*front)(i,j) = rand() % ((int)ill_state+1);
        }
    emit updated();
    statusChanged("Randomized", 3000);
}

void Automaton::Clear()
{
    for (int i=0; i<aheight; i++)
        for (int j=0; j<awidth; j++) {
            (*front)(i,j) = 0;
        }
    emit updated();
    emit statusChanged("Cleared", 3000);
}

void Automaton::ChangeSpeed(int speed)
{
    counter_max = 20 - speed;
}

void Automaton::start()
{
    if (running) return;
    running = true;
    emit statusChanged("Started", 3000);
}

void Automaton::stop()
{
    if (!running) return;
    running = false;
    emit statusChanged("Stopped", 3000);
}
