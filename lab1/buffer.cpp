#include "buffer.h"

Buffer::Buffer(){
    capacity = -1;
}

Buffer::Buffer(int k){
    capacity = k;
}

void Buffer::push(Packet* p, unsigned int ticks){
    //if there is a limit and limit is reached, lose the packet
    if (capacity >= 0 && buf.size() == (unsigned int)capacity) {
        p->lose();
        return;
    }
    p->enter(ticks);
    buf.push(p);
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

Packet* Buffer::front_buffer(){
    Packet* p = buf.front();
    return p;
}

int Buffer::getSize() {
    return buf.size();
}
