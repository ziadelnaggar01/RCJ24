#define MAX_RECORDS 999 // Define the maximum number of steps recorded
#define map_size 25 // Determine map size
#define starting_tile 12 // Determine coordinates of starting tile

struct Tile 
{
  int NOV = 0; // Number of visits for the tile, initialized to 0
  bool victim = false; // Victim status in the tile, initialized to false

  // Method that increments number of visits for a tile
  void visited() 
  {
    NOV++;
  }

  // Method that flags the tile if a victim is found
  void found_victim() 
  {
    victim = true;
  }

  // Method that returns number of visits for a tile
  int get_visits() 
  {
    return NOV;
  }

  // Method that returns whether a victim was found in this tile or not
  bool get_victim() 
  {
    return victim;
  }
};


struct Position 
{
  int x; // X-Coordinate of each position object
  int y; // Y-Coordinate of each position object
  char Direction; // Direction of each position object

  // Method that sets coordinates of position object
  void set_position(int x_new, int y_new) 
  {
    x = x_new;
    y = y_new;
  }

  // Method that increments coordinates of position object by given values
  void update_position(int dx, int dy) 
  {
    x += dx;
    y += dy;
  }

  // Method that sets the direction of position object
  void set_direction(char direction_new) 
  {
    Direction = direction_new;
  }

  // Method that returns the X-Coordinate of position object
  int get_x() 
  {
    return x;
  }

  // Method that returns the Y-Coordinate of position object
  int get_y() 
  {
    return y;
  }

  // Method that returns the current direction of position object
  char get_direction() 
  {
    return Direction;
  }
};


Tile Map[map_size][map_size]; // Assuming a 25x25 map
Position current_position; // Create a variable of type position for current position
Position last_checkpoint; // Create a variable of type position for last checkpoint position
char Record[MAX_RECORDS]; // Assuming a maximum of 999 steps
int checkpoint_index = 0; // pointer that points to index of latest checkpoint in record array
int New_Record_ptr = 1; // pointer that points to the index where a new element is added in record array


void lop() 
{
  // Update the current position of robot to coordinates of latest checkpoint
  current_position.set_position(last_checkpoint.get_x(), last_checkpoint.get_y());
  current_position.set_direction(last_checkpoint.get_direction());

  // Remove all the steps that occurred after leaving the latest checkpoint
  New_Record_ptr = checkpoint_index + 1;
}


void print_map() 
{
  for (int i = 0; i < map_size; i++) 
  {
    for (int j = 0; j < map_size; j++) 
    {
      Serial.print(Map[j][i].get_visits());
      Serial.print(" ");
    }
    Serial.println();
  }
  // Print current position
  Serial.print(current_position.get_x());
  Serial.print(" ");
  Serial.print(current_position.get_y());
  Serial.print(" ");
  Serial.println(current_position.get_direction());
}


void back_to_base() 
{
  // get index of last step recorded
  int i = New_Record_ptr - 1;

  // loop until you have re-traced all steps made
  while (i > 0) 
  {
    // check for the direction as robot entered current tile and reverse that direction
    char direction;
    switch (Record[i]) {
      case 'N':
        direction = 'S';
        break;
      case 'S':
        direction = 'N';
        break;
      case 'E':
        direction = 'W';
        break;
      case 'W':
        direction = 'E';
        break;
    }

    // rotate robot until it meets the reversed direction
    while (direction != current_position.get_direction()) 
    {
      // rotate(90); // You'll need to implement this function
    }

    // move a tile forward
    // move_forward(); // You'll need to implement this function

    // move to next step
    i--;
  }

  // print map after returning [if coordinates are (6, 6)] then robot returned successfully
  Serial.println("Returning path:");
  print_map();
}


void setup() 
{
  // Initialize global Record array with the starting tile
  Record[0] = 'N';

  // Set current position to middle of the map, and direction north
  current_position.set_position(starting_tile, starting_tile);
  current_position.set_direction('N');

  // Set position of the last checkpoint to starting tile
  last_checkpoint.set_position(starting_tile, starting_tile);
  last_checkpoint.set_direction('N');

  // Set the starting tile as visited
  Map[starting_tile][starting_tile].visited();
}


void loop() 
{
  // Your loop code here
}
