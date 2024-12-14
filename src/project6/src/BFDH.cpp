#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include "timer.h"
using namespace std;

struct Item {
    int w;  // 物体的宽度
    int h;  // 物体的高度
    int x;  // 左下角 x 坐标
    int y;  // 左下角 y 坐标
};
struct Level {
    vector<Item> items;
    int leftw;  // 剩余的宽度
    int h;      // 自己的高度
    int y;      // 自己左下角的 y 坐标
};
vector<Level> levels;  // 存放所有层
vector<Item> items;    // 存放所有物体
bool cmp(Item a, Item b) {
    // if(a.h==b.h){
    //     return a.w<b.w;
    // }
    return a.h > b.h;
}
int n, m;
int main() {
    scanf("%d%d", &m, &n);  // m 为画布宽度，n 为物体数量
    Item item;
    item.x = 0;
    item.y = 0;
    for (int i = 0; i < n; i++) {  // 输入物体的宽度和高度
        scanf("%d %d", &item.w, &item.h);
        items.push_back(item);
    }

    START_TIMER;

    sort(items.begin(), items.end(), cmp);  // 按照高度从大到小，宽度从小到大排序
    Level level;
    level.leftw = m;
    level.h = 0;
    level.y = 0;
    for (int i = 0; i < items.size(); i++) {  // 将物体放入层中
        // printf("%d\n",i);
        int k = -1;
        for (int j = 0; j < levels.size(); j++) {                                                   // 寻找合适的层，满足当前层宽度能容纳下物体而且宽度最小
            if (levels[j].leftw >= items[i].w && (k == -1 || levels[j].leftw < levels[k].leftw)) {  // 如果当前层的宽度足以容纳当前物体，则放入当前层
                k = j;
            }
            // printf("%d\n",j);
        }

        if (k == -1) {                                                                                    // 如果所有层的宽度不足以容纳当前物体，则新建一个层
            level.items.clear();                                                                          // 清空临时用的层
            level.leftw = m - items[i].w;                                                                 // 剩余的宽度为画布宽度减去当前物体的宽度
            level.h = items[i].h;                                                                         // 当前物体的高度为当前层的高度
            level.y = levels.size() > 0 ? levels[levels.size() - 1].y + levels[levels.size() - 1].h : 0;  // 当前层的 y 坐标为前一层的 y 坐标加上前一层的高度
            items[i].x = 0;                                                                               // 第一个物体的左下角 x 坐标为 0
            items[i].y = level.y;                                                                         // 物体的左下角 y 坐标为当前层的 y 坐标
            level.items.push_back(items[i]);                                                              // 将物体加入当前层
            levels.push_back(level);                                                                      // 将临时用的层加入 levels
        } else {
            items[i].x = m - levels[k].leftw;     // 物体的左下角 x 坐标为画布宽度减去剩余的宽度
            items[i].y = levels[k].y;             // 物体的左下角 y 坐标为当前层的 y 坐标
            levels[k].items.push_back(items[i]);  // 将物体加入当前层
            levels[k].leftw -= items[i].w;        // 更新剩余的宽度
        }
        // printf("%d\n",i);
    }

    double time = 0.0;
    STOP_TIMER(time);

    for (int i = 0; i < levels.size(); i++) {
        printf("Level %d %d %d %d:\n", i + 1, levels[i].leftw, levels[i].h, levels[i].y);
        for (int j = 0; j < levels[i].items.size(); j++) {
            printf("%d %d %d %d\n", levels[i].items[j].w, levels[i].items[j].h, levels[i].items[j].x, levels[i].items[j].y);
        }
        printf("\n");
    }
    printf("Total height: %d\n", levels[levels.size() - 1].y + levels[levels.size() - 1].h);
    for (int i = 0; i < items.size(); i++) {
        printf("%d %d %d %d\n", items[i].x, items[i].y, items[i].w, items[i].h);  // 按照 x,y,w,h 输出
    }

    printf("Running Time: %.6lf\n", time);
    return 0;
}