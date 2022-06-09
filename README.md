# DataStructure
这是基本数据结构及其算法的C++实现，涉及单链表、双链表、栈 、二叉树、并查集、哈夫曼树、平衡二叉树、二叉搜索树、堆、哈希表、图以及各种排序算法。该项目使用dev c++做编程环境。

---
# 一、文件结构

## 1 单链表

 - CSDN博客链接：[单链表](https://daipuweiai.blog.csdn.net/article/details/77148472)
 -  **主要介绍了单链表的基本操作。包括建表，插入，删除，逆序，判断是否为空，合并等。我这里写的是带有头结点的单链表，头结点保存链表长度。**

## 2 双链表
 -  **主要介绍了双链表的基本操作。包括建表，插入，删除，逆序，判断是否为空，合并，冒泡排序等。**

## 3 栈
 - CSDN博客链接：[栈的应用——表达式求值](https://daipuweiai.blog.csdn.net/article/details/77508171)
 -  **主要介绍了栈的应用——表达式求值。具体思路就是首先把输入的中缀表达式转换为后缀表达式，然后再根据后缀表达式进行计算求值。这份代码只能实现10以内的加减乘除。**

## 4 二叉树操作
 - CSDN博客链接：[二叉树的构建及其遍历算法](https://daipuweiai.blog.csdn.net/article/details/77531651)
 -  **主要介绍了二叉树的创建、先中后三种遍历方式的递归实现，再详细介绍先中后三种遍历方式的非递归实现与层次遍历。**

## 5 二叉搜索树
 - CSDN博客链接：[二叉搜索树](https://daipuweiai.blog.csdn.net/article/details/77720865)
 -  **主要介绍了二叉搜索树的创建、查找指定值结点、查找最大最小值、插入指定值、删除指定值，插入最大最小值、删除最大最小值操作**
 

## 6 平衡二叉树
 - CSDN博客链接：[平衡二叉树](https://daipuweiai.blog.csdn.net/article/details/77751134)
 -  **主要介绍了平衡二叉树的单左旋、单右旋、右左旋、插入指定值、删除指定值操作**

## 7 哈夫曼树
 -  **主要介绍了哈夫曼树与哈夫曼编码的建立**

# 8 并查集
 - CSDN博客链接：[并查集](https://daipuweiai.blog.csdn.net/article/details/77679030)
 -  **主要介绍了并查集的初始化、查找和并操作**

## 9 并查集

### 9.1 最小堆
 - CSDN博客链接：[最小堆](https://daipuweiai.blog.csdn.net/article/details/77776911)
 -  **主要介绍了最小堆的插入、删除与建堆的操作**
### 9.2 最大堆
 -  **主要介绍了最大堆的插入、删除与建堆的操作**

## 10 图
### 10.1 邻接矩阵
 - CSDN博客链接：[图的遍历（上）——邻接矩阵表示](https://daipuweiai.blog.csdn.net/article/details/77897881)
 -  **主要介绍了邻接矩阵存储下的图的建立、BFS、DFS的递归版本与非递归版本**
 
### 10.2 邻接表
 - CSDN博客链接：[图的遍历（下）——邻接表](https://daipuweiai.blog.csdn.net/article/details/77921966)
 -  **主要介绍了邻接表存储下的图的建立、BFS、DFS的递归版本与非递归版本**
### 10.3 Prim算法
 - CSDN博客链接：[最小生成树算法（上）——Prim(普里姆)算法](https://daipuweiai.blog.csdn.net/article/details/77985294)
 -  **主要介绍了邻接矩阵存储下的图生成最小生成树的Prim(普里姆)算法**
### 10.4 kruskal算法
 - CSDN博客链接：[最小生成树算法（下）——Kruskal(克鲁斯卡尔)算法](https://daipuweiai.blog.csdn.net/article/details/77987425)
 -  **主要介绍了邻接矩阵存储下的图生成最小生成树的Kruskal(克鲁斯卡尔)算法**

### 10.5 Dijiksta算法
 - CSDN博客链接：[最短路径算法（上）——迪杰斯特拉（Dijikstra）算法](https://daipuweiai.blog.csdn.net/article/details/77949979)
 -  **主要介绍了邻接矩阵存储下的图的单源最短路径算法——迪杰斯特拉（Dijikstra）算法**
 
### 10.6 Floyd算法
 - CSDN博客链接：[最短路径算法(下)——弗洛伊德（Floyd）算法](https://daipuweiai.blog.csdn.net/article/details/77964810)
 -  **主要介绍了邻接矩阵存储下的图的多源最短路径算法——弗洛伊德（Floyd）算法**

### 10.7 拓扑排序
 - CSDN博客链接：[拓扑排序](https://daipuweiai.blog.csdn.net/article/details/78004990)
 -  **主要介绍了邻接矩阵存储下的图的拓扑排序算法**
## 11 哈希表
### 11.1 开放定址法
 - CSDN博客链接：[散列表（上）——开放定址法](https://daipuweiai.blog.csdn.net/article/details/78044445)
 -  **主要介绍了开放地址法的哈希表，冲突处理策略为线性探测**
### 11.2 分离链接法
 - CSDN博客链接：[散列表（下）——分离链接法](https://daipuweiai.blog.csdn.net/article/details/78045574)
 -  **主要介绍了分离链接法的哈希表** 
## 12 各种排序
 - 相关CSDN博客链接：[简单排序](https://daipuweiai.blog.csdn.net/article/details/78077411)，[希尔排序](https://daipuweiai.blog.csdn.net/article/details/78077729)，[归并排序](https://daipuweiai.blog.csdn.net/article/details/78079184)，[快速排序](https://daipuweiai.blog.csdn.net/article/details/78079983)，[堆排序](https://daipuweiai.blog.csdn.net/article/details/78078821)
 - 主要介绍了各种排序算法包括：冒泡排序、插入排序、希尔排序、选择排序 、归并排序（递归版本与非递归版本）、堆排序、快速排序
