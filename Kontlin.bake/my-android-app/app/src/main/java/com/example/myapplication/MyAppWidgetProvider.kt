package com.example.myapplication

import android.app.PendingIntent
import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.Context
import android.content.Intent
import android.widget.RemoteViews

class MyAppWidgetProvider : AppWidgetProvider() {
    override fun onUpdate(context: Context, appWidgetManager: AppWidgetManager, appWidgetIds: IntArray) {
        for (appWidgetId in appWidgetIds) {
            val intent = Intent(context, MainActivity::class.java)
            val pendingIntent = PendingIntent.getActivity(context, 0, intent, 0)

            // 更新 Widget 布局
            val views = RemoteViews(context.packageName, R.layout.my_appwidget)
            views.setOnClickPendingIntent(R.id.appwidget_text, pendingIntent)

            // 更新 Widget
            appWidgetManager.updateAppWidget(appWidgetId, views)
        }
    }
}

