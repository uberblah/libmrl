#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mrl/gen/list.h>

typedef double(*nfunc)(double);

typedef struct neuron neuron;
struct neuron
{
    nfunc f;
    list in;
    list out;
    double bias;
};

typedef struct synapse synapse;
struct synapse
{
    neuron* in;
    neuron* out;
};

double sigmoid(double t)
{
    return 1.0 / (1.0 + exp(-t));
}

neuron* make_sigmizer(double bias)
{
    neuron* n = (neuron*)malloc(sizeof(neuron));
    n->f = sigmoid;
    n->in = list_null;
    n->out = list_null;
    n->bias = bias;

    return n;
}

void nop(void* a)
{

}

void free_sigmizer(neuron* n)
{
    list_free(n->in, free);
    list_free(n->out, free);
    n->f = NULL;
    free(n);
}

int main(int argc, char** argv)
{
    
}
