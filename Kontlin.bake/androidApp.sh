#!/bin/bash

# 目录设置
PROJECT_DIR="/home/ruhua/Demo/Android/Kontlin/initapp"
MIPMAP_DIR="/home/ruhua/Demo/Android/Kontlin/mipmap"

# 删除旧目录（如果存在）
if [ -d "$PROJECT_DIR" ]; then
    echo "Removing existing project directory: $PROJECT_DIR"
    rm -rf "$PROJECT_DIR"
fi

# 创建新的项目目录
echo "Creating new project directory: $PROJECT_DIR"
mkdir -p "$PROJECT_DIR/app/src/main/java/com/example/hello"
mkdir -p "$PROJECT_DIR/app/src/main/res/layout"
mkdir -p "$PROJECT_DIR/app/src/main/res/values"
mkdir -p "$PROJECT_DIR/app/src/test/java/com/example/hello"

# 切换到父目录并生成 Gradle Wrapper
cd /home/ruhua/Demo/Android/Kontlin
gradle wrapper

# 确保 gradlew 文件存在
if [ ! -f "gradlew" ]; then
    echo "Gradle wrapper script not found. Please ensure 'gradle wrapper' has been executed in the correct directory."
    exit 1
fi

# 创建 build.gradle.kts 文件
cat <<EOL > "$PROJECT_DIR/app/build.gradle.kts"
plugins {
    id("com.android.application") version "8.0.2"
    id("org.jetbrains.kotlin.android") version "1.9.24"
}

android {
    compileSdk = 33

    defaultConfig {
        applicationId = "com.example.hello"
        minSdk = 21
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"
    }

    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }
}

repositories {
    google()
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-stdlib:1.9.24")
    implementation("androidx.core:core-ktx:1.9.0")
    implementation("androidx.appcompat:appcompat:1.6.1")
    implementation("com.google.android.material:material:1.9.0")
    implementation("androidx.constraintlayout:constraintlayout:2.1.4")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}
EOL

# 创建 settings.gradle.kts 文件
cat <<EOL > "$PROJECT_DIR/settings.gradle.kts"
rootProject.name = "initapp"
include(":app")
EOL

# 创建 AndroidManifest.xml 文件
cat <<EOL > "$PROJECT_DIR/app/src/main/AndroidManifest.xml"
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.example.hello">
    <application
        android:allowBackup="true"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.MyApplication">
        <activity android:name=".MainActivity">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>
</manifest>
EOL

# 创建 MainActivity.kt 文件
cat <<EOL > "$PROJECT_DIR/app/src/main/java/com/example/hello/MainActivity.kt"
package com.example.hello

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.tooling.preview.Preview
import com.example.hello.ui.theme.MyApplicationTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MyApplicationTheme {
                Greeting("Android")
            }
        }
    }
}

@Composable
fun Greeting(name: String) {
    Text(text = "Hello $name!")
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    MyApplicationTheme {
        Greeting("Android")
    }
}
EOL

# 创建 activity_main.xml 文件
cat <<EOL > "$PROJECT_DIR/app/src/main/res/layout/activity_main.xml"
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    tools:context=".MainActivity">

    <TextView
        android:id="@+id/text_view"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="Hello World!" />
</RelativeLayout>
EOL

# 创建 strings.xml 文件
cat <<EOL > "$PROJECT_DIR/app/src/main/res/values/strings.xml"
<resources>
    <string name="app_name">MyApplication</string>
</resources>
EOL

# 创建 styles.xml 文件
cat <<EOL > "$PROJECT_DIR/app/src/main/res/values/styles.xml"
<resources>
    <style name="Theme.MyApplication" parent="Theme.Material3.DayNight.NoActionBar">
        <!-- Primary colors -->
        <item name="colorPrimary">@color/teal_200</item>
        <item name="colorPrimaryVariant">@color/teal_700</item>
        <item name="colorOnPrimary">@android:color/white</item>

        <!-- Secondary colors -->
        <item name="colorSecondary">@color/orange_500</item>
        <item name="colorSecondaryVariant">@color/orange_700</item>
        <item name="colorOnSecondary">@android:color/white</item>

        <!-- Background and text colors -->
        <item name="colorBackground">@android:color/white</item>
        <item name="colorOnBackground">@android:color/black</item>
    </style>
</resources>
EOL

# 检查并删除 mipmap 目录（如果存在）
if [ -d "$MIPMAP_DIR" ]; then
    echo "Removing existing mipmap directory: $MIPMAP_DIR"
    rm -rf "$MIPMAP_DIR"
fi

# 复制 mipmap 资源
if [ -d "$MIPMAP_DIR" ]; then
    echo "Copying mipmap resources to $PROJECT_DIR/app/src/main/res/"
    cp -r "$MIPMAP_DIR" "$PROJECT_DIR/app/src/main/res/"
else
    echo "Mipmap directory does not exist: $MIPMAP_DIR"
fi

echo "Android app project setup is complete."

