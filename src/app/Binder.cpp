//
// Created by Noy on 2023/7/10.
//

#include "app/Binder.h"

void Binder::bindWorld(WorldView &view, WorldViewModel &viewModel) {
    view.setBinderCameraPosition(viewModel.getBinderCameraPosition());
    view.setBinderLeftUpPosition(viewModel.getBinderLeftUpPosition());
    view.setBinderMaterialMatrix(viewModel.getBinderMaterialMatrix());
    ////view.setCommandPause();
    view.setBinderTicks(viewModel.getBinderTicks());
    view.setBinderWeather(viewModel.getBinderWeather());
    viewModel.setNotificationWeatherChanged(view.getNotificationWeatherChanged());
    viewModel.notifyBound();
}

void Binder::bindEntity(EntityView &view, EntityViewModel &viewModel) {
    view.setBinderPosition(viewModel.getBinderPosition());
    view.setBinderDirection(viewModel.getBinderDirection());
    view.setBinderVelocity(viewModel.getBinderVelocity());
    viewModel.setNotificationPositionChanged(view.getNotificationPositionChanged());
    viewModel.setNotificationDirectionChanged(view.getNotificationDirectionChanged());
    viewModel.setNotificationVelocityChanged(view.getNotificationVelocityChanged());
}

void Binder::bindPlayer(PlayerView &view, PlayerViewModel &viewModel) {
    bindEntity(view, viewModel);
    view.setCommandChangeCursorPosition(viewModel.getCommandChangeCursorPosition());
    view.setCommandChangeKeyState(viewModel.getCommandChangeKeyState());
    view.setCommandScrollMouseWheel(viewModel.getCommandScrollMouseWheel());
    view.setCommandClickedSlot(viewModel.getCommandClickedSlot());
    view.setBinderCurrentSlot(viewModel.getBinderCurrentSlot());
    view.setBinderSneaking(viewModel.getBinderSneaking());
    view.setBinderBreakingBlock(viewModel.getBinderBreakingBlock());
    view.setBinderCursor(viewModel.getBinderCursor());
    view.setBinderInventory(viewModel.getBinderInventory());
    viewModel.setNotificationCurrentSlotChanged(view.getNotificationCurrentSlotChanged());
    viewModel.setNotificationSneakingStateChanged(view.getNotificationSneakingStateChanged());
    viewModel.setNotificationBreakingBlockChanged(view.getNotificationBreakingBlockChanged());
    viewModel.setNotificationCursorChanged(view.getNotificationCursorChanged());
    viewModel.setNotificationInventoryChanged(view.getNotificationInventoryChanged());
    viewModel.notifyBound();
}

void Binder::bindDroppedItem(DroppedItemView &view, DroppedItemViewModel &viewModel) {
    bindEntity(view, viewModel);
    view.setBinderMaterialStack(viewModel.getBinderMaterialStack());
    viewModel.setNotificationMaterialStackChanged(view.getNotificationMaterialStackChanged());
    viewModel.setNotificationPickedUp(view.getNotificationPickedUp());
    viewModel.setNotificationDisappeared(view.getNotificationDisappeared());
    viewModel.notifyBound();
}
