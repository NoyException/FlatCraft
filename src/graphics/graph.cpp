
#include "graphics/graph.h"

DestroyBlock destroyBlock;
void graphMain(FlatCraft *game) {
	//int rW = GetSystemMetrics(SM_CXSCREEN); // ÆÁÄ»¿í¶È ÏñËØ
	//int rH = GetSystemMetrics(SM_CYSCREEN); // ÆÁÄ»¸ß¶È ÏñËØ
	//initgraph(rW, rH);
//	initgraph(1280, 768);
	Graph graph(game);
	graph.display();

}
void Graph::display() {
	//World* world = game->getPlayer()->getLocation().getWorld();
	World* world = FlatCraft::getInstance()->getWorld("test");
	
	while (true) {
//		BeginBatchDraw();
//		cleardevice();
//		IMAGE img;
//		loadimage(&img, _T("../../../src/graphics/textures/item/bell.png"), 400, 400);
//		fillcircle(600, 600, 40);
//		putimage(40, 40, &img);
//		EndBatchDraw();
	}
}