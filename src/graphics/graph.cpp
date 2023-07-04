#include <graphics.h>



void showGraph() {
	//int rW = GetSystemMetrics(SM_CXSCREEN); // ÆÁÄ»¿í¶È ÏñËØ
	//int rH = GetSystemMetrics(SM_CYSCREEN); // ÆÁÄ»¸ß¶È ÏñËØ
	//initgraph(rW, rH);
	initgraph(1280, 768);
	IMAGE img;
	loadimage(&img, _T("../../../src/graphics/textures/item/bell.png"), 400, 400);
	fillcircle(600, 600, 40);
	putimage(40, 40, &img);

}