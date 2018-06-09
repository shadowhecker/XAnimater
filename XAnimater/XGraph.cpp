//
// 基于FLTK 1.1.10的图形库基础版
// 图形类的实现
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
// Modified by ZhangHua @ 2015-11-09
//
// 请同学们在此文件增加自定义图形类的实现代码。

#include "XGraph.h"

#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
#include <FL/fl_draw.h>

void XShape::AddPoint(XPoint point)
{
	// 把点添加到点集
	points.push_back(point);
}

void XShape::SetPoint(int idx, XPoint point)
{
	// 修改点集中的指定点
	if (idx>=0 && idx<points.size())
	{
		points[idx] = point;
	}
}

void XShape::Draw()
{
	// 设置画笔的颜色
	fl_color(lineColor.ToInt());

	// 绘出图形
	DrawLines();

	// 恢复画笔的颜色
	XColor defaultColor;
	fl_color(defaultColor.ToInt());
}

XLine::XLine(XPoint p1, XPoint p2)
{
	// 把直线的两个点添加到点集中
	AddPoint(p1);
	AddPoint(p2);
}

void XLine::DrawLines()
{
	// 使用FLTK中的绘线函数画出直线
	fl_line(points[0].xx, points[0].yy, points[1].xx, points[1].yy);
}

XPolyline::XPolyline(initializer_list<XPoint> list)
{
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		points.push_back(*iter);
	}
}

void XPolyline::DrawLines()
{
	for (auto iter = points.begin(); iter != points.end() - 1; ++iter)
		fl_line((*iter).xx, (*iter).yy, (*(iter + 1)).xx, (*(iter + 1)).yy);
}

void XTriangle::DrawLines()
{
	fl_line(points[0].xx, points[0].yy, points[1].xx, points[1].yy);
	fl_line(points[1].xx, points[1].yy, points[2].xx, points[2].yy);
	fl_line(points[2].xx, points[2].yy, points[0].xx, points[0].yy);
}

void XTriangle::MoveLeft()
{
	for (auto idx = 0; idx != points.size(); ++idx)
		SetPoint(idx, XPoint(points[idx].xx - 1, points[idx].yy));
}

void XTriangle::MoveRight()
{
	for (auto idx = 0; idx != points.size(); ++idx)
		SetPoint(idx, XPoint(points[idx].xx + 1, points[idx].yy));
}

void XRectangle::DrawLines()
{
	auto iter = points.begin();
	for (auto iter = points.begin(); iter != points.end() - 1; ++iter)
		fl_line((*iter).xx, (*iter).yy, (*(iter + 1)).xx, (*(iter + 1)).yy);
	fl_line(points[points.size()-1].xx, points[points.size() - 1].yy, points[0].xx, points[0].yy);
}

void XRectangle::MoveLeft()
{
	XTriangle::MoveLeft();
}

void XRectangle::MoveRight()
{
	XTriangle::MoveRight();
}

void XPolygon::DrawLines()
{
	XRectangle::DrawLines();
}

XCircle::XCircle(XPoint p1,double r)
{
	points.push_back(p1);
	radius = r;
}

void XCircle::MoveLeft()
{
	SetPoint(0, XPoint(points[0].xx - 1, points[0].yy));
}

void XCircle::MoveRight()
{
	SetPoint(0, XPoint(points[0].xx + 1, points[0].yy));
}

void XCircle::DrawLines()
{
	fl_circle(points[0].xx, points[0].yy, radius);
}
