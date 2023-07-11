//
// Created by Noy on 2023/7/10.
//

#include "app/Binder.h"

void Binder::bindWorld(WorldView &view, WorldViewModel &viewModel) {
    view.setBinderCameraPosition(viewModel.getBinderCameraPosition());
    view.setBinderLeftUpPosition(viewModel.getBinderLeftUpPosition());
    view.setBinderMaterialMatrix(viewModel.getBinderMaterialMatrix());
    view.setBinderTicks(viewModel.getBinderTicks());
    view.setBinderWeather(viewModel.getBinderWeather());
    viewModel.setNotificationWeatherChanged(view.getNotificationWeatherChanged());
}

void Binder::bindPlayer(PlayerView &view, PlayerViewModel &viewModel) {
    view.setCommandChangeCursorPosition(viewModel.getCommandChangeCursorPosition());
    view.setCommandChangeKeyState(viewModel.getCommandChangeKeyState());
    view.setCommandScrollMouseWheel(viewModel.getCommandScrollMouseWheel());
    view.setBinderPosition(viewModel.getBinderPosition());
    view.setBinderDirection(viewModel.getBinderDirection());
    view.setBinderVelocity(viewModel.getBinderVelocity());
    view.setBinderCurrentSlot(viewModel.getBinderCurrentSlot());
    view.setBinderSneaking(viewModel.getBinderSneaking());
    view.setBinderBreakingProgress(viewModel.getBinderBreakingProgress());
    viewModel.setNotificationLocationChanged(view.getNotificationLocationChanged());
    viewModel.setNotificationDirectionChanged(view.getNotificationDirectionChanged());
    viewModel.setNotificationVelocityChanged(view.getNotificationVelocityChanged());
    viewModel.setNotificationCurrentSlotChanged(view.getNotificationCurrentSlotChanged());
    viewModel.setNotificationSneakingStateChanged(view.getNotificationSneakingStateChanged());
    viewModel.setNotificationBreakingProgressChanged(view.getNotificationBreakingProgressChanged());
}
