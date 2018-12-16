#include "pch.h"
#include"graph.h"
#include <iostream>
#include<stack>
void queryPositionInfo(int n,Node arr[]) {
	arr[n].print();

}
/*使用Dijkstra算法其中--暂时最短路径的点(已经访问过的不再访问)*/
int minVertex(Graphm*G,int*D) {
	int i, v = -1;
	for (i = 0; i < G->n(); i++) {
		if (G->getMark(i) == 0) {
			v = i;
			break;
		}
	}
	for (i++; i < G->n(); i++) {
		if ((G->getMark(i)==0) &&(D[i] < D[v]))
			v = i;
	}
	return v;
}
/*参数为图,距离数组，源点，终点，路径数组*/
void Dijkstra(Graphm*G, int*D, int s,int d,int root[]) {
	//初始化路径,所有点的父节点设置为-1，即不可到达
	for (int i = 0; i < 8; i++)
		root[i] = -1;
	//初始化距离，使s到自身的距离为0，其余为MAX
	int vertexNum = G->getNumVertex();
	for (int i = 0; i < G->n(); i++) {
		D[i] = MAX;
	}
	D[s] = 0;
	int v, w;
	int dis_temp = D[d];

	for (int i = 0; i < G->n(); i++) {
		dis_temp = D[d];
		/*
		for (int i = 0; i < 8; i++)
		cout << D[i] << " \t";
		cout << "Loop" << endl;
		*/

		v = minVertex(G, D);
		if (D[v] == MAX) return;//Unreachable vertices
		G->setMark(v, 1);

		for (w = G->first(v); w < G->n(); w = G->next(v,w)) {
			if (D[w] > D[v] + G->weight(v, w)) {
				D[w] = D[v] + G->weight(v, w);
				root[w] = v;
			}
		}
	}
}
void printRoot(int root[],int s,int d) {
	//root为路径数组，s为源点，d为路径终点
	stack<int> stemp;
	//把终点压入栈中
	stemp.push(d);
	//压入沿途中的点
	for (int elem = root[d]; (elem != s) && (elem!= -1);elem=root[elem]) {
		stemp.push(elem);
	}
	//压入起点
	stemp.push(s);
	if (root[d] == -1)
		cout << "No Way From " << s << " to " << d << endl;
	else {
		cout << "From " << s << " to " << d << " the shortest path is: " << endl;
		while (!stemp.empty()) {
			if (stemp.top() != d)
				cout << stemp.top() << "-->";
			else
				cout << stemp.top();
			stemp.pop();
		}
		cout << endl;
	}
	
}
int main()
{
	Node arr[]= {
		Node(0,"图书馆","学霸栖息地"),Node(1,"体育馆","肥宅的我从来没去过"),
		Node(2,"艺术学院","艺术气息浓厚（妹子多）"),Node(3,"一教A座","一栋超长的教学楼"),
		Node(4,"文科楼","四川大学江安校区文科楼"),Node(5,"华联超市","校园超市，不过水果超贵"),
		Node(6,"行政楼","同学你下来吧，老师说平时成绩有60"),Node(7,"二餐","江安二餐，最经常光顾的食堂")
	};
	/*0--图书馆---104.006277,30.562702
	*1--体育馆---104.012912,30.563747
	*2--艺术学院--104.00187,30.561488
	*3--一教---104.00634,30.560927
	*4--文科楼---104.010855,30.565392
	*5--华联超市--103.999783,30.559281
	*6--行政楼---104.009139,30.560129
	*7--二餐--103.998383,30.558462
	*/
	Graphm g(8);
	/*7点是起始点*/
	/*设置各点的路径*/
	g.setEdge(7, 5, 162); g.setEdge(7, 0, 891);
	g.setEdge(0, 3, 198);
	g.setEdge(5, 2, 316);	g.setEdge(5, 3, 654);
	g.setEdge(2, 4, 964);	g.setEdge(3, 4, 659);
	g.setEdge(3, 6, 282);	g.setEdge(2, 6, 713);
	/*D为距离数组，root为路径数组*/
	int D[8] = {};
	int root[8] = {};
	Dijkstra(&g, D, 7,4,root);

	/*测试两个点的最短路径*/
	printRoot(root, 7, 1);
	printRoot(root, 7, 2);
	printRoot(root, 7, 3);
	printRoot(root, 7, 4);
	printRoot(root, 7, 5);
	printRoot(root, 7, 6);
	printRoot(root, 5, 6);
	system("pause");
	return 0;
}
