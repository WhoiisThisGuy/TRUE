#ifndef NODE_H
#define NODE_H
#include "QSize"
#include "QPainter"
#include "QColor"
#include "QPushButton"

enum class NodeType{Empty,Block,Start,Target};

class Node : QPushButton
{
public:
    Node();
    void SetType(NodeType t);
    void Draw();
    void SetColor();
private:
    NodeType type;
    QColor color;
    QRectF noderect;
};

#endif // NODE_H
