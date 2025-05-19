#include <cstddef>
#include <ios>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <string>


using namespace std;


int main (){

    //std::cout << _POSIX_VERSION << std::endl;

    pid_t process = fork();

    if (process < 0) {
        cerr << "Fehler bei Prozesserstellung" << strerror(errno) << endl;
        return 1;   
    }

    if (process == 0) {
        cout << "Ich bin der Child-Prozess mit PID: " << getpid() << endl;

        const char *sh1 = "ls";
        const char *arg1 = "-l";
        const char *arg2 = "/home/mx";
        
        execlp(sh1, sh1, arg1, arg2, NULL);

        cerr << "Ausführung von execlp() mit \"ls -l ~\" Fehlgeschlagen" << strerror(errno) << endl;
        return 1;
    }

    else {
        cout << "Ich bin der Parent-Prozess mit PID: " << getpid() << endl << "Und mein Kind hat die PID " << process << endl;       
    }


    const char *filename = "test.txt";
    int fd = open(filename, O_WRONLY | O_CREAT, 0644); // Erstellt Datei
    if (fd == -1) {
        cerr << "Fehler beim Öffnen der Datei: " << strerror(errno) << endl;
        return 1;
    }

    const char *text = "Das schrieb ich in die Datei!";
    ssize_t bytes_written = write(fd, text, strlen(text));

    if (bytes_written == -1) {
        cerr << "Fehler beim Schreiben: " << strerror(errno) << endl;
        close(fd);
        return 1;
    }

    cout << "Erfolgreich in die Dateie test.txt geschrieben" << endl;

    close(fd);

    wait(NULL); // Warten auf den Kind Prozess

    ofstream file("test.txt",ios_base::app);
    if (file.is_open()){
        file << "\nBeginnen wir mit einer Neuen Zeile" << endl;
        file.close();
    }
    return 0;
}



