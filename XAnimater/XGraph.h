//
// ����FLTK 1.1.10��ͼ�ο������
// ͼ����
// XPoint���㣩
// XShape����״��
//   XLine��ֱ�ߣ�
// XColor����ɫ��
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
// Modified by ZhangHua @ 2015-11-09
//
// ��ͬѧ���ڴ��ļ������Լ���ͼ���ࡣ

#ifndef _XGRAPH_H_
#define _XGRAPH_H_

#include <vector>
#include <initializer_list>
using namespace std;

#include "FL/fl_draw.h"

// ��
class XPoint
{
public:
	int xx, yy; // �������ֵ

	XPoint(int x=0, int y=0) { xx=x; yy=y; }
};

// ��ɫ�����°�װFLTK�е���ɫ��
class XColor
{
private:
	Fl_Color cc; // ��ɫֵ

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

// ��״
class XShape
{
private:
	XColor lineColor; // �߶���ɫ

protected:
	vector<XPoint> points; // �㼯

public:
	XShape() : lineColor() {}

	// ��ӵ�
	void AddPoint(XPoint point);
	// �޸�ĳһ���ֵ
	void SetPoint(int idx, XPoint point);
	// �����߶���ɫ
	void SetLineColor(XColor c) { lineColor = c; }
	// ����ͼ�Σ��������û�����ɫ������߶Ρ��ָ����ʵ���ɫ��
	void Draw();

protected:
	// ����ĳһ�־���ͼ�Σ�ֻ�о���������ʵ�֣�
	// ע�⣺����һ�����麯������ÿһ���ǳ��������б������������Ͷ���˺�����
	virtual void DrawLines() = 0;
};

// ֱ��
class XLine : public XShape
{
public:
	// ֱ�߰���������
	XLine(XPoint p1=XPoint(0, 0), XPoint p2=XPoint(0, 0));

	// ���ֱ��
	void DrawLines();
};

//����
class XPolyline :public XShape
{
public:
	XPolyline() {}
	XPolyline(initializer_list<XPoint> list);//���߹��캯��
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
	double radius;//�뾶
public:
	XCircle(XPoint p1,double r);
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void DrawLines();
};
#endif