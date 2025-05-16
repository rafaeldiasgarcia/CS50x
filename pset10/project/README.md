# Termo Clone CS50x

#### Video Demo: https://youtu.be/15LTGLhmdxE

#### Description:

**Introduction**

This project, developed as the final assignment for Harvard's CS50x course, is a Portuguese-language recreation of the popular word-guessing game "Wordle" (known as "Termo" in Brazil). The game's objective is straightforward: the player has six attempts to guess a secret five-letter word. With each guess, the game provides visual feedback indicating which letters are in the correct position, which are in the word but in the wrong position, and which are not part of the word at all.

The motivation behind this project was the interest in applying concepts learned during the CS50x course, especially web development with Python (Flask) and JavaScript, to create an interactive and enjoyable application. Termo/Wordle served as an excellent foundation due to its clear game mechanics and the opportunity to focus on aspects of programming logic, DOM manipulation, and interface design.

**Main Features**

*   **Random Secret Word:** With every new game (page reload), a new five-letter word is randomly selected from an extensive Portuguese dictionary.
*   **Guessing Grid:** A visual grid of 6 rows (attempts) by 5 columns (letters) for the player to input their guesses.
*   **Detailed Visual Feedback:**
    *   Letters in the **correct position** are highlighted in green.
    *   Letters **present in the word but in the wrong position** are highlighted in yellow.
    *   Letters **absent** from the word are highlighted in gray.
*   **Interactive Virtual Keyboard:**
    *   An on-screen keyboard allows for letter input.
    *   The keys on the virtual keyboard change color to reflect the status of a_already_tried letters, helping the player strategize their next guesses.
*   **Physical Keyboard Support:** The game also accepts input from the computer's physical keyboard.
*   **Attempt Limit:** The player has a maximum of 6 attempts to guess the word.
*   **User Messages:** Feedback on the game's state, such as "Word incomplete!", "Congratulations, you guessed it!" or "Game over! The word was: [WORD]".
*   **Animations:** Subtle animations to "flip" letters, indicate errors ("shake"), and celebrate victory ("dance"), enhancing the user experience.
*   **"Play Again" Button:** Allows for an easy game restart after a match ends.
*   **Responsive Design:** The interface adapts to different screen sizes, providing a good experience on desktops and mobile devices.
*   **Accessibility:** Respects the user's preference for reduced motion by disabling animations if configured in the operating system.

**Technologies Used**

*   **Backend:** Python with the Flask micro-framework.
*   **Frontend:** HTML5, CSS3, and JavaScript (Vanilla JS).
*   **Word Source:** A text file (`words.txt`) containing over 1000 five-letter Portuguese words.

**Project Structure and File Explanation**

The project is organized as follows:

*   `app.py`: The core of the application's backend. It uses Flask to:
    *   Load and process the list of valid words from `static/data/words.txt`.
    *   Randomly select the secret word for each game session.
    *   Render the main `index.html` page, injecting the secret word and the full list of valid words into the template for use by client-side JavaScript.
*   `static/data/words.txt`: A simple text file containing the list of five-letter Portuguese words that serve as the game's foundation.
*   `static/css/style.css`: Contains all styling rules for the user interface. This includes the overall layout, colors, typography, the design of the grid and keyboard, animations (flip, shake, dance), and media queries to ensure responsiveness across different devices.
*   `static/js/script.js`: Responsible for all client-side game logic. Its main functions are:
    *   Dynamically initializing the game grid and virtual keyboard.
    *   Capturing and processing user input (from both virtual and physical keyboards).
    *   Validating each guess by comparing it against the secret word.
    *   Updating the user interface with visual feedback (colors in grid cells and keyboard keys) based on the guess's outcome.
    *   Managing the game state: remaining attempts, win/loss conditions.
    *   Controlling user-displayed messages and animations.
    *   Implementing the "Play Again" functionality.
*   `templates/index.html`: The application's single HTML file. It defines the page structure, including the title, message area, containers for the game grid and keyboard, and the "Play Again" button. This is where data (secret word, word list) passed by Flask is received and made available to `script.js`.
*   `requirements.txt`: Lists the project's Python dependencies, which in this case is primarily Flask.

**Important Design Decisions**

*   **Primarily Client-Side Logic:** The decision to implement most of the game logic (including word verification) in client-side JavaScript was made to simplify development and create a more fluid and responsive user experience, without the need for constant server requests after the initial page load. For this academic project, advanced cheat prevention was not the primary focus, allowing for this more direct approach.
*   **Secret Word Generation:** The secret word is randomly chosen by the Flask server each time the main page is loaded, ensuring a new word for each game session.
*   **Feedback and Animations:** Animations (like the "flip" of letters when revealing results, the "shake" of a row for an invalid/incomplete word, and the "dance" of letters upon victory) were incorporated to make the interaction more dynamic, intuitive, and rewarding for the player.
*   **Guess Validation:** Although the full list of valid words is sent to the client, the current version of the game does not actively prevent the user from submitting letter combinations that do not form a real word from the list (e.g., "XXXXX"). Validation focuses on comparing the guess against the secret word.

**Challenges and Learnings**

During the development of this project, one of the main challenges was correctly implementing the feedback logic for letters, especially when dealing with repeated letters in both the secret word and the player's guess. Ensuring that a letter marked as "present" (yellow) was not counted doubly if there was already a correct instance (green) of the same letter required a careful approach to counting and status assignment.

Another aspect that demanded attention was responsive design and styling the virtual keyboard to work well on different screen sizes while maintaining usability. The integration between Flask (for serving initial data) and JavaScript (for controlling all game interactivity) was also a crucial learning point, reinforcing the understanding of how full-stack web applications, even simple ones, are structured.

**How to Run the Project**

1.  Clone this repository to your local machine.
2.  Ensure you have Python 3 and pip installed.
3.  (Recommended) Create and activate a Python virtual environment:
    ```bash
    python -m venv venv
    # On Windows:
    # venv\Scripts\activate
    # On macOS/Linux:
    # source venv/bin/activate
    ```
4.  Install the project dependencies:
    ```bash
    pip install -r requirements.txt
    ```
5.  Run the Flask server:
    ```bash
    python app.py
    ```
6.  Open your browser and navigate to `http://127.0.0.1:5000/`.

Enjoy the game!
