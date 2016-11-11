#include "Frame.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace FITGLE_NS;

Frame::Frame(int n, char* fileName)
{
    trajectory = fopen(fileName, "r");
    numParticles = n;
    positions.resize(numParticles);
    residualForces.resize(numParticles);
    velocities.resize(numParticles);
    for (int i=0; i<numParticles; i++)
    {
      positions[i].resize(3);
      residualForces[i].resize(3);
      velocities[i].resize(3);
    }
}

Frame::~Frame()
{
    fclose(trajectory);
    printf("cleaning up Frame Information\n");
}

void Frame::readFrame()
{
    ssize_t read;
    size_t len;
    char*  line;
    int    lineID;
    for (int iline = 0; iline < numParticles+9; iline++)
    {
        read = getline(&line, &len, trajectory);
        if (iline >= 9)
        {
           char* pch = strtok(line, " \t");
           int atomID = atoi(pch);
           pch = strtok(NULL, " \t");
           int type = atoi(pch);
           pch = strtok(NULL, " \t");
           double atomMass = atof(pch);
           pch = strtok(NULL, " \t");
           positions[atomID][0] = atof(pch);
           pch = strtok(NULL, " \t");
           positions[atomID][1] = atof(pch);
           pch = strtok(NULL, " \t");
           positions[atomID][2] = atof(pch);
           pch = strtok(NULL, " \t");
           velocities[atomID][0] = atof(pch);
           pch = strtok(NULL, " \t");
           velocities[atomID][1] = atof(pch);
           pch = strtok(NULL, " \t");
           velocities[atomID][2] = atof(pch);
           pch = strtok(NULL, " \t");
           residualForces[atomID][0] = atof(pch);
           pch = strtok(NULL, " \t");
           residualForces[atomID][1] = atof(pch);
           pch = strtok(NULL, " \t");
           residualForces[atomID][2] = atof(pch);
        }
    } 
}
