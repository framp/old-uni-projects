#include "logic/grid.h"

Grid::Grid(int width, int height, int time) :
    width(width), height(height), time(time), cells(width*height)
{}

Grid::Grid(string expression):
    width(0), height(0), time(0), cells(0)
{
    stringstream stream(expression);

    while(stream.peek()==' ') stream.ignore();
    stream.ignore();

    int n[3];
    for (int i=0; i<3; i++) {
        stream >> n[i];
        while(stream.peek()==' ') stream.ignore();
        stream.ignore();
    }
    while(stream.peek()==' ') stream.ignore();
    stream.ignore();

    string children;
    while(!stream.eof() && stream.peek()!=']') {
        children.append(1, stream.get());
    }

    width = n[0];
    height = n[1];
    time = n[2];
    cells = vector<CISpointer<Cell> >(width*height);

    int size = children.size(), counter = 0;
    while(children.size()>0 && counter<2) {
        if ((unsigned)size==children.size()) {
            counter++;
        } else {
            size = children.size();
        }
        while(children[0]==' ') children = children.substr(1);
        if (children[0]==',') children = children.substr(1);
        if (children[0]==']') break;
        string result;
        result = Validator(children, """Input""($,$,$)").result();
        if (result!="") {
            insert(new Input(result));
            continue;
        }
        result = Validator(children, """Output""($,$,$)").result();
        if (result!="") {
            insert(new Output(result));
            continue;
        }
        result = Validator(children, """Wire""($,$,$)").result();
        if (result!="") {
            insert(new Wire(result));
            continue;
        }
        result = Validator(children, """Clock""($,$,$,$,$)").result();
        if (result!="") {
            insert(new Clock(result));
            continue;
        }
        result = Validator(children, """Gate""?(($,$,$,$)").result();
        if (result!="") {
            insert(new Gate(result));
            continue;
        }
        result = Validator(children, """Inverter""($,$,$)").result();
        if (result!="") {
            insert(new Inverter(result));
            continue;
        }
        result = Validator(children, """FlipFlop""($,$,$)").result();
        if (result!="") {
            insert(new FlipFlop(result));
            continue;
        }
    }
}

void Grid::insert(Cell* c)
{
    if ((c->y * width + c->x)<0 || (unsigned)(c->y * width + c->x)>=cells.size())
        throw "Out of bounds cell";
    cells[c->y * width + c->x] = c;
}

void Grid::remove(Cell* c)
{
    if ((c->y * width + c->x)<0 || (unsigned)(c->y * width + c->x)>=cells.size())
        throw "Out of bounds cell";
    if (cells[c->y * width + c->x]==0)
        throw "Empty cell";
    if (cells[c->y * width + c->x]->getType()!=c->getType())
        throw "Not the same cell type";
    cells[c->y * width + c->x] = 0;
}

void Grid::shift(int sx, int sy)
{
    int maxWidth = width, maxHeight = height;

    for (vector<CISpointer<Cell> >::iterator it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0) {
            int x = ((*it)->x+sx), y = ((*it)->y+sy);
            if (x>=maxWidth)
                maxWidth = x+1;
            else if (x<0)
                throw "Out of bounds cell";
            if (y>=maxHeight)
                maxHeight = y+1;
            else if (y<0)
                throw "Out of bounds cell";
            (*it)->x = x;
            (*it)->y = y;
        }
    }
    if (width<maxWidth)
        width = maxWidth;
    if (height<maxHeight)
        height = maxHeight;
    vector<CISpointer<Cell> > cells2(width*height);
    for (vector<CISpointer<Cell> >::const_iterator it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0) {
            cells2[(*it)->y * width + (*it)->x] = *it;
        }
    }
    cells.swap(cells2);
}

void Grid::merge(const Grid * g)
{
    if (g->width>width || g->height>height) {
        vector<CISpointer<Cell> > temp(cells);
        if (g->width>width)
            width = g->width;
        if (g->height>height)
            height = g->height;
        cells.clear();
        cells.resize(width*height);

        for (vector<CISpointer<Cell> >::const_iterator it=temp.begin(); it!=temp.end(); ++it) {
            if (*it!=0) {
                cells[(*it)->y * width + (*it)->x] = *it;
            }
        }
    }
    for (vector<CISpointer<Cell> >::const_iterator it=g->cells.begin(); it!=g->cells.end(); ++it) {
        if (*it!=0) {
            insert(&**it);
        }
    }
}
void Grid::propagateToNeighbours(Cell& c, int px, int py)
{
    vector< CISpointer<Cell> > neighbours;
    for (int j=0; j<4; ++j) {
        int x = c.x + ((j-2)%2),
            y = c.y + ((j-1)%2),
            i = y * width + x;
        if ((x!=px || y!=py) &&
                0<=x && x<width &&
                0<=y && y<height &&
                0<=i && (unsigned) i<cells.size() &&
                cells[i]!=0) {
            neighbours.push_back(cells[i]);
        }
    }
    if (c.isReady()) {
        c.propagateSignal(neighbours);

        for (vector< CISpointer<Cell> >::iterator it=neighbours.begin(); it!=neighbours.end(); ++it) {
            if (*it!=0) {
                propagateToNeighbours(**it, c.x, c.y);
            }
        }
    }
}

string Grid::getType() const
{
    return "Grid";
}

string Grid::toString() const
{
    stringstream os;
    os << "[" << width << "," << height << "," << time << ",[";
    bool first = true;
    vector< CISpointer<Cell> >::const_iterator it;
    for (it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0) {
            if (first)
                first = false;
            else
                os << ", ";
            os << (*it)->toString();
        }
    }
    os << "]]";
    return os.str();
}


void Grid::tick()
{
    for (vector< CISpointer<Cell> >::iterator it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0 && ((*it)->getType()=="Input" || (*it)->getType()=="Clock")) {
            propagateToNeighbours(**it, (*it)->x, (*it)->y);
        }
    }
    ++time;
}

void Grid::reset()
{
    vector< CISpointer<Cell> >::iterator it;
    for (it=cells.begin(); it!=cells.end(); ++it) {
        if (*it!=0) {
            (*it)->resetSignal();
        }
    }
    time = 0;
}

void Grid::operator<<(Base * b)
{
    if (b->getType()=="Grid" || b->getType()=="Vector")
        undefined();
    Cell *c = static_cast<Cell*>(b);
    insert(c);
}

void Grid::operator>>(Base * b)
{
    if (b->getType()=="Grid" || b->getType()=="Vector")
        undefined();
    Cell *c = static_cast<Cell*>(b);
    remove(c);
}

void Grid::operator+(const Base * b)
{
    if (b->getType()=="Grid") {
        const Grid *g = static_cast<const Grid*>(b);
        merge(g);
        return;
    }
    if (b->getType()!="Vector")
        undefined();
    const Vector *v = static_cast<const Vector*>(b);
    shift(v->x, v->y);
}

void Grid::operator-(const Base * b)
{
    if (b->getType()!="Vector")
        undefined();
    const Vector *v = static_cast<const Vector*>(b);
    shift(-v->x, -v->y);
}
