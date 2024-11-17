""" Module providing Main Menu. """

from src.menu import SelectionMenu
from src.hanoi_menu import HanoiMenu

# Constants
SCREEN_SIZE = (1000, 500)
OPTIONS = ["Exit", "Hanoi", "Pacman", "Robery"]
TITLE = "Game Menu"

class MainMenu(SelectionMenu):
    """ Main Menu. """

    def __init__(self):
        super().__init__(SCREEN_SIZE, OPTIONS, TITLE)

    def select_option(self):
        """ Function to select option in menu. """
        option = self.options[self.selected_option]

        match option:
            case "Exit":
                self.running = False
            case "Hanoi":
                self.running_option = HanoiMenu(self.show)
            case "Pacman":
                self.running_option = PacmanMenu()
            case "Robery":
                self.running_option = RoberyMenu()

def main() -> None:
    """ fofoca."""
    menu = MainMenu()
    menu.show()

if __name__ == "__main__":
    main()
