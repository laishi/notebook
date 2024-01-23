import requests

url = "http://127.0.0.1:8080/index.html"
headers = {
    "Custom-Content-Preference": "high-quality",
    "User-Agent": "Your User Agent",  # 添加必要的其他请求头
}

response = requests.get(url, headers=headers)

# 处理响应...

