#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    // 初始化 libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 创建一个 CURL 句柄
    curl = curl_easy_init();
    if(curl) {
        // 设置请求的 URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/index.html");

        // 执行 HTTP GET 请求
        res = curl_easy_perform(curl);

        // 检查执行结果
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        // 清理资源
        curl_easy_cleanup(curl);
    }

    // 全局清理
    curl_global_cleanup();

    return 0;
}

