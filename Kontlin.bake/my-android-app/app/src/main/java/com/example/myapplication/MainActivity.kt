package com.example.myapplication

import android.os.Bundle
import android.widget.ArrayAdapter
import android.widget.ListView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // 获取 ListView
        val listView: ListView = findViewById(R.id.listView)

        // 示例数据
        val items = arrayOf("Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 1", "Item 2", "Item 3", "Item 4", "Item 5")

        // 创建 ArrayAdapter
        val adapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, items)

        // 设置 Adapter
        listView.adapter = adapter
    }
}

