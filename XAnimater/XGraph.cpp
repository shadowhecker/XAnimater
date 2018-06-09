//
// ����FLTK 1.1.10��ͼ�ο������
// ͼ�����ʵ��
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
// Modified by ZhangHua @ 2015-11-09
//
// ��ͬѧ���ڴ��ļ������Զ���ͼ�����ʵ�ִ��롣

#include "XGraph.h"

#include <FL/Fl.H>
//#include <FL/Fl_Window.H>
#include <FL/fl_draw.h>

void XShape::AddPoint(XPoint point)
{
	// �ѵ���ӵ��㼯
	points.push_back(point);
}

void XShape::SetPoint(int idx, XPoint point)
{
	// �޸ĵ㼯�е�ָ����
	if (idx>=0 && idx<points.size())
	{
		points[idx] = point;
	}
}

void XShape::Draw()
{
	// ���û��ʵ���ɫ
	fl_color(lineColor.ToInt());

	// ���ͼ��
	DrawLines();

	// �ָ����ʵ���ɫ
	XColor defaultColor;
	fl_color(defaultColor.ToInt());
}

XLine::XLine(XPoint p1, XPoint p2)
{
	// ��ֱ�ߵ���������ӵ��㼯��
	AddPoint(p1);
	AddPoint(p2);
}

void XLine::DrawLines()
{
	// ʹ��FLTK�еĻ��ߺ�������ֱ��
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
