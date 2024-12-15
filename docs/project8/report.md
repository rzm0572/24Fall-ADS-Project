# Project 8: MapReduce
## 简介
介绍MapReduce框架的工作原理，并实现一个 MapReduce 程序来统计一组文档中每个单词的出现次数。

编写MapReduce程序，实现Map()和Reduce()函数，用于统计文档中单词的出现次数。
## 需求
### 输入
一组文档，每个文档包含若干单词。单词数量不少于 $10^5$。

### 输出
- 每个单词出现的次数。

- 输出结果需按单词出现次数的非降序排列，次数相同则按字典序排列。

- 分别实现串行和并行版本。


## 框架
MapReduce是一种编程模型，主要用于处理和生成大规模数据集。它通过在集群上运行并行、分布式算法来实现这一目标。


### Map
Map过程接收一个键值对作为输入，并产生一系列新的键值对作为输出。Map函数的目的是处理输入数据，并将其转换成适合进一步处理的形式。例如，在处理文本数据时，Map函数可能会将每一行文本拆分成单词，并为每个单词生成一个键值对，其中键是单词，值通常是数字1（表示出现一次）。大数据集被划分成多个分片，每个分片分配给一个Map任务，该任务在集群中的不同节点上并行执行。Map任务读取输入数据，执行用户定义的Map函数，并输出一系列中间键值对。

### Reduce（归约）
Reduce过程接收Map过程输出的中间键值对，并对具有相同键的所有值进行归约操作。归约操作的目的是将所有相关的数据聚合起来，例如，计算每个单词出现的总次数。
用户定义的Reduce函数会对每个键及其对应的所有值执行归约操作，并输出最终的结果。


## 实现
### 并行版本
#### 思路

#### 伪代码

### 串行版本

#### 思路
- 对于每个单词，构建一个Trie树（前缀树）。

- 将单词出现次数记录在每个单词的结束节点。

- 使用 dfs 遍历树，收集所有单词的数量和字符串。

- 使用 sort 按照出现次数和字典序进行排序。

- 将排序后的结果写入文件。

#### 伪代码

```c++
定义节点结构 Node：
    字符指针数组 sons[26]
    以此结尾单词出现次数 num

初始化根节点 root

定义全局变量：
    整数 n, m
    向量 sort_list 存储单词数量和字符串对

定义深度优先搜索函数 dfs(p, s)：
    如果 p 的 num 不为 0：
        将 (p 的 num, s) 添加到 sort_list
    对于每个字母 i：
        如果 p 的 sons[i] 不为空：
            调用 dfs(p 的 sons[i], s + 字母 i)

定义比较函数 cmp(a, b)：
    如果 单词出现次数不同：
        出现次数排序
    否则：
        字典序排序

重定向输入流到文件
读取 n
对于 每个单词：
    读取字符串 s
    设置 p 为 字典树的 root
    对于 s 中的每个字符：
        计算索引 index，此处为 s[i] - 'a'
        如果 p 的 sons[index] 为空：
            创建新节点
        更新 p 为 p 的 sons[index]
    p 的 num 加 1，即单词出现次数加 1
    更新 m 为最大值(m, p 的 num)

遍历整棵树，并统计所有单词
对 sort_list 进行排序，使用 cmp 作为比较函数

重定向输出流到文件
对于 sort_list 中的每个元素：
    将元素写入文件
```

## 测试
### 数据生成
#### 数据获取
从网上获得英文小说原文：

[Harry Potter](https://github.com/bobdeng/owlreader/tree/master/ERead/assets/books)

[Lord of the Rings](https://github.com/ganesh-k13/shell/tree/master/test_search/www.glozman.com/TextPages)

[Star Wars](https://github.com/ganesh-k13/shell/tree/master/test_search/www.glozman.com/TextPages)

[A Record of a Mortal's Journey to Immortality: Immortal Realm](https://novelbin.com/b/a-record-of-a-mortals-journey-to-immortality-immortal-realm)

[Charlie And The Chocolate Factory](https://archive.org/stream/CharlieAndTheChocolateFactory/Charlie%20and%20the%20Chocolate%20Factory_djvu.txt)

[The Great Gatsby](https://github.com/bobdeng/owlreader/blob/master/ERead/assets/books/The%20Great%20Gatsby.txt)

#### 数据清洗
将数据转换为小写，去除标点符号，分词。并分割为大小从 $100000$ 到 $900000$ 的文件，格式为：
```
n
word1 
word2

...

wordn
```
其中 $n$ 为单词出现的总次数。

#### 代码实现

```c++
重定向标准输入到 "1.txt"
重定向标准输出到 "./1/1.txt"
输出 100000 作为单词总数

初始化变量：
    长整数 n 为 0, maxnum 为 0
    字符串 s
    整数 j 为 1, mo 为 100000, m 为 3, nn 为 1

当从标准输入读取到单词 s 时：
    初始化空字符串 str
    对于 s 中的每个字符：
        如果字符是字母或撇号：
            如果不是撇号，将字符添加到 str
        否则：
            如果字符是大写字母，转换为小写并添加到 str
            否则：
                更新 maxnum 为 str 长度和 maxnum 中的最大值
                如果 str 长度大于 0 且小于 16：
                    输出 str
                    n 加 1
                    清空 str
                    如果 n 大于等于 mo：
                        mo 加 100000
                        n 重置为 0
                        nn 加 1
                        重定向标准输出到 "./" + nn + "/1.txt"
                        输出 mo

如果 str 长度大于 0 且小于 16：
    输出 str
    n 加 1
    清空 str
    如果 n 大于等于 mo：
        mo 加 100000
        n 重置为 0
        nn 加 1
        重定向标准输出到 "./" + nn + "/1.txt"
        输出 mo

```

### 性能测试

|单词数量 |100000 |200000 |300000 |400000 |500000 |600000 |700000 |800000 |900000 |
| --- | --- |--- | --- | --- | --- | --- | --- | --- | --- |
|串行版本（/ms） | 209.264|347.82|472.776|580.501|632.119|742.925|801.97|923.116|1023.6|



## 总结
