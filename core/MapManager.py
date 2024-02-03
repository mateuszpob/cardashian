
import sqlite3
from io import BytesIO
from PIL import Image, UnidentifiedImageError


class MapManager():
    def __init__(self, mock=False):
        self.emptyTile = '/home/mp/workspace/home/navi/nocny/mapserver/empty.png'
        self.mbtilesDBFile = '/home/mp/workspace/home/navi/nocny/mapserver/wawabi.mbtiles'
        self.connection = sqlite3.connect(self.mbtilesDBFile, check_same_thread=False)
        self.cursor = self.connection.cursor()
    
    def __del__(self):
        # Zamykamy połączenie przy zniszczeniu obiektu
        self.connection.close()

    def getTile(self, zoom_level, tile_column, tile_row):
        # Otwórz połączenie z bazą MBTiles
        

        try:
            # Wybierz kafelek na podstawie podanych parametrów
            query = "SELECT tile_data FROM tiles WHERE zoom_level=? AND tile_column=? AND tile_row=? ORDER BY zoom_level, tile_row, tile_column"

            # Dostosuj numerację kafelków do odwrotnej kolejności
            adjusted_tile_row = (2 ** zoom_level) - tile_row - 1

            self.cursor.execute(query, (zoom_level, tile_column, adjusted_tile_row))
            result = self.cursor.fetchone()

            if result:
                # Jeśli dane są dostępne, przekształć je do obrazu (załóżmy, że są w formacie PNG)
                tile_data = result[0]
                return tile_data
                # image = Image.open(BytesIO(tile_data))

                # # Zapisz obrazek w pamięci i skonwertuj go na BytesIO
                # img_buffer = BytesIO()
                # image.save(img_buffer, format="PNG")
                # img_buffer.seek(0)

                # return send_file(img_buffer, mimetype='image/png')
            else:
                print('---- No Data ----')
                return None

        except UnidentifiedImageError as e:
            return f"Error loading image: {e}"

        finally:
            # Zamknij połączenie z bazą danych
            pass

        return None # send_file(image_path, mimetype='image/jpeg')

    def stop(self):
        self.connection.close()