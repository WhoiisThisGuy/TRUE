#include "node.h"

Node::Node()
{
//noderect.
}

void Node::SetType(NodeType t){

    type = t;
    switch(type){

    case (NodeType::Empty):
        color = Qt::white;
        break;
    case (NodeType::Block):
        color = Qt::gray;
        break;
    case (NodeType::Start):
        color = Qt::green;
        break;
    case (NodeType::Target):
        color = Qt::red;
        break;
    default:
        color = Qt::white;
        break;
    }

}
void Node::Draw(){

    QPainter p;

    p.setPen(color);

    //p.
}
