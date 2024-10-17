#include "MinHeap.h"
#include <cstdio>
#include <cstdlib>

template class BinaryHeap<dist_pair>;
/*
初始化类
参数：
n：数据的总数
返回值：无
作用：初始化一个空的二叉堆，并分配（n+1）空间。
一部分空间用于储存每个节点都在堆中的位置，
另一部分空间用于储存堆。
*/

template <class T>
BinaryHeap<T>::BinaryHeap(int n)
{
    size = 0;
    Heap = (Pair<T> *)malloc((n + 1) * sizeof(Pair<T>)); // 分配空间用于储存堆
    Position = (int *)malloc((n + 1) * sizeof(int));     // 分配空间用于储存每个节点都在堆中的位置
    for (int i = 0; i <= n; i++)
    {
        Position[i] = -1; // 初始化每个节点都不在堆中
    }
    // printf("BinaryHeap created\n");
}

template <class T>
Pair<T> BinaryHeap<T>::findMin()
{
    // TODO
    return Heap[1];
}
/*
插入一个新的元素x到二叉堆中，并保持其为最小堆。
参数：
x：要插入的元素
返回值：成功返回true，检查到节点存在返回false，
应使用decreaseKey来更新节点的值。
*/
template <class T>
bool BinaryHeap<T>::insert(Pair<T> x)
{
    if (checkExist(x.key))
    { // 节点已存在，则不插入，返回false
        return false;
    }
    size++;                 // 节点不存在，则插入，堆大小加1
    Heap[size] = x;         // 插入新节点在堆的最后位置
    Position[x.key] = size; // 记录节点在堆中的位置，最初为堆的末尾
    int pos = size;         // 当前节点的位置
    while (pos > 1 && Heap[pos] < Heap[pos / 2])
    {                                      // 向上调整，直到父节点小于自己
        Position[Heap[pos].key] = pos / 2; // 更新节点在堆中的位置
        Position[Heap[pos / 2].key] = pos;

        Pair<T> temp = Heap[pos / 2]; // 更新堆
        Heap[pos / 2] = Heap[pos];
        Heap[pos] = temp;
        pos /= 2; // 向上调整
    }
    return true;
}
/*
删除最小元素。
返回值：成功返回true，若二叉堆为空返回false。
*/
template <class T>
bool BinaryHeap<T>::deleteMin()
{
    if (size == 0)
    { // 二叉堆为空，则不删除，返回false
        return false;
    }
    Position[Heap[1].key] = -1; // 该节点在堆中的位置不存在
    Heap[1] = Heap[size];       // 将最后一个节点放到根节点位置
    size--;
    int pos = 1;
    while (2 * pos <= size)
    { // 向下调整，直到子节点小于父节点
        int j = 2 * pos, i = j + 1;
        if (i <= size && Heap[i] < Heap[j])
        { // 选择较小的子节点
            j = i;
        }
        if (Heap[j] < Heap[pos])
        {                                // 父节点大于子节点，则交换位置
            Position[Heap[pos].key] = j; // 更新节点在堆中的位置
            Position[Heap[j].key] = pos;

            Pair<T> temp = Heap[pos]; // 更新堆
            Heap[pos] = Heap[j];
            Heap[j] = temp;
            pos = j;
        }
        else
        {
            break;
        }
    }
    return true;
}
/*
更新节点的值。
参数：
x：要更新的节点
返回值：成功返回true，若节点不存在或新值不小于当前值返回false。
*/
template <class T>
bool BinaryHeap<T>::decreaseKey(Pair<T> x)
{
    int pos = Position[x.key]; // 获取节点在堆中的位置
    if (!checkExist(x.key) || Heap[pos] < x)
    { // 节点不存在或新值不小于当前值，则不更新，返回false
        return false;
    }
    Heap[pos] = x; // 更新节点的值
    while (pos > 1 && Heap[pos] < Heap[pos / 2])
    {                                      // 向上调整，直到父节点小于自己
        Position[Heap[pos].key] = pos / 2; // 更新节点在堆中的位置
        Position[Heap[pos / 2].key] = pos;

        Pair<T> temp = Heap[pos / 2]; // 更新堆
        Heap[pos / 2] = Heap[pos];
        Heap[pos] = temp;
        pos /= 2;
    }
    return true;
}
/*
获取二叉堆的大小。
返回值：二叉堆的大小。
*/
template <class T>
int BinaryHeap<T>::getSize()
{
    return size;
}
/*
检查节点是否存在。
参数：
key：要检查的节点的键值
返回值：若节点存在返回true，否则返回false。
*/


template <class T>
bool BinaryHeap<T>::checkExist(int key) {
    return Position[key] != -1;
}
