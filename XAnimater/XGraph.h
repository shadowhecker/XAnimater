//
// 基于FLTK 1.1.10的图形库基础版
// 图形类
// XPoint（点）
// XShape（形状）
//   XLine（直线）
// XColor（颜色）
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
// Modified by ZhangHua @ 2015-11-09
//
// 请同学们在此文件增加自己的图形类。

#ifndef _XGRAPH_H_
#define _XGRAPH_H_

#include <vector>
#include <initializer_list>
using namespace std;

#include "FL/fl_draw.h"

// 点
class XPoint
{
public:
	int xx, yy; // 点的坐标值

	XPoint(int x=0, int y=0) { xx=x; yy=y; }
};

// 颜色（重新包装FLTK中的颜色）
class XColor
{
private:
	Fl_Color cc; // 颜色值

public:
	enum XColorType
	{
		XCOLOR_RED = FL_RED,
		XCOLOR_GREEN = FL_GREEN,
		XCOLOR_BLUE = FL_BLUE,
		XCOLOR_YELLOW = FL_YELLOW,
		XCOLOR_WHITE = FL_WHITE,
		XCOLOR_BLACK = FL_BLACK
	};

	XColor(XColorType c=XCOLOR_RED) : cc(Fl_Color(c)) { }

	int ToInt() { return cc; }
};

// 形状
class XShape
{
private:
	XColor lineColor; // 线段颜色

protected:
	vector<XPoint> points; // 点集

public:
	XShape() : lineColor() {}

	// 添加点
	void AddPoint(XPoint point);
	// 修改某一点的值
	void SetPoint(int idx, XPoint point);
	// 设置线段颜色
	void SetLineColor(XColor c) { lineColor = c; }
	// 绘制图形（包括设置画笔颜色、绘出线段、恢复画笔的颜色）
	void Draw();

protected:
	// 绘制某一种具体图形（只有具体的类才能实现）
	// 注意：这是一个纯虚函数，在每一个非抽象子类中必须重新声明和定义此函数！
	virtual void DrawLines() = 0;
};

// 直线
class XLine : public XShape
{
public:
	// 直线包括两个点
	XLine(XPoint p1=XPoint(0, 0), XPoint p2=XPoint(0, 0));

	// 绘出直线
	void DrawLines();
};

//折线
class XPolyline :public XShape
{
public:
	XPolyline() {}
	XPolyline(initializer_list<XPoint> list);//折线构造函数
	virtual void DrawLines();
};

class XTriangle :public XPolyline
{
public:
	XTriangle() {}
	XTriangle(initializer_list<XPoint> list) :XPolyline(list) {}
	XTriangle(XPoint p1, XPoint p2, XPoint p3) { points.push_back(p1); points.push_back(p2); points.push_back(p3); }
	virtual void DrawLines();
	virtual void MoveLeft();
	virtual void MoveRight();
};

class XRectangle :public XTriangle
{
public:
	XRectangle(initializer_list<XPoint> list) :XTriangle(list) {}
	XRectangle(XPoint p1, XPoint p2, XPoint p3,XPoint p4) { points.push_back(p1); points.push_back(p2); points.push_back(p3); points.push_back(p4);
	}
	virtual void DrawLines();
	virtual void MoveLeft();
	virtual void MoveRight();
};
class XPolygon :public XRectangle
{
public:
	XPolygon(initializer_list<XPoint> list):XRectangle(list){}
	virtual void DrawLines();
};

class XCircle :public XShape
{
private:
	double radius;//半径
public:
	XCircle(XPoint p1,double r);
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void DrawLines();
};
#endif