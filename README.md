# Snake Game Repository Description for GitHub

## Snake Game

### Overview
Welcome to the **Snake Game** repository! This project is a classic Snake game implemented in **C** for the **DE1-SoC board**. The game features three levels of increasing difficulty, where players control a snake to eat fruits while avoiding collisions with walls or the snake's own body. The ultimate goal is to achieve the highest possible score while navigating through progressively challenging levels.

---

### Features
- **Three Levels of Difficulty**:
  - **Level 1**: Basic layout with minimal obstacles. Progress to the next level by scoring 50 points.
  - **Level 2**: Moderate layout with increased obstacles. Unlock Level 3 by scoring 100 points.
  - **Level 3**: Advanced layout with intricate barriers and faster gameplay. Survive as long as possible!
- **User Controls**: 
  - Arrow keys (Up, Down, Left, Right) to control the snake.
- **Score Display**: Real-time score displayed on the screen.
- **Game Over Detection**: Ends when the snake collides with walls or itself, displaying the final score.

---

### Requirements
#### Hardware
- **DE1-SoC Board**
- **VGA Display**

#### Software
- **Quartus Prime**: For compiling and uploading to the DE1-SoC.
- **ARM DS-5**: For programming the HPS side of the DE1-SoC.

---

### Game Instructions
#### Controls
- **Up**: 0  
- **Left**: 1  
- **Right**: 2  
- **Down**: 3  

#### Level Progression
1. **Level 1**:  
   - Start with a minimal-length snake in an empty grid.  
   - Reach a score of 50 to unlock Level 2.  
2. **Level 2**:  
   - Navigate through a more complex environment with additional obstacles.  
   - Score 100 to progress to Level 3.  
3. **Level 3**:  
   - Face the most challenging layout and obstacles.  
   - Survive as long as possible and achieve the highest score!

#### Game Over
- The game ends when the snake collides with the wall or itself.
- The final score is displayed on the screen.

---

### Credits
This project was developed by **Krishna Purwar** as a demonstration of programming and hardware interfacing skills.  

Feel free to explore, contribute, or use this project as a learning resource! 🎮
