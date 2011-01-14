#include "sound.h"
#include "record.h"
#include <iostream>
#include <cstdio>


using namespace std;

/* This is the file that tests different parts of
 * the audio functionality.
 *
 */
int main(int argc, char** argv)
{
    /* Initialise ALUT. This needs to be called before
     * anything will work.
     */
    if (!alutInit(&argc, argv)) {
	 checkError();
	 return -1;
    }

    /* Check for correct usage. */
    if (argc !=  3) {
        cerr << "usage: soundtest <fileName> <play|loop|record>" << endl;
        cerr << "Note that the <fileName> with \'record\' doesn't matter" 
	     << endl;
	alutExit();
        return -1;
    }
    
    cout << argv[2] << endl;
    if(strcmp(argv[2],"play") == 0) {
	 playFile(argv[1]);
    } else if (strcmp(argv[2],"loop") == 0) {
	 playLoop(argv[1], 10); //Plays a 10 second loop
    } else if (strcmp(argv[2],"record") == 0) {
	 capturePlay();
    }
    
    checkError();

    return 0;
}
