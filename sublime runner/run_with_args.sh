#!/bin/bash

# Absoluter Pfad zur .out-Datei
OUT="$(realpath "$(dirname "$1")/.out")"

# Wenn die Datei nicht existiert, Fehlermeldung
if [[ ! -f "$OUT" ]]; then
    echo "❌ Kompilat nicht gefunden: $OUT"
    exit 1
fi

# Starten einer interaktiven Bash-Shell, um die Eingabeaufforderung zu ermöglichen
echo -n "▶ Eingabe der Argumente (leer = keine): "
read args

# Debugging-Ausgabe: Zeigt, was der Benutzer eingegeben hat
echo "Debugging: Eingabe des Benutzers - '$args'"

# Wenn keine Eingabe gemacht wurde, setze args auf leer
if [[ -z "$args" ]]; then
    args=""
fi

# Ausgabe zur Überprüfung
echo -e "\n🚀 Starte: $OUT $args"
echo "============================"

# Startet das Programm
"$OUT" $args

# Prüft den Exit-Status des Programms
if [[ $? -ne 0 ]]; then
    echo "❌ Fehler beim Ausführen des Programms!"
else
    echo "✅ Programmausführung erfolgreich!"
fi