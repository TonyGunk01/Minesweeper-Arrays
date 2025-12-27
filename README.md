# Minesweeper-Arrays

This is a minesweeper game made in Visual Studio C++ using SFML.

I used 2D arrays to store the cell positions and then rendered each row with its unique position and filled the board. Then I had to randomize the mines positions on the board. After that, I use the mine position to populate the rest of the empty cells with values which would indicate the number of mines surrounding it. The remaining cells would be blank.

Using event managers, I managed to capture left clicks to clear out the cell and right clicks to flag it based on its state (whether hidden or revealed). I also added logic to open neighbouring cells except for the ones which have mines.

Then I created a simple UI for play and quitting the game.

[Click for video demo:](https://youtu.be/Pz1ZVUq9h3Q)
