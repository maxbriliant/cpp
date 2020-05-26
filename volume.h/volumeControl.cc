#include <iostream>
#include <pulse/pulseaudio.h>
#include <pulse/volume.h>


using namespace std;

int main() 
{ 
    pa_volume_t *volume;
    pa_cvolume *cvolume;

    pa_volume_t first  = PA_VOLUME_NORM;
    first = first/4;

    pa_cvolume_set(cvolume, 10000 ,first);
    cout << "Volume: "<< first << endl;
    first != 0 ? cout << "Existing" << endl : cout << "Not Reached" << endl; 

    //cvolume->pa_cvolume_init(volume->,&cvolume);


    return 0;
}
