#ifndef SEARCH_H
#define SEARCH_H


class Search
{
public:
    Search();

    void setGridValue(int row, int col);
    void addToPath(int row, int col);
    void markAsVisited(int row, int col);

    int getGridValue(int row, int col);
    bool isVisited(int row, int col);
};

#endif // SEARCH_H
