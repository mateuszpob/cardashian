class DynamicRouteWriter:
    def __init__(self, output_file_path="output.gpx"):
        self.output_file_path = output_file_path

    def start_gpx(self):
        with open(self.output_file_path, "w") as gpx_file:
            gpx_file.write("""<?xml version="1.0" encoding="UTF-8"?><gpx version="1.1" creator="YourAppName"><trk><trkseg>""")

    def add_coordinates(self, coordinates):
        with open(self.output_file_path, "a") as gpx_file:
            for lat, lon in coordinates:
                gpx_file.write(f"<trkpt lat=\"{lat}\" lon=\"{lon}\"></trkpt>\n")

    def end_gpx(self):
        with open(self.output_file_path, "a") as gpx_file:
            gpx_file.write("""</trkseg></trk></gpx>""")

    def append_data(self, coordinates):
        self.add_coordinates(coordinates)

    def rewind_to_start(self):
        with open(self.output_file_path, "rb+") as gpx_file:
            end_size = len("</trkseg></trk></gpx>")
            gpx_file.seek(-end_size, 2)
            file_content = gpx_file.read()
            gpx_file.seek(-end_size, 2)
            gpx_file.truncate()
            gpx_file.write(file_content)