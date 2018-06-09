//
// 基于FLTK 1.1.10的图形类库的测试程序
//
// Created by ZhangHua @ 2011-04-27
// Modified by ZhangHua @ 2014-11-11
//
// 请同学们在此文件中增加自己的动画脚本代码。

#include "XWindow.h"

void draw_test(XInteractiveWindow& window);
void draw_test2(XInteractiveWindow& window);
int main(int argc, char **argv) {
	// 创建并显示交互式的绘图窗口
	const char *c = "简易动画制作程序（演示版）";
	XInteractiveWindow window(600, 400, const_cast<char *>(c));
	window.show(argc, argv);

	// 等待单击“下一步”按钮后继续，实现暂停功能
	window.WaitForClick();

	// 创建一条直线
	draw_test2(window);
	window.Clear();
	draw_test(window);
}

void draw_test(XInteractiveWindow& window)
{
	XPoint p(200, 50);//基准点
	XTriangle xtriangle = { p,XPoint(p.xx-30,p.yy+100),XPoint(p.xx + 30,p.yy + 100) };
	window.Add(xtriangle);
	XRectangle xrectangle= { XPoint(p.xx - 25,p.yy + 101),XPoint(p.xx - 25,p.yy + 201),XPoint(p.xx + 25,p.yy + 201),XPoint(p.xx + 25,p.yy + 101) };
	xrectangle.SetLineColor(XColor::XCOLOR_BLUE);
	window.Add(xrectangle);
	XRectangle xrectangle2 = { XPoint(p.xx - 100,p.yy + 202),XPoint(p.xx - 100,p.yy + 232),XPoint(p.xx + 100,p.yy + 232),XPoint(p.xx + 100,p.yy + 202) };
	xrectangle2.SetLineColor(XColor::XCOLOR_GREEN);
	window.Add(xrectangle2);
	XPolygon xpolygon = { XPoint(p.xx + 150,p.yy + 112), XPoint(p.xx + 120,p.yy + 142),XPoint(p.xx + 117,p.yy + 162),XPoint(p.xx + 120,p.yy + 182),XPoint(p.xx + 143,p.yy + 202),XPoint(p.xx + 173,p.yy + 210),XPoint(p.xx + 193,p.yy + 202),XPoint(p.xx + 203,p.yy + 172),XPoint(p.xx + 193,p.yy + 142),XPoint(p.xx + 183,p.yy + 122),XPoint(p.xx + 163,p.yy + 114) };
	xpolygon.SetLineColor(XColor::XCOLOR_GREEN);
	window.Add(xpolygon);
	XRectangle xrectangle3 = { XPoint(p.xx + 145,p.yy + 210),XPoint(p.xx +145,p.yy + 232),XPoint(p.xx + 173, p.yy + 232),XPoint(p.xx + 173, p.yy + 210) };
	window.Add(xrectangle3);
	window.WaitForClick();
}

void draw_test2(XInteractiveWindow& window)
{
	XPoint p(100, 80);//基准点
	double radius = 30;
	double radius2 = 21;
	XCircle xcircle(p, radius);
	window.Add(xcircle);
	XCircle xcircle2(XPoint(p.xx - radius * 2 / 3, p.yy), radius / 3);
	window.Add(xcircle2);
	XCircle xcircle3(XPoint(p.xx + radius * 2 / 3, p.yy), radius / 3);
	window.Add(xcircle3);
	XRectangle xrectangle = { XPoint(p.xx - radius-15,p.yy + radius),XPoint(p.xx - radius - 15,p.yy + radius+150),XPoint(p.xx + radius+15,p.yy + radius + 150),XPoint(p.xx + radius + 15,p.yy + radius) };
	xrectangle.SetLineColor(XColor::XCOLOR_BLUE);
	window.Add(xrectangle);
	XCircle xcircle4(XPoint(p.xx - radius - 15+ radius2, p.yy + radius + 150+radius2), radius2);
	window.Add(xcircle4);
	XCircle xcircle5(XPoint(p.xx + radius + 15 - radius2, p.yy + radius + 150 + radius2), radius2);
	window.Add(xcircle5);
	window.WaitForClick();
	while (p.xx != 300)
	{
		xcircle.MoveRight();
		xcircle2.MoveRight();
		xcircle3.MoveRight();
		xcircle4.MoveRight();
		xcircle5.MoveRight();
		xrectangle.MoveRight();
		++p.xx;
		window.Delay(50);
	}
	window.WaitForClick();
}