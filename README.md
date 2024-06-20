# Snake-Game\
\
**Overview**\
This is a classic Snake game programmed in C, designed to run on the DE1-SoC board. The game features three levels of increasing difficulty, with each level increasing the number of potential collisions. The aim of the game is to control the snake to eat as many fruits as possible without running into the walls or itself.\

**Features**\
Three Levels of Difficulty: As the game progresses, each level presents a higher difficulty with more obstacles and faster snake movement.\

**User Controls**: Use the arrow keys to control the direction of the snake.\
**Score Display**: The current score is displayed on the screen.\
**Game Over Detection**: The game ends when the snake collides with the wall or itself.

**Getting Started**

**Hardware Requirements**
1. DE1-SoC Board
2. VGA display (for output)

**Software Requirements**
1. Quartus Prime (for compiling and uploading to DE1-SoC)
2. ARM DS-5 (for programming the HPS side of the DE1-SoC)

**Game Instructions**

**Controls**
 ● Up:0
 ● Left: 1
 ● Right: 2
 ● Down:3

**Level Progression:**
 
 **1. Level 1:**
 **● Objective**: Survive and accumulate points by consuming food items.
 **● Initial State**: The player starts with a snake of minimal length in an empty
 grid.
 **● Goal**:Reach ascore of 50 points to progress to the next level.
 **● Difficulty**: Basic obstacles and simple layout.
 
 **2. Level 2:**
 **● Objective**: Continue navigating the snake through an increasingly complex
 environment.
 **● Starting Condition**: Upon reaching a score of 50, the game advances
 automatically to Level 2.
 **● Challenges**: The number of barriers and obstacles increases, requiring
 more strategic maneuvering.
 **● Goal**:Cross a score of 100 to unlock the final level.
 **● Difficulty**: Moderate, with tighter spaces and more obstacles to navigate
 around.
 
 3. Level 3:
 **● Objective**: Conquer the most difficult stage of the game.
 **● UnlockCondition**: Achieve a score of 100 to unlock Level 3.
 **● Challenge**: Introduces the most complex layout and obstacles, testing the
 player's agility and decision-making skills.
 **● Final Goal**: There's no specific score target; the player aims to survive as
 long as possible and achieve the highest score.
 **● Difficulty**: Advanced, with intricate barriers and fast-paced gameplay

**Game Over**
The game will end if the snake collides with the wall or itself.
The final score will be displayed on the screen.

**Credits**
Developed by **Krishna Purwar**.
