//
// ����FLTK 1.1.10��ͼ����������
// ������
// XWindow(��ͼ����)
//   XInteractiveWindow����һ����ť�Ľ������ڣ�
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
//
// ����������¹��ܣ��Ͳ����޸Ĵ��ļ��еĴ��롣

#ifndef _XWINDOW_H_
#define _XWINDOW_H_

#include <vector>
using namespace std;

#include <windows.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "XGraph.h"

// ��ͼ����
//   �������ͼ�ζ��󣬲�������Щͼ�ζ���
class XWindow : public Fl_Window
{
private:
	vector<XShape*> shapes; // ��״��

public:
	XWindow(int w, int h, char* c=0) : Fl_Window(w, h, c) {}

protected:
	// ��д�����еĶ�Ӧ���������ͼ�εĻ���
	void draw();

public:
	// �����״��ע���������������
	void Add(XShape& shape);
	// ��մ���
	void Clear();
};


#include <FL/Fl_Button.H>

// ����ʽ��ͼ����
//   ����һ����ť��Ϊ�����ṩ�򵥵Ľ�������
class XInteractiveWindow : public XWindow
{
private:
	Fl_Button button; // ����һ������ť
	bool buttonClicked; // ����һ������ť�Ƿ񱻵���

public:
	XInteractiveWindow(int w, int h, char* c=0) : XWindow(w, h, c),
		button(w-70, 0, 70, 20, "��һ��"), buttonClicked(false)
	{
		// ������Ӧ��������һ������ť�¼��Ļص�����
		button.callback(CbNext);
	}

	// �ڵ�������һ������ť֮ǰ���ִ��ڣ���ͣ������ǿ���ػ�����
	void WaitForClick();

	// ��ʱms����
	void Delay(unsigned ms);

	// �Ե�������һ������ť�¼��Ĵ���
	void Next()
	{
		buttonClicked = true;
	}

	// ����һ������ť�¼��Ļص�����
	static void CbNext(Fl_Widget* pWidget, void*);
};

#endif