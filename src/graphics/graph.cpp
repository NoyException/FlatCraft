#include <graphics.h>



void showGraph() {
	//int rW = GetSystemMetrics(SM_CXSCREEN); // ��Ļ��� ����
	//int rH = GetSystemMetrics(SM_CYSCREEN); // ��Ļ�߶� ����
	//initgraph(rW, rH);
	initgraph(1280, 768);
	IMAGE img;
	loadimage(&img, _T("../../../src/graphics/textures/item/bell.png"), 400, 400);
	fillcircle(600, 600, 40);
	putimage(40, 40, &img);

}