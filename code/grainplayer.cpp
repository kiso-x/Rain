

#include "grainplayer.h"

GrainPlayer::GrainPlayer(std::string filePath, int fs, int ident)
{

    cout << "Creating GrainPlayer with " << win_size << " samples window size! " << endl;

    nWindows = 500;
    looplength = fs;
    loopstyle = 0;
    id = ident;
    // windowlength ergibt sich aus loop länge und nwindows

    sample   = new SingleSample(filePath, fs);

    windows  = new TriangularWindow[nWindows];

    for(int i=0; i<nWindows; i++)
    {
        windows[i].initialize(win_size,i* (win_size/nWindows),i* (win_size/nWindows));
    }

}



double GrainPlayer::get_sample()
{

    double output = 0;

    // loop over all windows
    for(int windowCNT=0; windowCNT<nWindows; windowCNT++)
    {

        // get gain of this window
        double tmpGain = windows[windowCNT].get_value();
        // get the relative position of this window
        int tmpPos     = windows[windowCNT].get_relative_position();



        // only if we are within the sample boundaries
        if(tmpPos >= 0 && tmpPos <= sample->get_nFrames())
        {
            // add grain value to output
            output += tmpGain * sample->get_sample(0,tmpPos);
        }

        // if this grain (window) has reached its end
        if(windows[windowCNT].step()==1)
        {
           // move this grain (window) position
           windows[windowCNT].increment_relative_position(relative_stepsize,sample->get_nFrames());
        }
    }

    return output;

}


void GrainPlayer::set_relative_distance(double r)
{
    relative_stepsize = r;
}


