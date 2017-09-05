/*
 * Copyright (C) 2017 The Android Open Source Project
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
 */

#define LOG_TAG "VintfRuntimeInfo"
//#define LOG_NDEBUG 0

#include <nativehelper/JNIHelp.h>
#include <vintf/VintfObject.h>
#include <vintf/parse_string.h>
#include <vintf/parse_xml.h>

#include "core_jni_helpers.h"

namespace android {

using vintf::RuntimeInfo;
using vintf::VintfObject;

#define MAP_STRING_METHOD(javaMethod, cppString)                                       \
    static jstring android_os_VintfRuntimeInfo_##javaMethod(JNIEnv* env, jclass clazz) \
    {                                                                                  \
        std::shared_ptr<const RuntimeInfo> info = VintfObject::GetRuntimeInfo();       \
        if (info == nullptr) return nullptr;                                           \
        return env->NewStringUTF((cppString).c_str());                                 \
    }                                                                                  \

MAP_STRING_METHOD(getCpuInfo, info->cpuInfo());
MAP_STRING_METHOD(getOsName, info->osName());
MAP_STRING_METHOD(getNodeName, info->nodeName());
MAP_STRING_METHOD(getOsRelease, info->osRelease());
MAP_STRING_METHOD(getOsVersion, info->osVersion());
MAP_STRING_METHOD(getHardwareId, info->hardwareId());
MAP_STRING_METHOD(getKernelVersion, vintf::to_string(info->kernelVersion()));
MAP_STRING_METHOD(getBootAvbVersion, vintf::to_string(info->bootAvbVersion()));
MAP_STRING_METHOD(getBootVbmetaAvbVersion, vintf::to_string(info->bootVbmetaAvbVersion()));


static jlong android_os_VintfRuntimeInfo_getKernelSepolicyVersion(JNIEnv *env, jclass clazz)
{
    std::shared_ptr<const RuntimeInfo> info = VintfObject::GetRuntimeInfo();
    if (info == nullptr) return 0;
    return static_cast<jlong>(info->kernelSepolicyVersion());
}

// ----------------------------------------------------------------------------

static const JNINativeMethod gVintfRuntimeInfoMethods[] = {
    {"getKernelSepolicyVersion", "()J", (void*)android_os_VintfRuntimeInfo_getKernelSepolicyVersion},
    {"getCpuInfo", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getCpuInfo},
    {"getOsName", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getOsName},
    {"getNodeName", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getNodeName},
    {"getOsRelease", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getOsRelease},
    {"getOsVersion", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getOsVersion},
    {"getHardwareId", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getHardwareId},
    {"getKernelVersion", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getKernelVersion},
    {"getBootAvbVersion", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getBootAvbVersion},
    {"getBootVbmetaAvbVersion", "()Ljava/lang/String;", (void*)android_os_VintfRuntimeInfo_getBootVbmetaAvbVersion},
};

const char* const kVintfRuntimeInfoPathName = "android/os/VintfRuntimeInfo";

int register_android_os_VintfRuntimeInfo(JNIEnv* env)
{
    return RegisterMethodsOrDie(env, kVintfRuntimeInfoPathName, gVintfRuntimeInfoMethods, NELEM(gVintfRuntimeInfoMethods));
}

};
