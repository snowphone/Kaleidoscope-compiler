#pragma once

#include <vector>
#include <algorithm>
#include <cstdio>

class A_Top;

typedef std::vector<A_Top*>		A_TopList;

extern A_TopList *aroot;

class A_Top {
public:
	virtual ~A_Top() {}
	void indent(int d);				// 각 노드의 깊이를 지정해준다.
	virtual void Print(int d) {}	// 노드를 출력한다.
};

