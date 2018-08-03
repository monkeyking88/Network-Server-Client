#include "buffer.h"
#include <stdio.h>
#include <cstddef>

using namespace std;

Buffer::Buffer(){}

void Buffer::push(Packet* p){
    this->buf.push(p);
}

Packet* Buffer::pop(unsigned int ticks){
    if (buf.size() == 0){
        return NULL;
    }
    Packet* p = buf.front();
    buf.pop();
    p->leave(ticks);
    return p;
}

Packet* Buffer::front(){
    return this->buf.front();
}

int Buffer::size() {
    return this->buf.size();
}
