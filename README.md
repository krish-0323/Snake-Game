# Snake-Game
\
**Overview** <br /> <br />
This is a classic Snake game programmed in C, designed to run on the DE1-SoC board. The game features three levels of increasing difficulty, with each level increasing the number of potential collisions. The aim of the game is to control the snake to eat as many fruits as possible without running into the walls or itself.<br />

**User Controls**: Use the arrow keys to control the direction of the snake. <br />
**Score Display**: The current score is displayed on the screen. <br />
**Game Over Detection**: The game ends when the snake collides with the wall or itself. <br />

**Getting Started** <br />

**Hardware Requirements** <br />
1. DE1-SoC Board <br />
2. VGA display (for output) <br />

**Software Requirements** <br />
1. Quartus Prime (for compiling and uploading to DE1-SoC) <br />
2. ARM DS-5 (for programming the HPS side of the DE1-SoC) <br />

**Game Instructions** <br />

**Controls** <br />
 
 ● Up:0 <br />
 ● Left: 1 <br />
 ● Right: 2 <br />
 ● Down:3 <br />

**Level Progression:** <br />
 
 **1. Level 1:** <br />
 **● Objective**: Survive and accumulate points by consuming food items. <br />
 **● Initial State**: The player starts with a snake of minimal length in an empty grid. <br />
 **● Goal**:Reach ascore of 50 points to progress to the next level. <br />
 **● Difficulty**: Basic obstacles and simple layout. <br />
 
 **2. Level 2:** <br />
 **● Objective**: Continue navigating the snake through an increasingly complex environment. <br />
 **● Starting Condition**: Upon reaching a score of 50, the game advances automatically to Level 2. <br />
 **● Challenges**: The number of barriers and obstacles increases, requiring more strategic maneuvering. <br />
 **● Goal**:Cross a score of 100 to unlock the final level. <br />
 **● Difficulty**: Moderate, with tighter spaces and more obstacles to navigate around. <br />
 
 **3. Level 3:**  <br />
 **● Objective**: Conquer the most difficult stage of the game. <br />
 **● UnlockCondition**: Achieve a score of 100 to unlock Level 3. <br />
 **● Challenge**: Introduces the most complex layout and obstacles, testing the player's agility and decision-making skills.<br />
 **● Final Goal**: There's no specific score target; the player aims to survive as long as possible and achieve the highest score. <br />
 **● Difficulty**: Advanced, with intricate barriers and fast-paced gameplay. <br />

**Game Over** <br />

The game will end if the snake collides with the wall or itself. <br />
The final score will be displayed on the screen. <br />

**Credits** <br />

Developed by **Krishna Purwar**. <br />
