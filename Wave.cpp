// Finite differences numerical method solution to wave equation
// Cable fixed at both ends, initially at rest
// and displaced to position f(x) = sin(pi*x)

#include <iostream>
#include <iomanip>
#include <math.h>

#define PI 3.14159265

int main()
{
	using std::cout;
    using std::setprecision;
    using std::fixed;

    // Step sizes
    float dx = 0.25;
    float dt = 0.1;

    // Length
    float x = 1;
    // Time period
    float t = 0.4;

    // Mesh dimensions
    int height = x/dx + 1;
    int width = t/dt + 1;

    // Create mesh for numerical solution
    float numerical[height][width];

    for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			numerical[i][j] = 0;
		}
	}

    // Calculate values of first row using the boundary condition about
    // the initial displacement at time t = 0 to position f(x)=sin(pi*x)

    for (int n = 1; n < width-1; n++)
    {
        numerical[0][n] = sin( PI * dx * n );
    }

    // Calculate values for next row

    for (int n = 1; n < width-1; n++)
    {
        numerical[1][n] =  numerical[0][n] + ( pow(dt,2) / ( 2 * pow(dx,2) ) ) * ( numerical[0][n - 1] - 2 * numerical[0][n] + numerical[0][n + 1] ); 
    }

    // Calculate values for all other rows

    for (int o = 2; o < height; o++)
    {
        for (int n = 1; n < width-1; n++)
        {
            numerical[o][n] = 2 * numerical[o - 1][n] - numerical[o - 2][n] + ( pow(dt,2) / pow(dx,2) ) * ( numerical[o - 1][n - 1] - 2 * numerical[o - 1][n] + numerical[o - 1][n + 1] );
        }
    }

    // Print

    cout<<"\nNumerical solution:\n\n";

    for (int i = 0; i < height; i++)
	{
        cout<<"\tt = "<<fixed<<setprecision(4)<<i*dt;
		for (int j = 0; j < width; j++)
		{
			cout<<"\t\t"<<fixed<<setprecision(4)<<numerical[i][j];
		}
		cout<<"\n";
	}

    cout<<"\n\t\t\t";
    for (int j = 0; j < width; j++)
    {
        cout<<"\tx = "<<fixed<<setprecision(2)<<j*dx;
    }
    cout<<"\n\n";

    // Create mesh for exact solution

    float exact[height][width];

    for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			exact[i][j] = 0;
		}
	}

    // Fill in mesh with exact solutions

    for (int o = 0; o < height; o++)
    {
        for (int n = 0; n < width; n++)
        {
            exact[o][n] = sin( PI * dx * n ) * cos( PI * dt * o);
        }
    }

    // Print

    cout<<"\nExact solution:\n\n";

    for (int i = 0; i < height; i++)
	{
        cout<<"\tt = "<<fixed<<setprecision(4)<<i*dt;
		for (int j = 0; j < width; j++)
		{
			cout<<"\t\t"<<fixed<<setprecision(4)<<exact[i][j];
		}
		cout<<"\n";
	}

    cout<<"\n\t\t\t";
    for (int j = 0; j < width; j++)
    {
        cout<<"\tx = "<<fixed<<setprecision(2)<<j*dx;
    }
    cout<<"\n\n";

    return 0;
}