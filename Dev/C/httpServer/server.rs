use std::error::Error;
use std::fs::File;
use std::io::{self, Read};
use std::net::{TcpListener, TcpStream};
use std::path::Path;
use std::thread;
use std::time::Duration;

const DEFAULT_PORT: u16 = 8080;

struct CookieData {
    site: String,
    id: i32,
    login: String,
}

impl CookieData {
    fn new() -> Self {
        CookieData {
            site: "gald".to_string(),
            id: 385,
            login: "你已经成功登录".to_string(),
        }
    }
}

fn send_file(client_stream: &mut TcpStream, file_path: &str) -> Result<(), Box<dyn Error>> {
    let mut file = File::open(file_path)?;
    let mut buffer = [0; 1024];
    while let Ok(bytes_read) = file.read(&mut buffer) {
        if bytes_read == 0 {
            break;
        }
        client_stream.write_all(&buffer[..bytes_read])?;
    }
    Ok(())
}

fn get_http_date() -> String {
    let now = chrono::Utc::now();
    now.format("%a, %d %b %Y %H:%M:%S GMT").to_string()
}

fn handle_request(client_stream: TcpStream, cookie_data: &CookieData) -> Result<(), Box<dyn Error>> {
    let mut buffer = [0; 1024];
    let bytes_received = client_stream.peek(&mut buffer)?;
    if bytes_received > 0 {
        let request_str = String::from_utf8_lossy(&buffer[..bytes_received]);
        let cookie_header = request_str.lines().find(|line| line.contains("Cookie:"));

        let (method, path) = request_str
            .lines()
            .next()
            .ok_or("Invalid request")?
            .split_whitespace()
            .collect_tuple()
            .ok_or("Invalid request")?;

        let is_get = method == "GET";
        let mut request_path = Path::new("gald").to_owned();
        request_path.push(path);

        if path == "/" {
            request_path.push("index.html");
        }

        let content_type = match request_path.extension() {
            Some(ext) if ext == "html" => "text/html",
            Some(ext) if ext == "css" => "text/css",
            Some(ext) if ext == "js" => "application/js",
            Some(ext) if ext == "json" => "application/json",
            Some(ext) if ext == "jpg" || ext == "jpeg" => "image/jpeg",
            Some(ext) if ext == "png" => "image/png",
            _ => "text/plain",
        };

        let date_str = get_http_date();

        let response_header = format!(
            "HTTP/1.1 200 OK\r\n\
            Content-Type: {}\r\n\
            Date: {}\r\n\
            Set-Cookie: site={}; id={}; login={}; path=/; Max-Age=3600\r\n\
            Last-Modified: ...\r\n\
            Accept-Ranges: bytes\r\n\
            love: yes it is!\r\n\
            hi: hello world!\r\n\
            Content-Length: ...\r\n\r\n",
            content_type, date_str, cookie_data.site, cookie_data.id, cookie_data.login
        );

        let mut response = Vec::from(response_header.as_bytes());
        send_file(&mut response, request_path.to_str().ok_or("Invalid path")?)?;
        client_stream.write_all(&response)?;

        thread::sleep(Duration::from_millis(50)); // Ensure the response is sent before closing
    }

    Ok(())
}

fn handle_client(mut client_stream: TcpStream, cookie_data: &CookieData) {
    if let Err(err) = handle_request(client_stream.try_clone().unwrap(), cookie_data) {
        eprintln!("Error handling request: {}", err);
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let port = std::env::args()
        .nth(1)
        .and_then(|arg| arg.parse().ok())
        .unwrap_or(DEFAULT_PORT);

    let listener = TcpListener::bind(format!("127.0.0.1:{}", port))?;
    println!("Server listening on http://127.0.0.1:{}", port);

    let cookie_data = CookieData::new();

    for stream in listener.incoming() {
        match stream {
            Ok(client_stream) => {
                let cookie_data_clone = cookie_data.clone();
                thread::spawn(move || handle_client(client_stream, &cookie_data_clone));
            }
            Err(err) => eprintln!("Error accepting connection: {}", err),
        }
    }

    Ok(())
}

