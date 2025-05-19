#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <type_traits>
#include <sstream>
#include <iomanip>
#include <cmath>

// Ein universeller Typ-Handler mit if constexpr
// Demonstriert die elegante Handhabung verschiedener Typen

// Vor-Deklarationen für spezielle Typen
template<typename T>
struct is_container : std::false_type {};

template<typename T>
struct is_map : std::false_type {};

// Spezialisierung für std::vector
template<typename T, typename A>
struct is_container<std::vector<T, A>> : std::true_type {};

// Spezialisierung für std::map
template<typename K, typename V, typename... Args>
struct is_container<std::map<K, V, Args...>> : std::true_type {};

template<typename K, typename V, typename... Args>
struct is_map<std::map<K, V, Args...>> : std::true_type {};

// Helper-Variable für einfachere Syntax
template<typename T>
inline constexpr bool is_container_v = is_container<T>::value;

template<typename T>
inline constexpr bool is_map_v = is_map<T>::value;

// 1. Universeller Formatter mit Spezialisierungen zur Compile-Zeit
template<typename T>
class TypeFormatter {
public:
    static std::string format(const T& value) {
        // Hauptlogik mit if constexpr für Typverzweigungen
        if constexpr (std::is_same_v<T, std::string>) {
            // String-Spezialisierung
            return "\"" + value + "\"";
        }
        else if constexpr (std::is_arithmetic_v<T>) {
            // Arithmetische Typen (int, float, etc.)
            if constexpr (std::is_floating_point_v<T>) {
                // Float/Double-Präzisionsformatierung
                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << value;
                return ss.str();
            }
            else if constexpr (std::is_unsigned_v<T>) {
                // Unsigned-Werte mit Hinweis
                return std::to_string(value) + "u";
            }
            else {
                // Andere Zahlen einfach konvertieren
                return std::to_string(value);
            }
        }
        else if constexpr (is_container_v<T>) {
            // Container wie std::vector behandeln
            std::ostringstream result;
            
            if constexpr (is_map_v<T>) {
                // Spezialisierung für Map-Typen
                result << "{";
                bool first = true;
                for (const auto& [key, val] : value) {
                    if (!first) result << ", ";
                    result << TypeFormatter<decltype(key)>::format(key) << ": "
                           << TypeFormatter<decltype(val)>::format(val);
                    first = false;
                }
                result << "}";
            }
            else {
                // Andere Container (wie Vektoren)
                result << "[";
                bool first = true;
                for (const auto& item : value) {
                    if (!first) result << ", ";
                    result << TypeFormatter<decltype(item)>::format(item);
                    first = false;
                }
                result << "]";
            }
            return result.str();
        }
        else {
            // Fallback für unbekannte Typen
            return "<?>";
        }
    }
};

