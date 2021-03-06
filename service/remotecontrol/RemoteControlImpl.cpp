/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *  @author   yongguang.hong
 *  @version  1.0
 *  @date     2018/03/19
 *  @par function description:
 *  - 1 bluetooth rc server
 */

#define LOG_TAG "RemoteControlImpl"

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <fcntl.h>
#include <utils/Log.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#include "RemoteControlServer.h"
#include "RemoteControlImpl.h"

RemoteControlImpl::RemoteControlImpl()
    : mCallbacks(NULL)
    , mRemoteControl(NULL)
{
    //configureRpcThreadpool(1, false);
    mRemoteControl = new RemoteControl(*this);
    if (mRemoteControl->registerAsService() != OK) {
        ALOGE("Cannot register IRemoteControl service!!!");
    }
}

RemoteControlImpl::~RemoteControlImpl() {
    mRemoteControl = NULL;
}

void RemoteControlImpl::setCallback(rc_callbacks_t *rcCallback) {
    mCallbacks = rcCallback;
}

void RemoteControlImpl::onSetMicEnable(int flag) {
    if (mCallbacks != NULL && mCallbacks->setMicStatusCb != NULL)
        mCallbacks->setMicStatusCb(flag);
}

void RemoteControlImpl::onDeviceStatusChanged(int flag) {
    if (mCallbacks != NULL && mCallbacks->onDeviceStatusCb != NULL)
        mCallbacks->onDeviceStatusCb(flag);
}



