# import http.server
# import socketserver
# import os

# PORT = 8000

# web_dir = os.path.join(os.path.dirname(__file__), 'dist')
# os.chdir(web_dir)

# Handler = http.server.SimpleHTTPRequestHandler
# httpd = socketserver.TCPServer(("", PORT), Handler)
# print("serving at port", PORT)
# httpd.serve_forever()


import http.server
import socketserver
import os

class MyHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.tools = Tools()  # Utwórz instancję klasy Tools

    def do_GET(self):
        if self.path == "/dupa":
            self._handle_dupa()
        else:
            super().do_GET()

    def _handle_dupa(self):
        # Tutaj możesz wywołać funkcję z klasy Tools
        self.tools.your_function()  # Zamień 'your_function' na nazwę właściwej funkcji

# Ustawienia serwera
PORT = 8000
web_dir = os.path.join(os.path.dirname(__file__), 'dist')
os.chdir(web_dir)

Handler = MyHandler  # Użyj naszej własnej klasy obsługującej
httpd = socketserver.TCPServer(("", PORT), Handler)

print("serving at port", PORT)
httpd.serve_forever()