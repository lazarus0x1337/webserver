<h1 align="center">Webserv</h1>

### This is when you finally understand why a URL starts with HTTP 🚀

---

## 📖 About the Project

Webserv is a lightweight, high-performance HTTP/1.1 server built from scratch in C++. Inspired by NGINX, this project implements essential web server functionalities, including request parsing, response generation, CGI support, and handling various HTTP methods (GET, POST, DELETE). 

This project is a collaborative effort by:

- [@oussamaGUN](https://github.com/oussamaGUN)
- [@soufianeajai](https://github.com/soufianeajai)
- [@lazarus0x1337](https://github.com/lazarus0x1337) 

---

## 🌟 Features

- **HTTP/1.1 Compliance:** Handles persistent connections, chunked transfers, and correct status codes.This ensures efficient communication and compatibility with modern web standards.
- **HTTP Methods** : Fully supports GET, POST, and DELETE methods, ensuring compliance with common web standards.
- **CGI Support:** Execute scripts like PHP, Python, or other CGI programs. Supports handling infinite loops with a response timeout mechanism to avoid server hang-ups.
- **Custom Configuration:**  yml-style configuration for servers, locations, and error pages.
- **Error Handling:** Supports custom error pages for common HTTP errors. with support for server_name directives to differentiate requests by hostname.
- **Multi-Server Support:** Host multiple domains and configurations on a single server instance.
- **Security Features:** Input validation, limited body size, and request timeout handling to protect against malicious or oversized requests.
- **Non-Blocking I/O:** Utilizes epoll for efficient, non-blocking handling of multiple simultaneous connections, improving scalability and performance.
 

---

## 🛠️ Installation

1. Clone the repository:
   ```bash
     git clone https://github.com/your-github-username/webserv.git
     cd webserv
    ./webserv configFiles/default.config
