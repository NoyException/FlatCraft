#include "view/DroppedItemView.h"

void DroppedItemView::setBinderMaterialStack(const std::function<void(RefPtr<MaterialStack>)>& binder) {
	binder(binderMaterialStack);
}

std::function<void()> DroppedItemView::getNotificationMaterialStackChanged() {
	return [&]() {

	};
}
std::function<void()> DroppedItemView::getNotificationPickedUp() {
	return [&]() {

	};
}

std::function<void()> DroppedItemView::getNotificationDisappeared() {
	return [&]() {

	};
}