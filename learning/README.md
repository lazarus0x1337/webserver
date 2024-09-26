

















### What is CGI?

The Common Gateway Interface, or CGI, is a set of standards that define how information is exchanged between the web server and a custom script
is a standard for external gateway programs to interface with information servers such as HTTP servers.

The Common Gateway Interface (CGI) is a standard protocol for enabling applications (called CGI programs or CGI scripts) to interact with Web servers and with clients. These CGI programs can be a written in Python, PERL, Shell, C or C++ etc.

specification was introduced to enable and standardize the interface between Web servers and external programs.

more info : [CGI INFO IN C++](https://tutorialspoint.com/cplusplus/cpp_web_programming.htm)

GET and POST Methods
You must have come across many situations when you need to pass some information from your browser to web server and ultimately to your CGI Program. Most frequently browser uses two methods to pass this information to web server. These methods are GET Method and POST Method.

### GET Method

The GET method sends the encoded user information appended to the page request. The page and the encoded information are separated by the ? character as follows −
-> "http://www.test.com/cgi-bin/cpp.cgi?key1=value1&key2=value2"


Below is a program to generate cpp_get.cgi CGI program to handle input given by web browser. We are going to use C++ CGI library which makes it very easy to access passed information 

example : "/cgi-bin/cpp_get.cgi?first_name=ZARA&last_name=ALI"

```c++
#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  

using namespace std;
using namespace cgicc;

int main () {
   Cgicc formData;
   
   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Using GET and POST Methods</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";

   form_iterator fi = formData.getElement("first_name");  
   if( !fi->isEmpty() && fi != (*formData).end()) {  
      cout << "First name: " << **fi << endl;  
   } else {
      cout << "No text entered for first name" << endl;  
   }
   
   cout << "<br/>\n";
   fi = formData.getElement("last_name");  
   if( !fi->isEmpty() &&fi != (*formData).end()) {  
      cout << "Last name: " << **fi << endl;  
   } else {
      cout << "No text entered for last name" << endl;  
   }
   
   cout << "<br/>\n";
   cout << "</body>\n";
   cout << "</html>\n";
   
   return 0;
}
```







