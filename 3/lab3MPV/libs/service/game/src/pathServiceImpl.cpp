#include "pathServiceImpl.h"
#include "queue"

PathCalcServiceImpl::PathCalcServiceImpl(Map &map_, Castle & castle_): map(map_), castle(castle_) {}

void PathCalcServiceImpl::calcDistanceForMap() {
    int barrier = 999999;
    int rows = map.getRows();
    int cols = map.getCols();

    for (auto &c : map.get()) c.setPriority(barrier);

    std::queue<Point> q;

    Cell & castleCell = map.at(castle.getLocation().x, castle.getLocation().y);
    castleCell.setPriority(0);
    q.push(castleCell.pos);
    while (!q.empty()) {
        Point current = q.front();
        int currentPriority = map.at(current.x, current.y).getPriority();
        q.pop();

        Point neighbors[4]= {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (auto &neighbor : neighbors) {
            Point next= {current.x + neighbor.x, current.y + neighbor.y};

            if (next.x <0 || next.y < 0 || next.x >= cols || next.y >= rows) continue;

            if (map.at(next.x, next.y).type!= TerraType::road) continue;

            if (map.at(next.x, next.y).getPriority() > currentPriority+1) {
                map.at(next.x, next.y).setPriority(currentPriority+1);
                q.push(next);
            }
        }
    }
}


void PathCalcServiceImpl::calcFlowForMap() {
    int rows = map.getRows();
    int cols = map.getCols();
    for (int y = 0; y< rows; y++) {
        for (int x = 0; x< cols; x++) {
            if (map.at(x, y).priority >= 99999|| map.at(x, y).priority == 0) {
                map.at(x, y).flow = {0.f, 0.f};
                continue;
            }
            int left= (x>0) ? map.at(x-1, y).priority : map.at(x, y).priority;
            int right = (x < cols-1) ? map.at(x+1, y).priority : map.at(x, y).priority;
            int up = (y>0) ? map.at(x, y-1).priority : map.at(x, y).priority;
            int down = (y< rows-1) ? map.at(x, y+1).priority : map.at(x, y).priority;

            if (left >= 99999) left=map.at(x,y).priority;
            if (right >= 99999) right=map.at(x,y).priority;
            if (up>= 99999) up=map.at(x,y).priority;
            if (down >= 99999) down=map.at(x,y).priority;

            PointF vec;
            vec.x = static_cast<float>(left-right);
            vec.y = static_cast<float>(up-down);

            float length = std::sqrt(vec.x*vec.x + vec.y*vec.y);
            if (length >= 0.0001) {
                map.at(x, y).flow.x = vec.x/length;
                map.at(x, y).flow.y = vec.y/length;
            }
            else {
                map.at(x, y).flow.x = 0.f;
                map.at(x, y).flow.y = 0.f;
            }

        }

    }
}
