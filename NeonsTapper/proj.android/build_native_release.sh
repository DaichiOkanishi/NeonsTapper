#!/bin/bash

APPNAME="neonsTapper"

# options
date +"%y/%m/%d %H:%M" > ../Resources/built.date

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-h	this help
EOF
}

while getopts "sh" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
h)
usage
exit 0
;;
esac
done

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "please define NDK_ROOT"
exit 1
fi

if [ -z "${ANDROID_SDK_ROOT+aaa}" ];then
echo "please define ANDROID_SDK_ROOT"
exit 1
fi

# jarファイルをコピー
if [ ! -d libs ];then
	mkdir libs
fi
cp $ANDROID_SDK_ROOT/extras/google/google_play_services/libproject/google-play-services_lib/libs/google-play-services.jar libs/google-play-services.jar
cp $ANDROID_SDK_ROOT/extras/android/support/v4/android-support-v4.jar libs/android-support-v4.jar
cp ./ext/analytics_sdk_v1_1_0.jar libs/analytics_sdk_v1_1_0.jar
cp ./ext/smartbeat-android-1.10.jar libs/smartbeat-android-1.10.jar

# google play serviceのバージョンファイルをコピー
if [ ! -d res ];then
    mkdir res
fi
if [ ! -d res/values ];then
    mkdir res/values
fi
cp $ANDROID_SDK_ROOT/extras/google/google_play_services/libproject/google-play-services_lib/res/values/version.xml res/values/version.xml

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
COCOS2DX_ROOT="$DIR/../../cocos2d-x"
APP_ROOT="$DIR/.."
APP_ANDROID_ROOT="$DIR"

echo "NDK_ROOT = $NDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"

# make sure assets is exist
if [ -d "$APP_ANDROID_ROOT"/assets ]; then
    rm -rf "$APP_ANDROID_ROOT"/assets
fi

mkdir "$APP_ANDROID_ROOT"/assets

# copy resources
for file in "$APP_ROOT"/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi
if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

# 必要なリソースのみをコピーする
# ruby copy_resource.rb

# copy resources
for file in "$APP_ROOT"/Resources.android/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_ANDROID_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_ANDROID_ROOT"/assets
fi
done

# run ndk-build
if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    "$NDK_ROOT"/ndk-build APP_OPTIM=release -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source"
else
    echo "Using prebuilt externals"
    "$NDK_ROOT"/ndk-build APP_OPTIM=release -C "$APP_ANDROID_ROOT" $* \
        "NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt"
fi
