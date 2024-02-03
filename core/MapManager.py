
import sqlite3
from io import BytesIO
from PIL import Image, UnidentifiedImageError


class MapManager():
    def __init__(self, mock=False):
        self.mbtilesDBFile = '/home/mp/workspace/home/navi/nocny/mapserver/wawabi.mbtiles'

    def __enter__(self):
        self.connection = sqlite3.connect(self.mbtilesDBFile, check_same_thread=False)
        self.cursor = self.connection.cursor()
        return self
    
    def __exit__(self, exc_type, exc_value, traceback):
        # Zamykamy połączenie przy zniszczeniu obiektu
        self.connection.close()

    def getTile(self, zoom_level, tile_column, tile_row):
        # Otwórz połączenie z bazą MBTiles
        
        with self:
            try:
                # Wybierz kafelek na podstawie podanych parametrów
                query = "SELECT tile_data FROM tiles WHERE zoom_level=? AND tile_column=? AND tile_row=? ORDER BY zoom_level, tile_row, tile_column"

                # Dostosuj numerację kafelków do odwrotnej kolejności
                adjusted_tile_row = (2 ** zoom_level) - tile_row - 1

                self.cursor.execute(query, (zoom_level, tile_column, adjusted_tile_row))
                result = self.cursor.fetchone()

                if result:
                    tile_data = result[0]
                    return tile_data
                else:
                    return None

            except UnidentifiedImageError as e:
                return f"Error loading image: {e}"

        return None
