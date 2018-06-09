//
// ����FLTK 1.1.10��ͼ����������
// �������ʵ��
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
//
// ����������¹��ܣ��Ͳ����޸Ĵ��ļ��еĴ��롣

#include "XWindow.h"

void XWindow::Add(XShape& shape)
{
	shapes.push_back(&shape);
}

void XWindow::Clear()
{
	shapes.clear();
}

void XWindow::draw()
{
	Fl_Window::draw();

	for (int i=0; i<shapes.size(); i++)
	{
		shapes[i]->Draw();
	}
}

void XInteractiveWindow::WaitForClick()
{
	while (!buttonClicked) Fl::wait();
	buttonClicked = false;
	Fl::redraw();
}

void XInteractiveWindow::Delay(unsigned ms)
{
	Fl::wait();
	Sleep(ms);
	Fl::redraw();
}

void XInteractiveWindow::CbNext(Fl_Widget* pWidget, void*)
{
	if (pWidget)
	{
		void* pWnd = pWidget->window();
		if (pWnd)
		{
			((XInteractiveWindow*)pWnd)->Next();
		}
	}
}
