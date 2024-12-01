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

- **HTTP/1.1 Compliance:** Handles persistent connections, chunked transfers, and correct status codes.
- **CGI Support:** Execute scripts like PHP, Python, or other CGI programs.
- **Custom Configuration:** Mimics NGINX-style configuration for servers, locations, and error pages.
- **Error Handling:** Supports custom error pages for common HTTP errors.
- **Multi-Server Support:** Host multiple domains and configurations on a single server instance.
- **Security Features:** Input validation, limited body size, and request timeout handling.

---

## 🛠️ Installation

1. Clone the repository:
   ```bash
     git clone https://github.com/your-github-username/webserv.git
     cd webserv
    ./webserv configFiles/default.config