// 2. Datenanalyse-Funktion mit Typspezialisierungen
template<typename T>
class DataAnalyzer {
public:
    static std::string analyze(const T& data) {
        std::ostringstream result;
        result << "Analyse für " << TypeFormatter<T>::format(data) << ":\n";
        
        if constexpr (std::is_arithmetic_v<T>) {
            // Numerische Analyse
            result << "- Datentyp: " << (std::is_floating_point_v<T> ? "Fließkommazahl" : "Ganzzahl") << "\n";
            
            if constexpr (std::is_integral_v<T>) {
                // Ganzzahl-spezifische Analysen
                result << "- Binärdarstellung: ";
                T mask = T(1) << (sizeof(T) * 8 - 1);
                while (mask > 0) {
                    result << ((data & mask) ? '1' : '0');
                    mask >>= 1;
                }
                result << "\n";
                
                if constexpr (std::is_signed_v<T>) {
                    result << "- Vorzeichen: " << (data < 0 ? "negativ" : "positiv") << "\n";
                }
            }
            else if constexpr (std::is_floating_point_v<T>) {
                // Fließkomma-spezifische Analysen
                result << "- Gerundet: " << std::round(data) << "\n";
                result << "- Nachkommastellen: " << (data - std::floor(data)) << "\n";
            }
            
            // Mathematische Operationen basierend auf Datentyp
            if constexpr (std::is_signed_v<T> || std::is_floating_point_v<T>) {
                result << "- Quadratwurzel: ";
                if (data >= 0) {
                    result << std::sqrt(static_cast<double>(data)) << "\n";
                } else {
                    result << "nicht reell definiert\n";
                }
            }
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            // String-spezifische Analyse
            result << "- Länge: " << data.length() << " Zeichen\n";
            result << "- Leerzeichen: " << std::count(data.begin(), data.end(), ' ') << "\n";
            
            // Einfache statistische Analyse
            int uppercase = 0, lowercase = 0, digits = 0, other = 0;
            for (char c : data) {
                if (std::isupper(c)) uppercase++;
                else if (std::islower(c)) lowercase++;
                else if (std::isdigit(c)) digits++;
                else other++;
            }
            
            result << "- Großbuchstaben: " << uppercase << "\n";
            result << "- Kleinbuchstaben: " << lowercase << "\n";
            result << "- Ziffern: " << digits << "\n";
            result << "- Sonstige: " << other << "\n";
        }
        else if constexpr (is_container_v<T>) {
            // Container-spezifische Analyse
            result << "- Typ: " << (is_map_v<T> ? "Schlüssel-Wert-Sammlung" : "Sequenzielle Sammlung") << "\n";
            result << "- Elementanzahl: " << data.size() << "\n";
            
            if constexpr (!is_map_v<T> && !data.empty() && std::is_arithmetic_v<typename T::value_type>) {
                // Numerische Analyse für Container mit Zahlen
                typename T::value_type sum = 0;
                for (const auto& item : data) {
                    sum += item;
                }
                
                double average = static_cast<double>(sum) / data.size();
                result << "- Summe: " << sum << "\n";
                result << "- Durchschnitt: " << average << "\n";
                
                // Min/Max-Werte
                auto [min_it, max_it] = std::minmax_element(data.begin(), data.end());
                result << "- Minimum: " << *min_it << "\n";
                result << "- Maximum: " << *max_it << "\n";
            }
        }
        
        return result.str();
    }
};

// 3. Ein praktisches Beispiel: Konfigurierbares, typsicheres Debugging-Tool
template<typename T>
void debug_print(const std::string& name, const T& value) {
    std::cout << "DEBUG: " << name << " = ";
    
    if constexpr (std::is_pointer_v<T>) {
        // Spezielle Behandlung von Zeigern
        if (value == nullptr) {
            std::cout << "nullptr";
        } else {
            std::cout << "Ptr(" << static_cast<const void*>(value) << ")";
        }
    }
    else if constexpr (std::is_same_v<T, bool>) {
        // Boolean-Werte als true/false
        std::cout << (value ? "true" : "false");
    }
    else {
        // Andere Typen mit unserem Formatter
        std::cout << TypeFormatter<T>::format(value);
    }
    
    std::cout << std::endl;
}

// Beispiel mit tieferer Analyse
template<typename T>
void deep_inspect(const std::string& name, const T& value) {
    std::cout << "===== TIEFENINSPEKTION: " << name << " =====\n";
    std::cout << DataAnalyzer<T>::analyze(value);
    std::cout << "==============================\n";
}

// Hauptprogramm zum Testen verschiedener Typen
int main() {
    // Verschiedene Typen zum Testen
    int number = -42;
    unsigned int positive = 123;
    double pi = 3.14159265359;
    std::string text = "Hello C++17 World!";
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::map<std::string, int> ages = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    // Debug-Ausgabe demonstrieren
    debug_print("number", number);
    debug_print("positive", positive);
    debug_print("pi", pi);
    debug_print("text", text);
    debug_print("numbers", numbers);
    debug_print("ages", ages);
    
    // Tiefere Analyse demonstrieren
    std::cout << "\n";
    deep_inspect("number", number);
    deep_inspect("pi", pi);
    deep_inspect("text", text);
    deep_inspect("numbers", numbers);
    
    return 0;
}