#!/bin/bash

# Sprawdzenie, czy skrypt jest uruchamiany z odpowiednią liczbą argumentów
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <SSID> <PASSWORD>"
    exit 1
fi

SSID="$1"
PASSWORD="$2"
WPA_CONF="/etc/wpa_supplicant/wpa_supplicant.conf"

# Tworzenie kopii zapasowej pliku konfiguracyjnego
BACKUP_FILE="${WPA_CONF}.bak"
cp "$WPA_CONF" "$BACKUP_FILE"

# Dodanie wpisu do pliku konfiguracyjnego
cat >> "$WPA_CONF" <<EOL

network={
    ssid="$SSID"
    psk="$PASSWORD"
    key_mgmt=WPA-PSK
}
EOL

# Sprawdzanie, czy wpis został pomyślnie dodany
if grep -q "ssid=\"$SSID\"" "$WPA_CONF"; then
    echo "Sieć $SSID została pomyślnie dodana do $WPA_CONF"
else
    echo "Wystąpił problem podczas dodawania sieci. Przywracanie kopii zapasowej..."
    mv "$BACKUP_FILE" "$WPA_CONF"
    exit 1
fi