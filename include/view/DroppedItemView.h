#ifndef _DROPPED_ITEM_VIEW_H_
#define _DROPPED_ITEM_VIEW_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mouse.h"
#include "common.h"
#include "view/EnitityView.h"

#define MYLOAD(path, name) \
do{	\
tempString = TEXTURES_PATH;\
tempString.append(path);\
pic = IMG_Load(tempString.c_str());\
name = SDL_CreateTextureFromSurface(renderer, pic);\
SDL_FreeSurface(pic);\
}while(0);

class DroppedItemView : public EntityView {
public:
	void setBinderMaterialStack(const std::function<void(RefPtr<MaterialStack>)>& binder);

	std::function<void()> getNotificationMaterialStackChanged();
	std::function<void()> getNotificationPickedUp();
	std::function<void()> getNotificationDisappeared();

private:
	MaterialStack* binderMaterialStack;

};






#endif // !_DROPPED_ITEM_VIEW_H_
