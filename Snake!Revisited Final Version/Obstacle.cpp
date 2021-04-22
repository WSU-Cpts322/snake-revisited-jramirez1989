#include "Obstacle.h"

Obstacle::Obstacle()
{
    locations.push_back(Coordinates(10, 10));
    locations.push_back(Coordinates(11, 10));
    locations.push_back(Coordinates(12, 10));
}
/*x changes the x position on the map
 *y changes the y position on the map
 *xSize changes the size of the line created in x-direction
 *ySize changes the size of the line created in the y-direction
 *Changes in one x effects the other, both need to be changed
  in equal amounts */
  
Obstacle::Obstacle(string type, int x, int y, int xSize, int ySize)
{
    if (type == "Horizontal Line")
    {
        for (int i = x; i < x + xSize; i++)
        {
            locations.push_back(Coordinates(i, y));
        }
    }
    else if (type == "Vertical Line")
    {
        for (int i = y; i < y + ySize; i ++)
        {
            locations.push_back(Coordinates(x, i));
        }
    }
    else if (type == "Cross")
    {

        for (int i = y; i < y + ySize; i++)
        {
            locations.push_back(Coordinates(x + xSize, i - ySize));
        }
        for (int i = x; i < x + xSize; i++)
        {
            locations.push_back(Coordinates(i + xSize, y));
        }
    }
    else if (type == "Top-left L")
    {
        for (int i = y; i < y + ySize; i++)
        {
            //Vertical part
            locations.push_back(Coordinates(x, i - ySize));
        }
        for (int i = x; i < x + xSize; i++)
        {
            locations.push_back(Coordinates(i, y - ySize));
        }    
    }
    else if (type == "Top-right L")
    {
        for (int i = y; i < y + ySize; i++)
        {
            
            locations.push_back(Coordinates(x, i - ySize));
        }
        for (int i = x; i > x - xSize; i--)
        {
            locations.push_back(Coordinates(i, y - ySize));
        } 
    }
    else if (type == "Bottom-left L")
    {
        for (int i = y; i < y + ySize; i++)
        {
            //Vertical part
            locations.push_back(Coordinates(x, i - ySize));
        }
        for (int i = x; i < x + xSize; i++)
        {
            locations.push_back(Coordinates(i, y));
        }    
    }
    else if (type == "Bottom-right L")
    {
        for (int i = y; i < y + ySize; i++)
        {
            
            locations.push_back(Coordinates(x, i - ySize));
        }
        for (int i = x; i > x - xSize; i--)
        {
            locations.push_back(Coordinates(i, y));
        }        
    }
}
 vector<Coordinates> Obstacle::getLocations()
 {
     return locations;
 }