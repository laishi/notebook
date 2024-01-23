use std::collections::HashMap;

#[derive(Debug)]
struct HttpRequest {
    method: String,
    path: String,
    http_version: String,
    headers: HashMap<String, String>,
}

impl HttpRequest {
    fn from_str(msg: &str) -> Option<HttpRequest> {
        let mut lines = msg.lines();
        
        if let Some(request_line) = lines.next() {
            let mut parts = request_line.split_whitespace();
            let method = parts.next()?.to_string();
            let path = parts.next()?.to_string();
            let http_version = parts.next()?.to_string();
            
            let mut headers = HashMap::new();
            
            for line in lines {
                if line.trim().is_empty() {
                    break;
                }
                
                let mut header_parts = line.split(": ");
                if let (Some(name), Some(value)) = (header_parts.next(), header_parts.next()) {
                    headers.insert(name.to_string(), value.to_string());
                }
            }
            
            Some(HttpRequest {
                method,
                path,
                http_version,
                headers,
            })
        } else {
            None
        }
    }
}

fn main() {
    let msg = "GET / HTTP/1.1\n\
               Host: localhost:8080\n\
               Connection: keep-alive\n\
               Cache-Control: max-age=0\n\
               sec-ch-ua: \"Not_A Brand\";v=\"8\", \"Chromium\";v=\"120\", \"Microsoft Edge\";v=\"120\"\n\
               sec-ch-ua-mobile: ?0\n\
               sec-ch-ua-platform: \"Windows\"\n\
               Upgrade-Insecure-Requests: 1\n\
               User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36 Edg/120.0.0.0\n\
               Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\n\
               Sec-Fetch-Site: none\n\
               Sec-Fetch-Mode: navigate\n\
               Sec-Fetch-User: ?1\n\
               Sec-Fetch-Dest: document\n\
               Accept-Encoding: gzip, deflate, br\n\
               Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6";

    if let Some(request) = HttpRequest::from_str(msg) {
        // Print the value of 'Accept' header
        if let Some(accept_value) = request.headers.get("Accept") {
            println!("Value of 'Accept' header: {}", accept_value);
        } else {
            println!("'Accept' header not found");
        }

        println!("{:?}", request);
    } else {
        println!("Failed to parse HTTP request");
    }
}

