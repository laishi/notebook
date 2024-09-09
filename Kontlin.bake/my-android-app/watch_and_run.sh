#!/bin/bash

# 编译项目
./gradlew assembleDebug

# 检查 APK 是否已经安装
if adb shell pm list packages | grep -q "com.example.myapplication"; then
    echo "App is already installed."

    # 获取当前设备上的版本号
    DEVICE_VERSION=$(adb shell dumpsys package com.example.myapplication | grep versionCode | awk '{print $1}' | cut -d'=' -f2)
    LOCAL_VERSION=$(aapt dump badging app/build/outputs/apk/debug/app-debug.apk | grep versionCode | awk '{print $2}' | cut -d'=' -f2)

    if [ "$DEVICE_VERSION" != "$LOCAL_VERSION" ]; then
        echo "New version detected, installing APK..."
        adb install -r app/build/outputs/apk/debug/app-debug.apk
    else
        echo "App is up-to-date, skipping installation."
    fi
else
    # 如果应用没有安装，直接安装
    echo "App not found, installing APK..."
    adb install app/build/outputs/apk/debug/app-debug.apk
fi

# 启动应用
adb shell am start -n com.example.myapplication/.MainActivity

